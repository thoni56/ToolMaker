/*----------------------------------------------------------------------*\

    lmkPaSema.c

    ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include "lmk_i.h"
#include "lmkScan.h"
#include "tmkCommon.h"

extern lmkScContext lmkCtxt;

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
#include "lmkCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct lmkGrammar {
    TmkSrcp srcp;
    MessNodeP mline;
    int ival;
    char *sval;
} lmkGrammar;

/* END %%ATTRIBUTES */

extern short lmkStkP;
extern LmkToken lmkSySt[];
extern lmkGrammar lmkSeSt[];

/* %%DECLARATIONS - User data and routines */


#include <stdlib.h>
#include <string.h>
#include "lmk_i.h"
#include "lmkCommon.h"
#include "lmkList.h"

static int messCnt = 0;

static MessSectNodeP newMessSect(msNode)
  MessSectNodeP msNode;
{
  MessSectNodeP p,q;

  for (p = messSectRoot; p; q=p, p=p->next)
    if (strcmp(p->name, msNode->name) == 0)
      return NULL;
  if (messSectRoot)
    q->next = msNode;
  else
    messSectRoot = msNode;
  return msNode;
}


/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * lmkPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void lmkPaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 7: { /* messages_section = messages_header message_lines optional_end; */
{
          MessSectNodeP p = (MessSectNodeP) malloc(sizeof(MessSectNode));
          p->name = lmkSeSt[lmkStkP+1].sval;
	  p->messCnt = messCnt;
          p->messages = lmkSeSt[lmkStkP+2].mline;
          p->next = NULL;
          if (!newMessSect(p))
	    lmkLog(&lmkSeSt[lmkStkP+1].srcp, 200, sevERR, p->name);
        }	break;}
    case 8: { /* messages_header = '%%MESSAGES' IDENTIFIER; */
{
	  messCnt = 0;
	  lmkSeSt[lmkStkP+1].sval = lmkSySt[lmkStkP+2].sval;
	  lmkSeSt[lmkStkP+1].srcp = lmkSySt[lmkStkP+2].srcp;
	}	break;}
    case 9: { /* message_lines =; */
{
          lmkSeSt[lmkStkP+1].mline = NULL;
        }	break;}
    case 10: { /* message_lines = message_lines message_line; */
{
          MessNodeP p;

          if (lmkSeSt[lmkStkP+1].mline == NULL)
            lmkSeSt[lmkStkP+1].mline = lmkSeSt[lmkStkP+2].mline;
          else {
            for (p = lmkSeSt[lmkStkP+1].mline; p->next; p = p->next);
            p->next = lmkSeSt[lmkStkP+2].mline;
            lmkSeSt[lmkStkP+1].mline= lmkSeSt[lmkStkP+1].mline;
          }
	  messCnt++;
        }	break;}
    case 11: { /* message_line = NUMBER STRING ';'; */
{
          MessNodeP p = (MessNodeP) malloc(sizeof(MessNode));
          p->number = lmkSySt[lmkStkP+1].ival;
          p->text = lmkSySt[lmkStkP+2].sval;
          p->next = NULL;
          lmkSeSt[lmkStkP+1].mline = p;
        }	break;}
    default: break; }
}/*lmkPaSema()*/

