/*----------------------------------------------------------------------*\

	pmkPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pws.h"
#include "pmkList.h"
#include "pwsLexCode.h"
#include "set.h"
#include "pmk_i.h"
#include "tmk.h"
#include "pwSymSet.h"
#include "pwsGrm.h"
#include "pmkScan.h"
extern pmkScContext pmkCtxt;

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


TmkSrcp
	rulesSrcp,
	declarationsSrcp,
	exportSrcp,
	scannerSrcp,
	insertsymbolSrcp,
	deletesymbolSrcp;

StrListP grmAttrDecls, grmAttrNames;

CodeNodeP pmkImportSection = NULL,
	  exportSection = NULL,
	  declSection = NULL,
	  scannerSection = NULL,
	  insertSymbSection = NULL,
	  deleteSymbSection = NULL;

static Boolean scan_if_sect, attr_sect, errhand_sect, rules_sect;
static search_kind searchResult; /* Variable used for lookup calls */
static SETDEF(sym_kind_set, unknown_symb + 1); /* For lookup calls */
int symRef;        /* Variable used for lookup calls */

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
void pmkPaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 1: { /* pmk_document = skip_sections __genSym#0 other_sections; */

	    if (!rules_sect) {
	      /* ERROR: No RULES section. */
	      pmkLog(NULL, 238, sevERR, "");
	    }
	    if (!SeriousErr) order_gram();
	  	break;}
    case 2: { /* __genSym#0 =; */
{
	    term_sec_given = FALSE;
 	    scan_if_sect = FALSE;
	    attr_sect = FALSE;
	    errhand_sect = FALSE;
	    rules_sect = FALSE;
	 }	break;}
    case 15: { /* other_section = scanner_interface_section; */

        if (scan_if_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 235, sevERR, "");
	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	scan_if_sect = TRUE;
		break;}
    case 13: { /* other_section = attribute_section; */

        if (attr_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 235, sevERR, "");
	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	attr_sect = TRUE;
		break;}
    case 7: { /* other_section = error_handling_section; */

        if (errhand_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 235, sevERR, "");
	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	errhand_sect = TRUE;
		break;}
    case 14: { /* other_section = rule_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 235, sevERR, "");
        rules_sect = TRUE;
		break;}
    case 8: { /* other_section = declaration_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	declarationsSrcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 9: { /* other_section = export_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	exportSrcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 10: { /* other_section = scanner_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	scannerSrcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 11: { /* other_section = insertsymbol_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	insertsymbolSrcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 12: { /* other_section = deletesymbol_section; */

	if (rules_sect)
	   pmkLog(pmkSeSt[pmkStkP+1].srcp, 236, sevERR, "");
	deletesymbolSrcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 16: { /* declaration_section = '%%DECLARATIONS' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  if (declSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    declSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 17: { /* scanner_interface_section = TERMINALS_aux terminal_definitions endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSeSt[pmkStkP+1].srcp;
        	break;}
    case 18: { /* TERMINALS_aux = '%%TERMINALS'; */

	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	    pmkSeSt[pmkStkP+1].ival = pmkSySt[pmkStkP+1].ival;
	    occupied_code_values = SymSetAlloc();
	    SymSetIns(occupied_code_values, 0);
	    SymSetIns(occupied_code_values, 1);
	    term_sec_given = TRUE;
	  	break;}
    case 21: { /* terminal_definition = terminal '=' token_code error_recovery_data ';'; */

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
		    if (pmkSeSt[pmkStkP+4].sval) {
		        /* Use a print string, excluding string quotes */
		        pmkSeSt[pmkStkP+4].sval[strlen(pmkSeSt[pmkStkP+4].sval)-1] = '\0';
		        vocabulary[symRef]->syminfo.ter_info.psymb =
			  &pmkSeSt[pmkStkP+4].sval[1];
		    } else {
		        /* Insert and delete costs, but no print symbol */
		        vocabulary[symRef]->syminfo.ter_info.psymb = NULL;
                    }/*if*/
  		} else {
		    vocabulary[symRef]->syminfo.ter_info.icost = 1;
		    vocabulary[symRef]->syminfo.ter_info.dcost = 1;
		    vocabulary[symRef]->syminfo.ter_info.psymb = NULL;
		}/*if*/
	    } else if (searchResult == confl_search) {
		/* ERROR Ambiguous symbol, Terminal expected.
		 * This error should'nt happen since no other
		 * symbol kinds can occurr before scanner interface.
		 */
     		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 123, sevSYS,
		      vocabulary[symRef]->name);
	    }/*if*/
	  	break;}
    case 23: { /* symbol = term_or_nonterm; */

	    pmkSeSt[pmkStkP+1].q_str = FALSE;
	  	break;}
    case 24: { /* symbol = STRING; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].q_str = TRUE;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 25: { /* term_or_nonterm = IDENTIFIER; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 26: { /* term_or_nonterm = ANG_BRACK_STRING; */

	    pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 27: { /* token_code = INTEGER; */

	    if (SymSetMem(occupied_code_values, pmkSySt[pmkStkP+1].ival)) {
		/* ERROR Terminal code already in use
		 */
		sprintf(numStr, "%u", pmkSySt[pmkStkP+1].ival);
		pmkLog(&pmkSySt[pmkStkP+1].srcp, 120, sevERR, numStr);
	    } else {
		pmkSeSt[pmkStkP+1].ival = pmkSySt[pmkStkP+1].ival;
	    }/*if*/
	  	break;}
    case 28: { /* error_recovery_data =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 29: { /* error_recovery_data = ',' insert_cost ',' delete_cost print_symbol; */

	    pmkSeSt[pmkStkP+1].icost = pmkSeSt[pmkStkP+2].icost;
	    pmkSeSt[pmkStkP+1].dcost = pmkSeSt[pmkStkP+4].dcost;
	    pmkSeSt[pmkStkP+1].sval = pmkSeSt[pmkStkP+5].sval;
	    pmkSeSt[pmkStkP+1].nullf = FALSE;
	  	break;}
    case 30: { /* insert_cost =; */

	    pmkSeSt[pmkStkP+1].icost = 1;
	  	break;}
    case 31: { /* insert_cost = INTEGER; */

	    pmkSeSt[pmkStkP+1].icost = pmkSySt[pmkStkP+1].ival;
	  	break;}
    case 32: { /* delete_cost =; */

	    pmkSeSt[pmkStkP+1].dcost = 1;
	  	break;}
    case 33: { /* delete_cost = INTEGER; */

	    pmkSeSt[pmkStkP+1].dcost = pmkSySt[pmkStkP+1].ival;
	  	break;}
    case 34: { /* print_symbol =; */

	    pmkSeSt[pmkStkP+1].sval = NULL;
	  	break;}
    case 35: { /* print_symbol = '=>' terminal; */

	    pmkSeSt[pmkStkP+1].sval = pmkSeSt[pmkStkP+2].sval;
	  	break;}
    case 36: { /* attribute_section = '%%ATTRIBUTES' attributes ';' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
		break;}
    case 37: { /* attributes = attribute; */

	  if (pmkSeSt[pmkStkP+1].sval)
	    grmAttrDecls = appendStrList(pmkSeSt[pmkStkP+1].sval, NULL);
	  else
	    grmAttrDecls = NULL;
	  grmAttrNames = appendStrList(pmkSeSt[pmkStkP+1].sval2, NULL);
		break;}
    case 38: { /* attributes = attributes ',' attribute; */

          if (pmkSeSt[pmkStkP+3].sval)
	    grmAttrDecls = appendStrList(pmkSeSt[pmkStkP+3].sval, grmAttrDecls);
	  grmAttrNames = appendStrList(pmkSeSt[pmkStkP+3].sval2, grmAttrNames);
          if ((pmkSeSt[pmkStkP+3].sval && !pmkSeSt[pmkStkP+1].sval) ||
	      (!pmkSeSt[pmkStkP+3].sval && pmkSeSt[pmkStkP+1].sval))
	    tmkLog(pmkSeSt[pmkStkP+3].srcp, 65, sevERR, "grammar attribute");
		break;}
    case 39: { /* attribute = IDENTIFIER optional_decl; */

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
    case 40: { /* optional_decl =; */

	  pmkSeSt[pmkStkP+1].sval = NULL;
		break;}
    case 41: { /* optional_decl = '%%'; */

	  pmkSeSt[pmkStkP+1].sval = pmkSySt[pmkStkP+1].sval;
		break;}
    case 42: { /* error_handling_section = recovery_aux recovery_parts endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSeSt[pmkStkP+1].srcp;
		break;}
    case 43: { /* recovery_aux = '%%RECOVERY'; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
		break;}
    case 50: { /* meta_part = 'META' meta_definitions; */

	  pmkLog(&pmkSySt[pmkStkP+1].srcp, 132, sevWAR, "META");
		break;}
    case 54: { /* meta_name = terminal; */

	  terminals_set = SymSetAlloc();
		break;}
    case 55: { /* terminals = terminal; */

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
		/* ERROR Ambiguous symbol, Terminal expected. */
		pmkLog(&pmkSeSt[pmkStkP+1].srcp, 117, sevERR, pmkSeSt[pmkStkP+1].sval);
		SymSetIns(terminals_set, symRef);
	    }/*if*/
	  	break;}
    case 56: { /* terminals = terminals ',' terminal; */

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
    case 59: { /* separator_part = separator_aux '(' terminals ')' ';'; */

	    recovery_spec.separators = terminals_set;
	  	break;}
    case 60: { /* separator_aux = 'SEPARATOR'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 61: { /* fiducial_part = fiducial_aux '(' terminals ')' ';'; */

	    recovery_spec.fiducials = terminals_set;
	  	break;}
    case 62: { /* fiducial_aux = 'FIDUCIAL'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 63: { /* skip_part = skip_aux '(' terminals ')' ';'; */

	    recovery_spec.skips = terminals_set;
	  	break;}
    case 64: { /* skip_aux = 'SKIP'; */

	    terminals_set = SymSetAlloc();
	  	break;}
    case 65: { /* rule_section = '%%RULES' __genSym#1 rules endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  rulesSrcp = pmkSySt[pmkStkP+1].srcp;
        	break;}
    case 66: { /* __genSym#1 =; */
 init_action_structs(TRUE); 	break;}
    case 69: { /* rule = nonterminal '=' rhss ';'; */

	    /* Main routine for analysis of rhss associated with a single lhs
	     */
	    if (!SeriousErr) analyze_rhss(temp_lhs, pmkSeSt[pmkStkP+3].rhslist);
	  	break;}
    case 70: { /* nonterminal = term_or_nonterm; */

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
    case 71: { /* rhss = rhs; */

	    pmkSeSt[pmkStkP+1].rhslist_last = pmkSeSt[pmkStkP+1].rhslist;
	  	break;}
    case 72: { /* rhss = rhss '!' rhs; */

	    pmkSeSt[pmkStkP+1].rhslist_last->nxtrhs = pmkSeSt[pmkStkP+3].rhslist;
	    pmkSeSt[pmkStkP+1].rhslist = pmkSeSt[pmkStkP+1].rhslist;
	    pmkSeSt[pmkStkP+1].rhslist_last = pmkSeSt[pmkStkP+3].rhslist;
	  	break;}
    case 73: { /* rhs = symbols_or_actions modifiers; */

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
    case 74: { /* symbols_or_actions =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 75: { /* symbols_or_actions = symbols_or_actions symbol_or_action; */

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
    case 77: { /* Alternatives = Alternatives '|' modifiers symbols_or_actions modifiers; */

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
    case 76: { /* Alternatives = modifiers symbols_or_actions modifiers; */

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
    case 78: { /* symbol_or_action = symbol; */

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
    case 79: { /* symbol_or_action = '{' modifiers symbols_or_actions modifiers '}'; */

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
		    /* This shouldn't happen */
		    printf("Non terminal generated by PMK is equal to user's symbol");
		}/*if*/

		/* Make list */
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
    case 80: { /* symbol_or_action = '[' modifiers symbols_or_actions modifiers ']'; */
{
	    /* Convert this to "'(' '|' modifiers symbols_or_actions modifiers ')' */
	    altr_lst *altrs;
	    altr_lst *altr;

	    /* Create the empty alternative */
	    altrs = altr_lstAlloc();
	    altrs->altr = prod_elnodeAlloc();
	    altrs->altr->node_kind = null_node_kind;

	    /* Then the other part */
	    if (pmkSeSt[pmkStkP+3].nullf) {
		pmkSeSt[pmkStkP+3].rule_elnode = prod_elnodeAlloc();
		pmkSeSt[pmkStkP+3].rule_elnode->node_kind = null_node_kind;
		pmkSeSt[pmkStkP+3].rule_elnode_last =
		    pmkSeSt[pmkStkP+3].rule_elnode;
		if (!(pmkSeSt[pmkStkP+4].nullf) && !(pmkSeSt[pmkStkP+2].nullf)) {
		    /* Test red and nored sets intersection
		     */
		    if (pmkSeSt[pmkStkP+2].red_set != NULL &&
			pmkSeSt[pmkStkP+4].nored_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+2].red_set, pmkSeSt[pmkStkP+2].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+4].srcp, 113, sevERR, syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+2].red_set = NULL;
			}/*if*/
		    }/*if*/
		    if (pmkSeSt[pmkStkP+2].nored_set != NULL &&
			pmkSeSt[pmkStkP+4].red_set != NULL)
		    {
			if (modify_intersect_set == NULL) {
			    modify_intersect_set = SymSetAlloc();
			}/*if*/
			SymSetClear(modify_intersect_set);
			SymSetInter(pmkSeSt[pmkStkP+2].red_set, pmkSeSt[pmkStkP+2].nored_set,
				    modify_intersect_set);
			if (!(SymSetEmpty(modify_intersect_set))) {
			    syms_str = makeSymStr(modify_intersect_set);
			    pmkLog(&pmkSeSt[pmkStkP+4].srcp, 113, sevERR, syms_str);
			    free(syms_str);
			    pmkSeSt[pmkStkP+2].red_set = NULL;
			}/*if*/
		    }/*if*/
		}/*if*/
	    }/*if*/

	    /* Make list */
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
		pmkSeSt[pmkStkP+3].rule_elnode_last = pmkSeSt[pmkStkP+4].rule_elnode;
	    }/*if*/

	    altr = altr_lstAlloc();

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
		altr->altr = pmkSeSt[pmkStkP+2].rule_elnode;
	    } else {
		altr->altr = pmkSeSt[pmkStkP+3].rule_elnode;
	    }/*if*/
	    altrs->nxtalt = altr;

	    /* Generate a new symbol node (with a new symbol)
	     * keep symbols_or_actions's rule_nodelist in the symbol node
	     */
	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, nts_symb);
	    lookup(gensym(), sym_kind_set, &symRef, &searchResult);
	    vocabulary[symRef]->symbol_typ = nts_symb;
	    vocabulary[symRef]->syminfo.firstp = -1;
	    if (confl_search == searchResult || found_search == searchResult) {
		/* This shouldn't happen */
		printf("Non terminal generated by PMK is equal to user's symbol");
	    }/*if*/

	    /* Make list */
	    SymSetIns(on_right, symRef);
	    pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
	    pmkSeSt[pmkStkP+1].rule_elnode->node_kind = sym_node_kind;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.sym_ind = symRef;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.newnont = TRUE;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.rplc_info = altrs_rplc;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.sym_node.altrs_seq = altrs;
	    pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+1].rule_elnode;
	    pmkSeSt[pmkStkP+1].nullf = FALSE;

	  }	break;}
    case 81: { /* symbol_or_action = '(' Alternatives ')'; */

	    /* Generate a new symbol node (with a new symbol)
	     * keep symbols_or_actions's rule_nodelist in the symbol node
	     */
	    SetClear(sym_kind_set, unknown_symb + 1);
	    SetIns(sym_kind_set, nts_symb);
	    lookup(gensym(), sym_kind_set, &symRef, &searchResult);
	    vocabulary[symRef]->symbol_typ = nts_symb;
	    vocabulary[symRef]->syminfo.firstp = -1;
	    if (confl_search == searchResult || found_search == searchResult) {
		/* This shouldn't happen */
		printf("Non terminal generated by PMK is equal to user's symbol");
	    }/*if*/

	    /* Make list */
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
    case 82: { /* symbol_or_action = modifiers action modifiers; */

	    if (!(pmkSeSt[pmkStkP+3].nullf) && !(pmkSeSt[pmkStkP+1].nullf)) {
		/* Test red and nored sets intersection */
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
    case 83: { /* modifiers =; */

	    pmkSeSt[pmkStkP+1].nullf = TRUE;
	  	break;}
    case 84: { /* modifiers = modifiers modifier; */

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
    case 85: { /* modifier = reduce_modifier; */

	    pmkSeSt[pmkStkP+1].red_set = pmkSeSt[pmkStkP+1].red_set;
	    pmkSeSt[pmkStkP+1].nored_set = NULL;
	  	break;}
    case 86: { /* modifier = reduce_not_modifier; */

	    pmkSeSt[pmkStkP+1].nored_set = pmkSeSt[pmkStkP+1].nored_set;
	    pmkSeSt[pmkStkP+1].red_set = NULL;
	  	break;}
    case 87: { /* reduce_modifier = <+red_aux> '(' terminals ')'; */

	    pmkSeSt[pmkStkP+1].red_set = terminals_set;
	  	break;}
    case 88: { /* <+red_aux> = '%+'; */

	    terminals_set = SymSetAlloc();
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 89: { /* reduce_not_modifier = <-red_aux> '(' terminals ')'; */

	    pmkSeSt[pmkStkP+1].nored_set = terminals_set;
	  	break;}
    case 90: { /* <-red_aux> = '%-'; */

	    terminals_set = SymSetAlloc();
	    pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  	break;}
    case 91: { /* action = '%%'; */

	    pmkSeSt[pmkStkP+1].rule_elnode = prod_elnodeAlloc();
	    pmkSeSt[pmkStkP+1].rule_elnode->node_kind = act_node_kind;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_srcp = pmkSySt[pmkStkP+1].srcp;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_start = pmkSySt[pmkStkP+1].fpos;
	    pmkSeSt[pmkStkP+1].rule_elnode->node_info.act_node.act_length = pmkSySt[pmkStkP+1].length;
	    pmkSeSt[pmkStkP+1].rule_elnode_last = pmkSeSt[pmkStkP+1].rule_elnode;
	  	break;}
    case 92: { /* export_section = '%%EXPORT' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  if (exportSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    exportSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 93: { /* scanner_section = '%%SCANNER' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  if (scannerSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    scannerSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 94: { /* insertsymbol_section = '%%INSERTSYMBOL' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  if (insertSymbSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    insertSymbSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    case 95: { /* deletesymbol_section = '%%DELETESYMBOL' endOpt; */

	  pmkSeSt[pmkStkP+1].srcp = pmkSySt[pmkStkP+1].srcp;
	  if (deleteSymbSection)
	    pmkLog(pmkSySt[pmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    deleteSymbSection = tmkNewCode(pmkSySt[pmkStkP+1].fpos, pmkSySt[pmkStkP+1].length);
		break;}
    default: break; }
}/*pmkPaSema()*/

