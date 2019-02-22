#include <stdio.h>
#include <math.h>
#include "char.h"
#include "dfa.h"
#include "lmprintf.h"
#include "lookahead.h"
#include "map.h"
#include "nfa.h"
#include "nfas.h"
#include "pack.h"
#include "rule.h"
#include "scanner.h"
#include "set.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"
#include "vocabulary.h"

DFA dfaRoot=NULL;
int dfaSize=0;

static DFA dfaEnd=NULL;

static DFA *dfaHashTable=NULL;
static int dfaHashSize=0;

/*
 * This function locates a DFA node given a closure for a transition.
 * If the requested DFA node does not exist, it is created.
 */

static DFA dfaPut(NFAs nfas)
{
  unsigned int hashKey;
  DFA dfa;
  NFAs nfas1;
  NFAs nfas2;
  int n;

  static int primes[46]={
    23,37,59,89,137,211,317,479,719,1087,1637,2459,3691,5557,8353,12539,18839,
    28277,42433,63649,95479,143239,214867,322319,483481,725273,1087937,1631911,
    2447897,3671849,5507773,8261689,12392551,18588827,27883243,41824889,62737333,
    94106009,141159019,211738547,317607809,476411713,714617621,1071926411,1607889683,
    0x7FFFFFFF};

  if(dfaHashTable==NULL) {
    for(n=0;nfaSize>primes[n];n++);
    dfaHashSize=primes[n];
    dfaHashTable=(DFA *)smalloc((unsigned int)(sizeof(DFA)*dfaHashSize));
    for(n=0;n<dfaHashSize;n++) dfaHashTable[n]=NULL;
  }

  /* get hash key */

  hashKey=0;
  for(nfas1=nfas;nfas1!=NULL;nfas1=nfas1->next)
    hashKey=(hashKey<<1)^(int)(nfas1->nfa);
  hashKey%=dfaHashSize;


  /* check if node already exist, if it does return the node */

  for(dfa=dfaHashTable[hashKey];dfa!=NULL;dfa=dfa->list) {
    for(nfas1=nfas,nfas2=dfa->closure;
    nfas1!=NULL && nfas2!=NULL;
    nfas1=nfas1->next,nfas2=nfas2->next)
      if(nfas1->nfa!=nfas2->nfa) break;
    if(nfas1==NULL && nfas2==NULL) {
      nfasDelete(nfas);
      return dfa;
    }
  }

  /* node does not exist, create, link it and return the new node */

  dfa=(DFA)smalloc(sizeof(DFAItem));
  dfa->node=dfaSize++;
  dfa->transition=(DFA *)smalloc((unsigned int)(sizeof(DFA)*charSize));
  dfa->closure=nfas;
  dfa->accept=NULL;
  dfa->next=NULL;
  if(dfaEnd)
    dfaEnd=dfaEnd->next=dfa;
  else
    dfaEnd=dfaRoot=dfa;
  dfa->list=dfaHashTable[hashKey];
  dfaHashTable[hashKey]=dfa;

  return dfa;
}

void dfaCreate()
{
  NFAs transitionNFAs;
  short c1;
  short c2;
  short max;
  short min;

  Vocabulary vocabulary;
  Scanner scanner;
  Lookahead lookahead;
  int transition[256];
  NFAs nfas;
  NFA nfa;
  DFA dfa;

  dfaSize=0;
  dfaRoot=NULL;
  dfaEnd=NULL;

  /* Create initial states */

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      scanner->dfa=dfaPut(scanner->nfa);

  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next)
    if(lookahead->lengthPrefix<0 && lookahead->lengthSuffix<0) {
      lookahead->dfaPrefix=dfaPut(lookahead->nfaPrefix);
      lookahead->dfaSuffix=dfaPut(lookahead->nfaSuffix);
    }

  for(c1=0;c1<charSize;c1++) transition[c1]=1;
  transitionNFAs=NULL;

  /* create rest of dfa by traversing the list of unvisited dfa nodes */

  for(dfa=dfaRoot;dfa!=NULL;dfa=dfa->next)
    for(c1=0;c1<charSize;c1++)
      if(transition[c1]) {
    transitionNFAs=NULL;
    for(nfas=dfa->closure;nfas!=NULL;nfas=nfas->next) {
      nfa=nfas->nfa;
      if(c1>=nfa->charMin && c1<=nfa->charMax)
        transitionNFAs=nfasMergeCopy(transitionNFAs,nfa->follow);
    }
    dfa->transition[c1]=(transitionNFAs==NULL ? NULL : dfaPut(transitionNFAs));
    for(c2=c1+1;c2<charSize;c2++)
      if(transition[c2]) {
        for(nfas=dfa->closure;nfas!=NULL;nfas=nfas->next) {
          min=nfas->nfa->charMin;
          max=nfas->nfa->charMax;
          if((c1<min || c1>max) != (c2<min || c2>max)) break;
        }
        if(nfas==NULL) {
          dfa->transition[c2]=dfa->transition[c1];
          transition[c2]=0;
        }
      }
      }
      else
    transition[c1]=1;
  /*
   * Make excluded characters to loop back
   */

  if(optExclude>=0)
    for(dfa=dfaRoot;dfa;dfa=dfa->next)
      dfa->transition[charTable[optExclude]]=dfa;
}

void dfaAccept()
{
  DFA dfa;
  NFAs nfas;
  int n;

  /*
   * Check each node in closure to locate an accept state
   */

  for(dfa=dfaRoot;dfa;dfa=dfa->next) {
      /*
       * Find non-screened token rule as accepting token
       */
      for(nfas=dfa->closure;nfas;nfas=nfas->next) {
          if(nfas->nfa->type!=nfaNONE && nfas->nfa->rule->screening==NO) {
              if(dfa->accept)
                  smkLog(&(nfas->nfa->rule->srcp),243,sevINF,dfa->accept->token->name);
              else {
                  dfa->accept=nfas->nfa->rule;
                  if(nfas->nfa->type==nfaCUT)
                      for(n=0;n<charSize;n++) dfa->transition[n]=NULL;
              }
          }
      }
      if(optScreen) {
          if(dfa->accept) {
              /*
               * if a rule exist in this state which has a screening YES mark accept token
               * to screens.
               */
              for(nfas=dfa->closure;nfas;nfas=nfas->next)
                  if(nfas->nfa->type!=nfaNONE && nfas->nfa->rule->screening==YES)
                      dfa->accept->screens=YES;
          } else {
              /*
               * If no accept token was find and screening is on, check to find if there
               * exist a screened token which may accept the state. If so turn off screening
               * for that token.
               */
              for(nfas=dfa->closure;nfas;nfas=nfas->next)
                  if(nfas->nfa->type!=nfaNONE) {
                      smkLog(&(nfas->nfa->rule->srcp),260,sevINF,nfas->nfa->rule->token->name);
                      nfas->nfa->rule->screening=NO;
                      if(dfa->accept)
                          smkLog(&(nfas->nfa->rule->srcp),243,sevINF,dfa->accept->token->name);
                      else {
                          dfa->accept=nfas->nfa->rule;
                          if(nfas->nfa->type==nfaCUT)
                              for(n=0;n<charSize;n++) dfa->transition[n]=NULL;
                      }
                  }
          }
      }
  }
}

void dfaOptimize()
{
  DFA dfa1;
  DFA dfa2;
  DFA dfa3;
  DFA dfaEnd;
  DFA dfaHashEnd;
  int n;
  int changed;
  Lookahead lookahead;
  Vocabulary vocabulary;
  Scanner scanner;

  /*
   * Partion all dfas in one state
   */

  dfaHashEnd=0;
  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next) {
    dfa1->list=dfa1->next;
    dfa1->set=0;
    dfaHashEnd=dfa1;
  }
  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->list) dfa1->next=NULL;
  dfaEnd=dfaRoot;
  dfaSize=1;

  /*
   * Split scanner start states, each an own partion
   */

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(dfa1=dfaRoot,dfa2=dfaRoot->list;dfa2;dfa1=dfa2,dfa2=dfa2->list)
    if(dfa2==scanner->dfa) {
      dfa2->set=dfaSize++;
      dfaEnd=dfaEnd->next=dfa2;
      dfa1->list=dfa2->list;
      dfa2->list=NULL;
      dfa2=dfa1;
    }

  /*
   * Split lookahead start states, each an own partion
   */

  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next)
    if(lookahead->lengthPrefix<0 && lookahead->lengthSuffix<0)
      for(dfa1=dfaRoot,dfa2=dfaRoot->list;dfa2;dfa1=dfa2,dfa2=dfa2->list)
    if(dfa2==lookahead->dfaPrefix || dfa2==lookahead->dfaSuffix) {
      dfa2->set=dfaSize++;
      dfaEnd=dfaEnd->next=dfa2;
      dfa1->list=dfa2->list;
      dfa2->list=NULL;
      dfa2=dfa1;
    }

  /*
   * Split accept states, each rule an own partion
   */

  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next) {
    for(dfa3=dfa1,dfa2=dfa1->list;dfa2;dfa3=dfa2,dfa2=dfa2->list) {
      if(dfa2->accept!=dfa1->accept) {
    if(dfaEnd->next) {
      dfaHashEnd=dfaHashEnd->list=dfa2;
    }
    else {
      dfaEnd->next=dfa2;
      dfaHashEnd=dfa2;
    }
    dfa2->set=dfaSize;
    dfa3->list=dfa2->list;
    dfa2->list=NULL;
    dfa2=dfa3;
      }
    }
    if(dfaEnd->next) {
      dfaSize++;
      dfaEnd=dfaEnd->next;
    }
  }

  /*
   * Optimize DFA
   */

  do {
    changed=0;
    for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next) {
      for(dfa3=dfa1,dfa2=dfa1->list;dfa2;dfa3=dfa2,dfa2=dfa2->list) {
    for(n=0;n<charSize;n++) {
      if(dfa1->transition[n]==dfa2->transition[n])
        continue;
      else if(dfa1->transition[n] && dfa2->transition[n] && dfa1->transition[n]->set==dfa2->transition[n]->set)
        continue;
      else {
        if(dfaEnd->next) {
          dfaHashEnd=dfaHashEnd->list=dfa2;
        }
        else {
          dfaEnd->next=dfa2;
          dfaHashEnd=dfa2;
        }
        dfa3->list=dfa2->list;
        dfa2->list=NULL;
        dfa2=dfa3;
        changed=1;
        break;
      }
    }
      }
      if(dfaEnd->next) {
    for(dfa3=dfaEnd->next;dfa3;dfa3=dfa3->list)
      dfa3->set=dfaSize;
    dfaSize++;
    dfaEnd=dfaEnd->next;
      }
    }
  } while(changed);

  /*
   * Make list to point to first DFA in list and remap node numbers
   */

  dfaHashEnd=NULL;		/* from now used to hold states to be removed */
  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next) {
    dfa1->node=dfa1->set;
    for(dfa2=dfa1;dfa2;dfa2=dfa3) {
      dfa3=dfa2->list;
      dfa2->list=dfa1;
      if(dfa2!=dfa1) {
    dfa2->next=dfaHashEnd;
    dfaHashEnd=dfa2;
      }
    }
  }

  /*
   * Fix transitions
   */

  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next)
    for(n=0;n<charSize;n++)
      if(dfa1->transition[n]) dfa1->transition[n]=dfa1->transition[n]->list;

  /*
   * Fix scanner pointers
   */

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      scanner->dfa=scanner->dfa->list;

  /*
   * Fix lookahead pointers
   */

  for(lookahead=lookaheadRoot;lookahead;lookahead=lookahead->next) {
    if(lookahead->dfaPrefix) lookahead->dfaPrefix=lookahead->dfaPrefix->list;
    if(lookahead->dfaSuffix) lookahead->dfaSuffix=lookahead->dfaSuffix->list;
  }

  /*
   * Remove equivalent nodes
   */

  for(dfa1=dfaHashEnd;dfa1;) {
    DFA this = dfa1;
    free((char *)dfa1->transition);
    nfasDelete(dfa1->closure);
    dfa1 = dfa1->next;
    free((char *)this);
  }

  /*
   * Set list to NULL
   */

  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next)
    dfa1->list=NULL;
}

Pack dfaPack()
{
    DFA dfa;
    Pack pack;
    int row;
    int col;
    int min;
    int max;
    int value;
    unsigned type;

    type = getSetOpt(PACK_OPT);
    pack=(Pack)smalloc(sizeof(PackItem));
    pack->type=type;
    pack->insign=dfaSize;
    pack->rows=dfaSize;
    pack->matrix=(int **)smalloc((unsigned int)(sizeof(int *)*dfaSize));
    if(type&ePackCOL && setUsed==0 && mapUsed==0) {
        int *COLcol;

        /*
         * Wait to expand column to after packing (expand cols)
         */

        pack->cols=charSize;
        for(dfa=dfaRoot;dfa;dfa=dfa->next) {
            row=dfa->node;
            pack->matrix[row]=(int *)smalloc((unsigned int)(sizeof(int)*charSize));
            for(col=0;col<charSize;col++)
                pack->matrix[row][col]=dfa->transition[col] ? dfa->transition[col]->node : dfaSize;
            if(optExclude>=0)
                pack->matrix[row][charTable[optExclude]]+=dfaSize+1;
        }
        packMatrix(pack);
        COLcol=(int *)smalloc(sizeof(int)*256);
        for(col=0;col<charSize;col++) {
            min=charMinTable[col];
            max=charMaxTable[col];
            value=pack->COLcol[col];
            for(;min<=max;min++) COLcol[min]=value;
        }
        free((char *)pack->COLcol);
        pack->COLcol=COLcol;
        pack->COLcols=256;
    }
    else {
        pack->cols=256;
        for(dfa=dfaRoot;dfa;dfa=dfa->next) {
            row=dfa->node;
            pack->matrix[row]=(int *)smalloc(sizeof(int)*256);
            for(col=0;col<256;col++) pack->matrix[row][col]=dfaSize;
            for(col=0;col<charSize;col++) {
                min=charMinTable[col];
                max=charMaxTable[col];
                value=dfa->transition[col] ? dfa->transition[col]->node : dfaSize;
                for(;min<=max;min++) {
                    if(setTable[min]!=setSkip)
                        pack->matrix[row][setTable[min]]=value;
                    else
                        pack->matrix[row][setTable[min]]=dfaSize;
                    if(optExclude>-1 && charTable[optExclude]==charTable[min])
                        pack->matrix[row][setTable[min]]+=dfaSize+1;
                }
            }
            if(mapUsed) for(col=0;col<256;col++) {
                    if(mapTable[col]==mapSkip)
                        pack->matrix[row][setTable[col]]=row;
                    else if(mapTable[col]!=col)
                        pack->matrix[row][setTable[col]]=pack->matrix[row][setTable[mapTable[col]]];
                }
        }
        packMatrix(pack);
    }
    return pack;
}

void dfaDumpOptimize()
{
  DFA dfa1;
  DFA dfa2;

  printf("Optimized DFA\n\n");
  for(dfa1=dfaRoot;dfa1;dfa1=dfa1->next) {
    printf("%3d : {",dfa1->set);
    for(dfa2=dfa1;dfa2;dfa2=dfa2->list) {
      if(dfa1->set!=dfa2->set) printf("*");
      printf(dfa2->list?"%3d,":"%3d}",dfa2->node);
    }
    printf("\n");
  }
}

static void dfaDumpAcceptAll(NFAs nfas)
{
  for(;nfas;nfas=nfas->next)
    switch(nfas->nfa->type) {
    case nfaNONE:
      break;
    case nfaFINAL:
      printf("  %s-%d/%s",
         nfas->nfa->rule->token->name,
         nfas->nfa->rule->code,
         nfas->nfa->rule->scanner->name);
      break;
    case nfaCUT:
      printf("  <%s-%d/%s>",
         nfas->nfa->rule->token->name,
         nfas->nfa->rule->code,
         nfas->nfa->rule->scanner->name);
      break;
    }
}

static void dfaDumpTransition(DFA *transition)
{
  short n;
  short min;
  short max;

  for(n=0;n<charSize;n++)
    if(transition[n]) {
      min=n;
      for(;n<charSize && transition[min]==transition[n];n++);
      max= --n;
      if(min>max) break;
      printf("\tgoto %4d on [",transition[min]->node);
      if(charSize<256) {
    min=charMinTable[min];
    max=charMaxTable[max];
      }
      printf(min<' '||min>'~' ? "%02X" : "%c",min);
      if(min!=max) printf(max<' '||max>'~' ? "-%02X" : "-%c",max);
      printf("]\n");
    }
}

void dfaDump()
{
  DFA dfa;

  printf("DFA Table\n\n");
  for(dfa=dfaRoot;dfa;dfa=dfa->next) {
    printf("  %4d: ",dfa->node);
    dfaDumpAcceptAll(dfa->closure);
    printf("\n");
    dfaDumpTransition(dfa->transition);
  }
}

void dfaDumpAccept()
{
  Vocabulary vocabulary;
  Scanner scanner;
  DFA dfa;

  printf("Accept table\n\n    ");
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      printf("    Scanner %s::%s\n",scanner->vocabulary->name,scanner->name);
      for(dfa=dfaRoot;dfa;dfa=dfa->next) {
    if(dfa->accept && dfa->accept->scanner==scanner)
      printf("\t%3d: accept %3d  %s/%d\n",
         dfa->node,
         dfa->accept->token->code,
         dfa->accept->token->name,
         dfa->accept->code);
      }
    }
}

static void dfaPrintTransition(DFA *transition)
{
  short n;
  short min;
  short max;

  for(n=0;n<charSize;n++)
    if(transition[n]) {
      min=n;
      for(;n<charSize && transition[min]==transition[n];n++);
      max= --n;
      if(min>max) break;
      lmPrintf("\tgoto %4d on [",transition[min]->node);
      if(charSize<256) {
    min=charMinTable[min];
    max=charMaxTable[max];
      }
      lmPrintf(min<' '||min>'~' ? "%02X" : "%c",min);
      if(min!=max) lmPrintf(max<' '||max>'~' ? "-%02X" : "-%c",max);
      lmPrintf("]\n");
    }
}

void dfaPrint()
{
  DFA dfa;
  Vocabulary vocabulary;
  Scanner scanner;

  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("DFA Table Entries\n\n");
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      lmPrintf("    scanner %s::%s enters at %d, NFA closure ",vocabulary->name, scanner->name, scanner->dfa->node);
      nfasPrint(scanner->dfa->closure);
    }
  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("DFA Table\n\n");
  for(dfa=dfaRoot;dfa;dfa=dfa->next) {
    lmPrintf("  %4d: ",dfa->node);
    if(dfa->accept) {
      lmPrintf("  %s-%d/%s::%s",dfa->accept->token->name, dfa->accept->code, dfa->accept->scanner->vocabulary->name, dfa->accept->scanner->name);
    }
    lmPrintf("\n");
    dfaPrintTransition(dfa->transition);
  }
  lmFlush();
}
