/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 * 
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/rule.h,v 1.1 2002/06/25 20:04:49 Thomas Nilsson Exp $
 *
 * $Log: rule.h,v $
 * Revision 1.1  2002/06/25 20:04:49  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:15  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/04/23  10:33:24  tools
 * Initial revision. Replaces old token.*.
 *
 */

#ifndef _rule_h_
#define _rule_h_

typedef struct Rule *Rule;

#include "common.h"
#include "tmkCommon.h"
#include "scanner.h"
#include "token.h"
#include "ast.h"
#include "lookahead.h"
#include "action.h"

typedef enum {ruleMATCH, ruleSKIP, rulePREDEF, ruleUNDEF} RuleType;

/*
 * UNIQUE KEY: code 
 */

typedef struct Rule {
  TmkSrcp srcp;			/* The rules source position */
  Code code;			/* The rule's internal code */
  Token token;			/* The rule's external token */
  Scanner scanner;		/* The scanner which the rule is defined in */
  RuleType type;		/* The type of the rule */
  Bool screening;		/* Per rule screening flag */
  Bool screens;			/* Is true if this rule screens another rule */
  AST ast;			/* The rule */
  Lookahead lookahead;		/* The rules lookahead */
  Action action;		/* The rule's action */
  Rule next;
} RuleItem;

extern Code ruleCodes;

extern Rule ruleGet(Rule rules, Code code);
extern Rule ruleNew(Rule* rules);
extern Rule rulePredefined(Rule rules, Name name);
extern void rulePredefinedToMatch(Rule rules);
extern void ruleCopy(Rule to, Rule from);
extern void ruleDump(Rule rule);
extern void rulePrint(void);

#endif
