/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-17/tools@lion
 * CREATED: 1990-06-21
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/lookahead.c,v 1.1 2002/06/25 20:04:44 Thomas Nilsson Exp $
 *
 * $Log: lookahead.c,v $
 * Revision 1.1  2002/06/25 20:04:44  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:32:50  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:04:35  tools
 * Updated to use rules instead as tokens.
 *
 * Revision 1.1  1993/03/24  09:23:59  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:35:24  tools
 * Initial revision
 * 
 *
 */

#include <stdio.h>
#include "ast.h"
#include "lookahead.h"
#include "rule.h"
#include "smalloc.h"

Lookahead lookaheadRoot=NULL;

static Lookahead lookaheadEnd=NULL;

Lookahead lookaheadPut(rule,astPrefix,lengthPrefix,astSuffix,lengthSuffix)
     Rule rule;
     AST astPrefix;
     short lengthPrefix;
     AST astSuffix;
     short lengthSuffix;
{
  Lookahead lookahead;

  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next)
    if(lookahead->rule==rule) return lookahead;
  lookahead=(Lookahead)smalloc(sizeof(LookaheadItem));
  lookahead->rule=rule;
  lookahead->lengthPrefix=lengthPrefix;
  lookahead->lengthSuffix=lengthSuffix;
  lookahead->astPrefix=astPrefix;
  lookahead->astSuffix=astSuffix;
  lookahead->nfaPrefix=NULL;
  lookahead->nfaSuffix=NULL;
  lookahead->dfaPrefix=NULL;
  lookahead->dfaSuffix=NULL;
  lookahead->next=NULL;
  if(lookaheadRoot)
    lookaheadEnd=lookaheadEnd->next=lookahead;
  else
    lookaheadEnd=lookaheadRoot=lookahead;
  return lookahead;
}

void lookaheadDump()
{
  Lookahead lookahead;

  printf("Lookahead\n\n");
  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next) {
    printf("Lookahead %3d: ",lookahead->rule->code);
    if(lookahead->lengthPrefix>=0)
      printf("fix prefix %d character\n",lookahead->lengthPrefix);
    else if(lookahead->lengthSuffix>=0)
      printf("fix suffix %d character\n",lookahead->lengthSuffix);
    else {
      printf("prefix start ");
      nfasDump(lookahead->nfaPrefix);
      printf(" and suffix start ");
      nfasDump(lookahead->nfaSuffix);
      printf("\n");
    }
  }
}
