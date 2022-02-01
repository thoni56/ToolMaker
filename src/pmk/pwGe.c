/*-----------------------------------------------------------------------------
 * pwGe - Parse table generator
 *      @(#)pwGe.c  1.3 (91/03/27 16:10:12)
 *-----------------------------------------------------------------------------
 * Created: 89-08-11 by Tom
 *           From VAX/VMS Pascal V1.34, dated 1988-02-18
 * Modified:    90-11-06 by Yngve
 *          Replaced divFactor with shifting and masking
 *          in actTbl entries.
 *-----------------------------------------------------------------------------
 * Entries:
 *  pwGenTab - The entry of the LALR(1) generator
 *-----------------------------------------------------------------------------
 *
 * Static structure
 * ----------------
 *
 *  pwGenTab                Entry point
 *  abort                   Terminates the generating process
 *  wrItemSet               Outputs the item set for a state
 *
 *  compAccItemSet          Entry point of the item set computation
 *      incItemPtr          Increments the number of items
 *      incNrStates         Increments the number of states
 *      incCorePtr          Increments the core pointer
 *      addPredList         Adds an item to the predecessor list
 *      compItemSet         Computes the LR(0) item set
 *      symAfterDot         Finds the symbol after the "."
 *      closOfCore          Computes the closure set
 *          depthFirstCl    Compute closure depth-first
 *      addSuccState        Computes the successor state
 *          lookUpCore      Checks for distinct cores
 *          lr0State        Checks for LR0 states
 *      compPredecessors    Computes the PRED function
 *      append              Appends two lists
 *      max                 Computes max value
 *      orderItem           Sorts the item set
 *
 *  compLaSet               Entry point of the look-ahead computation
 *      nullSym             Finds the nullable nonterminals
 *      lalr1Set            Computes the LALR(1) look_ahead (start)
 *      trans               Computes the FIRST function
 *      lalr                LALR(1) algorithm
 *
 *  compParseTable          Computes the LALR(1) parse tables
 *      isLalr1             Checks for LALR(1)-ness
 *      compContinuation    Computes the continuation function
 *
 *  compDontCare            Computes the "don't care" entries
 *      nextState           Finds the successor state
 *
 *  writeParseTable         Outputs the parse tables
 *  writeGeStatistics       Output a generated summary
 *      nrBytes             Compute a values byte size
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Imports
 */
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "pmk_i.h"
#include "pws.h"
#include "set.h"
#include "pwsGrm.h"
#include "pwLog.h"
#ifdef DEBUG
#include "pwDbg.h"
#endif

/*-----------------------------------------------------------------------------
 * Exported Variables
 */
#include "pwGe.h"

int **actTbl;           /* Action table */
int **gtoTbl;           /* Goto table */
SETPTR *dontCare;       /* Don't care symbols */
int stateCnt;           /* Number of parser states */
int actRowCnt;          /* Number of rows in the action table */
int actColCnt;          /* Number of columns in the action table */
int actMax;             /* Largest value in action table */
int gtoRowCnt;          /* Number of rows in the goto table */
int gtoColCnt;          /* Number of columns in the goto table */
int gtoMax;             /* Largest value in goto table */
int tableFactor;        /* Divide factor in tables */
ContRec *contTbl;       /* Continuation function */
StateRepr *stateList = NULL;    /* States */
ItemRepr *accItem = NULL;       /* Item Table */

/*-----------------------------------------------------------------------------
 * Static variables
 */
static int stateMax;        /* Current state limit */
static int *coreLen = NULL; /* Core length */
static int itemPtr;         /* Pointer in table */
static int itemMax;         /* Current item limit */
static Boolean *gotoOnTerm = NULL;


/*-----------------------------------------------------------------------------
 * incItemPtr - Increment the number of items (overflow check)
 *-----------------------------------------------------------------------------
 */
static void incItemPtr()
{
    itemPtr++;
    if (itemPtr == itemMax) {
        itemMax *= 2;
        accItem = (ItemRepr *)realloc(accItem, itemMax * sizeof(ItemRepr));
    }/*if*/
}/*incItemPtr()*/


/*-----------------------------------------------------------------------------
 * incNrStates - Increment the number of parser states
 *-----------------------------------------------------------------------------
 */
static void incNrStates()
{
    stateCnt++;
    if (stateCnt == stateMax) {
        stateMax *= 2;
        stateList =
            (StateRepr *)realloc(stateList, stateMax * sizeof(StateRepr));
        coreLen = (int *)realloc(coreLen, stateMax * sizeof(int));
        contTbl = (ContRec *)realloc(contTbl, stateMax * sizeof(ContRec));
    }/*if*/
}/*incNrStates()*/


/*-----------------------------------------------------------------------------
 * addPredList - Add a state to the predecessor list
 *-----------------------------------------------------------------------------
 */
static void addPredList(itemnr, state)
    int itemnr;         /* IN item number */
    int state;          /* IN predecessor state */
{
    PredItem *pt;

    pt = (PredItem *)malloc(sizeof(PredItem));
    pt->pred = state;
    pt->nxt = accItem[itemnr].predList;
    accItem[itemnr].predList = pt;
}/*addPredList()*/


/*-----------------------------------------------------------------------------
 * symAfterDot - Gets the symbol which appears immediately after the dot.
 *-----------------------------------------------------------------------------
 */
static int symAfterDot(item)
    ItemSpec item;         /* IN item descriptor */
    /* RET vocabulary symbol. 0 if dot is at end */
    /*     of production */
{
    if (item.dot < global_prod_tbl[item.prod]->rssz) {
        return global_pvec_tbl[global_prod_tbl[item.prod]->start +
                               (item.dot + 1)];
    } else {
        return 0;
    }/*if*/
}/*symAfterDot()*/


/*-----------------------------------------------------------------------------
 * depthFirstCl - Compute the closure of an item in a depth-first manner.
 *-----------------------------------------------------------------------------
 */
static void depthFirstCl(state, item, pt, legClosure, size)
    int state;              /* IN state number */
    int item;               /* IN item number to close */
    PredItem *pt;           /* IN predecessor list */
    Boolean *legClosure;    /* INOUT closure start symbols */
    int *size;              /* INOUT number of elements */
{
    int sym;                /* Index in vocabulary */
    int prod;               /* Loop variable for productions */

    sym = accItem[item].afterDot;

    /* "sym" is index in vocabulary, 0 if completed item.
     */
    if (contTbl[state].tsym == -1) {
        if (sym == 0) {
            /* Completed item
             */
            contTbl[state].tsym = global_pvec_tbl[
                                                  global_prod_tbl[accItem[item].item.prod]->start];
        } else if (sym <= termCnt) {
            /* Terminal
             */
            contTbl[state].tsym = sym;
        }/*if*/
    }/*if*/

    /* No member in closure set if:
     * 1. terminal
     * 2. already done
     * 3. completed item
     */
    if (legClosure[sym]) {
        /* We have found one more to add
         */
        legClosure[sym] = FALSE;
        prod = vocabulary[sym]->syminfo.firstp;
        do {
            /* Follow the path through all productions with the same
             * lefthand symbol recursively
             */
            incItemPtr();
            accItem[itemPtr].item.prod = prod;
            accItem[itemPtr].item.dot = 0;
            accItem[itemPtr].predList = pt;
            accItem[itemPtr].laPtr = NULL;
            accItem[itemPtr].afterDot = symAfterDot(accItem[itemPtr].item);
            accItem[itemPtr].succState = 0;
            accItem[itemPtr].sr = FALSE;

            (*size)++;

            /* Now recur to compute items depth-first
             */
            depthFirstCl(state, itemPtr, pt, legClosure, size);

            /* Get next production for current level
             */
            prod = global_prod_tbl[prod]->nxtls;
        } while (prod != -1);
    }/*if*/
}/*depthFirstCl()*/


/*-----------------------------------------------------------------------------
 * closOfCore - Computes the closure of current set of core
 *-----------------------------------------------------------------------------
 * Compute the closure set by applying a "Depth first" strategy.
 *
 * In parallel with the closure computation the continuation
 * function will be evaluated (or some part of it)
 *
 * The terminating function (TSYM) is computed by inspecting the
 * the items in the order they are computed.
 * An item has the form [A -> aX . b]    ;where a,b are strings
 *     - If "b" is empty (a reduce action) an arbitrary symbol
 *       from the look-ahead set is chosen. The selection
 *       is postponed until later as the look-ahead is not yet
 *       computed.
 *     - If b  is a terminal symbol "b" is chosen.
 *     - Otherwise the next item is inspected
 *
 * The advancing function (SSYM) for dealing with separators are
 * computed later.
 *-----------------------------------------------------------------------------
 */
static void closOfCore(state, size)
    int state;              /* IN state number */
    int *size;              /* OUT number of elements */
{
    Boolean *legClosure;    /* Possible closure start symbols */
    int i;                  /* Loop variable */
    PredItem *pt;           /* Predecessor list */

    legClosure = (Boolean *)malloc((vocCnt + 1) * sizeof(Boolean));
    for (i = 0; i <= termCnt; i++) legClosure[i] = FALSE;
    for (i = termCnt + 1; i <= vocCnt; i++) legClosure[i] = TRUE;

    contTbl[state].tsym = -1;
    contTbl[state].ssym = -1;

    pt = (PredItem *)malloc(sizeof(PredItem));
    pt->pred = state;
    pt->nxt = NULL;
    *size = coreLen[state];

    for (i = 0; i < coreLen[state]; i++) {
        depthFirstCl(state, stateList[state].istart + i, pt, legClosure, size);
    }/*for*/
    free((char *)legClosure);
}/*closOfCore()*/


/*-----------------------------------------------------------------------------
 * lookUpCore - Check whether current core is distinct to all other cores
 *              computed.
 *-----------------------------------------------------------------------------
 */
static int lookUpCore(state, core_start, core_len)
    int state;          /* IN current state number */
    int core_start;     /* IN start of core */
    int core_len;       /* IN length of core */
    /* RET state nr with equal core. Otherw. 0 */
{
    int i, j, tptr, cptr;
    Boolean equal, unequal;

    i = 1;
    equal = FALSE;
    while ((i <= state ) && !equal) {
        if (coreLen[i] == core_len) {
            tptr = stateList[i].istart;
            cptr = core_start;
            j = 1;
            unequal = FALSE;
            while ((j <= core_len) && !unequal) {
                if ((accItem[tptr].item.prod == accItem[cptr].item.prod) &&
                    (accItem[tptr].item.dot == accItem[cptr].item.dot))
                    {
                        j++;
                        cptr++;
                        tptr++;
                    } else {
                    unequal = TRUE;
                }/*if*/
            }/*while*/

            equal = !unequal;
        }/*if*/

        i++;
    }/*while*/

    if (equal) return i - 1;
    else return 0;
}/*lookUpCore()*/


/*-----------------------------------------------------------------------------
 * lr0State - Check whether current state is an LR0 reduce state
 *-----------------------------------------------------------------------------
 * A state is a LR0 reduce state on the following conditions
 * - There is only one element in the item set
 * - The item has the form: [A --> a.]
 * - A = a is not the augmented rule
 * - The OPTIMIZE(LR0) option is set
 *-----------------------------------------------------------------------------
 */
static Boolean lr0State(item, core_len)
     int item;          /* IN item  number */
     int core_len;      /* IN core length */
     /* RET TRUE if a LR0 reduce state */
{
    return (getSetOpt(OPTIMIZE_OPT) & 1) &&
        (core_len == 1) &&
        (accItem[item].afterDot == 0) &&
        (accItem[item].item.prod != 0);
}/*lr0State()*/


static void compItemSet();


/*-----------------------------------------------------------------------------
 * incCorePtr - Increments a core counter
 *-----------------------------------------------------------------------------
 */
static void incCorePtr(corePtr, coreMax, cindex)
    int *corePtr;       /* INOUT the current core counter */
    int *coreMax;       /* INOUT the current size of index table */
    int **cindex;       /* INOUT the current index table */
{
    (*corePtr)++;
    if (*corePtr == *coreMax) {
        *coreMax *= 2;
        *cindex = (int *)realloc(*cindex, *coreMax * sizeof(int));
    }/*if*/
}/*incCorePtr()*/


/*-----------------------------------------------------------------------------
 * addSuccState - Compute the successor states
 *-----------------------------------------------------------------------------
 * Compute the successor state (core and closure) to all items in current
 * state. That means that we compute the states which are directly
 * accessible from current state.
 *-----------------------------------------------------------------------------
 */
static void addSuccState(state)
    int state;          /* IN current state number */
{
    int cnt, i, j;
    int strt, tmp;
    int newstate;
    int *cindex;        /* Core item index table */
    int corePtr;        /* Pointer in table */
    int coreMax;        /* Current core item limit */
    Boolean *done;
    Boolean state_is_lr0;

    strt = stateList[state].istart;
    cnt = stateList[state].setsz;

    /* FALSE is assumed to be = 0 (assigned by calloc)
     */
    done = (Boolean *)calloc(cnt, sizeof(Boolean));

    coreMax = 10;
    cindex = (int *)malloc(coreMax * sizeof(int));

    for (i = strt; i < strt + cnt; i++) {
        /* Compute core, i.e. move the dot one position right,
         * all items with the dot in front of the same symbol
         * belongs to the core. Add core to item set and associate
         * a statenumber with it. Note that the core must be
         * distinct to all other cores.
         */
        if ((accItem[i].afterDot != 0) && !done[i - strt]) {
            /* Not at end of rule, so add it
             */
            incItemPtr();
            tmp = itemPtr;
            accItem[itemPtr].item = accItem[i].item;
            accItem[itemPtr].item.dot++;
            accItem[itemPtr].predList = NULL;
            accItem[itemPtr].laPtr = NULL;
            accItem[itemPtr].afterDot = symAfterDot(accItem[itemPtr].item);
            accItem[itemPtr].succState = 0;
            accItem[itemPtr].sr = FALSE;
            cindex[1] = i;
            corePtr = 1;

            for (j = i + 1; j < strt + cnt; j++) {
                /* Look for more items to add
                 */
                if (accItem[j].afterDot == accItem[i].afterDot) {
                    /* Oh! A lucky day, one to add
                     */
                    incItemPtr();
                    accItem[itemPtr].item = accItem[j].item;
                    accItem[itemPtr].item.dot++;
                    accItem[itemPtr].predList = NULL;
                    accItem[itemPtr].laPtr = NULL;
                    accItem[itemPtr].afterDot =
                        symAfterDot(accItem[itemPtr].item);
                    accItem[itemPtr].succState = 0;
                    accItem[itemPtr].sr = FALSE;
                    incCorePtr(&corePtr, &coreMax, &cindex);
                    cindex[corePtr] = j;
                    done[j - strt] = TRUE;
                }/*if*/
            }/*for*/

            /* Core is now computed
             */

            newstate = lookUpCore(stateCnt, tmp, corePtr);
            state_is_lr0 = FALSE;
            if (newstate == 0) {
                /* Distinct core, add new state if notstate is an LR0 state
                 */
                if (lr0State(tmp, corePtr)) {
                    itemPtr = tmp - 1;
                    state_is_lr0 = TRUE;
                } else {
                    incNrStates();
                    stateList[stateCnt].istart = tmp;
                    stateList[stateCnt].top = accItem[i].afterDot;
                    addPredList(tmp, state);
                    coreLen[stateCnt] = corePtr;
                    newstate = stateCnt;

                    /* Compute closure and successor state
                     */
                    compItemSet(newstate);
                }/*if*/
            } else {
                /* Not different core, no more state
                 */
                addPredList(stateList[newstate].istart, state);
                itemPtr = tmp - 1; /* Backup */
            }/*if*/

            /* Fill in successor state
             */
            for (j = 1; j <= corePtr; j++) {
                accItem[cindex[j]].succState = newstate;
                if (state_is_lr0) accItem[cindex[j]].sr = TRUE;
            }/*if*/
        }/*if*/

        if (accItem[i].afterDot == 0) {
            accItem[i].typ = complete;
        } else if (accItem[i].afterDot > termCnt) {
            /* nt-transition
             */
            accItem[i].typ = ntTrans;
        } else {
            accItem[i].typ = tTrans;
        }/*if*/
    }/*for*/
    free((char *)done);
    free((char *)cindex);
}/*addSuccState()*/


/*-----------------------------------------------------------------------------
 * compItemSet - Compute the accessible LR(0) item set
 *-----------------------------------------------------------------------------
 *    Indirect recursive routine, which computes all sets of items
 *    accessible from the starting item, i.e. from <sys> --> .<goal>
 *    Algorithm works as follows:
 *
 *    1. Add core to current set of item (core is computed by caller),
 *       i.e. for each item of the form  [A --> a . Xb] in previous
 *       set, we add [A --> aX . b]. (a,b are strings)
 *
 *    2. Compute the closure set from the core and add it to the set.
 *       Associate a statenumber to the set.
 *
 *    3. Compute successors to current state by:
 *       for all items in the set compute core and apply step 1 to 3.
 *-----------------------------------------------------------------------------
 */
static void compItemSet(state)
    int state;          /* IN state number */
{
    int setlen;         /* Size of the item set */

    /* Compute closure of core
     */
    closOfCore(state, &setlen);
    stateList[state].setsz = setlen;

    /* Compute sucessor states
     */
    addSuccState(state);
}/*compItemSet()*/


/*-----------------------------------------------------------------------------
 * append - Append two predecessor lists
 *-----------------------------------------------------------------------------
 */
static PredItem *append(pt1, pt2)
    PredItem *pt1;      /* IN first list */
    PredItem *pt2;      /* IN second list */
    /* RET "pt1" appended to "pt2" */
{
    PredItem *p, *newpt, *pt;

    if (pt1) {
        newpt = (PredItem *)malloc(sizeof(PredItem));
        newpt->pred = pt2->pred;
        pt = newpt;
        while (pt2->nxt) {
            pt2 = pt2->nxt;
            p = (PredItem *)malloc(sizeof(PredItem));
            pt->nxt = p;
            p->pred = pt2->pred;
            pt = p;
        }/*while*/

        pt->nxt = pt1;
    } else {
        newpt = pt2;
    }/*if*/

    return newpt;
}/*append()*/


/*-----------------------------------------------------------------------------
 * compPredecessors - Compute the PRED function
 *-----------------------------------------------------------------------------
 *  Compute the function PRED(T, alfa), i.e. the states T' such that
 *  GOTO(T', alfa) = T.
 *
 *  Definition:
 *             (T)               alfa = empty
 *     PRED(T, alfa) =
 *             (PRED(S, alfa'):GOTO(S, X) = T) alfa = alfa' X
 *-----------------------------------------------------------------------------
 */
static void compPredecessors()
{
    int *mxdotpos;
    int pos;
    int maxpos;
    int *startpos, *endpos;
    int ibeg, iend;
    int s;
    PredItem *pt, *pt1;
    int i, j, k;
    ItemSpec titem;

    maxpos = 0;
    mxdotpos = (int *)malloc((stateCnt + 1) * sizeof(int));
    startpos = (int *)malloc((stateCnt + 1) * sizeof(int));
    endpos = (int *)malloc((stateCnt + 1) * sizeof(int));
    for (i = 1; i <= stateCnt; i++) {
        ibeg = stateList[i].istart;
        startpos[i] = ibeg;
        iend = ibeg + coreLen[i] - 1;
        endpos[i] = iend;
        mxdotpos[i] = accItem[ibeg].item.dot;
        pt = accItem[ibeg].predList;
        for (j = ibeg+1; j <= iend; j++) {
            accItem[j].predList = pt;
            mxdotpos[i] = max(mxdotpos[i], accItem[j].item.dot);
        }/*for*/

        maxpos = max(maxpos, mxdotpos[i]);
    }/*for*/

    for (pos = 2; pos <= maxpos; pos++) {
        for (i = 1; i <= stateCnt; i++) {
            if (pos <= mxdotpos[i]) {
                for (j = startpos[i]; j <= endpos[i]; j++) {
                    if (accItem[j].item.dot == pos) {
                        pt = accItem[j].predList;
                        titem = accItem[j].item;
                        accItem[j].predList = NULL;
                        titem.dot--;
                        while (pt != NULL) {
                            s = pt->pred;
                            for (k = startpos[s]; k <= endpos[s]; k++) {
                                if ((accItem[k].item.dot == titem.dot) &&
                                    (accItem[k].item.prod == titem.prod))
                                    {
                                        pt1 = accItem[k].predList;
                                    }/*if*/
                            }/*for*/

                            accItem[j].predList =
                                append(accItem[j].predList, pt1);
                            pt = pt->nxt;
                        }/*while*/
                    }/*if*/
                }/*for j*/
            }/*if*/
        }/*for i*/
    }/*for pos*/
    free((char *)mxdotpos);
    free((char *)startpos);
    free((char *)endpos);
}/*compPredecessors()*/


/*-----------------------------------------------------------------------------
 * orderItem - Rearrange the item set
 *-----------------------------------------------------------------------------
 * Move all completed items to the beginning of the list.
 *-----------------------------------------------------------------------------
 */
static void orderItem()
{
    int i, j;           /* Loop index */
    int cmp_ptr;        /* Pointer to completed items */
    ItemRepr itmp;      /* Temporary item */

    /* FALSE is assumed to be = 0 (initial value by calloc)
     */
    gotoOnTerm = (Boolean *)calloc(stateCnt + 1, sizeof(Boolean));

    for (i = 1; i <= stateCnt; i++) {
        /* For all states
         */
        cmp_ptr = stateList[i].istart;
        for (j = stateList[i].istart;
             j < stateList[i].istart + stateList[i].setsz; j++)
            {
                if (accItem[j].typ == complete) {
                    itmp = accItem[j];
                    accItem[j] = accItem[cmp_ptr];
                    accItem[cmp_ptr] = itmp;
                    cmp_ptr = cmp_ptr + 1;
                } else if (accItem[j].typ == tTrans) {
                    if (!accItem[j].sr) gotoOnTerm[accItem[j].succState] = TRUE;
                }/*if*/
            }/*for*/
    }/*for*/
}/*orderItem()*/


/*-----------------------------------------------------------------------------
 * compAccItemSet - Compute the LR(0) item set (Start up)
 *-----------------------------------------------------------------------------
 */
static void compAccItemSet()
{
    itemMax = 1200;
    accItem = (ItemRepr *)malloc(itemMax * sizeof(ItemRepr));

    /* Start with item: <sys> --> .<goal>
     */
    accItem[1].item.dot = 0;
    accItem[1].item.prod = 0;
    accItem[1].predList = NULL;
    accItem[1].laPtr = NULL;
    accItem[1].afterDot = goal_sym;
    accItem[1].sr = FALSE;
    accItem[1].succState = 0;

    itemPtr = 1;

    stateMax = 200;
    stateList = (StateRepr *)malloc(stateMax * sizeof(StateRepr));
    coreLen = (int *)malloc(stateMax * sizeof(int));
    contTbl = (ContRec *)malloc(stateMax * sizeof(ContRec));

    stateList[1].istart = 1;
    stateList[1].top = 0;

    stateCnt = 1;
    coreLen[1] = 1;

    compItemSet(stateCnt);
    compPredecessors();
    orderItem();
}/*compAccItemSet()*/


/*-----------------------------------------------------------------------------
 * nullSym - Compute the "nullable" nonterminals
 *-----------------------------------------------------------------------------
 */
static void nullSym(nullable)
     Boolean *nullable; /* OUT symbol is nullable? */
{
    int i;
    int cnt;
    int sptr;
    int eptr;
    Boolean terminals;
    Boolean null;
    Boolean changed;
    int *prodvec;

    for (i = 0; i <= vocCnt; i++) nullable[i] = FALSE;
    cnt = 0;

    /* Find all rules which contains just nonterminals. If
     * right part of a rule is empty, mark left side as nullable.
     */
    prodvec = (int *)malloc((global_prod_cnt + 1) * sizeof(int));
    for (i = 1; i <= global_prod_cnt; i++) {
        sptr = global_prod_tbl[i]->start;
        eptr = global_prod_tbl[i]->start + global_prod_tbl[i]->rssz;

        if (sptr == eptr) {
            /* Empty right part
             */
            nullable[global_pvec_tbl[sptr]] = TRUE;
        } else {
            sptr++;
            terminals = FALSE;
            do {
                /* Terminal found or end of rule
                 */
                if (vocabulary[global_pvec_tbl[sptr]]->symbol_typ ==
                    t_symb)
                    {
                        terminals = TRUE;
                    }/*if*/
                sptr++;
            } while (!(terminals || (sptr > eptr)));

            if (!terminals) {
                cnt++;
                prodvec[cnt] = i;
            }/*if*/
        }/*if*/
    }/*for*/

    /* The variable "prodvec" contains the productions that contains
     * only terminals in their right hand side. If the nonterminals in
     * the right hand side are nullable the left hand side is set to
     * nullable.
     */
    do {
        changed = FALSE;

        for (i = 1; i <= cnt; i++) {
            sptr = global_prod_tbl[prodvec[i]]->start;
            eptr = global_prod_tbl[prodvec[i]]->start +
                global_prod_tbl[prodvec[i]]->rssz;

            if (!nullable[global_pvec_tbl[sptr]]) {
                do {
                    sptr++;
                    null = nullable[global_pvec_tbl[sptr]];
                } while (null && (sptr != eptr));

                if (null) {
                    nullable[global_pvec_tbl[global_prod_tbl[
                                                             prodvec[i]]->start]] = TRUE;
                    changed = TRUE;
                }/*if*/
            }/*if*/
        }/*for*/
    } while (changed);
    free((char *)prodvec);
}/*nullSym()*/


/*-----------------------------------------------------------------------------
 * trans - Computes acceptable terminals in state
 *-----------------------------------------------------------------------------
 * TRANS(T) computes these symbols (terminals) which are legal
 * input symbols in this state. Used as a simulation of the
 * FIRST - function, by using the LR(0) automaton directly
 *-----------------------------------------------------------------------------
 */
static void trans(t, nullable, visitedState, la)
    int t;                      /* IN current state */
    Boolean *nullable;          /* IN symbol is nullable? */
    Boolean *visitedState;      /* INOUT state is visited? */
    SET la;                     /* OUT computed look-ahead */
{
    int i;
    int sym;

    visitedState[t] = TRUE;
    for (i = stateList[t].istart;
         i < stateList[t].istart + stateList[t].setsz; i++)
        {
            sym = accItem[i].afterDot;
            if ((sym == 0) && (accItem[i].item.prod == 0)) sym = 1;
            if (sym > termCnt) {
                if (nullable[sym] && !accItem[i].sr &&
                    !visitedState[accItem[i].succState])
                    {
                        trans(accItem[i].succState, nullable, visitedState, la);
                    }/*if*/
            } else if (sym != 0) {
                SetIns(la, sym);
            }/*if*/
        }/*for*/
}/*trans()*/


/*-----------------------------------------------------------------------------
 * lalr - Computes the LALR(1) look-ahead to a particular item
 *-----------------------------------------------------------------------------
 *  Compute the LALR1 look-ahead set to the item
 *  [A --> alfa . beta] = I(temnr) in state T.
 *
 *  The LALR-set to I is defined as those terminal symbols which
 *  could follow A after the reduction.
 *
 *  1.  LALR1(I, T) = LALR([A --> . alfa beta], S)
 *      if GOTO(S, alfa) = T
 *
 *  2.  LALR([A --> . alfa beta, S] =
 *      (FIRST(psi) | [B --> fi . A psi] is in S)
 *          Union
 *      (LALR([B --> fi . A psi], S) | If psi ==>* empty string)
 *-----------------------------------------------------------------------------
 */
static void lalr(itemnr, visitedState, nullable, visitedItem, la)
    int itemnr;                 /* IN current item nr. */
    Boolean *visitedState;      /* IN state visited? */
    Boolean *nullable;          /* IN symbol is nullable? */
    Boolean *visitedItem;       /* INOUT item visited? */
    SET la;                     /* OUT computed look-ahead */
{
    PredItem *tp;     /* Predecessor list */
    int lsym;         /* Left hand side symbol */
    int sym;          /* Terminal */
    int s;            /* Current state */
    int pos;          /* Pos. in RHS */
    int rsize;        /* Size of RHS */
    int i;            /* Loop variable */
    Boolean empty;    /* Nullable symbol? */

    visitedItem[itemnr] = TRUE;
    tp = accItem[itemnr].predList;
    lsym = global_pvec_tbl[global_prod_tbl[accItem[itemnr].item.prod]->start];
    while (tp) {
        s = tp->pred;

        /* Locate item [B --> fi . A psi] in S
         */
        for (i = stateList[s].istart;
             i < stateList[s].istart + stateList[s].setsz; i++)
            {
                if (accItem[i].afterDot == lsym) {
                    if (!visitedState[accItem[i].succState] && !accItem[i].sr) {
                        trans(accItem[i].succState, nullable, visitedState, la);
                    }/*if*/
                    if (!visitedItem[i]) {
                        /* Check whether "psi" can generate the empty string
                         */
                        pos = global_prod_tbl[accItem[i].item.prod]->start +
                            (accItem[i].item.dot + 2);
                        rsize = global_prod_tbl[accItem[i].item.prod]->start +
                            global_prod_tbl[accItem[i].item.prod]->rssz;

                        if (pos <= rsize) sym = global_pvec_tbl[pos];
                        else sym = 0;

                        empty = !((sym == 0) && (accItem[i].item.prod == 0));
                        while (empty && (sym != 0)) {
                            if (sym <= termCnt) empty = FALSE;
                            else {
                                empty = nullable[sym];
                                pos++;
                                if (pos <= rsize) sym = global_pvec_tbl[pos];
                                else sym = 0;
                            }/*if*/
                        }/*while*/

                        if (empty) {
                            lalr(i, visitedState, nullable, visitedItem, la);
                        }/*if*/
                    }/*if*/
                }/*if*/
            }/*for*/
        tp = tp->nxt;
    }/*while*/
}/*lalr()*/


/*-----------------------------------------------------------------------------
 * lalr1Set - Computes the LALR(1) look-ahead
 *-----------------------------------------------------------------------------
 */
static void lalr1Set(itemnr, nullable, la)
    int itemnr;         /* IN LR(0) item */
    Boolean *nullable;  /* IN symbol is nullable? */
    SET la;             /* OUT computed look-ahead */
{
    Boolean *visitedState;
    Boolean *visitedItem;

    /* FALSE is assumed = 0 (assigned by calloc)
     */
    visitedState = (Boolean *)calloc(stateCnt + 1, sizeof(Boolean));
    visitedItem = (Boolean *)calloc(itemPtr + 1, sizeof(Boolean));

    SetClear(la, termCnt + 1);

    if (accItem[itemnr].item.prod == 0) SetIns(la, 1);
    else lalr(itemnr, visitedState, nullable, visitedItem, la);
    free((char *)visitedState);
    free((char *)visitedItem);
}/*lalr1Set()*/


/*-----------------------------------------------------------------------------
 * compLaSet - Compute the LALR(1) look_ahead
 *-----------------------------------------------------------------------------
 *  Compute the LALR(1) look-ahead set for all completed items
 *  [A --> alfa .]
 *
 *  Algorithm: See TOPLAS januari 1981 pp. 60 - 82 and comments below.
 *-----------------------------------------------------------------------------
 */
static void compLaSet()
{
    Boolean *nullable;
    int i, j;           /* Loop index */

    nullable = (Boolean *)malloc((vocCnt + 1) * sizeof(Boolean));
    nullSym(nullable);      /* Result in "nullable" */
    for (i = 1; i <= stateCnt; i++) {
        for (j = stateList[i].istart;
             j < stateList[i].istart + stateList[i].setsz; j++)
            {
                if (accItem[j].typ == complete) {
                    accItem[j].laPtr = (SETPTR)malloc(SETLEN(termCnt + 1));
                    lalr1Set(j, nullable, accItem[j].laPtr);
                }/*if*/
            }/*for*/
    }/*for*/
    free((char *)nullable);
}/*compLaSet()*/


/*-----------------------------------------------------------------------------
 * isLalr1 - Check the LALR(1) conditions
 *-----------------------------------------------------------------------------
 * A LALR(1) grammar must not have any Shift-Reduce or Reduce-Reduce
 * conflicts. In a Shift-Reduce conflict the shift symbol is a member
 * in the look-ahead set of the reduction. In a Reduce-Reduce
 * conflict the look-ahead sets are not disjoint.
 *
 * If the grammar is not LALR(1) the routine tries to resolve the
 * conflicts by
 *
 * 1)  Modifications
 *     Shift-Reduce: Force or prevent a reduction on the shift sym.
 *     Reduce_Reduce: Actions are specified for each common symbol
 *            in the look-ahead sets for both productions
 *
 * 2)  Default (if CONFLICT(DEFAULT) and not CONFLICT(ABORT))
 *     Shift-Reduce: Shift in favour of reduce.
 *     Reduce-Reduce: Reduce with the production that appears first
 *            in the grammar.
 *-----------------------------------------------------------------------------
 */
static Boolean isLalr1(state, resByDefault, resByModify)
    int state;                  /* IN state number to check */
    Boolean *resByDefault;      /* OUT conflicts resolved by default rules? */
    Boolean *resByModify;       /* OUT conflicts resolved by modification? */
    /* RET grammar status */
{
    int firstItem;      /* First item in state */
    int lastItem;       /* Last item in state */
    int last_red_item;  /* Last reduce item */
    int sym;            /* Vocabulary symbol */
    int p1;             /* Production 1 */
    int p2;             /* Production 2 */
    Boolean p1_red;     /* Reduce modification for p1? */
    Boolean p1_nored;   /* Shift modification for p1? */
    Boolean p2_red;     /* Reduce modification for p2? */
    Boolean p2_nored;   /* Shift modification for p2? */
    int reduce_prod;    /* Default production */
    Boolean conflicts;  /* LALR(1) status */
    Boolean sr_confl;   /* Shift-Reduce conflict? */
    Boolean rr_confl;   /* Reduce-Reduce conflict? */
    SETPTR intres;      /* Result from intersect */
    int i, j, k;        /* Loop index */

    conflicts = FALSE;
    firstItem = stateList[state].istart;
    lastItem = firstItem + stateList[state].setsz - 1;

    if ((lastItem > firstItem) && (accItem[firstItem].typ == complete)) {
        /* A check is to be done
         */
        last_red_item = firstItem + 1;

        /* Find index to last reduce item
         */
        while ((last_red_item <= lastItem) &&
               (accItem[last_red_item].typ == complete))
            {
                last_red_item++;
            }/*while*/
        last_red_item--;

        /* Find all reduce-reduce conflicts
         * --------------------------------
         */
        intres = (SETPTR)malloc(SETLEN(termCnt + 1));
        for (i = firstItem; i < last_red_item; i++) {
            for (j = i+1; j <= last_red_item; j++) {
                p1 = accItem[i].item.prod;
                p2 = accItem[j].item.prod;
                SetInter(accItem[i].laPtr, accItem[j].laPtr, intres,
                         termCnt + 1);

                for (k = 1; k <= termCnt; k++) {
                    /* For all conflict symbols
                     */
                    rr_confl = SetMem(intres, k);
                    if (rr_confl) {
                        fprintf(pwsLog,
                                "*******  Reduce-Reduce conflict in state %4u Symbol: %s Productions: %4u %4u\n",
                                state, vocabulary[k]->name, p1, p2);
                    }/*if*/
                    if (rr_confl) {
                        /* Try modification
                         */
                        if (global_prod_tbl[p1]->modify &&
                            global_prod_tbl[p2]->modify)
                            {
                                p1_red = global_prod_tbl[p1]->modify->red &&
                                    SymSetMem(global_prod_tbl[p1]->modify->red, k);
                                p1_nored = global_prod_tbl[p1]->modify->nored &&
                                    SymSetMem(global_prod_tbl[p1]->modify->nored,
                                              k);
                                p2_red = global_prod_tbl[p2]->modify->red &&
                                    SymSetMem(global_prod_tbl[p2]->modify->red, k);
                                p2_nored = global_prod_tbl[p2]->modify->nored &&
                                    SymSetMem(global_prod_tbl[p2]->modify->nored,
                                              k);
                                if ((p1_red && p2_nored) ||
                                    (p1_nored && p2_red))
                                    {
                                        /* Resolved
                                         */
                                        rr_confl = FALSE;
                                        *resByModify = TRUE;
                                        if (p1_red) {
                                            reduce_prod = p1;
                                            SetDel(accItem[j].laPtr, k);
                                        } else {
                                            reduce_prod = p2;
                                            SetDel(accItem[i].laPtr, k);
                                        }
                                        fprintf(pwsLog,
                                                "         Resolved by modification (Reduce: %4u)\n", reduce_prod);
                                    } else if (p1_nored && p2_nored) {
                                    rr_confl = FALSE;
                                    *resByModify = TRUE;
                                    SetDel(accItem[i].laPtr, k);
                                    SetDel(accItem[j].laPtr, k);
                                    fprintf(pwsLog,
                                            "         ** Warning! Resolved by preventing the reduction for %s\n",
                                            vocabulary[k]->name);
                                }/*if*/
                            }/*if*/
                    }/*if*/

                    if (rr_confl &&
                        (getSetOpt(RESOLVE_OPT) & 1)) {
                        /* Resolve conflict by default rules
                         */
                        if (global_prod_tbl[p1]->orig <
                            global_prod_tbl[p2]->orig)
                            {
                                reduce_prod = p1;
                                SetDel(accItem[j].laPtr, k);
                            } else {
                            reduce_prod = p2;
                            SetDel(accItem[i].laPtr, k);
                        }/*if*/
                        fprintf(pwsLog,
                                "         Resolved by default rule (Reduce: %4u)\n", reduce_prod);
                        rr_confl = FALSE;
                        *resByDefault = TRUE;
                    }/*if*/

                    if (rr_confl) conflicts = TRUE;
                }/*for k*/
            }/*for j*/
        }/*for i*/
        free((char *)intres);

        /* Find all shift-reduce conflicts
         * -------------------------------
         */
        for (i = last_red_item + 1; i <= lastItem; i++) {
            if (accItem[i].typ == tTrans) {
                sym = accItem[i].afterDot;
                for (j = firstItem; j <= last_red_item; j++) {
                    p1 = accItem[i].item.prod;
                    p2 = accItem[j].item.prod;
                    sr_confl = SetMem(accItem[j].laPtr, sym);

                    if (sr_confl) {
                        /* Shift - Reduce conflict
                         */
                        fprintf(pwsLog,
                                "*******  Shift-Reduce conflict in state %4u Symbol: %s Production: %4u\n",
                                state, vocabulary[sym]->name, p2);
                    }/*if*/
                    if (sr_confl) {
                        /* Try modifications
                         */
                        if (global_prod_tbl[p2]->modify) {
                            if (global_prod_tbl[p2]->modify->red &&
                                SymSetMem(global_prod_tbl[p2]->modify->red,
                                          sym))
                                {
                                    /* Force reduction
                                     */
                                    sr_confl = FALSE;
                                    fprintf(pwsLog,
                                            "         Resolved by modification (Reduce: %4u)\n", p2);
                                    *resByModify = TRUE;
                                } else if (global_prod_tbl[p2]->modify->nored &&
                                           SymSetMem(global_prod_tbl[p2]->
                                                     modify->nored, sym))
                                {
                                    /* Prevent reduce
                                     */
                                    sr_confl = FALSE;
                                    SetDel(accItem[j].laPtr, sym);
                                    fprintf(pwsLog,
                                            "         Resolved by modification (Shift: %s)\n", vocabulary[sym]->name);
                                    *resByModify = TRUE;
                                }/*if*/
                        }/*if*/
                    }/*if*/

                    /* Default rules
                     */
                    if (sr_confl &&
                        (getSetOpt(RESOLVE_OPT) & 1)) {
                        /* Resolve conflict by default rules
                         */
                        sr_confl = FALSE;
                        SetDel(accItem[j].laPtr, sym);
                        fprintf(pwsLog,
                                "         Resolved by default rule (Shift: %s)\n", vocabulary[sym]->name);
                        *resByDefault = TRUE;
                    }/*if*/

                    if (sr_confl) conflicts = TRUE;
                }/*for*/
            }/*if*/
        }/*for*/
    }/*if*/

    return !conflicts;
}/*isLalr1()*/


/*-----------------------------------------------------------------------------
 * compContinuation - Find the continuation function
 *-----------------------------------------------------------------------------
 * The terminating function is already computed for terminal
 * transitions. For reduce states one terminal is chosen from the
 * look-ahead set.
 *
 * If a state has a transition on a separator the separator will be
 * selected in the error recovery process. The separator part of the
 * continuation function (SSYM) contains the separator if applicable
 * and the terminating function otherwise.
 *-----------------------------------------------------------------------------
 */
static void compContinuation(state)
    int state;          /* IN current state */
{
    int firstItem;      /* First item number */
    int lastItem;       /* Last item number */
    int i, j;           /* Loop variables */
    int tsym;           /* Saved production for reduce states */

    firstItem = stateList[state].istart;
    lastItem = firstItem + stateList[state].setsz - 1;

    /* If the tsym is a non-terminal find a continuation from the */
    /* follow set, but make sure it is picked from the cheapest production */
    if ((contTbl[state].tsym > termCnt) || (contTbl[state].tsym == 0)) {
        /* Find one symbol from the look_ahead set */
        i = firstItem;
        tsym = contTbl[state].tsym; /* Save possible nonterminal */
        contTbl[state].tsym = - 1;
        while (i <= lastItem && contTbl[state].tsym == -1) {
            /* Correct production ?*/
            if (tsym == global_pvec_tbl[global_prod_tbl[accItem[i].item.prod]->start]) {
                /* If so find a terminal in the follow set */
                for (j = 1; j <= termCnt; j++) {
                    if (accItem[i].laPtr && SetMem(accItem[i].laPtr, j)) {
                        contTbl[state].tsym = j;
                        break;
                    }
                }
            }
            i++;
        }
    }

    /* Find the separator part */
    i = firstItem;
    while ((i <= lastItem) && (contTbl[state].ssym == -1)) {
        if (accItem[i].typ == complete) {
            for (j = 1; j <= termCnt; j++) {
                if (SetMem(accItem[i].laPtr, j) &&
                    recovery_spec.separators &&
                    SymSetMem(recovery_spec.separators, j) &&
                    (j != contTbl[state].tsym)) {
                    contTbl[state].ssym = j;
                    goto exit;
                } /*if*/
            } /*for*/
        } else if (accItem[i].typ == tTrans) {
            if (recovery_spec.separators &&
                SymSetMem(recovery_spec.separators, accItem[i].afterDot) &&
                (accItem[i].afterDot != contTbl[state].tsym)) {
                contTbl[state].ssym = accItem[i].afterDot;
            } /*if*/
        } /*if*/
        i++;
    } /*while*/
 exit:
    if (contTbl[state].ssym == -1) contTbl[state].ssym = contTbl[state].tsym;
}/*compContinuation()*/


/*-----------------------------------------------------------------------------
 * compParseTable - Compute the LALR(1) parse table
 *-----------------------------------------------------------------------------
 * The procedure verifies the LALR(1) conditions. If the grammar is
 * LALR(1) tables are generated. The tables are stored in a linear form
 * and where the error entries are omitted. The GOTO and the ACTION table
 * not separeted from each other.
 *-----------------------------------------------------------------------------
 */
static void compParseTable()
{
    Boolean *done;              /* Entry gen.? */
    Boolean lalr1;              /* Condition flag */
    Boolean state_ok;           /* Current state is LALR(1) */
    Boolean resByDefault;       /* Conflicts resolved by default rules? */
    Boolean resByModify;        /* Conflicts resolved by modification? */
    int ent;                    /* Parse table entry */
    int i, j, k;                /* Loop index */

    /* done is initialized to 0 = FALSE
     */
    done = (Boolean *)malloc((termCnt + nonTermCnt + 1) *
                             sizeof(Boolean));
    resByDefault = FALSE;
    resByModify = FALSE;
    lalr1 = TRUE;
    for (i = 1; i <= stateCnt; i++) {
        state_ok = isLalr1(i, &resByDefault, &resByModify);
        compContinuation(i);
        if (contTbl[i].tsym == -1) {
            fprintf(pwsLog,
                    "*******  All transitions on terminals have been removed in state %u\n", i);
            state_ok = FALSE;
        }/*if*/
        if (state_ok) {
            if (getSetOpt(LIST_OPT)>>2 & 1) {
                logItemSet(i, i == 1);
            }/*if*/
        } else {
            if (getSetOpt(LIST_OPT)>>2 & 1) {
                logItemSet(i, i == 1);
            } else {
                logItemSet(i, FALSE);
            }/*if*/
            lalr1 = FALSE;
        }/*if*/
    }/*for*/

    if (lalr1) {
        /* Compute the tables
         */

        /* A C T I O N   T A B L E
         * -----------------------
         *
         *  Row "i" of the ACTION-table is constructed as follows
         *
         *  u = input symbol
         *  i = current state
         *  A = nonterminal
         *  a = string (may be empty)
         *
         *  For all terminal symbol, "u"
         *
         *  1. ACTION[i,u] = SHIFT s
         *  if [A --> a . b] is in the LR(0) item set no "i"
         *  and b = u. "s" is GOTO(i,u).
         *
         *  2. ACTION[i,u] = REDUCE "p"
         *  if [A --> a.] is in the i:th item set and
         *  A --> a is the p:th rule of the grammar, and
         *  "u" is in the look-ahead set for [A --> a.]
         *
         *  3. ACTION[i,u] = SHIFT-REDUCE "p"
         *  if OPTIMIZE(LR0) is demanded and [A --> a . b] is
         *  in the item set and b = u and s = GOTO(i,b)
         *  is a LR(0) reduce state for production "p"
         *
         *  4. ACTION[i,u] = ACCEPT
         *  if u = $ and [SYS --> GOAL.] is in the item set.
         *
         *  5. ACTION[i,u] = ERROR otherwise
         */

        /* NULL pointers are assumed = 0 (value assigned by calloc)
         */
        actTbl = (int **)calloc(stateCnt, sizeof(int *));
        actMax = 0;
        tableFactor = (stateCnt > global_prod_cnt? stateCnt + 1:
                     global_prod_cnt + 1);

        for (i = 1; i <= stateCnt; i++) {
            /* For all states. Note that error entries are assumed to be = 0
             */
            actTbl[i - 1] = (int *)calloc(termCnt, sizeof(int));
            for (j = 1; j <= termCnt; j++) done[j] = FALSE;

            for (j = stateList[i].istart;
                 j < stateList[i].istart + stateList[i].setsz; j++)
                {
                    switch (accItem[j].typ) {

                    case tTrans:    /* SHIFT */
                        if (!done[accItem[j].afterDot]) {
                            if (accItem[j].sr) {
                                ent = (accItem[j].item.prod << 3) + shiftReduce;
                            } else {
                                ent = (accItem[j].succState << 3) + shift;
                            }/*if*/
                            actTbl[i - 1][accItem[j].afterDot - 1] = ent;
                            if (ent > actMax) actMax = ent;
                            done[accItem[j].afterDot] = TRUE;
                        }/*if*/
                        break;

                    case complete:  /* REDUCE or ACCEPT */
                        for (k = 1; k <= termCnt; k++) {
                            if (SetMem(accItem[j].laPtr, k)) {
                                if (!done[k]) {
                                    if (accItem[j].item.prod == 0) {
                                        /* Accept
                                         */
                                        ent = accept;
                                    } else {
                                        ent = (accItem[j].item.prod << 3)
                                            + reduce;
                                    }/*if*/
                                    actTbl[i - 1][k - 1] = ent;
                                    if (ent > actMax) actMax = ent;
                                    done[k] = TRUE;
                                }/*if*/
                            }/*if*/
                        }/*for*/
                        break;

                    case ntTrans:   /* GOTO-table, wait!!! */
                        break;

                    }/*switch*/
                }/*for*/
        }/*for*/

        /* G O T O   T A B L E
         * -------------------
         *
         *   Row "i" of the GOTO-table is constructed as:
         *
         *   For all nonterminal symbols B
         *
         *   1. GOTO[i, B] = GOTO(i,B), the successor state
         *  if [A --> a . B] is in the LR(0) item set.
         *
         *   2. GOTO[i,B] = REDUCE "p"
         *  if s = GOTO(i,B), OPTIMIZE(LR0) is demanded and
         *  s is a LR(0) reduce state, reducing "p"
         *
         *   3. GOTO[i,B] = ERROR  otherwise
         */

        /* NULL pointers are = 0
         */
        gtoTbl = (int **)calloc(stateCnt, sizeof(int *));
        gtoMax = 0;

        for (i = 1; i <= stateCnt; i++) {
            gtoTbl[i - 1] = (int *)calloc(nonTermCnt, sizeof(int));
            for (j = termCnt + 1; j <= termCnt + nonTermCnt;
                 j++)
                {
                    done[j] = FALSE;
                }/*for*/

            for (j = stateList[i].istart;
                 j < stateList[i].istart + stateList[i].setsz; j++)
                {
                    if (accItem[j].typ == ntTrans) {
                        if (!done[accItem[j].afterDot]) {
                            if (accItem[j].sr) {
                                ent = (accItem[j].item.prod << 3) + shiftReduce;
                            } else {
                                ent = (accItem[j].succState << 3) + shift;
                            }/*if*/
                            gtoTbl[i - 1][accItem[j].afterDot - termCnt - 1] =
                                ent;
                            if (ent > gtoMax) gtoMax = ent;
                            done[accItem[j].afterDot] = TRUE;
                        }/*if*/
                    }/*if*/
                }/*for*/
        }/*for*/

        actRowCnt = stateCnt;
        actColCnt = termCnt;
        gtoRowCnt = stateCnt;
        gtoColCnt = nonTermCnt;

        if (resByDefault) pmkLog(NULL, 301, sevWAR, "");
        if (resByModify) pmkLog(NULL, 302, sevINF, "");
    } else {
        /* Grammar not LALR(1)
         */
        pmkLog(NULL, 303, sevERR, "");
    }/*if*/
    free((char *)done);
}/*compParseTable()*/


/*-----------------------------------------------------------------------------
 * nextState - Find the successor state after a transition
 *-----------------------------------------------------------------------------
 */
static int nextState(t, sym)
    int t;              /* IN transition state */
    int sym;            /* IN transition symbol */
    /* RET successor state */
{
    int i;

    for (i = stateList[t].istart;
         i < stateList[t].istart + stateList[t].setsz; i++) {
        if (accItem[i].afterDot == sym) return accItem[i].succState;
    }/*for*/

    return -1;
}/*nextState()*/


/*-----------------------------------------------------------------------------
 * compDontCare - Computes the don't care entries
 *-----------------------------------------------------------------------------
 * Compute the don't care entries of the parse table, i.e. the error
 * entries which are never consulted by the parser, for any input.
 *
 * 1. All error entries in the GOTO table are don't care
 *
 * 2. An error entry in state T of the ACTION table is "essential"
 *    on input symbol "a" iff
 *
 *  -  T is the initial table
 *
 *  -  GOTO(T',b) = T for some T' and terminal b
 *
 *  -  There is a state T' with T in NEXT(T',p) and ACTION[T',a]
 *     is "reduce p".
 *
 *
 * NEXT(T,p) defines the states T', which can be on top of stack after
 * a "reduce p" action in T.
 * Assume that the p:th production is A --> alfa,
 * NEXT(T,p) = GOTO(PRED(T,alfa),A)
 *-----------------------------------------------------------------------------
 */
static void compDontCare()
{
    int i, j, k;
    SETPTR essentialPtr;
    SETPTR dontPtr;
    Boolean *done;
    PredItem *tp;
    int next;

    dontCare = (SETPTR *)calloc(stateCnt + 1, sizeof(SETPTR));
    essentialPtr = (SETPTR)malloc(SETLEN(termCnt + 1));
    SetClear(essentialPtr, termCnt + 1);
    done = (Boolean *)malloc((stateCnt + 1) * sizeof(Boolean));

    for (i = 1; i <= stateCnt; i++) {
        dontCare[i] = essentialPtr;
        if (gotoOnTerm[i]) done[i] = TRUE;
        else done[i] = FALSE;
    }/*for*/

    done[0] = TRUE;
    done[1] = TRUE;

    for (i = 2; i <= stateCnt; i++) {
        for (j = stateList[i].istart;
             j < stateList[i].istart + stateList[i].setsz; j++)
            {
                if ((accItem[j].typ == complete) && (accItem[j].item.prod != 0 )) {
                    tp = accItem[j].predList;
                    while (tp) {
                        next = nextState(tp->pred, global_pvec_tbl[global_prod_tbl[
                                                                                   accItem[j].item.prod]->start]);
                        if (!done[next]) {
                            dontPtr = (SETPTR)malloc(SETLEN(termCnt + 1));
                            SetClear(dontPtr, termCnt + 1);
                            for (k = 1; k <= termCnt; k++) {
                                if ((actTbl[next - 1][k - 1] & 07) == error &&
                                    !SetMem(accItem[j].laPtr, k))
                                    {
                                        SetIns(dontPtr, k);
                                    }/*if*/
                            }/*for*/

                            dontCare[next] = dontPtr;
                        }/*if*/

                        done[next] = TRUE;
                        tp = tp->nxt;
                    }/*while*/
                } else {
                    break;
                }/*if*/
            }/*for*/
    }/*for*/
    free((char *)done);
}/*compDontCare()*/


/*-----------------------------------------------------------------------------
 * pwGenTab - Generate the tables
 *-----------------------------------------------------------------------------
 */
void pwGenTab()
{
    compAccItemSet();
    if (!SeriousErr) {
        compLaSet();
        compParseTable();
        if (!SeriousErr) {
            compDontCare();
            logParseTables();
            logGeStats();
        }/*if*/
    }/*if*/

    if (stateList) free((char *)stateList);
    if (coreLen) free((char *)coreLen);
    if (accItem) free((char *)accItem);
    if (gotoOnTerm) free((char *)gotoOnTerm);
}/*pwGenTab()*/
