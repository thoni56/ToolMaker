/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 * 
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/scanner.c,v 1.1 2002/06/25 20:04:49 Thomas Nilsson Exp $
 *
 * $Log: scanner.c,v $
 * Revision 1.1  2002/06/25 20:04:49  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:16  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:12:12  tools
 * Totaly rewritten to correctly handle vocabularies and rules.
 *
 */

#include <stdio.h>
#include "common.h"
#include "scanner.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"
 
Code scannerCodes=0;

Scanner scannerGet(Scanner scanner, Name name)
{
  for(;scanner;scanner=scanner->next) 
    if(scanner->name==name) return scanner;
  return 0;
}  

Scanner scannerNew(Scanner* scanners, Name name)
{
  Scanner scanner;
  if((*scanners)==0) {
    *scanners=scanner=(Scanner)smalloc(sizeof(ScannerItem));
    scanner->name=name;
    scanner->vocabulary=0;
    scanner->code=0;
    scanner->rules=0;
    scanner->nfa=0;
    scanner->dfa=0;
    scanner->next=0;
    return scanner;
  }
  else for(scanner=(*scanners);;) {
    if(scanner->name==name)
      return 0;
    else if(scanner->next)
      scanner=scanner->next;
    else {
      scanner=(scanner->next=(Scanner)smalloc(sizeof(ScannerItem)));
      scanner->name=name;
      scanner->vocabulary=0;
      scanner->code=0;
      scanner->rules=0;
      scanner->nfa=0;
      scanner->dfa=0;
      scanner->next=0;
      return scanner;
    }
  }
}

void scannerCopy(Scanner to, Scanner from)
{
  Rule rule;
  to->code=from->code;
  to->rules=0;
  for(rule=to->rules;rule;rule=rule->next)
    ruleCopy(ruleNew(&to->rules), rule);
  to->nfa=0;
  to->dfa=0;
}

Bool scannerCheckRules(Scanner scanner)
{
  Rule rule;
  Token tokenEOT=0;
  Token tokenUNKNOWN=0;
  for(rule=scanner->rules;rule;rule=rule->next) {
    /*
     * Check if ONE token has EOT or UNKNOWN defined, if not report an error
     */
    if(rule->type!=ruleUNDEF)
      if(rule->ast==astEOT)
	if(tokenEOT)
	  if(rule->token==tokenEOT)
	    /* OK */;
	  else
	    smkLog(&rule->srcp,214,sevERR,"");
	else
	  tokenEOT=rule->token;
      else if(rule->ast==astUNKNOWN)
	if(tokenUNKNOWN)
	  if(rule->token==tokenUNKNOWN)
	    /* OK */;
	  else
	    smkLog(&rule->srcp,215,sevERR,"");
	else
	  tokenUNKNOWN=rule->token;
    /*
     * Check if a token with screening has a sequence (STRING) as rule and is of 
     * the minimum specified screen length or longer. Check only if optScreen > 0
     */
    if(optScreen && rule->token->screening) {
      rule->screening=astSequenceLength(rule->ast) >= optScreen ? YES : NO;
    }
  }
  if(tokenEOT==0)
    smkLog(&scanner->srcp,216,sevERR,"");
  if(tokenUNKNOWN==0)
    smkLog(&scanner->srcp,218,sevERR,"");
  return tokenEOT==0 || tokenUNKNOWN==0;
}

void scannerCheckRedefinedPredefined(Scanner firstScanner, Scanner scanner)
{
  Rule rule1;
  Rule rule2;
  for(rule1=firstScanner->rules;rule1;rule1=rule1->next)
    if(rule1->type==rulePREDEF)
      for(rule2=scanner->rules;rule2;rule2=rule2->next)
	if(rule2->type==ruleMATCH || rule2->type==ruleSKIP)
	  if(rule1->token->name==rule2->token->name)
	    smkLog(&rule2->srcp,261,sevWAR,firstScanner->name);

}

void scannerDump(Scanner scanner)
{
  Rule rule;
  printf("  %%SCANNER %03d name='%s'\n", 
	 scanner->code,
	 scanner->name);
  for(rule=scanner->rules;rule;rule=rule->next)
    ruleDump(rule);
}
