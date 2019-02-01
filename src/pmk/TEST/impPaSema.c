/*----------------------------------------------------------------------*\

	impPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

/* .pmk-import */
#include <stdio.h>
#include "ast.h"
#include "impScan.h"
#include "impList.h"
extern impContext impcontext;
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
#include "impCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct impGrammar {
    Ast ast         /* An abstract syntax tree */;
    TmSrcp srcp      /* Source position         */;
} impGrammar;

/* END %%ATTRIBUTES */

extern short impStkP;
extern TmToken impSySt[];
extern impGrammar impSeSt[];

/* %%DECLARATIONS - User data and routines */

/* .pmk-declarations */

/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * impPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void impPaSema(rule)
int rule;			/* IN production number */
{
    switch (rule) {
          case 1: { /* goal = statements_opt; */
 
  impAstRoot = impSeSt[impStkP+1].ast; 
	break;}
    case 3: { /* statements_opt = statements_opt statement; */
 
  impSeSt[impStkP+2].ast->next=impSeSt[impStkP+1].ast; 
  impSeSt[impStkP+1].ast=impSeSt[impStkP+2].ast; 
	break;}
    case 2: { /* statements_opt =; */
 
  impSeSt[impStkP+1].ast=NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 4: { /* statement = TEXT; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_TEXT,impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1, 
                              impSySt[impStkP+1].text, NULL, NULL, NULL, NULL);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 5: { /* statement = keep_statement; */
 /* transfer all attributes */ 	break;}
    case 10: { /* statement = set_statement; */
 /* transfer all attributes */ 	break;}
    case 11: { /* statement = eset_statement; */
 /* transfer all attributes */ 	break;}
    case 6: { /* statement = insert_statement; */
 /* transfer all attributes */ 	break;}
    case 13: { /* statement = if_statement; */
 /* transfer all attributes */ 	break;}
    case 15: { /* statement = loop_statement; */
 /* transfer all attributes */ 	break;}
    case 12: { /* statement = message_statement; */
 /* transfer all attributes */ 	break;}
    case 14: { /* statement = region_statement; */
 /* transfer all attributes */ 	break;}
    case 7: { /* statement = include_statement; */
 /* transfer all attributes */ 	break;}
    case 8: { /* statement = einclude_statement; */
 /* transfer all attributes */ 	break;}
    case 9: { /* statement = process_statement; */
 /* transfer all attributes */ 	break;}
    case 16: { /* keep_statement = '%%KEEP'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_KEEP,
                                   impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1, impSySt[impStkP+1].text, 
				   NULL, NULL, NULL, NULL);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 17: { /* set_statement = '%%SET' ident '(' values_opt ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				  AST_ASSIGN, 0, impSeSt[impStkP+2].ast, impSeSt[impStkP+4].ast, NULL, NULL, NULL); 
  free(impSySt[impStkP+5].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 18: { /* set_statement = '%%SET' ident '(' ',' values_opt ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				  AST_APPEND, 0, impSeSt[impStkP+2].ast, impSeSt[impStkP+5].ast, NULL, NULL, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 19: { /* eset_statement = '%%ESET' ident '(' eval_expressions_opt ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				   AST_ASSIGN, 0, impSeSt[impStkP+2].ast, 
				   impSeSt[impStkP+4].ast, NULL, NULL, NULL); 
  free(impSySt[impStkP+5].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 20: { /* eset_statement = '%%ESET' ident '(' ',' eval_expressions_opt ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				   AST_APPEND, 0, impSeSt[impStkP+2].ast,
				   impSeSt[impStkP+5].ast, NULL, NULL, NULL); 
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 21: { /* insert_statement = '%%(' expression ')'; */
 
  impSeSt[impStkP+1].ast=impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				   AST_EVAL, 0, impSeSt[impStkP+2].ast,  impSySt[impStkP+3].text, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 22: { /* if_statement = '%%IF' '(' condition ')' statements_opt else_part '%%ENDIF'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, impSySt[impStkP+7].srcp, impSeSt[impStkP+6].srcp, 
				 AST_IF, 0, impSeSt[impStkP+3].ast, impSeSt[impStkP+5].ast, 
				 impSeSt[impStkP+6].ast, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 25: { /* else_part = '%%ELSIF' '(' condition ')' statements_opt else_part; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, impSeSt[impStkP+1].srcp, 
			       AST_ELSIF, 0, impSeSt[impStkP+3].ast, impSeSt[impStkP+5].ast, 
			       impSeSt[impStkP+6].ast, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 24: { /* else_part = '%%ELSE' statements_opt; */
 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast; 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 23: { /* else_part =; */
 
  impSeSt[impStkP+1].ast = NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 26: { /* loop_statement = '%%LOOP' '(' ident '<=' expression ')' statements_opt '%%ENDLOOP' '(' ident ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, impSySt[impStkP+8].srcp, nulSrcp, 
				   AST_LOOP1, 0, impSeSt[impStkP+3].ast, 
                                impAstNode(impSeSt[impStkP+5].srcp, nulSrcp, nulSrcp, 
					   AST_EVAL, 0, impSeSt[impStkP+5].ast, "", NULL, NULL, NULL),
                                impSeSt[impStkP+7].ast, impSeSt[impStkP+10].ast, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 27: { /* loop_statement = '%%LOOP' '(' ident ',' variable ')' statements_opt '%%ENDLOOP' '(' ident ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, impSySt[impStkP+8].srcp, nulSrcp, 
				   AST_LOOP2, 0, impSeSt[impStkP+3].ast, 
				   impSeSt[impStkP+5].ast, impSeSt[impStkP+7].ast, impSeSt[impStkP+10].ast, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 28: { /* message_statement = '%%MESSAGE' '(' expression ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_MESSAGE, 0, impSeSt[impStkP+3].ast, NULL, NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 29: { /* region_statement = '%%BEGIN' '(' ident parameters_opt locals_opt ')' statements_opt '%%END' '(' ident ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, impSySt[impStkP+8].srcp, nulSrcp, 
				     AST_REGION, 0, impSeSt[impStkP+3].ast, impSeSt[impStkP+4].ast,
                                  impSeSt[impStkP+5].ast, impSeSt[impStkP+7].ast, impSeSt[impStkP+10].ast); 
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 31: { /* parameters_opt = '(' idents ')'; */

  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast;
  free(impSySt[impStkP+3].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 30: { /* parameters_opt =; */

  impSeSt[impStkP+1].ast = NULL;
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 33: { /* locals_opt = ',' idents; */

  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast;
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 32: { /* locals_opt =; */

  impSeSt[impStkP+1].ast = NULL;
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 35: { /* include_statement = '%%INCLUDE' '(' ident ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_INCLUDE, 0, impSeSt[impStkP+3].ast, NULL, impSySt[impStkP+4].text, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 37: { /* include_statement = '%%INCLUDE' '(' ident '(' values_opt ')' ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_INCLUDE, 0, impSeSt[impStkP+3].ast, 
                                   impAstNode(impSeSt[impStkP+5].srcp, nulSrcp, nulSrcp, 
					      AST_PARAMS, 0, impSeSt[impStkP+5].ast, NULL, NULL, NULL, NULL),
                                    impSySt[impStkP+7].text, NULL, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 36: { /* include_statement = '%%INCLUDE' '(' quoted_string ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_PROCESS, 0, impSeSt[impStkP+3].ast, NULL, FALSE, impSySt[impStkP+4].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 34: { /* include_statement = '%%INCLUDE' '(' ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_PROCESS, 0, NULL, NULL, FALSE, impSySt[impStkP+3].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 39: { /* einclude_statement = '%%EINCLUDE' '(' ident ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				       AST_INCLUDE, 0, impSeSt[impStkP+3].ast, NULL, impSySt[impStkP+4].text, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 41: { /* einclude_statement = '%%EINCLUDE' '(' ident '(' eval_expressions_opt ')' ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				       AST_INCLUDE, 0, impSeSt[impStkP+3].ast, 
				       impAstNode(impSeSt[impStkP+5].srcp, nulSrcp, nulSrcp, 
						  AST_PARAMS, 0, impSeSt[impStkP+5].ast, 
						  NULL, NULL, NULL, NULL), 
				       impSySt[impStkP+7].text, NULL, NULL); 
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 40: { /* einclude_statement = '%%EINCLUDE' '(' quoted_string ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_PROCESS, 0, 
				       impSeSt[impStkP+3].ast, NULL, FALSE, impSySt[impStkP+4].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 38: { /* einclude_statement = '%%EINCLUDE' '(' ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				       AST_PROCESS, 0, NULL, NULL, FALSE, impSySt[impStkP+3].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 43: { /* process_statement = '%%PROCESS' '(' file_name ',' file_name ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_PROCESS, 0, impSeSt[impStkP+3].ast, 
				      impSeSt[impStkP+5].ast, FALSE, impSySt[impStkP+6].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 42: { /* process_statement = '%%PROCESS' '(' file_name ')'; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				      AST_PROCESS, 0, impSeSt[impStkP+3].ast, NULL, TRUE, impSySt[impStkP+4].text, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 45: { /* condition = condition 'OR' and_condition; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
			       AST__OR, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 44: { /* condition = and_condition; */
 
  /* Transfer all attributes */ 
	break;}
    case 47: { /* and_condition = and_condition 'AND' not_condition; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				   AST__AND, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				   NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 46: { /* and_condition = not_condition; */
 
  /* Transfer all attributes */ 
	break;}
    case 49: { /* not_condition = 'NOT' boolean_expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST__NOT, 0, 
				  impSeSt[impStkP+2].ast, NULL, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 48: { /* not_condition = boolean_expression; */
 
  /* Transfer all attributes */ 
	break;}
    case 62: { /* boolean_expression = system_call; */
 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+1].ast; 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
	break;}
    case 50: { /* boolean_expression = expression '=' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__EQ, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 51: { /* boolean_expression = expression '#' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__NEQ, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 52: { /* boolean_expression = expression '>' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__GT, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 53: { /* boolean_expression = expression '<' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__LT, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 54: { /* boolean_expression = expression '>=' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__GE, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 55: { /* boolean_expression = expression '<=' expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				       AST__LE, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 57: { /* boolean_expression = variable '(' '?R' ')'; */
 
  if (impSeSt[impStkP+1].ast->type == AST_INTEGER) {
    char errStr[19];
    strcat(errStr, "INTEGER**IDENTIFIER");
    errStr[7] = (char)0xff;
    impLog(&impSeSt[impStkP+1].ast->srcp, 103, sevERR, errStr);
  }
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+3].srcp, nulSrcp, nulSrcp, AST__RDEFINED, 0, 
				       impSeSt[impStkP+1].ast, NULL, NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+3].srcp;
	break;}
    case 58: { /* boolean_expression = variable '(' '?V' ')'; */
 
  if (impSeSt[impStkP+1].ast->type == AST_INTEGER) {
    char errStr[19];
    strcat(errStr, "INTEGER**IDENTIFIER");
    errStr[7] = (char)0xff;
    impLog(&impSeSt[impStkP+1].ast->srcp, 103, sevERR, errStr);
  }
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+3].srcp, nulSrcp, nulSrcp, AST__DEFINED, 0, 
				       impSeSt[impStkP+1].ast, NULL, NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+3].srcp;
	break;}
    case 59: { /* boolean_expression = variable '(' '?' ')'; */
 
  if (impSeSt[impStkP+1].ast->type == AST_INTEGER) {
    char errStr[19];
    strcat(errStr, "INTEGER**IDENTIFIER");
    errStr[7] = (char)0xff;
    impLog(&impSeSt[impStkP+1].ast->srcp, 103, sevERR, errStr);
  }
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+3].srcp, nulSrcp, nulSrcp, AST__DEFINED, 0, 
				       impSeSt[impStkP+1].ast, NULL, NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+3].srcp;
	break;}
    case 60: { /* boolean_expression = variable '(' '*' ')'; */
 
  if (impSeSt[impStkP+1].ast->type == AST_INTEGER) {
    char errStr[19];
    strcat(errStr, "INTEGER*IDENTIFIER");
    errStr[7] = (char)0xff;
    impLog(&impSeSt[impStkP+1].ast->srcp, 103, sevERR, errStr);
  }
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+3].srcp, nulSrcp, nulSrcp, AST__NONEMPTY, 0, 
				       impSeSt[impStkP+1].ast, NULL, NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+3].srcp;
	break;}
    case 56: { /* boolean_expression = variable '(' values_opt ')'; */
 
  if (impSeSt[impStkP+1].ast->type == AST_INTEGER) {
    char errStr[19];
    strcat(errStr, "INTEGER**IDENTIFIER");
    errStr[7] = (char)0xff;
    impLog(&impSeSt[impStkP+1].ast->srcp, 103, sevERR, errStr);
  }
  impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				       AST__IN, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				       NULL, NULL, NULL); 
  free(impSySt[impStkP+4].text);
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+3].srcp;
	break;}
    case 61: { /* boolean_expression = '(' condition ')'; */
 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast; 
  free(impSySt[impStkP+3].text);
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+2].srcp;
	break;}
    case 63: { /* system_call = 'IMP$SYSTEM' '(' ident ',' ident ')'; */

  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				AST__SYSTEM, 0, impSeSt[impStkP+3].ast, impSeSt[impStkP+5].ast, 
				NULL, NULL, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 64: { /* system_call = 'IMP$SYSTEM' '(' quoted_string ',' ident ')'; */

  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				AST__SYSTEM, 0, impSeSt[impStkP+3].ast, impSeSt[impStkP+5].ast, 
				NULL, NULL, NULL);
  free(impSySt[impStkP+6].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 66: { /* eval_expressions_opt = eval_expressions; */
 
  /* Transfer all attributes */ 
	break;}
    case 65: { /* eval_expressions_opt =; */
 
  impSeSt[impStkP+1].ast = NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 68: { /* eval_expressions = eval_expressions ',' expression; */
 
  impSeSt[impStkP+3].ast = impAstNode(impSeSt[impStkP+3].srcp, nulSrcp, nulSrcp, AST_EVAL, 0, 
			       impSeSt[impStkP+3].ast, "", NULL, NULL, NULL);
  impSeSt[impStkP+3].ast->next = impSeSt[impStkP+1].ast; 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+3].ast; 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
	break;}
    case 67: { /* eval_expressions = expression; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				     AST_EVAL, 0, impSeSt[impStkP+1].ast, "", NULL, NULL, NULL);
	break;}
    case 70: { /* expression = expression '+' term; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				AST__PLUS, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 71: { /* expression = expression '-' term; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, 
				AST__MINUS, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, 
				NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 69: { /* expression = term; */

  /* Transfer all attributes */ 
	break;}
    case 73: { /* term = term '*' factor; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, AST__TIMES, 0,
			  impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 74: { /* term = term '/' factor; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+2].srcp, nulSrcp, nulSrcp, AST__DIVID, 0,
			  impSeSt[impStkP+1].ast, impSeSt[impStkP+3].ast, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+2].srcp;
	break;}
    case 72: { /* term = factor; */
 
  /* Transfer all attributes */ 
	break;}
    case 75: { /* factor = operand; */
 
  /* Transfer all attributes */
	break;}
    case 76: { /* factor = '-' factor; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST__NEG, 0, 
			    impSeSt[impStkP+2].ast, NULL, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 77: { /* operand = quoted_string; */
 
  /* Transfer all attributes */
	break;}
    case 78: { /* operand = variable; */
 
  /* Transfer all attributes */
	break;}
    case 79: { /* operand = '(' expression ')'; */

  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast;
  free(impSySt[impStkP+3].text);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 80: { /* variable = ident index_opt; */

  if (impSeSt[impStkP+2].ast || impSeSt[impStkP+1].ast->type != AST_INTEGER)
    impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_GET, 0, 
			       impSeSt[impStkP+1].ast, impSeSt[impStkP+2].ast, NULL, NULL, NULL);
  /* else */
    /* Transfer all attributes */
	break;}
    case 81: { /* variable = value_list index_opt; */

  impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, 
			     AST_GET, 0, impSeSt[impStkP+1].ast, impSeSt[impStkP+2].ast, NULL, NULL, NULL);
	break;}
    case 83: { /* index_opt = '[' expression ']'; */
 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast; 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+2].srcp;
	break;}
    case 82: { /* index_opt =; */
 
  impSeSt[impStkP+1].ast=NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 85: { /* idents = idents ',' ident; */
 
  impSeSt[impStkP+3].ast->next = impSeSt[impStkP+1].ast; 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+3].ast; 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
	break;}
    case 84: { /* idents = ident; */
 
  /* Transfer all attributes */ 
	break;}
    case 86: { /* ident = unquoted_string; */

  if (impSeSt[impStkP+1].ast->type != AST_INTEGER)
    impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, 
			    AST_IDENT, 0, impSeSt[impStkP+1].ast, NULL, NULL, NULL, NULL);
  /* else */
    /* Transfer all attributes */
	break;}
    case 88: { /* unquoted_string = unquoted_string unquoted_string_item; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, AST__CONCAT, 0,
				     impSeSt[impStkP+1].ast,impSeSt[impStkP+2].ast, 
				     NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
	break;}
    case 87: { /* unquoted_string = unquoted_string_item; */
 
  /* Transfer all attributes */ 
	break;}
    case 89: { /* unquoted_string_item = UNQUOT_STRING; */
 
  impSeSt[impStkP+1].ast=impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_UNQUOTED_STRING,
				       impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1,
				       impSySt[impStkP+1].text, NULL, NULL, NULL, NULL);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 91: { /* unquoted_string_item = insert_statement; */
 
  /* Transfer all attributes */
	break;}
    case 90: { /* unquoted_string_item = INTEGER; */

  impSeSt[impStkP+1].ast=impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_INTEGER,
				       impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1,
				       impSySt[impStkP+1].text, NULL, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 92: { /* value_list = '{' values_opt '}'; */

  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_VALUE_LIST, 0, 
			       impSeSt[impStkP+2].ast, NULL, NULL, NULL, NULL);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 94: { /* values_opt = values; */
 
  /* Transfer all attributes */
	break;}
    case 93: { /* values_opt =; */
 
  impSeSt[impStkP+1].ast=NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 95: { /* values = value; */
 
  /* Transfer all attributes */ 
	break;}
    case 96: { /* values = values ',' value; */
 
  impSeSt[impStkP+3].ast->next = impSeSt[impStkP+1].ast; 
  impSeSt[impStkP+1].ast = impSeSt[impStkP+3].ast; 
  impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
	break;}
    case 97: { /* value = literal; */


	break;}
    case 98: { /* value = unquoted_string; */

    
	break;}
    case 99: { /* literal = quoted_string; */
 
  /* Transfer all attributes */ 
	break;}
    case 100: { /* literal = value_list; */

  /* Transfer all attributes */ 
	break;}
    case 102: { /* file_name = quoted_string; */

  /* Transfer all elements */
	break;}
    case 103: { /* file_name = unquoted_string; */

  /* Transfer all elements */
	break;}
    case 101: { /* file_name =; */

  impSeSt[impStkP+1].ast = NULL;
	break;}
    case 104: { /* quoted_string = QUOT_STRING quoted_string_tail; */

{
  if(impSeSt[impStkP+2].ast)
    impSeSt[impStkP+1].ast=impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST__CONCAT, 0,
				  impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_STRING,
					     impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1,
					     impSySt[impStkP+1].text, NULL, NULL, NULL, NULL),
				  impSeSt[impStkP+2].ast, NULL, NULL, NULL);
  else
    impSeSt[impStkP+1].ast=impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, AST_STRING,
				  impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1, 
				  impSySt[impStkP+1].text, NULL, NULL, NULL, NULL);
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
}
	break;}
    case 106: { /* quoted_string_tail = quoted_string_tail quoted_string_item; */

{
  if(impSeSt[impStkP+1].ast) {
    impSeSt[impStkP+1].ast = impAstNode(impSeSt[impStkP+1].srcp, nulSrcp, nulSrcp, AST__CONCAT, 0,
					  impSeSt[impStkP+1].ast, impSeSt[impStkP+2].ast, 
					  NULL, NULL, NULL);
    impSeSt[impStkP+1].srcp = impSeSt[impStkP+1].srcp;
  } else {
    impSeSt[impStkP+1].ast = impSeSt[impStkP+2].ast;
    impSeSt[impStkP+1].srcp = impSeSt[impStkP+2].srcp;
  }
}
	break;}
    case 105: { /* quoted_string_tail =; */

  impSeSt[impStkP+1].ast = NULL; 
  impSeSt[impStkP+1].srcp = nulSrcp;
	break;}
    case 107: { /* quoted_string_item = QUOT_STRING; */
 
  impSeSt[impStkP+1].ast = impAstNode(impSySt[impStkP+1].srcp, nulSrcp, nulSrcp, 
				       AST_STRING, impSySt[impStkP+1].end-impSySt[impStkP+1].begin+1,
                                       impSySt[impStkP+1].text, NULL, NULL, NULL, NULL); 
  impSeSt[impStkP+1].srcp = impSySt[impStkP+1].srcp;
	break;}
    case 108: { /* quoted_string_item = insert_statement; */
 
  /* Transfer all attributes */
	break;}
    default: break; }
}/*impPaSema()*/

