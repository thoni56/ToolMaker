/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 *
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/rule.c,v 1.1 2002/06/25 20:04:48 Thomas Nilsson Exp $
 *
 * $Log: rule.c,v $
 * Revision 1.1  2002/06/25 20:04:48  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:13  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/04/23  10:33:22  tools
 * Initial revision. Replaces old token.*.
 *
 */

#include <stdio.h>
#include "common.h"
#include "lmprintf.h"
#include "ast.h"
#include "rule.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"

Code ruleCodes=0;   /* ALL rules share the same internal code numbers */

Rule ruleGet(Rule rule, Code code)
{
  for(;rule;rule=rule->next)
    if(rule->code==code) return rule;
  return 0;
}

Rule rulePredefined(Rule rule, Name name)
{
  for(;rule;rule=rule->next)
    if(rule->type==rulePREDEF && rule->token && rule->token->name==name) return rule;
  return 0;
}

Rule ruleNew(Rule* rules)
{
  Rule rule;
  if((*rules)==0) {
    *rules=rule=(Rule)smalloc(sizeof(RuleItem));
    rule->code=0;
    rule->token=0;
    rule->scanner=0;
    rule->type=ruleUNDEF;
    rule->screening=NO;
    rule->screens=NO;
    rule->ast=0;
    rule->lookahead=0;
    rule->action=0;
    rule->next=0;
    return rule;
  }
  else {
    for(rule=(*rules);rule->next;rule=rule->next);
    rule=(rule->next=(Rule)smalloc(sizeof(RuleItem)));
    rule->code=0;
    rule->token=0;
    rule->scanner=0;
    rule->type=ruleUNDEF;
    rule->screening=NO;
    rule->screens=NO;
    rule->ast=0;
    rule->lookahead=0;
    rule->action=0;
    rule->next=0;
    return rule;
  }
}

void rulePredefinedToMatch(Rule rules)
{
  for(;rules;rules=rules->next) if(rules->type==rulePREDEF) rules->type=ruleMATCH;
}

void ruleCopy(Rule to, Rule from)
{
  to->token=from->token;
  to->type=from->type;
  to->screening=from->screening;
  to->screens=from->screens;
  to->ast=from->ast;
  to->action=from->action;
  to->lookahead=from->lookahead;
}

void ruleDump(Rule rule)
{
  printf("    %%RULE code=%3d   name='%s'   type=%s   AST=%s   lookahead=%s   action=%s\n",
   rule->code,
   rule->token ? rule->token->name : "<<<NIL>>>",
   rule->type==ruleMATCH ? "MATCH" : rule->type==ruleSKIP ? "SKIP" : rule->type==ruleUNDEF ? "UNDEFINED" : rule->type==rulePREDEF ? "PREDEFINED" : "<<<NIL>>>",
   rule->ast ? "YES" : "NO",
   rule->lookahead ? "YES" : "NO",
   rule->action ? "YES" : "NO");
}

void rulePrint()
{
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
      lmPrintf("Scanner %3d: %s::%s\n", scanner->code, vocabulary->name, scanner->name);
      for(rule=scanner->rules;rule;rule=rule->next) {
  if(rule->token->code==codeSKIP)
    lmPrintf("    %3d SKIP %-15s\t= ",rule->code, rule->token->name);
  else
    lmPrintf("    %3d %4d %-15s\t= ",rule->code, rule->token->code, rule->token->name);
  astPrint(rule->ast);
  lmPrintf("\n");
      }
    }
}
