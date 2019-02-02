/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-21
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/nfa.h,v 1.1 2002/06/25 20:04:46 Thomas Nilsson Exp $
 *
 * $Log: nfa.h,v $
 * Revision 1.1  2002/06/25 20:04:46  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.4  1993/04/30 12:33:03  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.3  1993/04/27  14:21:51  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.2  1993/04/23  11:08:58  tools
 * Updated to use rules instead of tokens.
 * External functions prepared for ANSI-C
 *
 * Revision 1.1  1993/03/24  09:24:20  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:07  tools
 * Initial revision
 * 
 *
 */

#ifndef _nfa_h_
#define _nfa_h_

typedef struct NFA *NFA;

#include "common.h"
#include "nfas.h"
#include "rule.h"

typedef enum NFAtype {
  nfaNONE,
  nfaFINAL,
  nfaCUT
} NFAtype;

typedef struct NFA {
  int node;			/* Node number */
  short charMin;		/* Lower character of character range */
  short charMax;		/* Upper character of character range */
  NFAtype type;			/* Type of node */
  Rule rule;			/* Rule */
  NFAs follow;			/* List of nodes following character range */
  NFA next;
} NFAItem;

extern int nfaSize;
extern NFA nfaRoot;

extern void nfaCreate(void);
extern void nfaOptimize(void);
extern void nfaDump(void);
extern void nfaPrint(void);

#endif


