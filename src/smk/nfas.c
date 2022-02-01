/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-07-12
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/nfas.c,v 1.1 2002/06/25 20:04:47 Thomas Nilsson Exp $
 *
 * $Log: nfas.c,v $
 * Revision 1.1  2002/06/25 20:04:47  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:05  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:10:45  tools
 * Removed use of explicit allocated variables.
 *
 * Revision 1.1  1993/03/24  09:24:23  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:53:13  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include "common.h"
#include "smalloc.h"
#include "lmprintf.h"
#include "nfa.h"
#include "nfas.h"

NFAs nfasInsert(NFAs nfas, NFA nfa)
{
  NFAs nfas1,nfas2,nfas3;

  if(nfas==NULL) {
    nfas1=(NFAs)smalloc(sizeof(NFAsItem));
    nfas1->nfa=nfa;
    nfas1->next=NULL;
    return nfas1;
  }
  else if(nfas->nfa==nfa)
    return nfas;
  else if(nfas->nfa->node>nfa->node) {
    nfas1=(NFAs)smalloc(sizeof(NFAsItem));
    nfas1->nfa=nfa;
    nfas1->next=nfas;
    return nfas1;
  }
  else {
    for(nfas1=nfas,nfas2=nfas->next;nfas2!=NULL;nfas1=nfas2,nfas2=nfas2->next)
      if(nfas2->nfa==nfa) return nfas;
      else if(nfas2->nfa->node>nfa->node) break;
    nfas3=(NFAs)smalloc(sizeof(NFAsItem));
    nfas3->nfa=nfa;
    nfas3->next=nfas2;
    nfas1->next=nfas3;
    return nfas;
  }
}

/*
 * Merge nfas1 and nfas2
 */

NFAs nfasMerge(NFAs nfas1, NFAs nfas2)
{
  NFAs nfas3;
  NFAs nfas4;
  NFAs nfas5;

  if(nfas1==NULL) return nfas2;
  if(nfas2==NULL) return nfas1;

/* Check if first item in nfas1 is greater than first item in nfas2.
   If it is link first item in nfas2 before nfas1 */

  if(nfas1->nfa->node>nfas2->nfa->node) {
    nfas3=nfas2;
    nfas2=nfas2->next;
    nfas3->next=nfas1;
    nfas5=nfas3;
  }
  else {
    nfas3=nfas1;
    nfas5=nfas1;
  }

  while(nfas1!=NULL && nfas2!=NULL)
    if(nfas1->nfa->node>nfas2->nfa->node) { /* link nfas2 before nfas1 */
      nfas3->next=nfas2;
      nfas3=nfas2;
      nfas2=nfas2->next;
      nfas3->next=nfas1;
    }
    else if(nfas1->nfa->node<nfas2->nfa->node) { /* advance nfas1 */
      nfas3=nfas1;
      nfas1=nfas1->next;
    }
    else {      /* remove duplicate nfas2 nfa */
      nfas4=nfas2;
      nfas2=nfas2->next;
      free((char *)nfas4);
    }
  if(nfas1==NULL)
    nfas3->next=nfas2;
  return nfas5;
}

/*
 * Merge a copy of nfas2 to nfas1
 */

NFAs nfasMergeCopy(NFAs nfas1, NFAs nfas2)
{
  NFAs nfas3;
  NFAs nfas5;

  if(nfas2==NULL) return nfas1;
  if(nfas1==NULL) {
    nfas5=(NFAs)smalloc(sizeof(NFAsItem));
    nfas5->nfa=nfas2->nfa;
    nfas3=nfas5;
    for(nfas2=nfas2->next;nfas2!=NULL;nfas2=nfas2->next) {
      nfas3->next=(NFAs)smalloc(sizeof(NFAsItem));
      nfas3=nfas3->next;
      nfas3->nfa=nfas2->nfa;
    }
    nfas3->next=NULL;
    return nfas5;
  }

/* Check if first item in nfas1 is greater than first item in nfas2.
   If it is link first item in nfas2 before nfas1 */

  if(nfas1->nfa->node>nfas2->nfa->node) {
    nfas3=(NFAs)smalloc(sizeof(NFAsItem));
    nfas3->nfa=nfas2->nfa;
    nfas2=nfas2->next;
    nfas3->next=nfas1;
    nfas5=nfas3;
  }
  else {
    nfas3=nfas1;
    nfas5=nfas1;
  }

  while(nfas1!=NULL && nfas2!=NULL)
    if(nfas1->nfa->node>nfas2->nfa->node) { /* link duplicate of nfas2 before nfas1 */
      nfas3->next=(NFAs)smalloc(sizeof(NFAsItem));
      nfas3=nfas3->next;
      nfas3->nfa=nfas2->nfa;
      nfas2=nfas2->next;
      nfas3->next=nfas1;
    }
    else if(nfas1->nfa->node<nfas2->nfa->node) { /* advance nfas1 */
      nfas3=nfas1;
      nfas1=nfas1->next;
    }
    else {      /* advance nfas2 */
      nfas2=nfas2->next;
    }
  if(nfas1==NULL) {
    for(;nfas2!=NULL;nfas2=nfas2->next) {
      nfas3->next=(NFAs)smalloc(sizeof(NFAsItem));
      nfas3=nfas3->next;
      nfas3->nfa=nfas2->nfa;
    }
    nfas3->next=NULL;
  }
  return nfas5;
}

/*
 * Delete nfas
 */

NFAs nfasDelete(NFAs nfas)
{
  NFAs nfas1;

  while(nfas!=NULL) {
    nfas1=nfas;
    nfas=nfas->next;
    free((char *)nfas1);
  }
  return NULL;
}

void nfasDump(NFAs nfas)
{
  printf("{");
  for(;nfas;nfas=nfas->next)
    printf(nfas->next?"%d,":"%d",nfas->nfa->node);
  printf("}");
}

void nfasPrint(NFAs nfas)
{
  lmPrintf("{");
  for(;nfas;nfas=nfas->next)
    lmPrintf(nfas->next?"%d,":"%d",nfas->nfa->node);
  lmPrintf("}");
}
