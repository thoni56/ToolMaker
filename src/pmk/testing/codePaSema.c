/*----------------------------------------------------------------------*\

    codePaSema.c

    ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include <stdio.h>

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
#include "codeCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct codeGrammar {
    double floatValue ;
    TmSrcp srcp ;
} codeGrammar;

/* END %%ATTRIBUTES */

extern short codeStkP;
extern TmToken codeSySt[];
extern codeGrammar codeSeSt[];

/* %%DECLARATIONS - User data and routines */


static int noOfItems = 0;


/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * codePaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void codePaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 1: { /* items = __genSym#0; */
 printf("%d items found!\n", noOfItems); 	break;}
    case 3: { /* __genSym#0 = __genSym#0 ITEM; */

        /* Semantic action */
        noOfItems++;
		break;}
    default: break; }
}/*codePaSema()*/

