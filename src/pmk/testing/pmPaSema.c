/*----------------------------------------------------------------------*\

	pmPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include <stdio.h>
#include <strings.h>

#include "ttParse.h"
#include "ttList.h"
#include "ttScan.h"
extern ttScContext lexContext;

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
#include "tmCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct pmGrammar {
    int integerValue ;
    char stringValue[256] ;
    Node* list ;
    TmSrcp srcp ;
} pmGrammar;

/* END %%ATTRIBUTES */

extern short pmStkP;
extern TmToken pmSySt[];
extern pmGrammar pmSeSt[];

/* %%DECLARATIONS - User data and routines */


/* Counters for the various contructs */
static int constants, variables, procedures, statements;

/* The node constituting the program */
static Node *program;


/*-----------------------------------------------------------------------------
    makeNode()

    Make a new list node and initialize it.

 */
static Node *makeNode(char *string, int value)
{
    Node *temp;

    temp = (Node *)malloc(sizeof(Node));
    temp->string = (char *)malloc(strlen(string) + 1);
    strcpy(temp->string, string);
    temp->value = value;
    temp->next = NULL;
    return temp;
}


/*-----------------------------------------------------------------------------
    append()

    Append two lists of nodes.

 */
static Node *append(Node *list1, Node *list2)
{
   if (list1->next) return append(list1->next, list2);
    else {
	list1->next = list2;
	return list1;
    }
}


/*-----------------------------------------------------------------------------
    summary()

    Print a summary of the PL/0 program using the Lister.

 */
void summary()
{
  Node *node;
  char buf[256];

  sprintf(buf, "Number of constants:  %u", constants);
  ttLiPrint(buf);
  for (node = program; node; node = node->next) {
    sprintf(buf,"  %s = %d", node->string, node->value);
    ttLiPrint(buf);
  }
  ttLiPrint("");
  sprintf(buf, "Number of variables:  %u", variables);
  ttLiPrint(buf);
  sprintf(buf, "Number of procedures: %u", procedures);
  ttLiPrint(buf);
  sprintf(buf, "Number of statements: %u", statements);
  ttLiPrint(buf);
} 



/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * pmPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void pmPaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 1: { /* <program> = <block> '.'; */

            program = pmSeSt[pmStkP+1].list;
          	break;}
    case 2: { /* <block> = <declarations> <statement>; */

	    pmSeSt[pmStkP+1].list = pmSeSt[pmStkP+1].list;
	  	break;}
    case 3: { /* <declarations> = <constant declaration> <variable declaration> <procedure declarations>; */

	    pmSeSt[pmStkP+1].list = pmSeSt[pmStkP+1].list;
	  	break;}
    case 5: { /* <constant declaration> = 'CONST' <constant definitions> ';'; */

	    pmSeSt[pmStkP+1].list = pmSeSt[pmStkP+2].list;
	  	break;}
    case 4: { /* <constant declaration> =; */

	    pmSeSt[pmStkP+1].list = NULL;
	  	break;}
    case 7: { /* <constant definitions> = <constant definitions> ',' <constant definition>; */

	    pmSeSt[pmStkP+1].list =
		append(pmSeSt[pmStkP+1].list,
		       makeNode(pmSeSt[pmStkP+3].stringValue,
				pmSeSt[pmStkP+3].integerValue));
	  	break;}
    case 6: { /* <constant definitions> = <constant definition>; */

	    pmSeSt[pmStkP+1].list = 
		makeNode(pmSeSt[pmStkP+1].stringValue,
			 pmSeSt[pmStkP+1].integerValue);
	  	break;}
    case 8: { /* <constant definition> = IDENTIFIER '=' NUMBER; */

	    constants++;
	    strcpy(pmSeSt[pmStkP+1].stringValue, pmSySt[pmStkP+1].stringValue);
	    pmSeSt[pmStkP+1].integerValue = pmSySt[pmStkP+3].integerValue;
	  	break;}
    case 12: { /* <identifiers> = <identifiers> ',' IDENTIFIER; */

	    variables++;
	  	break;}
    case 11: { /* <identifiers> = IDENTIFIER; */

	    variables++;
	  	break;}
    case 15: { /* <procedure declaration> = 'PROCEDURE' IDENTIFIER ';' <block> ';'; */

	    procedures++;
	  	break;}
    case 19: { /* <statement> = <assignment statement>; */

	    statements++;
	  	break;}
    case 17: { /* <statement> = <call statement>; */

	    statements++;
	  	break;}
    case 18: { /* <statement> = <compound statement>; */

	    statements++;
	  	break;}
    case 20: { /* <statement> = <if statement>; */

	    statements++;
	  	break;}
    case 21: { /* <statement> = <while statement>; */

	    statements++;
	  	break;}
    default: break; }
}/*pmPaSema()*/

