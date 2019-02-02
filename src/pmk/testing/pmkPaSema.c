/*----------------------------------------------------------------------*\

	pmkPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include <stdio.h>

#include "pws.h"
#include "pmkList.h"
#include "pwsLexCode.h"
#include "set.h"
#include "pmk_i.h"
#include "tmk.h"
#include "pwSymSet.h"
#include "pwsGrm.h"
#include "pmkScan.h"
extern pmkContext pmkCtxt;
/* END %%IMPORT */

/* System dependencies
 * -------------------
 */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;

/* Token and Srcp definition */
#include "pmkCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct pmkGrammar {
    prod_elnode *rule_elnode_last;
    prod_elnode *rule_elnode /* list of rhs elements (see prod_elnode's def) */;
    rhs_node *rhslist_last /* last element in the list above. This used to
                                        to avoid making a reversed list */;
    rhs_node *rhslist /* list of alternative righthand sides */;
    altr_lst *altr_last;
    altr_lst *altr_node /* list of alternatives (in EBNF alternation) */;
    SymSet nored_set /* modifier sets */;
    SymSet red_set /* modifier sets */;
    int code /* terminals code value given in TERMINAL section */;
    int dcost /* Delete cost given in TERMINAL section */;
    int icost /* Insert cost given in TERMINAL section */;
    Boolean nullf /* null flag */;
    Boolean q_str /* quoted_ string flag */;
    TmkSrcp srcp;
    char *sval2;
    char *sval;
    int ival;
} pmkGrammar;

/* END %%ATTRIBUTES */

extern short pmkStkP;
extern PmkToken pmkSySt[];
extern pmkGrammar pmkSeSt[];

/* %%DECLARATIONS - User data and routines */

static Boolean optimizeObsolete = FALSE;
StrListP grmAttrDecls, grmAttrNames;
CodeNodeP pmkImportSection = NULL,
	  exportSection = NULL,
	  declSection = NULL,
	  scannerSection = NULL,
	  insertSymbSection = NULL;

static search_kind searchResult; /* Variable used for lookup calls */
static SETDEF(sym_kind_set, unknown_symb + 1); /* For lookup calls */
int symRef;        /* Variable used for lookup calls */

static int i;
static attr_kind reading_attr_class = nts_attr; /* Type of attributes when reading */
                                     /* attribute section.              */
static SymSet occupied_code_values = NULL; /* Occupied terminal code values */
static SymSet terminals_set = NULL;        /* Variable used to read a list  */
                                            /* of terminals.                 */
static SymSet modify_intersect_set = NULL; /* Variable used to keep         */
                                            /* intersection of red and nored */
                                            /* sets modifiers.               */
static prod_elnode * temp_lhs;              /* lhs of current production     */
static char * syms_str;                  /* Variable used to construct    */
                                            /* error messages.               */
static char numStr[20];

/*-----------------------------------------------------------------------------
 * makeSymStr - makes a string of symbols in the set s separated by commas.
 *-----------------------------------------------------------------------------
 */
static char *makeSymStr(s)
SymSet s;
{
    char *temp;
    int totlen = 0;
    int nr = 0;
    int i;

    for (i = 0; i < SymSetSize(s); i++) {
	if (SymSetMem(s,i)) {
	    totlen += strlen(vocabulary[i]->name) + 3;
	}/*if*/
    }/*for*/

    temp = (char *)calloc(totlen, sizeof(char));
    nr=0;
    for (i = 0; i < SymSetSize(s); i++) {
	if (SymSetMem(s, i)) {
	    if (nr > 0) strcat(temp, ", ");
	    strcat(temp, vocabulary[i]->name);
	    nr++;
	}/*if*/
    }/*for*/
    return(temp);
}/*makeSymStr()*/


/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * pmkPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void pmkPaSema(rule)
int rule;			/* IN production number */
{
    switch (rule) {
          case 4: { /* program_paragraph = declaration_part code_part; */

	    init_action_structs(TRUE);
	  	break;}
    case 8: { /* declaration_part = '%%DECLARATIONS' endOpt; */

	  if (declSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    declSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 9: { /* grammar_paragraph = scanner_interface_section attribute_section error_handling_section rule_section; */

	    if (!SeriousErr) order_gram();
	  	break;}
    case 10: { /* scanner_interface_section =; */

	    term_sec_given = FALSE;
	  	break;}
    case 12: { /* TERMINALS_aux = '%%TERMINALS'; */

	    pmkSeSt[pmkStkP+1].ival = pmkSySt[pmkStkP+1].ival;
	    occupied_code_values = SymSetAlloc();
	    SymSetIns(occupied_code_values, 0);
	    SymSetIns(occupied_code_values, 1);
	    term_sec_given = TRUE;
	  	break;}
    case 15: { /* terminal_definition = terminal '=' token_code error_recovery_data ';'; */

	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, t_symb);
	    lookup(pmkSeSt[pmkStkP+1].sval, sym_kind_set, &symRef, &searchResult);
	    if (searchResult == new_search || searchResult == found_search) {
		if (searchResult == found_search) {
		    /* ERROR terminal defined twice, old definition overridden
		     */
		    pmkLog(&pmkSeSt[pmkStkP+1].srcp, 121, sevWAR,
			  vocabulary[symRef]->name);
		}/*if*/
		vocabulary[symRef]->symbol_typ = t_symb;
		vocabulary[symRef]->code = pmkSeSt[pmkStkP+3].ival;
		SymSetIns(occupied_code_values, pmkSeSt[pmkStkP+3].ival);
		if (pmkSeSt[pmkStkP+3].ival > tc_val) tc_val = pmkSeSt[pmkStkP+3].ival;

		if (!(pmkSeSt[pmkStkP+4].nullf)) {
		    vocabulary[symRef]->syminfo.ter_info.icost =
			pmkSeSt[pmkStkP+4].icost;
		    if (pmkSeSt[pmkStkP+4].icost > icostMax) {
			icostMax = pmkSeSt[pmkStkP+4].icost;
		    }/*if*/
		    vocabulary[symRef]->syminfo.ter_info.dcost =
			pmkSeSt[pmkStkP+4].dcost;
		    if (pmkSeSt[pmkStkP+4].dcost > dcostMax) {
			dcostMax = pmkSeSt[pmkStkP+4].dcost;
		    }/*if*/
		    vocabulary[symRef]->syminfo.ter_info.psymb =
			pmkSeSt[pmkStkP+4].sval;
  		} else {
		    vocabulary[symRef]->syminfo.ter_info.icost = 1;
		    vocabulary[symRef]->syminfo.ter_info.dcost = 1;
		    vocabulary[symRef]->syminfo.ter_info.psymb = NULL;
		}/*if*/
	    } else if (searchResult == confl_search) {
		/* ERROR Ambiguous symbol, Terminal expected.
		 * This error should'nt happen since no other
		 * symbol kinds can ocurr before scanner interface.
		 */
     		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 123, sevSYS,
		      vocabulary[symRef]->name);
	    }/*if*/
	  	break;}
    case 17: { /* symbol = term_or_nonterm; */

	    pmkSeSt[pmkStkP+1].q_str = FALSE;
	  	break;}
    case 18: { /* symbol = STRING; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].q_str = TRUE;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 19: { /* term_or_nonterm = IDENTIFIER; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 20: { /* term_or_nonterm = ANG_BRACK_STRING; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 21: { /* token_code = INTEGER; */

	    if (SymSetMem(occupied_code_values, pmkSySt[pmkStkP+1].ival)) {
		/* ERROR Terminal code already in use
		 */
		sprintf(numStr, "%u", pmkSySt[pmkStkP+1].ival);
		pmkLog(&pmkSySt[pmkStkP+1].srcp, 120, sevERR, numStr);
	    } else {
		pmkSeSt[pmkStkP+1].ival = pmkSySt[pmkStkP+1].ival;
	    }/*if*/
	  	break;}
    case 22: { /* error_recovery_data =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 23: { /* error_recovery_data = ',' insert_cost ',' delete_cost print_symbol; */

	    pmkSeSt[pmkStkP+1].icost = pmkSeSt[pmkStkP+2].icost;
	    pmkSeSt[pmkStkP+1].dcost = pmkSeSt[pmkStkP+4].dcost;
	    pmkSeSt[pmkStkP+1].sval = pmkSeSt[pmkStkP+5].sval;
	    pmkSeSt[pmkStkP+1].nullf = FALSE;
	  	break;}
    case 24: { /* insert_cost =; */

	    pmkSeSt[pmkStkP+1].icost = 1;
	  	break;}
    case 25: { /* insert_cost = INTEGER; */

	    pmkSeSt[pmkStkP+1].icost = pmkSySt[pmkStkP+1].ival;
	  	break;}
    case 26: { /* delete_cost =; */

	    pmkSeSt[pmkStkP+1].dcost = 1;
	  	break;}
    case 27: { /* delete_cost = INTEGER; */

	    pmkSeSt[pmkStkP+1].dcost = pmkSySt[pmkStkP+1].ival;
	  	break;}
    case 28: { /* print_symbol =; */

	    pmkSeSt[pmkStkP+1].sval = NULL;
	  	break;}
    case 29: { /* print_symbol = '=>' terminal; */

	    pmkSeSt[pmkStkP+1].sval = pmkSeSt[pmkStkP+2].sval;
	  	break;}
    case 32: { /* attributes = attribute; */

	  grmAttrDecls = appendStrList(pmkSeSt[pmkStkP+1].sval, NULL);
	  grmAttrNames = appendStrList(pmkSeSt[pmkStkP+1].sval2, NULL);
		break;}
    case 33: { /* attributes = attributes ',' attribute; */

	  grmAttrDecls = appendStrList(pmkSeSt[pmkStkP+3].sval, grmAttrDecls);
	  grmAttrNames = appendStrList(pmkSeSt[pmkStkP+3].sval2, grmAttrNames);
		break;}
    case 34: { /* attribute = IDENTIFIER optional_decl; */

            pmkSeSt[pmkStkP+1].sval = pmkSeSt[pmkStkP+2].sval;
	    pmkSeSt[pmkStkP+1].sval2 = pmkSySt[pmkStkP+1].sval;
	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, attr_symb);
	    lookup(pmkSySt[pmkStkP+1].sval, sym_kind_set, &symRef, &searchResult);
	    if (new_search == searchResult) {
		vocabulary[symRef]->symbol_typ = attr_symb;
		vocabulary[symRef]->syminfo.attr_class = nts_attr;
	    } else if (found_search == searchResult) {
  		if (vocabulary[symRef]->syminfo.attr_class != nts_attr &&	
		    vocabulary[symRef]->syminfo.attr_class != unk_attr)	{
		    vocabulary[symRef]->syminfo.attr_class = voc_attr;
		} else if (vocabulary[symRef]->syminfo.attr_class == nts_attr) {
		    /* ERROR Attribute defined twice
		     */
		    pmkLog(&pmkSySt[pmkStkP+1].srcp, 119, sevWAR, pmkSySt[pmkStkP+1].sval);
		}/*if*/
	    } else {
		/* ERROR Ambiguous symbol. Attribute expected.
		 */
    		pmkLog(&pmkSySt[pmkStkP+1].srcp, 118, sevERR, pmkSySt[pmkStkP+1].sval);
	    }/*if*/
	  	break;}
    case 35: { /* optional_decl =; */

	  pmkSeSt[pmkStkP+1].sval = NULL;
		break;}
    case 36: { /* optional_decl = '%%'; */

	  pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
		break;}
    case 51: { /* terminals = terminal; */

	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, t_symb);
	    lookup(pmkSeSt[pmkStkP+1].sval, sym_kind_set, &symRef, &searchResult);
	    if (new_search == searchResult || searchResult == found_search) {
		if (searchResult == new_search) {
		    vocabulary[symRef]->symbol_typ = t_symb;
		    vocabulary[symRef]->syminfo.ter_info.icost = 1;
		    vocabulary[symRef]->syminfo.ter_info.dcost = 1;
		    vocabulary[symRef]->syminfo.ter_info.psymb = NULL;
		}/*if*/
		SymSetIns(terminals_set, symRef);
	    } else if (searchResult == confl_search) {
		/* ERROR Ambiguous symbol, Terminal expected.
		 */
		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 117, sevERR, pmkSeSt[pmkStkP+1].sval);
		SymSetIns(terminals_set, symRef);
	    }/*if*/
	  	break;}
    case 52: { /* terminals = terminals ',' terminal; */

	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, t_symb);
	    lookup(pmkSeSt[pmkStkP+3].sval, sym_kind_set, &symRef, &searchResult);
	    if (new_search == searchResult || searchResult == found_search) {
		if (searchResult == new_search) {
		    vocabulary[symRef]->symbol_typ = t_symb;
		    vocabulary[symRef]->syminfo.ter_info.icost = 1;
		    vocabulary[symRef]->syminfo.ter_info.dcost = 1;
		    vocabulary[symRef]->syminfo.ter_info.psymb = NULL;
		}/*if*/
		SymSetIns(terminals_set, symRef);
	    } else if (searchResult == confl_search) {
		/* ERROR Ambiguous symbol, Terminal expected.
		 */
		pmkLog(&pmkSeSt[pmkStkP+3].srcp, 117, sevERR, pmkSeSt[pmkStkP+3].sval);
		SymSetIns(terminals_set, symRef);
	    }/*if*/
	  	break;}
    case 55: { /* separator_part = separator_aux '(' terminals ')' ';'; */

	    recovery_spec.separators = terminals_set;
	  	break;}
    case 56: { /* separator_aux = 'SEPARATOR'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 57: { /* fiducial_part = fiducial_aux '(' terminals ')' ';'; */

	    recovery_spec.fiducials = terminals_set;
	  	break;}
    case 58: { /* fiducial_aux = 'FIDUCIAL'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 59: { /* skip_part = skip_aux '(' terminals ')' ';'; */

	    recovery_spec.skips = terminals_set;
	  	break;}
    case 60: { /* skip_aux = 'SKIP'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 65: { /* rule = nonterminal '=' rhss ';'; */

	    /* Main routine for analysis of rhss associated with a single lhs
	     */
	    if (!SeriousErr) analyze_rhss(temp_lhs, pmkSeSt[pmkStkP+3].rhslist);
	  	break;}
    case 66: { /* nonterminal = term_or_nonterm; */

	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, nts_symb);
	    lookup(pmkSeSt[pmkStkP+1].sval, sym_kind_set, &symRef,
		   &searchResult);
	    if (new_search == searchResult) {
		vocabulary[symRef]->symbol_typ = nts_symb;
		vocabulary[symRef]->syminfo.firstp = -1;
	    }/*if*/
	    temp_lhs = prod_elnodeAlloc();
	    temp_lhs->node_kind = sym_node_kind;
	    temp_lhs->node_info.sym_node.sym_ind = symRef;
	    temp_lhs->node_info.sym_node.lhs_sym = TRUE;
	    temp_lhs->node_info.sym_node.newnont = FALSE;
	    if (confl_search == searchResult) {
		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 116, sevERR,
		      pmkSeSt[pmkStkP+1].sval);
	    }/*if*/
	  	break;}
    case 67: { /* rhss = rhs; */

	    pmkSeSt[pmkStkP+1].rhslist_last = pmkSeSt[pmkStkP+1].rhslist;
	  	break;}
    case 68: { /* rhss = rhss '!' rhs; */

	    pmkSeSt[pmkStkP+1].rhslist_last->nxtrhs = pmkSeSt[pmkStkP+3].rhslist;
	    pmkSeSt[pmkStkP+1].rhslist = pmkSeSt[pmkStkP+1].rhslist;
	    pmkSeSt[pmkStkP+1].rhslist_last = pmkSeSt[pmkStkP+3].rhslist;
	  	break;}
    case 69: { /* rhs = symbols_or_actions modifiers; */

	    if (pmkSeSt[pmkStkP+1].nullf) {
		/* Allocated a null node
		 */
		pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_kind = null_node_kind;
		pmkSeSt[pmkStkP+1].rule_elnode_last =
		    pmkSeSt[pmkStkP+1].rule_elnode;
	    }/*if*/
	    if (!(pmkSeSt[pmkStkP+2].nullf)) {
		/* Allocate a modifier node
		 */
		pmkSeSt[pmkStkP+2].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+2].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+2].red_set;
		pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+2].nored_set;
		pmkSeSt[pmkStkP+1].rule_elnode_last->nxtnode =
		    pmkSeSt[pmkStkP+2].rule_elnode;
	    }/*if*/

	    pmkSeSt[pmkStkP+1].rhslist = rhs_nodeAlloc();
	    pmkSeSt[pmkStkP+1].rhslist->rhs = pmkSeSt[pmkStkP+1].rule_elnode;
	  	break;}
    case 70: { /* symbols_or_actions =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 71: { /* symbols_or_actions = symbols_or_actions symbol_or_action; */

	    /* Make list
	     */
	    if (pmkSeSt[pmkStkP+1].nullf) {
		if (pmkSeSt[pmkStkP+2].nullf) {
		    pmkSeSt[pmkStkP+1].nullf = TRUE;
		} else {
		    pmkSeSt[pmkStkP+1].nullf = FALSE;
		    pmkSeSt[pmkStkP+1].rule_elnode =
			pmkSeSt[pmkStkP+2].rule_elnode;
		    pmkSeSt[pmkStkP+1].rule_elnode_last =
			pmkSeSt[pmkStkP+2].rule_elnode_last;
		}/*if*/
	    } else if (pmkSeSt[pmkStkP+2].nullf) {
		pmkSeSt[pmkStkP+1].nullf = FALSE;
		pmkSeSt[pmkStkP+1].rule_elnode =
		    pmkSeSt[pmkStkP+1].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode_last =
		    pmkSeSt[pmkStkP+1].rule_elnode_last;
	    } else {
		pmkSeSt[pmkStkP+1].nullf = FALSE;
		pmkSeSt[pmkStkP+1].rule_elnode_last->nxtnode =
		    pmkSeSt[pmkStkP+2].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode =
		    pmkSeSt[pmkStkP+1].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode_last =
		    pmkSeSt[pmkStkP+2].rule_elnode_last;
	    }/*if*/
	  	break;}
    case 73: { /* Alternatives = Alternatives '|' modifiers symbols_or_actions modifiers; */

	    if (pmkSeSt[pmkStkP+4].nullf) {
		pmkSeSt[pmkStkP+4].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+4].rule_elnode->node_kind = null_node_kind;
		pmkSeSt[pmkStkP+4].rule_elnode_last =
		    pmkSeSt[pmkStkP+4].rule_elnode;
		if (!(pmkSeSt[pmkStkP+5].nullf) && !(pmkSeSt[pmkStkP+3].nullf)) {
		    /* Test red and nored sets intersection
		     */
		    if (pmkSeSt[pmkStkP+3].red_set != NULL &&
			pmkSeSt[pmkStkP+5].nored_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+3].red_set, pmkSeSt[pmkStkP+3].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+5].srcp, 113, sevERR, syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+3].red_set = NULL;
			}/*if*/
		    }/*if*/
		    if (pmkSeSt[pmkStkP+3].nored_set != NULL &&
			pmkSeSt[pmkStkP+5].red_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+3].red_set, pmkSeSt[pmkStkP+3].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+5].srcp, 113, sevERR, syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+3].red_set = NULL;
			}/*if*/
		    }/*if*/
		}/*if*/
	    }/*if*/

	    /* Make list
	     */
	    if (!(pmkSeSt[pmkStkP+5].nullf)) {
		pmkSeSt[pmkStkP+5].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+5].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+5].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+5].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+5].red_set;
		pmkSeSt[pmkStkP+5].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+5].nored_set;
		pmkSeSt[pmkStkP+4].rule_elnode_last->nxtnode =
		    pmkSeSt[pmkStkP+5].rule_elnode;
		pmkSeSt[pmkStkP+4].rule_elnode_last = pmkSeSt[pmkStkP+5].rule_elnode;
	    }/*if*/

	    pmkSeSt[pmkStkP+1].altr_last->nxtalt = altr_lstAlloc();

	    if (!(pmkSeSt[pmkStkP+3].nullf)) {
		pmkSeSt[pmkStkP+3].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+3].red_set;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+3].nored_set;
		pmkSeSt[pmkStkP+3].rule_elnode->nxtnode =
		    pmkSeSt[pmkStkP+4].rule_elnode;
		pmkSeSt[pmkStkP+1].altr_last->nxtalt->altr =
		    pmkSeSt[pmkStkP+3].rule_elnode;
	    } else {
		pmkSeSt[pmkStkP+1].altr_last->nxtalt->altr =
		    pmkSeSt[pmkStkP+4].rule_elnode;
	    }/*if*/

	    pmkSeSt[pmkStkP+1].altr_node = pmkSeSt[pmkStkP+1].altr_node;
	    pmkSeSt[pmkStkP+1].altr_last = pmkSeSt[pmkStkP+1].altr_last->nxtalt;
	  	break;}
    case 72: { /* Alternatives = modifiers symbols_or_actions modifiers; */

	    if (pmkSeSt[pmkStkP+2].nullf) {
		pmkSeSt[pmkStkP+2].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+2].rule_elnode->node_kind = null_node_kind;
		pmkSeSt[pmkStkP+2].rule_elnode_last =
		    pmkSeSt[pmkStkP+2].rule_elnode;
		if (!(pmkSeSt[pmkStkP+3].nullf) && !(pmkSeSt[pmkStkP+1].nullf)) {
		    /* Test red and nored sets intersection
		     */
		    if (pmkSeSt[pmkStkP+1].red_set != NULL &&
			pmkSeSt[pmkStkP+3].nored_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+1].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+3].srcp, 113, sevERR, syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+1].red_set = NULL;
			}/*if*/
		    }/*if*/

		    /* Test red and nored sets intersection
		     */
		    if (pmkSeSt[pmkStkP+1].nored_set != NULL &&
			pmkSeSt[pmkStkP+3].red_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+1].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+3].srcp,113,sevERR,syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+1].red_set = NULL;
			}/*if*/
		    }/*if*/
		}/*if*/
	    }/*if*/

	    if (!(pmkSeSt[pmkStkP+3].nullf)) {
		pmkSeSt[pmkStkP+3].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+3].red_set;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+3].nored_set;
		pmkSeSt[pmkStkP+2].rule_elnode_last->nxtnode =
		    pmkSeSt[pmkStkP+3].rule_elnode;
		pmkSeSt[pmkStkP+2].rule_elnode_last =
		    pmkSeSt[pmkStkP+3].rule_elnode;
	    }/*if*/

	    pmkSeSt[pmkStkP+1].altr_node = altr_lstAlloc();

	    if (!(pmkSeSt[pmkStkP+1].nullf)) {
		pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+1].red_set;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+1].nored_set;
		pmkSeSt[pmkStkP+1].rule_elnode->nxtnode =
		    pmkSeSt[pmkStkP+2].rule_elnode;
		pmkSeSt[pmkStkP+1].altr_node->altr = pmkSeSt[pmkStkP+1].rule_elnode;
	    } else {
		pmkSeSt[pmkStkP+1].altr_node->altr =
		    pmkSeSt[pmkStkP+2].rule_elnode;
	    }/*if*/

	    pmkSeSt[pmkStkP+1].altr_last = pmkSeSt[pmkStkP+1].altr_node;
	  	break;}
    case 74: { /* symbol_or_action = symbol; */

	    SetClear(sym_kind_set, unknown_symb + 1);
	    if (pmkSeSt[pmkStkP+1].q_str) {
		SetIns(sym_kind_set, t_symb);
	    } else {
		SetIns(sym_kind_set, t_symb);
		SetIns(sym_kind_set, nts_symb);
	    }/*if*/

	    lookup(pmkSeSt[pmkStkP+1].sval, sym_kind_set, &symRef, &searchResult);
	    if (confl_search == searchResult) {
		/* ERROR Ambiguous symbol Terminal or non terminal expected
		 */
		pmkSeSt[pmkStkP+1].nullf = TRUE;
		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 115, sevERR, pmkSeSt[pmkStkP+1].sval);
	    } else {
		SymSetIns(on_right, symRef);
		pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_kind = sym_node_kind;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.sym_ind =
		    symRef;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.lhs_sym =
		    FALSE;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.newnont =
		    FALSE;
		SymSetIns(on_right, symRef);
		pmkSeSt[pmkStkP+1].rule_elnode_last =
		    pmkSeSt[pmkStkP+1].rule_elnode;
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    }/*if*/
	  	break;}
    case 76: { /* symbol_or_action = '{' modifiers symbols_or_actions modifiers '}'; */

	    if (pmkSeSt[pmkStkP+3].nullf) {
		/* ERROR Repetition of Null string ignored
		 */
		pmkSeSt[pmkStkP+1].nullf = TRUE;
		pmkLog(&pmkSySt[pmkStkP+1].srcp,114,sevWAR,"");
	    } else {
		/* Generate a new symbol node (with a new symbol).
		 * Keep symbols_or_actions's rule_nodelist in the symbol node
		 */
		SetClear(sym_kind_set, unknown_symb + 1);
		SetIns(sym_kind_set, nts_symb);
		lookup(gensym(), sym_kind_set, &symRef, &searchResult);
		vocabulary[symRef]->symbol_typ = nts_symb;
		vocabulary[symRef]->syminfo.firstp = -1;
		if (confl_search == searchResult ||
		    found_search == searchResult)
		{
		    /* This should'nt happen
		     */
		    printf(
"Non terminal generated by PMK is equal to user's symbol");
		}/*if*/

		/* Make list
		 */
		if (!(pmkSeSt[pmkStkP+4].nullf)) {
		    pmkSeSt[pmkStkP+4].rule_elnode = prod_elnodeAlloc();
		    pmkSeSt[pmkStkP+4].rule_elnode->node_kind = mod_node_kind;
		    pmkSeSt[pmkStkP+4].rule_elnode->node_info.modify_node =
			modify_recAlloc();
		    pmkSeSt[pmkStkP+4].rule_elnode->node_info.modify_node->red =
			pmkSeSt[pmkStkP+4].red_set;
		    pmkSeSt[pmkStkP+4].rule_elnode->node_info.modify_node->nored =
			pmkSeSt[pmkStkP+4].nored_set;
		    pmkSeSt[pmkStkP+3].rule_elnode_last->nxtnode =
			pmkSeSt[pmkStkP+4].rule_elnode;
		    pmkSeSt[pmkStkP+3].rule_elnode_last =
			pmkSeSt[pmkStkP+4].rule_elnode;
		}/*if*/
		SymSetIns(on_right, symRef);
		pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_kind = sym_node_kind;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.sym_ind =
		    symRef;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.newnont =
		    TRUE;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.rplc_info =
		    rept_rplc;
		if (!(pmkSeSt[pmkStkP+2].nullf)) {
		    pmkSeSt[pmkStkP+2].rule_elnode = prod_elnodeAlloc();
		    pmkSeSt[pmkStkP+2].rule_elnode->node_kind = mod_node_kind;
		    pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node =
			modify_recAlloc();
		    pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node->red =
			pmkSeSt[pmkStkP+2].red_set;
		    pmkSeSt[pmkStkP+2].rule_elnode->node_info.modify_node->nored =
			pmkSeSt[pmkStkP+2].nored_set;
		    pmkSeSt[pmkStkP+2].rule_elnode->nxtnode =
			pmkSeSt[pmkStkP+3].rule_elnode;
		    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.rplc_seq=
			pmkSeSt[pmkStkP+2].rule_elnode;
		} else {
		    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.rplc_seq=
			pmkSeSt[pmkStkP+3].rule_elnode;
		}/*if*/
		pmkSeSt[pmkStkP+1].rule_elnode_last =
		    pmkSeSt[pmkStkP+1].rule_elnode;
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    }/*if*/
	  	break;}
    case 77: { /* symbol_or_action = '(' Alternatives ')'; */

	    /* Generate a new symbol node (with a new symbol)
	     * keep symbols_or_actions's rule_nodelist in the symbol node
	     */
	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, nts_symb);
	    lookup(gensym(), sym_kind_set, &symRef, &searchResult);
	    vocabulary[symRef]->symbol_typ = nts_symb;
	    vocabulary[symRef]->syminfo.firstp = -1;
	    if (confl_search == searchResult || found_search == searchResult) {
		/* This should'nt happen
		 */
		printf(
"Non terminal generated by PMK is equal to user's symbol");
	    }/*if*/

	    /* Make list
	     */
	    SymSetIns(on_right, symRef);
	    pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
	    pmkSeSt[pmkStkP+1].rule_elnode->node_kind = sym_node_kind;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.sym_ind = symRef;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.newnont = TRUE;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.rplc_info =
		altrs_rplc;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.altrs_seq =
		pmkSeSt[pmkStkP+2].altr_node;
	    pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+1].rule_elnode;
	    pmkSeSt[pmkStkP+1].nullf = FALSE;
	  	break;}
    case 75: { /* symbol_or_action = modifiers action modifiers; */

	    if (!(pmkSeSt[pmkStkP+3].nullf) && !(pmkSeSt[pmkStkP+1].nullf)) {
		/* Test red and nored sets intersection
		 */
		if (pmkSeSt[pmkStkP+1].red_set != NULL &&
		    pmkSeSt[pmkStkP+3].nored_set != NULL)
		{
		    if (modify_intersect_set == NULL) {
			modify_intersect_set = SymSetAlloc();
		    }/*if*/
		    SymSetClear(modify_intersect_set);
		    SymSetInter(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+1].nored_set,
				modify_intersect_set);
		    if (!(SymSetEmpty(modify_intersect_set))) {
			syms_str = makeSymStr(modify_intersect_set);
			pmkLog(&pmkSeSt[pmkStkP+3].srcp, 113, sevERR, syms_str);
			free(syms_str);
			pmkSeSt[pmkStkP+1].red_set = NULL;
		    }/*if*/
		}/*if*/
		if (pmkSeSt[pmkStkP+1].nored_set != NULL &&
		    pmkSeSt[pmkStkP+3].red_set != NULL)
		{
		    if (modify_intersect_set == NULL) {
			modify_intersect_set = SymSetAlloc();
		    }/*if*/
		    SymSetClear(modify_intersect_set);
		    SymSetInter(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+1].nored_set,
				modify_intersect_set);
		    if (!(SymSetEmpty(modify_intersect_set))) {
			syms_str = makeSymStr(modify_intersect_set);
			pmkLog(&pmkSeSt[pmkStkP+3].srcp, 113, sevERR, syms_str);
			free(syms_str);
			pmkSeSt[pmkStkP+1].red_set = NULL;
		    }/*if*/
		}/*if*/
	    }/*if*/
     
	    if (!(pmkSeSt[pmkStkP+3].nullf)) {
		pmkSeSt[pmkStkP+3].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+3].red_set;
		pmkSeSt[pmkStkP+3].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+3].nored_set;
		pmkSeSt[pmkStkP+2].rule_elnode->nxtnode = pmkSeSt[pmkStkP+3].rule_elnode;
		pmkSeSt[pmkStkP+2].rule_elnode_last = pmkSeSt[pmkStkP+3].rule_elnode;
	    }/*if*/

	    if (!(pmkSeSt[pmkStkP+1].nullf)) {
		pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_kind = mod_node_kind;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node =
		    modify_recAlloc();
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node->red =
		    pmkSeSt[pmkStkP+1].red_set;
		pmkSeSt[pmkStkP+1].rule_elnode->node_info.modify_node->nored =
		    pmkSeSt[pmkStkP+1].nored_set;
		pmkSeSt[pmkStkP+1].rule_elnode->nxtnode = pmkSeSt[pmkStkP+2].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode = pmkSeSt[pmkStkP+1].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+2].rule_elnode_last;
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    } else {
		pmkSeSt[pmkStkP+1].rule_elnode = pmkSeSt[pmkStkP+2].rule_elnode;
		pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+2].rule_elnode_last;
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    }/*if*/
	  	break;}
    case 78: { /* modifiers =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 79: { /* modifiers = modifiers modifier; */

	    /* Merge modifier sets
	     */
	    if (!(pmkSeSt[pmkStkP+1].nullf)) {
		if (pmkSeSt[pmkStkP+1].red_set == NULL) {
		    if (pmkSeSt[pmkStkP+2].red_set != NULL) {
			pmkSeSt[pmkStkP+1].red_set = pmkSeSt[pmkStkP+2].red_set;
		    }/*if*/
		} else if (pmkSeSt[pmkStkP+2].red_set == NULL) {
		    pmkSeSt[pmkStkP+1].red_set = pmkSeSt[pmkStkP+1].red_set;
		} else {
		    SymSetUnion(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+2].red_set,
				pmkSeSt[pmkStkP+1].red_set);
		}/*if*/
		if (pmkSeSt[pmkStkP+1].nored_set == NULL) {
		    if (pmkSeSt[pmkStkP+2].nored_set != NULL) {
			pmkSeSt[pmkStkP+1].nored_set = pmkSeSt[pmkStkP+2].nored_set;
		    }/*if*/
		} else if (pmkSeSt[pmkStkP+2].nored_set == NULL) {
		    pmkSeSt[pmkStkP+1].nored_set = pmkSeSt[pmkStkP+1].nored_set;
		} else {
		    SymSetUnion(pmkSeSt[pmkStkP+1].nored_set, pmkSeSt[pmkStkP+2].nored_set,
				pmkSeSt[pmkStkP+1].nored_set);
		}/*if*/
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    } else {
		pmkSeSt[pmkStkP+1].red_set = pmkSeSt[pmkStkP+2].red_set;
		pmkSeSt[pmkStkP+1].nored_set = pmkSeSt[pmkStkP+2].nored_set;
		pmkSeSt[pmkStkP+1].nullf = FALSE;
	    }/*if*/

	    /* Test red and nored sets intersection
	     */
	    if (pmkSeSt[pmkStkP+1].red_set != NULL &&
		pmkSeSt[pmkStkP+1].nored_set != NULL)
	    {
		if (modify_intersect_set == NULL) {
		    modify_intersect_set = SymSetAlloc();
		}/*if*/
		SymSetClear(modify_intersect_set);
		SymSetInter(pmkSeSt[pmkStkP+1].red_set, pmkSeSt[pmkStkP+1].nored_set,
			    modify_intersect_set);
		if (!(SymSetEmpty(modify_intersect_set))) {
		     syms_str = makeSymStr(modify_intersect_set);
		     pmkLog(&pmkSeSt[pmkStkP+2].srcp, 113, sevERR, syms_str);
		     free(syms_str);
		     pmkSeSt[pmkStkP+1].red_set = NULL;
		}/*if*/
	    }/*if*/
	  	break;}
    case 80: { /* modifier = reduce_modifier; */

	    pmkSeSt[pmkStkP+1].red_set = pmkSeSt[pmkStkP+1].red_set;
	    pmkSeSt[pmkStkP+1].nored_set = NULL;
	  	break;}
    case 81: { /* modifier = reduce_not_modifier; */

	    pmkSeSt[pmkStkP+1].nored_set = pmkSeSt[pmkStkP+1].nored_set;
	    pmkSeSt[pmkStkP+1].red_set = NULL;
	  	break;}
    case 82: { /* reduce_modifier = <+red_aux> '(' terminals ')'; */

	    pmkSeSt[pmkStkP+1].red_set = terminals_set;
	  	break;}
    case 83: { /* <+red_aux> = '%+'; */

	    terminals_set = SymSetAlloc();
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 84: { /* reduce_not_modifier = <-red_aux> '(' terminals ')'; */

	    pmkSeSt[pmkStkP+1].nored_set = terminals_set;
	  	break;}
    case 85: { /* <-red_aux> = '%-'; */

	    terminals_set = SymSetAlloc();
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 86: { /* action = '%%'; */

	    pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
	    pmkSeSt[pmkStkP+1].rule_elnode->node_kind = act_node_kind;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_srcp = pmkSySt[pmkStkP+1].srcp;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_start = pmkSySt[pmkStkP+1].fpos;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_length = pmkSySt[pmkStkP+1].length;
	    pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+1].rule_elnode;
	  	break;}
    case 87: { /* export_section = '%%EXPORT' endOpt; */

	  if (exportSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    exportSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 88: { /* scanner_section = '%%SCANNER' endOpt; */

	  if (scannerSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    scannerSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 89: { /* insertsymbol_section = '%%INSERTSYMBOL' endOpt; */

	  if (insertSymbSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    insertSymbSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    default: break; }
}/*pmkPaSema()*/

