#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pmkList.h"
#include "pmk_i.h"
#include "pwsGrm.h"

typedef struct sortinfo {	/* Sorting structure */
    int key;
    int index;
} sortinfo;

static int *newprod;		/* New production no (map) */
int max_sym_len;		/* Max symbol length in vocabulary */
int *newsym;			/* New symbol no (map). newsym should'nt be */
                /* deallocated since references in syntax */
                /* tree nodes are not updated. */

static sortinfo *sortvec;	/* Sort vector. */


static sortinfo *sortvecAlloc(vec_size)
int vec_size;
{
    sortinfo *temp;

    temp = (sortinfo *)calloc(vec_size, sizeof(sortinfo));
    if (temp == NULL) {
        /* Refactor all these "out of memory" errors to a PANIC() */
        pmkLog(NULL, 213, sevFAT, "");
        return NULL;
    } else return(temp);
}/*sortvecAlloc()*/


static int *int_vecAlloc(vec_size)
int vec_size;
{
    int *temp;

    temp = (int *)calloc(vec_size, sizeof(int));
    if (temp == NULL) {
        pmkLog(NULL, 213, sevFAT, "");
        return NULL;
    } else return(temp);
}/*int_vecAlloc()*/


#define VOC 1
#define PROD 0
/*-----------------------------------------------------------------------------
 * gram_sort - Sorts vocabulary or productions
 *-----------------------------------------------------------------------------
 */
static void gram_sort(spos, epos, typ)
int spos;			/* IN start position */
int epos;			/* IN end position */
Boolean typ;			/* IN array to sort */
{
    /* Quicksort
     */
    int top, bot;
    sortinfo z, tmp;
    sym_ref vtmp;
    prod_rec *ptmp;

    top = spos;
    bot = epos;
    z = sortvec[(top + bot) / 2];

    do {
    while (sortvec[top].key < z.key) top++;
    while (sortvec[bot].key > z.key) bot--;
    if (top <= bot) {
        tmp = sortvec[top];
        sortvec[top] = sortvec[bot];
        sortvec[bot] = tmp;

        if (typ == VOC) {
        vtmp = vocabulary[top];
        vocabulary[top] = vocabulary[bot];
        vocabulary[bot] = vtmp;
        } else {
        ptmp = global_prod_tbl[top];
        global_prod_tbl[top] = global_prod_tbl[bot];
        global_prod_tbl[bot] = ptmp;
        }/*if*/

        top++;
        bot--;
    }/*if*/
    } while (top <= bot);

    if (spos < bot) gram_sort(spos, bot, typ);
    if (epos > top) gram_sort(top, epos, typ);
}/*gram_sort()*/


/*-----------------------------------------------------------------------------
 * order_voc - Sort and order the vocabulary symbols
 *-----------------------------------------------------------------------------
 *        Find goal symbol and count symbols
 *
 *        Sort on:   1) Terminal/Nonterminal/Attribute
 *			 2) Terminals
 *				- Code value
 *                          - of symbol length
 *              Others
 *                      - Length of symbol
 *			 3) Original order of occurence
 *-----------------------------------------------------------------------------
 */
static void order_voc()
{
    int i, j;
    SymSet red_list;
    SymSet nored_list;
    SymSet sym_list;
    Boolean key_set;

    /* Resolve unknown symbols
     */
    for(i = 2; i <= vocCnt; i++) {
        if (vocabulary[i]->symbol_typ == unknown_symb) {
            /* Assume terminal symbol
             */
            vocabulary[i]->symbol_typ = t_symb;
            vocabulary[i]->syminfo.ter_info.icost = 1;
            vocabulary[i]->syminfo.ter_info.dcost = 1;
            vocabulary[i]->syminfo.ter_info.psymb = NULL;
        }/*if*/
    }/*for*/

    /* Find goal symbol and count all symbols
     */
    goal_sym = 0;
    termCnt = 1;
    nonTermCnt = 0;
    attrCnt = 0;
    max_sym_len = 0;
    for(i = 2; i <= vocCnt; i++) {
        if (strlen(vocabulary[i]->name) > max_sym_len) {
            max_sym_len = strlen(vocabulary[i]->name);
        }/*if*/

        switch (vocabulary[i]->symbol_typ) {

        case t_symb:
            if (!SymSetMem(on_right, i) && (vocabulary[i]->code != -1)) {
                pmkLog(NULL, 230, sevWAR, vocabulary[i]->name);
            }/*if*/
            if ((vocabulary[i]->code == -1) && term_sec_given &&
                (getSetOpt(LIST_OPT)>>5 & 1)) {
                pmkLog(NULL, 231, sevINF, vocabulary[i]->name);
            }/*if*/
            termCnt++;
            break;

        case nts_symb:
            if (!SymSetMem(on_right, i)) {
                if (goal_sym == 0) goal_sym = i;
                else {
                    /* Make error message string
                     */
                    char *temp;
                    temp =
                        (char *)calloc(strlen(vocabulary[goal_sym]->name) +
                                       strlen(vocabulary[i]->name) + 10,
                                       sizeof(char));
                    if (temp == NULL) pmkLog(NULL, 214, sevFAT, "");
                    else {
                        strcat(temp, vocabulary[i]->name);
                        strcat(temp, " ignored ");
                        strcat(temp, vocabulary[goal_sym]->name);
                        pmkLog(NULL, 232, sevWAR, temp);
                        free(temp);
                    }/*if*/
                }/*if*/
            }/*if*/
            nonTermCnt++;
            break;

        case attr_symb:
            attrCnt++;
            break;

        case unknown_symb:
            break;
        }/*switch*/

    }/*for*/

    gramSymCnt = nonTermCnt + termCnt;

    if (goal_sym == 0) {
        goal_sym = global_pvec_tbl[3];
        pmkLog(NULL, 233, sevWAR, vocabulary[goal_sym]->name);
    }/*if*/

    global_pvec_tbl[2] = goal_sym; /* Production 0 */

    /* Sort vocabulary
     */
    sortvec = sortvecAlloc(vocCnt + 1);
    sortvec[0].index = 0;
    sortvec[1].index = 1;

    for(i = 2; i <= vocCnt; i++) {
        /* Compute keys for all symbols
         */
        key_set = FALSE;

        switch (vocabulary[i]->symbol_typ) {

        case t_symb:
            if (vocabulary[i]->code != -1) {
                sortvec[i].key = vocabulary[i]->code;
                /* Terminal should not be sorted by its length
                 */
                key_set = TRUE;
            } else {
                sortvec[i].key = 1;
            }/*if*/
            break;

        case nts_symb:
            sortvec[i].key = 2;
            break;

        case attr_symb:
            if (vocabulary[i]->syminfo.attr_class == voc_attr) {
                sortvec[i].key = 3;
            } else if (vocabulary[i]->syminfo.attr_class == t_attr) {
                sortvec[i].key = 4;
            } else {
                sortvec[i].key = 5;
            }/*if*/
            break;

        case unknown_symb:
            break;
        }/*switch*/

        if (!key_set) {
            sortvec[i].key = sortvec[i].key * (max_sym_len + 1)  * sym_max +
                sym_max * strlen(vocabulary[i]->name) + i;
        }/*if*/
        sortvec[i].index = i;

    }/*for*/

    gram_sort(2, vocCnt, VOC);

    /* Give codes to all terminals
     */
    for(i = 1; i <= termCnt; i++) {
        if (vocabulary[i]->code == -1) vocabulary[i]->code = ++tc_val;
    }/*for*/

    /* Replace old references in "global_pvec_tbl" with new one
     */
    newsym = int_vecAlloc(vocCnt + 1);

    for(i = 0; i <= vocCnt; i++) newsym[sortvec[i].index] = i;
    for(i = 1; i <= global_pvec_ptr; i++) {
        global_pvec_tbl[i] = newsym[global_pvec_tbl[i]];
    }/*for*/
    goal_sym = newsym[goal_sym];

    /* Replace "modifiers" with updated symbols
     */
    for(i = 1; i <= global_prod_cnt; i++) {
        if (global_prod_tbl[i]->modify != NULL) {
            if (global_prod_tbl[i]->modify->red != NULL) {
                red_list = global_prod_tbl[i]->modify->red;
                global_prod_tbl[i]->modify->red = SymSetAlloc();
                for(j = 0; j <= vocCnt; j++) {
                    if (SymSetMem(red_list, j)) {
                        SymSetIns(global_prod_tbl[i]->modify->red, newsym[j]);
                    }/*if*/
                }/*for*/
                free(red_list);
            }/*if*/
            if (global_prod_tbl[i]->modify->nored != NULL) {
                nored_list = global_prod_tbl[i]->modify->nored;
                global_prod_tbl[i]->modify->nored = SymSetAlloc();
                for(j = 0; j <= vocCnt; j++) {
                    if (SymSetMem(nored_list, j)) {
                        SymSetIns(global_prod_tbl[i]->modify->nored,
                                  newsym[j]);
                    }/*if*/
                }/*for*/
                free(nored_list);
            }/*if*/
        }/*if*/
    }/*for*/

    free(sortvec);

    /* Replace error recovery data
     */
    if (recovery_spec.separators != NULL) {
        sym_list = recovery_spec.separators;
        recovery_spec.separators = SymSetAlloc();
        for(i = 0; i <= vocCnt; i++) {
            if (SymSetMem(sym_list, i)) {
                SymSetIns(recovery_spec.separators, newsym[i]);
            }/*if*/
        }/*for*/
        free(sym_list);
    }/*if*/

    if (recovery_spec.fiducials != NULL) {
        sym_list = recovery_spec.fiducials;
        recovery_spec.fiducials = SymSetAlloc();
        for(i = 0; i <= vocCnt; i++) {
            if (SymSetMem(sym_list, i)) {
                SymSetIns(recovery_spec.fiducials, newsym[i]);
            }/*if*/
        }/*for*/
        free(sym_list);
    }/*if*/

    if (recovery_spec.skips != NULL) {
        sym_list = recovery_spec.skips;
        recovery_spec.skips = SymSetAlloc();
        for(i = 0; i <= vocCnt; i++) {
            if (SymSetMem(sym_list, i)) {
                SymSetIns(recovery_spec.skips, newsym[i]);
            }/*if*/
        }/*for*/
        free(sym_list);
    }/*if*/
}/*order_voc()*/


/*-----------------------------------------------------------------------------
 * lcs - finds the Least-Cost production function
 *-----------------------------------------------------------------------------
 */
static void lcs(prod_cost, infinity)
int *prod_cost;
int *infinity;
{
    int *sym_cost;
    int p;			/* Production */
    int cost;			/* Current cost */
    int sym;			/* Symbol */
    int i;			/* Loop index */
    Boolean change;		/* Terminator */
    int temp;

    sym_cost = int_vecAlloc(vocCnt + 1);

    for(sym = 1; sym <= gramSymCnt; sym++) {
    if (sym <= termCnt) {
        sym_cost[sym] = vocabulary[sym]->syminfo.ter_info.icost;
    } else {
        sym_cost[sym] = *infinity;
    }/*if*/
    }/*for*/

    do {
    change = FALSE;
    for(p = 1; p <= global_prod_cnt; p++) {
        sym = global_pvec_tbl[global_prod_tbl[p]->start];
        cost = 0;
        temp = global_prod_tbl[p]->start + global_prod_tbl[p]->rssz;
        for(i = global_prod_tbl[p]->start + 1; i <= temp; i++) {
        cost = cost + sym_cost[global_pvec_tbl[i]];
        }/*for*/
        if (cost < sym_cost[sym]) {
        sym_cost[sym] = cost;
        change = TRUE;
        }/*if*/
        if (cost < prod_cost[p]) prod_cost[p] = cost;
    }/*for*/
    } while (change);
    free(sym_cost);
}/*lcs()*/


/*-----------------------------------------------------------------------------
 * order_prod - sorts and orders the transformed productions
 *-----------------------------------------------------------------------------
 *        sorts on: 1) Left hand side
 *			2) Least cost production
 *			3) Original order of occurence
 *-----------------------------------------------------------------------------
 */
static void order_prod()
{
    int *p_cost;
    int *nrleftsy;
    Boolean *done;
    int prod_2;
    int i, j, k;
    int skey;
    int len;
    int nxt;
    int leftsy;
    int infinity = prod_max;

    p_cost = int_vecAlloc(global_prod_cnt + 1);
    nrleftsy = int_vecAlloc(vocCnt + 1);
    done = (Boolean *)calloc(global_prod_cnt + 1, sizeof(Boolean));
    if (nrleftsy == NULL) pmkLog(NULL, 213, sevFAT, "");
    sortvec = sortvecAlloc(global_prod_cnt+1);

    /* Compute the least cost function
     */
    for(i = 1; i <= global_prod_cnt; i++) p_cost[i] = infinity;

    lcs(p_cost, &infinity);

    for(i = 1; i <= global_prod_cnt; i++) {
    if (p_cost[i] == infinity) {
        pmkLog(NULL, 234, sevERR,
          vocabulary[global_pvec_tbl[
              global_prod_tbl[i]->start]]->name);
        break;
    }/*if*/
    }/*for*/

    /* Compute an order key for all productions
     */
    prod_2 = (prod_max + 1) * (prod_max + 1);
    for(i = 1; i <= global_prod_cnt; i++) done[i] = FALSE;
    i = 1;
    skey = 0;

    while (i <= global_prod_cnt) {
    if (done[i]) i++;
    else {
        skey++;
        leftsy = global_pvec_tbl[global_prod_tbl[i]->start];
        len = 1;
        sortvec[i].key = prod_2 * skey + (prod_max + 1) * p_cost[i] + i;
        sortvec[i].index = i;
        done[i] = TRUE;
        nxt = global_prod_tbl[i]->nxtls;

        /* Find all productions with same lefthand symbol
         */
        while (nxt != -1) {
        len++;
        done[nxt] = TRUE;
        sortvec[nxt].key =
            prod_2 * skey + (prod_max + 1) * p_cost[nxt] + nxt;
        sortvec[nxt].index = nxt;
        nxt = global_prod_tbl[nxt]->nxtls;
        }/*while*/
        i++;
        nrleftsy[leftsy] = len;
    }/*if*/
    }/*while*/

    gram_sort(1, global_prod_cnt, PROD);

    /* Update pointers
     */
    i = 1;
    while (i <= global_prod_cnt) {
    leftsy = global_pvec_tbl[global_prod_tbl[i]->start];
    vocabulary[leftsy]->syminfo.firstp = i;

    for(j = 1; j <= nrleftsy[leftsy] - 1; j++) {
        k = i++;
        global_prod_tbl[k]->nxtls = i;
    }/*for*/

    global_prod_tbl[i]->nxtls = -1;
    i++;
    }/*while*/

    free(nrleftsy);
    free(p_cost);
    free(done);

    newprod = int_vecAlloc(global_prod_cnt+1);
    if (newprod == NULL) pmkLog(NULL, 213, sevFAT, "");
    else {
    for(i = 1; i <= global_prod_cnt; i++) newprod[sortvec[i].index] = i;
    free(sortvec);
    }/*if*/
}/*order_prod()*/


/*-----------------------------------------------------------------------------
 * order_action - orders the actions and rewrites the references
 *-----------------------------------------------------------------------------
 *                (O)EBNF references have been rewritten previously
 *		  (modul pwsGrm.c) and these will be processed as
 *		  symbol references (errors are not reported for these).
 *-----------------------------------------------------------------------------
 */
static void order_action()
{
    int prod;			/* Current production */
    int actPos;			/* Current attribute reference position */
    int symbol;			/* Current vocabulary symbol */
    int attribute;		/* Current attribute */
    int instance;		/* Current symbol instance */
    Boolean symfound;		/* Symbol is within production? */
    Boolean instfound;		/* Right instance found? */
    int count;			/* Instance counter */
    int i, j;			/* Loop index */
    int index;			/* Symbol offset within prod. */
    int temp;
    attr_kind attr_class;
    sym_kind sym_typ;

    global_attref_sto = (attref *)calloc(attref_cnt + 1, sizeof(attref));
    if (global_attref_sto == NULL) pmkLog(NULL, 213, sevFAT, "");
    global_attref_cnt = 0;

    /* Change old production numbers in the action to new ones
     */
    for(i = 0; i <= semActCnt; i++) {
    semAct[i].prod = newprod[semAct[i].prod];
    }/*for*/

    /* Insert the right action number in the production table
     */
    for(i = 0; i <= semActCnt; i++) {
    global_prod_tbl[semAct[i].prod]->actno = i;
    }/*for*/

    /* Replace old symbol references with new ones. Verify the
     * vocabulary symbol and the attribute
     */
    for(j = 0; j <= attref_cnt; j++) {
    prod = semAct[attref_storage[j]->actno].prod;
    actPos = attref_storage[j]->actPos;
    symbol = newsym[attref_storage[j]->voc_sym];
    if (attref_storage[j]->att != -1) {
        attribute = newsym[attref_storage[j]->att];
    } else {
        attribute = -1;
    }/*if*/
    instance = attref_storage[j]->symins;

    count = 1;		/* Instance count */
    symfound = FALSE;
    instfound = FALSE;

    temp = global_prod_tbl[prod]->start + global_prod_tbl[prod]->rssz;
    for(i = global_prod_tbl[prod]->start; i <= temp; i++) {
        if (global_pvec_tbl[i] == symbol) {
        symfound = TRUE;
        if (instance == count) {
            instfound = TRUE;
            index = i - global_prod_tbl[prod]->start;
            break;
        } else {
            count++;
        }/*if*/
        }/*if*/
    }/*for*/

    if (symfound && instfound) {
        if (attribute == -1 ||
        attr_symb == vocabulary[attribute]->symbol_typ)
        {
        if (attribute == -1) attr_class = voc_attr;
        else attr_class = vocabulary[attribute]->syminfo.attr_class;
        sym_typ = vocabulary[symbol]->symbol_typ;
        if (((attr_class == t_attr || attr_class == voc_attr) &&
             (sym_typ == t_symb)) ||
            ((attr_class == nts_attr || attr_class == voc_attr) &&
             (sym_typ == nts_symb)))
        {
            /* Copy information
             */
            global_attref_sto[global_attref_cnt].ruleno = prod;
            global_attref_sto[global_attref_cnt].actPos = actPos;
            global_attref_sto[global_attref_cnt].sym = symbol;
            global_attref_sto[global_attref_cnt].pos = index;
            global_attref_sto[global_attref_cnt].att = attribute;
            global_attref_cnt++;
        } else if (attr_class == unk_attr &&
               !attref_storage[attref_cnt]->no_errm)
        {
            pmkLog(&(attref_storage[j]->attref_srcp), 150, sevERR,
              vocabulary[attribute]->name);
        } else if (!attref_storage[attref_cnt]->no_errm) {
            pmkLog(&(attref_storage[j]->attref_srcp), 158, sevERR, "");
        }/*if*/
        }/*if*/
    } else if (symfound && !attref_storage[attref_cnt]->no_errm) {
        pmkLog(&(attref_storage[j]->attref_srcp), 159, sevERR, "");
    } else if (!attref_storage[attref_cnt]->no_errm) {
        pmkLog(&(attref_storage[j]->attref_srcp), 149, sevERR, "");
    }/*if*/
    }/*for j*/
}/*order_action()*/


/*-----------------------------------------------------------------------------
 * order_gram -
 *-----------------------------------------------------------------------------
 */
void order_gram()
{
    order_voc();
    order_prod();
    order_action();
    free(newprod);
}/*order_gram()*/
