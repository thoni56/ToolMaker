/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-07-12
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/nfas.h,v 1.1 2002/06/25 20:04:47 Thomas Nilsson Exp $
 *
 * $Log: nfas.h,v $
 * Revision 1.1  2002/06/25 20:04:47  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:06  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:11:05  tools
 * External functions prepared for ANSI-C
 *
 * Revision 1.1  1993/03/24  09:24:27  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:09  tools
 * Initial revision
 *
 *
 */

#ifndef _nfas_h_
#define _nfas_h_

typedef struct NFAs *NFAs;

#include "nfa.h"

typedef struct NFAs {
  NFA nfa;
  NFAs next;
} NFAsItem;

extern NFAs nfasInsert(NFAs nfas, NFA nfa);
extern NFAs nfasMerge(NFAs nfas1, NFAs nfas2);
extern NFAs nfasMergeCopy(NFAs nfas1, NFAs nfas2);
extern NFAs nfasDelete(NFAs nfas);
extern void nfasDump(NFAs nfas);
extern void nfasPrint(NFAs nfas);

#endif
