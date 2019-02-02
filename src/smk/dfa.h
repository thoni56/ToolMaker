/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-21
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/dfa.h,v 1.1 2002/06/25 20:04:43 Thomas Nilsson Exp $
 *
 * $Log: dfa.h,v $
 * Revision 1.1  2002/06/25 20:04:43  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:32:45  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:03:17  tools
 * Updated to handle multiple vocabularies.
 * External functions prepared for ANSI-C.
 *
 * Revision 1.1  1993/03/24  09:23:51  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:22:58  tools
 * Initial revision
 * 
 *
 */

#ifndef _DFA_H_
#define _DFA_H_

typedef struct DFA *DFA;

#include "pack.h"
#include "nfas.h"

/*
 * KEY UNIQUE: closure
 * KEY UNIQUE: node
 */

typedef struct DFA {
  int node;			/* Node number */
  DFA *transition;		/* Transisition vector to other nodes */
  NFAs closure;			/* DFA closure (key) */
  Rule accept;			/* Accepting rule for this DFA node */
  int set;			/* Used when optimizing  */
  DFA list;			/* Also used when optimizing */
  DFA next;
} DFAItem;
  
extern DFA dfaRoot;
extern int dfaSize;

extern Pack dfaPack(void);
extern void dfaAccept(void);
extern void dfaCreate(void);
extern void dfaDump(void);
extern void dfaDumpAccept(void);
extern void dfaDumpOptimize(void);
extern void dfaOptimize(void);
extern void dfaPrint(void);

#endif
