/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1991-01-10
 *
 * SoftLab ab (c) 1991
 *
 * $Header: /Repository/ToolMaker/src/smk/nfa.c,v 1.1 2002/06/25 20:04:46 Thomas Nilsson Exp $
 *
 * $Log: nfa.c,v $
 * Revision 1.1  2002/06/25 20:04:46  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:01  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:08:28  tools
 * Updated to use vocabularies.
 * Updated to use rules instead of tokens.
 *
 * Revision 1.1  1993/03/24  09:24:18  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.4  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.3  91/08/22  07:21:07  tools
 * Changed handling of EOT and UNKNOWN tokens.
 *
 * Revision 1.2  1991/07/11  10:38:37  tools
 * Added Inherited scanners and Undefined tokens
 *
 * Revision 1.1  1991/01/10  13:34:05  tools
 * Initial revision
 *
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "ast.h"
#include "char.h"
#include "lmprintf.h"
#include "lookahead.h"
#include "nfa.h"
#include "nfas.h"
#include "scanner.h"
#include "smalloc.h"
#include "smkList.h"
#include "smkList.h"
#include "smk_i.h"
#include "vocabulary.h"

int nfaSize=0;
NFA nfaRoot=NULL;

static NFA nfaEnd=NULL;

typedef struct Follow {
  short nullable;
  short length;
  NFAs first;
  NFAs last;
} *Follow, FollowItem;

static Follow followCreate(Rule rule, AST ast)
{
  Follow left;
  Follow right;
  NFAs nfas;

  if(ast==NULL) return NULL;
  left=NULL;
  switch(ast->type) {
  case '/':
    left=followCreate(rule, ast->car);
    right=followCreate(rule, ast->cdr);
    rule->lookahead=lookaheadPut(rule,ast->car,left->length,astInverse(ast->cdr),right->length);
    for(nfas=left->last;nfas!=NULL;nfas=nfas->next)
      nfas->nfa->follow=nfasMergeCopy(nfas->nfa->follow,right->first);
    if(left->nullable)
      left->first=nfasMerge(left->first,right->first);
    else
      nfasDelete(right->first);
    if(right->nullable)
      right->last=nfasMerge(right->last,left->last);
    else
      nfasDelete(left->last);
    left->last=right->last;
    left->nullable=left->nullable && right->nullable;
    if(left->length<0 || right->length<0)
      left->length=-1;
    else
      left->length=left->length+right->length;
    free((char *)right);
    break;
  case '.':
    left=followCreate(rule,ast->car);
    right=followCreate(rule,ast->cdr);
    for(nfas=left->last;nfas!=NULL;nfas=nfas->next)
      nfas->nfa->follow=nfasMergeCopy(nfas->nfa->follow,right->first);
    if(left->nullable)
      left->first=nfasMerge(left->first,right->first);
    else
      nfasDelete(right->first);
    if(right->nullable)
      right->last=nfasMerge(right->last,left->last);
    else
      nfasDelete(left->last);
    left->last=right->last;
    left->nullable=left->nullable && right->nullable;
    if(left->length<0 || right->length<0)
      left->length=-1;
    else
      left->length=left->length+right->length;
    free((char *)right);
    break;
  case '!':
    left=followCreate(rule,ast->car);
    right=followCreate(rule,ast->cdr);
    left->first=nfasMerge(left->first,right->first);
    left->last=nfasMerge(left->last,right->last);
    left->nullable=left->nullable || right->nullable;
    if(left->length!=right->length) left->length=-1;
    free((char *)right);
    break;
  case '*':
    left=followCreate(rule,ast->car);
    for(nfas=left->last;nfas!=NULL;nfas=nfas->next)
      nfas->nfa->follow=nfasMergeCopy(nfas->nfa->follow,left->first);
    /* propogate first/last */
    left->nullable=1;
    left->length=-1;
    break;
  case '+':
    left=followCreate(rule,ast->car);
    for(nfas=left->last;nfas!=NULL;nfas=nfas->next)
      nfas->nfa->follow=nfasMergeCopy(nfas->nfa->follow,left->first);
    /* propogate first/last */
    /* propogate nullable */
    left->length=-1;
    break;
  case '?':
    left=followCreate(rule,ast->car);
    /* propogate first/last */
    left->nullable=1;
    left->length=-1;
    break;
  case 'c':
    if(nfaEnd==NULL)
      nfaRoot=nfaEnd=(NFA)smalloc(sizeof(NFAItem));
    else
      nfaEnd=(nfaEnd->next=(NFA)smalloc(sizeof(NFAItem)));
    nfaEnd->node=nfaSize++;
    nfaEnd->charMin=(intptr_t)(ast->car);
    nfaEnd->charMax=(intptr_t)(ast->cdr);
    nfaEnd->type=nfaNONE;
    nfaEnd->follow=NULL;
    nfaEnd->rule=rule;
    nfaEnd->next=NULL;

    left=(Follow)smalloc(sizeof(FollowItem));
    left->first=nfasInsert(NULL,nfaEnd);
    left->last=nfasInsert(NULL,nfaEnd);
    left->nullable=(nfaEnd->charMin) > (nfaEnd->charMax);
    left->length=left->nullable ? -1 : 1;
    break;
  case '#':
    if(nfaEnd==NULL)
      nfaRoot=nfaEnd=(NFA)smalloc(sizeof(NFAItem));
    else
      nfaEnd=(nfaEnd->next=(NFA)smalloc(sizeof(NFAItem)));
    nfaEnd->node=nfaSize++;
    nfaEnd->charMin=1;
    nfaEnd->charMax=0;
    nfaEnd->type=nfaCUT;
    nfaEnd->follow=NULL;
    nfaEnd->rule=rule;
    nfaEnd->next=NULL;

    left=(Follow)smalloc(sizeof(FollowItem));
    left->first=nfasInsert(NULL,nfaEnd);
    left->last=nfasInsert(NULL,nfaEnd);
    left->nullable=1;
    left->length=0;
    break;
  default:
    break;
  }
  return left;
}

static NFAs nfaConstruct(Rule rule, AST ast)
{
  Follow left;
  NFAs nfas;
  NFAs first;

  left=followCreate(rule, ast);
  if(nfaEnd==NULL)
    nfaRoot=nfaEnd=(NFA)smalloc(sizeof(NFAItem));
  else
    nfaEnd=(nfaEnd->next=(NFA)smalloc(sizeof(NFAItem)));
  nfaEnd->node=nfaSize++;
  nfaEnd->charMin=1;
  nfaEnd->charMax=0;
  nfaEnd->type=nfaFINAL;
  nfaEnd->follow=NULL;
  nfaEnd->rule=rule;
  nfaEnd->next=NULL;

  first=nfasInsert(NULL,nfaEnd);

  for(nfas=left->last;nfas!=NULL;nfas=nfas->next)
    nfas->nfa->follow=nfasMergeCopy(nfas->nfa->follow,first);
  if(left->nullable)
    left->first=nfasMerge(left->first,first);
  else
    nfasDelete(first);
  nfasDelete(left->last);
  first=left->first;
  free((char *)left);
  return first;
}

void nfaCreate()
{
  Vocabulary vocabulary;
  Scanner scanner;
  Lookahead lookahead;
  Rule rule;
  NFA nfa;
  NFAs nfas;

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      scanner->nfa=0;
      for(rule=scanner->rules;rule;rule=rule->next)
  if((rule->type==ruleMATCH || rule->type==ruleSKIP) &&
     rule->ast &&
     rule->ast!=astEOT &&
     rule->ast!=astUNKNOWN)
    scanner->nfa=nfasMerge(scanner->nfa,nfaConstruct(rule,rule->ast));
    }

  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next)
    if(lookahead->lengthPrefix<0 || lookahead->lengthSuffix<0) {
      lookahead->nfaPrefix=nfaConstruct(lookahead->rule,lookahead->astPrefix);
      lookahead->nfaSuffix=nfaConstruct(lookahead->rule,lookahead->astSuffix);
    }

  /*
   * Check all cut-states and remove follow set
   */

  for(nfa=nfaRoot;nfa;nfa=nfa->next)
    if(nfa->type==nfaCUT) {
      for(nfas=nfa->follow;nfas && nfas->nfa->type!=nfaFINAL;nfas=nfas->next);
      if(nfas==NULL || nfas->nfa->rule!=nfa->rule)
  smkLog(&nfa->rule->srcp,241,sevERR,"");
      nfasDelete(nfa->follow);
      nfa->follow=NULL;
    }
}

void nfaOptimize()
{
  short c1;
  short c2;
  short min;
  short max;
  short maxChr;
  NFA nfa;

 /* Find equavallent charcater classes */

  maxChr=0;
  for(c1=0;c1<charSize;c1++) charTable[c1]=0;
  for(c1=0;c1<charSize;c1++)
    if(charTable[c1]<=maxChr) {
      charMinTable[maxChr]=c1;
      for(c2=c1+1;c2<charSize;c2++)
  if(charTable[c2]<=maxChr) {
    for(nfa=nfaRoot;nfa;nfa=nfa->next) {
      min=nfa->charMin;
      max=nfa->charMax;
      if((c1<min || c1>max) != (c2<min || c2>max)) break;
    }
    if(nfa)
      break;
    else
      charTable[c2]=maxChr;
  }
      charMaxTable[maxChr]=c2-1;
      charTable[c1]=maxChr++;
      c1=c2-1;
    }

 /* Remap the character ranges used by the NFA to the newly */
 /* constructed character classes */

  for(nfa=nfaRoot;nfa;nfa=nfa->next) {
    nfa->charMax=charTable[nfa->charMax];
    nfa->charMin=charTable[nfa->charMin];
  }
  charSize=maxChr;
}

void nfaDump()
{
  NFA nfa;
  short min;
  short max;

  printf("NFA\n");
  for(nfa=nfaRoot;nfa;nfa=nfa->next) {
    printf("%3d / %3d: ",nfa->node,nfa->rule->code);
    switch(nfa->type) {
    case nfaNONE:
      min=charSize<256?charMinTable[nfa->charMin]:nfa->charMin;
      max=charSize<256?charMaxTable[nfa->charMax]:nfa->charMax;
      printf(min<' '||min>'~'?"x%02X":"'%c'",min);
      if(min<max)
  printf(max<' '||max>'~'?"-x%02X ":"-'%c' ",max);
      else
  printf("     ");
      break;
    case nfaFINAL:
      printf("#       ");
      break;
    case nfaCUT:
      printf("# <cut> ");
      break;
    }
    nfasDump(nfa->follow);
    printf("\n");
  }
}

void nfaPrint()
{
  NFA nfa;
  short min;
  short max;

  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("NFA\n");
  for(nfa=nfaRoot;nfa;nfa=nfa->next) {
    lmPrintf("%3d / %3d: ",nfa->node,nfa->rule->code);
    switch(nfa->type) {
    case nfaNONE:
      min=charSize<256?charMinTable[nfa->charMin]:nfa->charMin;
      max=charSize<256?charMaxTable[nfa->charMax]:nfa->charMax;
      lmPrintf(min<' '||min>'~'?"x%02X":"'%c'",min);
      if(min<max)
  lmPrintf(max<' '||max>'~'?"-x%02X ":"-'%c' ",max);
      else
  lmPrintf("     ");
      nfasPrint(nfa->follow);
      break;
    case nfaFINAL:
      lmPrintf("#       ");
      nfasPrint(nfa->follow);
      lmPrintf("    ACCEPT %s in %s::%s",nfa->rule->token->name, nfa->rule->scanner->vocabulary->name, nfa->rule->scanner->name);
      break;
    case nfaCUT:
      lmPrintf("# <cut> ");
      nfasPrint(nfa->follow);
      lmPrintf("    ACCEPT %s in %s::%s",nfa->rule->token->name, nfa->rule->scanner->vocabulary->name, nfa->rule->scanner->name);
      break;
    }
    lmPrintf("\n");
  }
  lmFlush();
}
