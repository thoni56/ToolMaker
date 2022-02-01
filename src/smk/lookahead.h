/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1990-06-21
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/lookahead.h,v 1.1 2002/06/25 20:04:44 Thomas Nilsson Exp $
 *
 * $Log: lookahead.h,v $
 * Revision 1.1  2002/06/25 20:04:44  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/08/20 11:33:50  tony
 * Conforms more to ANSI C standard.
 *
 * Revision 1.2  1993/04/23  11:05:20  tools
 * Updated to use rules instead as tokens.
 * External functions prepared for ANSI-C
 *
 * Revision 1.1  1993/03/24  09:24:01  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:02  tools
 * Initial revision
 *
 *
 */

#ifndef _LOOKAHEAD_H_
#define _LOOKAHEAD_H_

typedef struct Lookahead *Lookahead;

#include "rule.h"
#include "nfas.h"
#include "dfa.h"

typedef struct Lookahead {
  Rule rule;
  short lengthPrefix;
  short lengthSuffix;
  AST astPrefix;
  AST astSuffix;
  NFAs nfaPrefix;
  NFAs nfaSuffix;
  DFA dfaPrefix;
  DFA dfaSuffix;
  Lookahead next;
} LookaheadItem;

extern Lookahead lookaheadRoot;

extern Lookahead lookaheadPut();
extern void lookaheadDump();

#endif
