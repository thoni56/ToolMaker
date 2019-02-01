/*-----------------------------------------------------------------------------
 * pwsGrm - Grammar analysis and AST building functions
 *		@(#)pwsGrm.c	1.2 (90/11/07 14:13:58)
 *-----------------------------------------------------------------------------
 * Created:	89-08-01 by Arash
 * Modified:	90-04-18 by Tom. EBNF attribute bug fixed. put_code & calls
 *				 removed (no pmLength support).
 *-----------------------------------------------------------------------------
 * Entries:								     
 *	?????
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef WIN32
#include <io.h>
#endif
#include "pmk_i.h"
#include "pmkList.h"
#include "pwsGrm.h"
#include "pwsLexCode.h"
#include "pwsQueue.h"
#include "pwsOrd.h"
#include "pwsWrit.h"

int orig_prod_max;		/* Max. number of EBNF productions */
int prod_max;			/* Max. number of BNF productions */
int sym_max;			/* Max. number of symbols */

int pvec_sz;			/* Size of production array */
int action_max;			/* Max. number of actions */
int att_max;			/* Number of attribute references */


/* Vocabulary
 * ----------
 */
sym_ref *vocabulary;		/* Vocabulary */
int vocCnt;			/* Number of symbols in vocabulary */
int termCnt;			/* Number of terminals */
int nonTermCnt;			/*Number of non terminals */
int attrCnt;			/* Number of attributes */
int gramSymCnt;			/* Number of terminals + non terminals */
int goal_sym;			/* Goal symbol */
int tc_val = 0;			/* Highest terminal code value */
SymSet on_right;		/* Set of symbols ocurring on rhs */
int gen_nonterms_cnt;		/* Number of generated non terminals */
Boolean term_sec_given;		/* Terminal section flag */
int icostMax;			/* Max insertion cost */
int dcostMax;			/* Max deletion cost */

/* Error Recovery
 * --------------
 */
recovery_rec recovery_spec;	/* Improvments of the recovery */


/* Productions
 * -----------
 */
pvec_arr_typ global_pvec_tbl;	/* Storage for the grammar */
int global_pvec_ptr;		/* Grammar storage pointer */
prod_rec **global_prod_tbl;	/* Production data */
int global_prod_cnt;		/* Production data */
int rsszMax;			/* Max size of right hand side */

prod_elnode **orig_prod_tbl;	/* Abstract syntax trees for productions */
int orig_prod_cnt;		/* Number of original Productions */

/* Actions
 * -------
 */
SemActRepr *semAct;		/* Semantic actions */
int semActCnt;			/* Number of semantic actions */
attref_rec_arr attref_storage;	/* Storage for attribute references */
				/* temporary */
attref *global_attref_sto;	/* Final attribute reference storage */
int attref_cnt;
int global_attref_cnt;		/* Number of correct attribute */
				/* references. */

/* Allocation routines
 * -------------------
 */

static prod_rec *prod_recAlloc()
{
    prod_rec *temp;

    temp = (prod_rec *)malloc(sizeof(prod_rec));
    if (temp == NULL) pmkLog(NULL, 201, sevFAT, "");
    else {
	temp->start = -1;
	temp->nxtls = -1;
	temp->rssz = -1;
	temp->orig = -1;
	temp->modify = NULL;
	temp->actno = -1;
	temp->orig_prod = -1;
	return(temp);
    }/*if*/
}/*prod_recAlloc()*/

altr_lst *altr_lstAlloc()
{
    altr_lst *temp;

    temp = (altr_lst *)malloc(sizeof(altr_lst));
    if (temp == NULL) pmkLog(NULL, 204, sevFAT, ""); 
    else {
	temp->nxtalt = NULL;
	return(temp);
    }/*if*/
}/*altr_lstAlloc()*/

prod_elnode *prod_elnodeAlloc()
{
    prod_elnode *temp;

    temp = (prod_elnode *)malloc(sizeof(prod_elnode));
    if (temp == NULL) pmkLog(NULL, 204, sevFAT, "");
    else {
	temp->nxtnode = NULL;
	return(temp);
    }/*if*/
}/*prod_elnodeAlloc()*/

rhs_node *rhs_nodeAlloc()
{
    rhs_node *temp;

    temp = (rhs_node *)malloc(sizeof(rhs_node));
    if (temp == NULL) pmkLog(NULL, 204, sevFAT, "");
    else{
	temp->rhs = NULL;
	temp->nxtrhs = NULL;
	return(temp);
    }/*if*/
}/*rhs_nodeAlloc()*/

modify_ref modify_recAlloc()
{
    modify_ref temp;

    temp = (modify_ref)malloc(sizeof(modify_rec));
    if (temp == NULL) pmkLog(NULL, 205, sevFAT, "");
    else {
	temp->red = NULL;
	temp->nored = NULL;
	return(temp);
    }/*if*/
}/*modify_recAlloc()*/

static attref_rec *attref_recAlloc()
{
    attref_rec *temp;

    temp = (attref_rec *)malloc(sizeof(attref_rec));
    if (temp == NULL) pmkLog(NULL, 206, sevFAT, "");
    else {
	temp->ruleno = -1;
	temp->actno = -1;
	temp->voc_sym = -1;
	temp->pos = -1;
	temp->symins = -1;
	temp->att = -1;
	temp->no_errm = FALSE;
	return(temp);
    }/*if*/
}/*attref_recAlloc()*/

/*------------------End of allocation routines---------------------*/


/*-----------------------------------------------------------------------------
 * incAttrefCnt - Increment the number of attribute references
 *-----------------------------------------------------------------------------
 */
static void incAttrefCnt()
{
    attref_cnt++;
    if (attref_cnt == att_max) {
	att_max *= 2;
	attref_storage = (attref_rec **)realloc(attref_storage,
					       att_max * sizeof(attref_rec *));
    }/*if*/
}/*incAttrefCnt()*/


/*-----------------------------------------------------------------------------
 * incSemActCnt - increments semantic action counter
 *-----------------------------------------------------------------------------
 */
static void incSemActCnt()
{
    semActCnt++;    
    if (semActCnt == action_max) {
	action_max *= 2;
	semAct =
	    (SemActRepr *)realloc(semAct, action_max * sizeof(SemActRepr));
    }/*if*/
}/*incSemActCnt()*/


/*-----------------------------------------------------------------------------
 * init_action_structs - allocates semAct, attref_storage
 *                       if build or generate option is given.
 *-----------------------------------------------------------------------------
 */
void init_action_structs(build_or_generate)
Boolean build_or_generate;
{
    if (!build_or_generate) {
	semAct = NULL;
	attref_storage = NULL;
    } else {
	action_max = 200;
	semAct = (SemActRepr *)calloc(action_max, sizeof(SemActRepr));
	if (semAct == NULL) pmkLog(NULL, 207, sevFAT, "");
	else {
	    semActCnt = -1;
	    att_max = 500;
	    attref_storage =
		(attref_rec **)calloc(att_max, sizeof(attref_rec *));
	    if (attref_storage == NULL) pmkLog(NULL, 208, sevFAT, "");
	    else attref_cnt = -1;
	}/*if*/
    }/*if*/
}/*init_action_structs()*/


/*-----------------------------------------------------------------------------
 * init_grm - allocates and initiates vocabulary,
 *            global_prod_tbl,global_pvec_tbl,orig_prod_tbl,
 *            (and their counters) also on_right, gen_nonterms
 *            tc_val. Symbols for augmenting the grammar is
 *            inserted in vocabulary in initSymTab.
 *-----------------------------------------------------------------------------
 * init_hash_sym_tbl must be called after init_grm because symbol table
 * structure is not allocated before.
 *-----------------------------------------------------------------------------
 */
void init_grm()
{
    sym_max = 1023;
    vocabulary = (sym_ref *)calloc(sym_max, sizeof(sym_ref));
    icostMax = 1;
    dcostMax = 1;

    prod_max = 250;
    global_prod_tbl = (prod_rec **)calloc(prod_max, sizeof(prod_rec *));
    global_prod_tbl[0] = prod_recAlloc();
    global_prod_tbl[0]->start = 1;
    global_prod_tbl[0]->rssz = 1;
    global_prod_tbl[0]->orig = 0;
    global_prod_cnt = 0;
    rsszMax = 1;

    pvec_sz = 800;
    global_pvec_tbl = (int *)calloc(pvec_sz, sizeof(int));
    global_pvec_tbl[1] = 0;
    global_pvec_ptr = 2;
    tc_val = 1;
    orig_prod_max = 250;
    orig_prod_tbl =
	(prod_elnode **)calloc(orig_prod_max, sizeof(prod_elnode *));
    orig_prod_cnt = -1;
    on_right = SymSetAlloc();
    gen_nonterms_cnt = 0;
}/*init_grm()*/


/*-----------------------------------------------------------------------------
 * gensym - Generates a new unique symbol %%genSym#(gen_nonterms_cnt)
 *-----------------------------------------------------------------------------
 */
char *gensym()
{
    char *temp;

    temp = (char *)malloc(14);
    if (temp == NULL) pmkLog(NULL, 209, sevFAT, "");
    else {
	sprintf(temp, "__genSym#%u", gen_nonterms_cnt++);
	return temp;
    }/*if*/
}/*gensym()*/


/*-----------------------------------------------------------------------------
 * gen_node - generates a symbol node (with a new symbol).
 *-----------------------------------------------------------------------------
 */

static prod_elnode *gen_node()
{
    SETDEF(sym_kind_set, unknown_symb + 1);
    prod_elnode *temp;
    int temp_reff;
    search_kind temp_search;

    temp = prod_elnodeAlloc();
    SetClear(sym_kind_set, unknown_symb + 1);
    SetIns(sym_kind_set, nts_symb);
    lookup(gensym(), sym_kind_set, &temp_reff, &temp_search);
    vocabulary[temp_reff]->symbol_typ = nts_symb;
    vocabulary[temp_reff]->syminfo.firstp = -1;
    SymSetIns(on_right, temp_reff);
    temp->node_kind = sym_node_kind;
    temp->node_info.sym_node.sym_ind = temp_reff;
    temp->node_info.sym_node.newnont = TRUE;
    temp->node_info.sym_node.rplc_info = act_rplc;
    return(temp);
}/*gen_node()*/


/*-----------------------------------------------------------------------------
 * add_to_pvec  - adds one symbol to the production vector
 *-----------------------------------------------------------------------------
 */
static void add_to_pvec(symnode)
prod_elnode *symnode;
{
    global_pvec_ptr++;
    if (global_pvec_ptr == pvec_sz) {
	pvec_sz *= 2;
	global_pvec_tbl =
	    (int *)realloc(global_pvec_tbl, pvec_sz * sizeof(int));
    }/*if*/
    global_pvec_tbl[global_pvec_ptr] = symnode->node_info.sym_node.sym_ind;
}/*add_to_pvec()*/


/*-----------------------------------------------------------------------------
 * incProdCnt  - increments production counter
 *-----------------------------------------------------------------------------
 */
static void incProdCnt()
{
    global_prod_cnt++;
    if (global_prod_cnt == prod_max) {
	prod_max *= 2;
	global_prod_tbl = (prod_rec **)realloc(global_prod_tbl,
					       prod_max * sizeof(prod_rec *));
    }/*if*/
}/*incProdCnt()*/


/*-----------------------------------------------------------------------------
 * incOrigProdCnt  - increments original production counter
 *-----------------------------------------------------------------------------
 */
static void incOrigProdCnt()
{
    orig_prod_cnt++;    
    if (orig_prod_cnt == orig_prod_max) {
	orig_prod_max *= 2;
	orig_prod_tbl = (prod_elnode **)realloc(orig_prod_tbl,
	    orig_prod_max * sizeof(prod_elnode *));
    }/*if*/
}/*incOrigProdCnt()*/


#ifdef USE_PUTCODE
/*-----------------------------------------------------------------------------
 * put_code  - writes code necessary for counting length of
 *             repetition constructs ( { a b c } ).
 *-----------------------------------------------------------------------------
 */
static void put_code(code_type, sym_ind)
action_analysis_kind code_type;  
int sym_ind;			/* Symbol pmLength to be associated with */
{
    SETDEF(sym_kind_set, unknown_symb + 1);
    int actI;
    static int temp_reff;
    int temp_search;
    static Boolean pmLength_looked_up = FALSE;
    static TmkSrcp lastSrcp = {0, 0}; /* Dummy source position */


    if (semAct[semActCnt].act) {
	actI = strlen(semAct[semActCnt].act);
	semAct[semActCnt].act = (char *)realloc(semAct[semActCnt].act,
					actI + 11);
    } else {
	actI = 0;
	semAct[semActCnt].act = (char *)malloc(11);
    }/*if*/

    if (!pmLength_looked_up) {
	SetClear(sym_kind_set, unknown_symb + 1);
	SetIns(sym_kind_set, attr_symb);
	lookup("pmLength", sym_kind_set, &temp_reff, &temp_search);
	if (new_search == temp_search) {
	    vocabulary[temp_reff]->symbol_typ = attr_symb;
	    vocabulary[temp_reff]->syminfo.attr_class = voc_attr;
	} else if (confl_search == temp_search) {
	    pmkLog(NULL, 157, sevERR, "");
	}/*if*/
	pmLength_looked_up = TRUE;
    }/*if*/

    if (code_type == rept_first || code_type == rept_second) {
	incAttrefCnt();
	attref_storage[attref_cnt] = attref_recAlloc();
	attref_storage[attref_cnt]->ruleno = global_prod_cnt;
	attref_storage[attref_cnt]->actno = semActCnt;
	attref_storage[attref_cnt]->actPos = actI + 1;
	attref_storage[attref_cnt]->voc_sym = sym_ind;
	attref_storage[attref_cnt]->att = temp_reff;
	attref_storage[attref_cnt]->pos = 0;
	attref_storage[attref_cnt]->symins = 1;
	attref_storage[attref_cnt]->attref_srcp = lastSrcp;
	if ((strcmp(pmkTarget, "C")) || (strcmp(pmkTarget, "c"))) {
	    strcat(semAct[semActCnt].act, " = ");
	    actI += 3;
	} else {
	    strcat(semAct[semActCnt].act, " := ");
	    actI += 4;
	}/*if*/
	if (code_type == rept_first) {
	    incAttrefCnt();
	    attref_storage[attref_cnt] = attref_recAlloc();
	    attref_storage[attref_cnt]->ruleno = global_prod_cnt;
	    attref_storage[attref_cnt]->actno = semActCnt;
	    attref_storage[attref_cnt]->actPos = actI;
	    attref_storage[attref_cnt]->voc_sym = sym_ind;
	    attref_storage[attref_cnt]->att = temp_reff ;
	    attref_storage[attref_cnt]->pos = 1;
	    attref_storage[attref_cnt]->symins = 2;
	    attref_storage[attref_cnt]->attref_srcp = lastSrcp;
	    strcat(semAct[semActCnt].act, " + 1;");
	} else {
	    strcat(semAct[semActCnt].act, " 0;");
	}/*if*/
    } /*if*/
}/*put_code()*/
#endif


/*-----------------------------------------------------------------------------
 * verify_insert_ref  - creates attribute referenece structure
 *                      and verifies references to EBNF and OEBNF
 *                      constructs. Other references will be
 *                      verified in pwsOrd.c
 *                      All references are indicated by #% in
 *                      pwsTempCodefile.
 *-----------------------------------------------------------------------------
 */
static void verify_insert_ref(lhs, rhs, actPos, inst, symstr, attrstr,
			      analysis, srcp)
prod_elnode *lhs;		/* lhs symbol node */
prod_elnode *rhs;		/* rhs sequence */
int actPos;			/* IN position of reference in action */
int inst;			/* given instance */
char *symstr;			/* symbol's string */
char *attrstr;			/* attribute's string */
action_analysis_kind analysis;	/* Type of legal reference to OEBNF. */
TmkSrcp srcp;			/* Reference source pos */
{
    char *ebnf_ref_upp = "EBNF";
    char *ebnf_ref_low = "ebnf";
    char *o_ebnf_ref_upp = "OEBNF";
    char *o_ebnf_ref_low = "oebnf";
    Boolean ebnf;
    Boolean outer_ebnf;
    int pos;
    int loc_inst;
    prod_elnode *curr_node;
    int temp_reff;
    int temp_reff1;
    search_kind temp_search;
    SETDEF(sym_kind_set, unknown_symb + 1);
    attr_kind att_kind;

    /* Test whether symbol is (O)EBNF
     */
    ebnf = (strcmp(symstr, ebnf_ref_low) == 0 ||
	    strcmp(symstr, ebnf_ref_upp) == 0);
    outer_ebnf = (strcmp(symstr, o_ebnf_ref_low) == 0 ||
		  strcmp(symstr, o_ebnf_ref_upp) == 0);

    if (attrstr) {
	/* Look up attribute symbol
	 */
	SetClear(sym_kind_set, unknown_symb + 1);
	SetIns(sym_kind_set, attr_symb);
	lookup(attrstr, sym_kind_set, &temp_reff, &temp_search);
    } else {
	/* No attribute section given, ignore attribute symbol
	 */
	temp_reff = -1;
	temp_search = found_search;
    }/*if*/

    if (temp_search == confl_search) {
	pmkLog(&srcp, 118, sevERR, attrstr);
    } else {
	if (temp_search == new_search) {
	    pmkLog(&srcp, 150, sevERR, attrstr);
	    vocabulary[temp_reff]->symbol_typ = attr_symb;
	    att_kind = unk_attr;
	} else if (temp_reff != -1) {
	    att_kind = vocabulary[temp_reff]->syminfo.attr_class;
	} else {
	    att_kind = unk_attr;
	}/*if*/

	if (!ebnf && !outer_ebnf) {
	    /* Reference to a user symbol's attr
	     */
	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, t_symb);
	    SetIns(sym_kind_set, nts_symb);
	    lookup(symstr, sym_kind_set, &temp_reff1, &temp_search);
	    if (temp_search != confl_search) {
		incAttrefCnt();
		attref_storage[attref_cnt] = attref_recAlloc();
		attref_storage[attref_cnt]->ruleno = global_prod_cnt;
		attref_storage[attref_cnt]->actno = semActCnt;
		attref_storage[attref_cnt]->actPos = actPos;
		attref_storage[attref_cnt]->voc_sym = temp_reff1;
		attref_storage[attref_cnt]->att = temp_reff;
		attref_storage[attref_cnt]->no_errm = FALSE;
		attref_storage[attref_cnt]->pos = -1;
		attref_storage[attref_cnt]->symins = inst;
		attref_storage[attref_cnt]->attref_srcp = srcp;
	    } else {
		pmkLog(&srcp, 115, sevERR, symstr);
	    }/*if*/
	} else {
	    if (outer_ebnf) {
		/* Reference to OEBNF's attr
		 */
		switch(analysis) {

		case top:
		    pmkLog(&srcp, 151, sevERR, "");
		    break;

		case rept_first:
		    if (att_kind != t_attr) {
			incAttrefCnt();
			attref_storage[attref_cnt] = attref_recAlloc();
			attref_storage[attref_cnt]->ruleno = global_prod_cnt;
			attref_storage[attref_cnt]->actno = semActCnt;
			attref_storage[attref_cnt]->actPos = actPos;
			attref_storage[attref_cnt]->voc_sym =
			    lhs->node_info.sym_node.sym_ind;
			attref_storage[attref_cnt]->att = temp_reff;
			if (inst != 1 && inst != 2) { 
			    pmkLog(&srcp, 153, sevERR, "");
			    /* assume first instance
			     */
			    attref_storage[attref_cnt]->pos = 0;
			    attref_storage[attref_cnt]->symins = 1;
			} else {
			    attref_storage[attref_cnt]->pos = inst - 1;
			    attref_storage[attref_cnt]->symins = inst;
			}/*if*/
			attref_storage[attref_cnt]->no_errm = TRUE;
			attref_storage[attref_cnt]->attref_srcp = srcp;
		    } else if (att_kind == t_attr) {
			pmkLog(&srcp, 152, sevERR, attrstr);
		    }/*if*/
		    break;
	
		default:
		    if (att_kind != t_attr) {
			incAttrefCnt();
			attref_storage[attref_cnt] = attref_recAlloc();
			attref_storage[attref_cnt]->ruleno = global_prod_cnt;
			attref_storage[attref_cnt]->actno = semActCnt;
			attref_storage[attref_cnt]->actPos = actPos;
			attref_storage[attref_cnt]->voc_sym =
			    lhs->node_info.sym_node.sym_ind;
			attref_storage[attref_cnt]->att = temp_reff;
			if (inst != 1) pmkLog(&srcp, 153, sevERR, "");
			attref_storage[attref_cnt]->pos = 0;
			attref_storage[attref_cnt]->symins = 1;
			attref_storage[attref_cnt]->no_errm = TRUE;
			attref_storage[attref_cnt]->attref_srcp = srcp;
		    } else if (att_kind == t_attr) {
			pmkLog(&srcp, 152, sevERR, attrstr);
		    }/*if*/
		    break;

		}/*switch*/
	    } else if (ebnf) {
		/* Reference to EBNF, verify instance
		 */
		curr_node = rhs;     
		pos = 1;
		loc_inst = 0;
		while(curr_node != NULL &&
		      curr_node->node_kind != mod_node_kind &&
		      curr_node->node_kind != null_node_kind &&
		      curr_node->node_kind != act_node_kind )
		{
		    if (curr_node->node_info.sym_node.newnont &&
			curr_node->node_info.sym_node.rplc_info != act_rplc)
		    {
			loc_inst++;
			if (inst == loc_inst) {
			    if (att_kind != t_attr) {
				incAttrefCnt();
				attref_storage[attref_cnt] = attref_recAlloc();
				attref_storage[attref_cnt]->ruleno =
				    global_prod_cnt;
				attref_storage[attref_cnt]->actno = semActCnt;
				attref_storage[attref_cnt]->actPos = actPos;
				attref_storage[attref_cnt]->voc_sym =
				    curr_node->node_info.sym_node.sym_ind;
				attref_storage[attref_cnt]->att = temp_reff;
				attref_storage[attref_cnt]->pos = pos;
				/* attref_storage[attref_cnt]->symins = inst;*/
				attref_storage[attref_cnt]->symins = 1;
				attref_storage[attref_cnt]->no_errm = TRUE;
				attref_storage[attref_cnt]->attref_srcp = srcp;
			    } else {
				pmkLog(&srcp, 152, sevERR, attrstr);
			    }/*if*/
			    break;
			}/*if*/
		    }/*if*/
		    curr_node = curr_node->nxtnode;
		    pos++;
		}/*while*/
		if (loc_inst == 0) pmkLog(&srcp, 153, sevERR, "");
		else if (loc_inst != inst) pmkLog(&srcp, 156, sevERR, "");
	    }/*if*/
	}/*if*/
    }/*if*/
}/*verify_insert_ref()*/


/*-----------------------------------------------------------------------------
 * copy_action - processes a semantic action from the grammar file and
 *		 verifies all attribute references.
 *-----------------------------------------------------------------------------
 */
static void copy_action(lhs, rhs, analysis, start, length, srcp)
prod_elnode *lhs;               /* lhs symbol node */
prod_elnode *rhs;               /* rhs sequence */
action_analysis_kind analysis;	/* passed to verify_insert_ref */
long start;			/* action's start pos in grammar file */
long length;			/* length of action */
TmkSrcp *srcp;			/* action's source pos */
{
    char inststr[5];
    char symstr[81];
    char attrstr[81];
    int actI = 0;
    int inst;
    char c;
    int j;
    long i = 0;
    Boolean ang_br_str;
    Boolean q_str;
    TmkSrcp attr_srcp;


    lseek(pwsGrm, start, 0);
    srcp->col += 2;
    semAct[semActCnt].act = (char *)malloc(length + 1);
    semAct[semActCnt].line = srcp->line;

    while (i < length) {
	read(pwsGrm, &c, 1);
	i++;
	if (c == '\n') {
	    srcp->line++;
	    srcp->col = 0;
	} else {
	    srcp->col++;
	}/*if*/

	switch(c) {

	case '%':
	    /* Scan instance integer
	     */
            read(pwsGrm, &c, 1);
	    i++;
	    if (c == '\n') {
		srcp->line++;
		srcp->col = 0;
	    } else {
		srcp->col++;
	    }/*if*/
	    attr_srcp = *srcp;
	    if (isdigit(c)) {
		j = 0;
		while (isdigit(c) && i <= length) {
		    inststr[j++] = c;
		    read(pwsGrm, &c, 1);
		    i++;
		    if (c == '\n') {
			srcp->line++;
			srcp->col = 0;
		    } else {
			srcp->col++;
		    }/*if*/
		}/*while*/
		if (i > length) pmkLog(srcp, 155, sevERR, "Vocabulary symbol");
		else {
		    inststr[j] = '\0';
		    inst = atoi(inststr);
		}/*if*/
	    } else {
		/* No instance number given, assume first instance
		 */
		inst = 1;
	    }/*if*/

	    /* Scan a vocabulary symbol (O)EBNF */
	    ang_br_str = FALSE;
	    q_str = FALSE;
	    if (isalpha(c) || c == '\'' || c == '<') {
		if (c == '<') ang_br_str = TRUE;
		else if (c == '\'') q_str = TRUE;
		j = 0;
		while ((c == '_' || isalnum(c) || ang_br_str || q_str) &&
		       i <= length)
		{
		  if (j<=80) symstr[j++] = c;
		  read(pwsGrm, &c, 1);
		  i++;
		  if (c == '\n') {
		    srcp->line++;
		    srcp->col = 0;
		  } else {
		    srcp->col++;
		  } /*if*/

		  if (q_str && c == '\'') {
		    read(pwsGrm, &c, 1);
		    i++;
		    srcp->col++;
		    if (c != '\'') {
		      symstr[j++] = '\'';
		      break;
		    } /*if*/
		  } /*if*/

		  if (ang_br_str && c == '>') {
		    if (i <= length) {
		      symstr[j++] = c;
		      read(pwsGrm, &c, 1);
		      i++;
		      if (c == '\n') {
			srcp->line++;
			srcp->col = 0;
		      } else {
			srcp->col++;
		      }	/*if*/
		      break;
		    } /*if*/
		  } /*if*/
		} /*while*/

		symstr[j] = '\0';

		if (i > length || c != '.') {
		  pmkLog(srcp, 155, sevERR, "'.'");
		} else {
		  /* Scan an attribute symbol
		   */
		  read(pwsGrm, &c, 1);
		  i++;
		  if (c == '\n') {
		    srcp->line++;
		    srcp->col = 0;
		  } else {
		    srcp->col++;
		  }/*if*/
		  if ((isalpha(c) || c == '_') && i <= length) {
		    j = 0;
		    while ((isalnum(c) || c == '_') && i <= length) {
		      if (j<=80) attrstr[j++] = c;
		      read(pwsGrm, &c, 1);
		      i++;
		      if (c == '\n') {
			srcp->line++;
			srcp->col = 0;
		      } else {
			srcp->col++;
		      }/*if*/
		    }/*while*/
		    attrstr[j] = '\0';
		    verify_insert_ref(lhs, rhs, actI, inst, symstr,
				      attrstr, analysis, attr_srcp);
		    semAct[semActCnt].act[actI++] = c;
		  } else {
		    pmkLog(srcp, 155, sevERR, "Attribute");
		  }/*if*/
		}/*if*/
	      } else {
		pmkLog(srcp, 155, sevERR, "Vocabulary symbol or (O)EBNF");
	      }/*if*/
	    break;

	default:
	    /* Copy characters in action
	     */
	    if (c == pmkEscape) {
		read(pwsGrm, &c, 1);
		i++;
		if (c == '\n') {
		    srcp->line++;
		    srcp->col = 0;
		} else {
		    srcp->col++;
		}/*if*/
		if (i <= length) semAct[semActCnt].act[actI++] = c;
	    } else if (i <= length) {
		semAct[semActCnt].act[actI++] = c;
	    }/*if*/

	}/*switch*/
    }/*while*/
    semAct[semActCnt].act[actI] = '\0';
}/*copy_action()*/


/*-----------------------------------------------------------------------------
 * process_modifiers_actions - merges modifiers and actions associated with
 *			       a production (at the end), also calls
 *                             copy_action and put_code.
 *-----------------------------------------------------------------------------
 */
static void process_modifiers_actions(action_analysis, rhs, lhs)
action_analysis_kind action_analysis; /* passed to copy_action */
prod_elnode *rhs;		/* rhs sequence */
prod_elnode *lhs;		/* lhs symbol node */
{
    prod_elnode *curr_node;
    Boolean action_found = FALSE;

    curr_node = rhs;

    do {
	/* Merge and insert modifiers sets
	 */
        if (curr_node->node_kind == mod_node_kind) { 
	    if (global_prod_tbl[global_prod_cnt]->modify == NULL) {
		global_prod_tbl[global_prod_cnt]->modify =
		    curr_node->node_info.modify_node;
	    } else {
		if (curr_node->node_info.modify_node->red != NULL) {
		    if (global_prod_tbl[global_prod_cnt]->modify->red ==
			NULL)
		    {
			global_prod_tbl[global_prod_cnt]->modify->red =
			    curr_node->node_info.modify_node->red;
		    } else {
			SymSetUnion(curr_node->node_info.modify_node->red,
			    global_prod_tbl[global_prod_cnt]->modify->red,
			    global_prod_tbl[global_prod_cnt]->modify->red);
		    }/*if*/
		}/*if*/

		if (curr_node->node_info.modify_node->nored != NULL) {
		    if (global_prod_tbl[global_prod_cnt]->modify->nored ==
			NULL)
		    {
			global_prod_tbl[global_prod_cnt]->modify->nored =
			    curr_node->node_info.modify_node->nored;
		    } else {
			SymSetUnion(curr_node->node_info.modify_node->nored,
			    global_prod_tbl[global_prod_cnt]->modify->nored,
			    global_prod_tbl[global_prod_cnt]->modify->nored);
		    }/*if*/
		}/*if*/
	    }/*if*/
	} else if (curr_node->node_kind == act_node_kind) {
	    /* Handle action nodes
	     */
	    if (semAct) {
		/* Generate or build option is given
		 */
		if (!action_found) {
		    /* Merge contiguous actions
		     */
		    incSemActCnt();
		    semAct[semActCnt].prod = global_prod_cnt;
		    global_prod_tbl[global_prod_cnt]->actno = semActCnt;
		    action_found = TRUE;
		}/*if*/
		curr_node->node_info.act_node.ass_actno = semActCnt;
		copy_action(lhs, rhs, action_analysis,
			    curr_node->node_info.act_node.act_start,
			    curr_node->node_info.act_node.act_length,
			    &curr_node->node_info.act_node.act_srcp);
	    }/*if*/
	}/*if*/

	curr_node = curr_node->nxtnode;	/* Skip symbol nodes */
    } while (curr_node);

    if (action_found && semAct) {
	/* Code for incrementing pmLength
	 */
/*	put_code(action_analysis, lhs->node_info.sym_node.sym_ind); */
    }/*if*/
}/*process_modifiers_actions()*/

    
/*-----------------------------------------------------------------------------
 * insert_pvec-prod - inserts a production in production vector,
 *                    also enqueues symbol nodes which are
 *                    replaced for an EBNF construct for further
 *                    processing. Note that a pointer
 *                    to replaced sequence is avaiable in the
 *                    symbol node.
 *-----------------------------------------------------------------------------
 */
static void insert_pvec_prod(lhs, rhs)
prod_elnode *rhs;		/* rhs of production */
prod_elnode *lhs;		/* lhs of production */
{
    int curr_rssz;
    int prev;

    incProdCnt();
    global_prod_tbl[global_prod_cnt] = prod_recAlloc();

    /* Find previous rule with same lhs
     */
    prev = vocabulary[lhs->node_info.sym_node.sym_ind]->syminfo.firstp;
    if (prev != -1) {
	while (global_prod_tbl[prev]->nxtls != -1) {
	    prev = global_prod_tbl[prev]->nxtls;
	}/*while*/
	global_prod_tbl[prev]->nxtls = global_prod_cnt;
    } else {
	vocabulary[lhs->node_info.sym_node.sym_ind]->syminfo.firstp =
	    global_prod_cnt;
    }/*if*/
    curr_rssz = 0;
    add_to_pvec(lhs);
    global_prod_tbl[global_prod_cnt]->start = global_pvec_ptr;
    global_prod_tbl[global_prod_cnt]->orig_prod = orig_prod_cnt;

    do {
	/* Walk thourogh production enqueue replaced symbol nodes
	 */
	if (rhs->node_kind == act_node_kind ||
	    rhs->node_kind == mod_node_kind ||
	    rhs->node_kind == null_node_kind)
	{
	    /* End of production. Note that in this stage
	     * there are no actions in the node sequeuce,
	     * but in the replaced sequences.
	     */
	    break;
	}/*if*/

	if (rhs->node_info.sym_node.newnont) {

	    switch(rhs->node_info.sym_node.rplc_info) {

	    case altrs_rplc:
		enqueue(rhs, altrs_analysis);
		break;

	    case rept_rplc:
		enqueue(rhs, rept_analysis);
		break;
	    }/*switch*/
	}/*if*/

	add_to_pvec(rhs);
	curr_rssz++;
	rhs = rhs->nxtnode;
    } while (rhs != NULL);

    global_prod_tbl[global_prod_cnt]->rssz = curr_rssz;
    if (curr_rssz > rsszMax) rsszMax = curr_rssz;
}/*insert_pvec_prod()*/


/*-----------------------------------------------------------------------------
 * sem_act_cut - Removes semantic actions and modifiers embedded in rules by
 *		 creating new empty rules and associating the actions and
 *		 modifiers with the new rules.
 *-----------------------------------------------------------------------------
 */
static void sem_act_cut(rhs_p)
prod_elnode **rhs_p;		/* INOUT rhs to be analyzed */
{
    prod_elnode *curr_node;
    prod_elnode *temp;
    prod_elnode *rhs;

    curr_node = *rhs_p;
    rhs = NULL;

    while (curr_node->nxtnode) {

	if (curr_node->node_kind == act_node_kind ||
	    curr_node->node_kind == mod_node_kind)
	{
	    /* Look for all contiguous actions and modifiers
	     */
	    while (curr_node->nxtnode &&
		   (curr_node->nxtnode->node_kind == act_node_kind ||
		    curr_node->nxtnode->node_kind == mod_node_kind))
	    {
		curr_node = curr_node->nxtnode;
	    }/*while*/
	    if (curr_node->nxtnode) {
		/* The sequence of actions and modifiers are not located last
		 * in the rule so we have to create a new empty rule and
		 * place the sequence of actions and modifiers in the new rule
		 */
		temp = gen_node();
		temp->nxtnode = curr_node->nxtnode;
		if (rhs) {
		    /* The sequence of actions and modifiers are not located
		     * first in the rule, just rearrange links
		     */
		    temp->node_info.sym_node.rplc_seq = rhs->nxtnode;
		    rhs->nxtnode = temp;
		} else {
		    /* The sequence of actions and modifiers are located
		     * first in the rule, return the newly created rule
		     */
		    temp->node_info.sym_node.rplc_seq = *rhs_p;
		    *rhs_p = temp;
		}/*if*/
		curr_node->nxtnode = NULL;
		curr_node = temp;
		enqueue(temp, sem_act_analysis);
	    } else {
		/* End of the rule
		 */
		break;
	    }/*if*/
	}/*if*/
	rhs = curr_node;
	curr_node = curr_node->nxtnode;
    }/*while*/
}/*sem_act_cut()*/


/*-----------------------------------------------------------------------------
 * queue_analyze - analyzes queued symbol nodes and creates new
 *                 nodes according to the second argument.
 *-----------------------------------------------------------------------------
 */
static void queue_analyze(lhs, analysis)
prod_elnode *lhs;		/* symbol node replaced for a normal */
				/* sequeuce of symbol nodes (because */
				/* of semantic action) or EBNF constructs. */
analysis_kind analysis;
{
    altr_lst *curr_node;
    prod_elnode *temp1;
    prod_elnode *temp2;
    prod_elnode *temp3;
  
    switch (analysis) {

    case sem_act_analysis:
	insert_pvec_prod(lhs, lhs->node_info.sym_node.rplc_seq);
	process_modifiers_actions(top, lhs->node_info.sym_node.rplc_seq, lhs);
	break;

    case altrs_analysis:
	curr_node = lhs->node_info.sym_node.altrs_seq;
	while (curr_node != NULL) {
	    /* Iterate over alternative list
	     */
	    temp1 = curr_node->altr;
	    /* Remove semantic actions within alternative
	     */
	    sem_act_cut(&temp1);
	    curr_node->altr = temp1;
	    insert_pvec_prod(lhs, temp1);
	    process_modifiers_actions(alter, temp1, lhs);
	    curr_node = curr_node->nxtalt;
	}/*while*/
	break;

    case rept_analysis:
	temp1 = lhs->node_info.sym_node.rplc_seq;
	temp2 = temp1;
	/* Remove modifiers and actions in the beginning of
	 * repetition construct (these will be placed in
	 * the end of generated null production).
	 */
	while ((temp1->node_kind == act_node_kind ||
		temp1->node_kind == mod_node_kind) &&
	       (temp1->nxtnode != NULL &&
		(temp1->nxtnode->node_kind == act_node_kind ||
		 temp1->nxtnode->node_kind == mod_node_kind)))
	{
	    temp1 = temp1->nxtnode;
	}/*while*/
	if (temp1->node_kind == act_node_kind ||
	    temp1->node_kind == mod_node_kind)
	{
	    if (temp1->nxtnode == NULL) {
		/* Better error message is needed here
		 * current rule is in orig_prod_tbl[orig_prod_cnt]
		 */
		pmkLog(NULL, 148, sevERR, "");
		break;
	    } else {
		/* Note that in this case two rules are generated
		 */
		temp2 = temp1->nxtnode;
		sem_act_cut(&temp2);
		temp1->nxtnode = NULL;
		temp3 = prod_elnodeAlloc();
		temp3->nxtnode = temp2;
		temp3->node_kind = sym_node_kind;
		temp3->node_info.sym_node.sym_ind =
		    lhs->node_info.sym_node.sym_ind;
		temp3->node_info.sym_node.newnont = TRUE;
		temp3->node_info.sym_node.rplc_info = act_rplc;
		temp3->node_info.sym_node.rplc_seq =
		    lhs->node_info.sym_node.rplc_seq;
		lhs->node_info.sym_node.rplc_seq = temp3;
	    }/*if*/
	} else {
	    temp1 = prod_elnodeAlloc();
	    temp1->node_kind = null_node_kind;
	    sem_act_cut(&temp2);
	    temp3 = prod_elnodeAlloc();
	    temp3->nxtnode = temp2;
	    temp3->node_kind = sym_node_kind;
	    temp3->node_info.sym_node.sym_ind =
		lhs->node_info.sym_node.sym_ind;
	    temp3->node_info.sym_node.newnont = TRUE;
	    temp3->node_info.sym_node.rplc_info = null_rplc;
	    temp3->node_info.sym_node.rplc_seq = temp1;
	    lhs->node_info.sym_node.rplc_seq = temp3;
	}/*if*/
	insert_pvec_prod(lhs, temp3);
	process_modifiers_actions(rept_first, temp3->nxtnode, lhs);
	insert_pvec_prod(temp3, temp3->node_info.sym_node.rplc_seq);
	process_modifiers_actions(rept_second,
				  temp3->node_info.sym_node.rplc_seq, temp3);
	break;
    }/*switch*/
}/*queue_analyze()*/

    
/*-----------------------------------------------------------------------------
 * top_analysis - analyzes an original production and inserts it
 *		  in orig_prod_tbl.
 *-----------------------------------------------------------------------------
 */
static void top_analysis(lhs, rhs_p)
prod_elnode **rhs_p;
prod_elnode *lhs;
{
    prod_elnode *rhs;

    rhs = *rhs_p;
    sem_act_cut(&rhs);
    incOrigProdCnt();
    lhs->nxtnode = rhs;
    orig_prod_tbl[orig_prod_cnt] = lhs;
    insert_pvec_prod(lhs, rhs);
    process_modifiers_actions(top, rhs, lhs);
    *rhs_p = rhs;
}/*top_analysis()*/


/*-----------------------------------------------------------------------------
 * analyze_rhss - analyzes a list of righthand sides by calling
 *                top_analysis and then analyzing queued symbol
 *                nodes by calling queue_analyze.
 *-----------------------------------------------------------------------------
 */
void analyze_rhss(lhs, rhss)
rhs_node *rhss;			/* list of righthand sides */
prod_elnode *lhs;		/* lhs symbol node         */
{
    prod_elnode *q_lhs;
    analysis_kind q_analysis;
    rhs_node *curr_rhss = rhss;

    while (curr_rhss != NULL) {
	init_queue();
	top_analysis(lhs, &curr_rhss->rhs);
	while (!empty_queue()) {
	    front(&q_lhs, &q_analysis);
	    queue_analyze(q_lhs, q_analysis);
	}/*while*/
#ifdef DEBUG
	write_orig_prod(orig_prod_cnt, FALSE);
	write_derived_prods(orig_prod_cnt, TRUE, TRUE, TRUE, FALSE);
#endif
	curr_rhss = curr_rhss->nxtrhs;
    }/*while*/
}/*analyze_rhss()*/


#ifdef DEBUG
/* Test routine called in after order_gram in pwssm.c
 */
static void testOrd()
{
    int i;

    for(i = 0; i <= orig_prod_cnt; i++) {
	write_orig_prod(i, FALSE);
	write_derived_prods(i, TRUE, TRUE, TRUE, TRUE);
    }/*for*/
    printf("   ************   Final  *************  \n");
    write_only_derived();
}/*testOrd()*/
#endif
