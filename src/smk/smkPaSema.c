/*----------------------------------------------------------------------*\

	smkPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


/*
 * "Bug" in generated code does not include definition of memset
 */
#include <memory.h>

#include <stdio.h>
#include "common.h"
#include "action.h"
#include "ast.h"
#include "definition.h"
#include "map.h"
#include "name.h"
#include "pack.h"
#include "rule.h"
#include "scanner.h"
#include "set.h"
#include "smkList.h"
#include "smkScan.h"
#include "smk_i.h"
#include "token.h"
#include "vocabulary.h"

extern smkScContext lexContext;

/* END %%IMPORT */

/* System dependencies
 * -------------------
 */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;

/* Token and Srcp definition */
#include "smkCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct smkGrammar {
    Action action;
    AST ast;
    Name name;
    double fnumber;
    int inumber;
    TmkSrcp srcp;
} smkGrammar;

/* END %%ATTRIBUTES */

extern short smkStkP;
extern SmkToken smkSySt[];
extern smkGrammar smkSeSt[];

/* %%DECLARATIONS - User data and routines */


  Vocabulary grmVocabulary=0;
  Scanner grmScanner=0;
  RuleType grmRuleType=ruleUNDEF;


/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * smkPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void smkPaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 1: { /* <goal> = <skip sections opt> __genSym#0 <code sections opt> <set definition sections opt> __genSym#1 <definition sections opt> <vocabulary sections>; */
{
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;

  ruleCodes=0;
  scannerCodes=0;
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      scanner->code=scannerCodes++;
      for(rule=scanner->rules;rule;rule=rule->next)
	if(rule->type==ruleUNDEF)
	  rule->code=codeSKIP;
	else
	  rule->code=ruleCodes++;
    }
}	break;}
    case 2: { /* __genSym#0 =; */
{
  /* Read vocabulary file */
  vocabularyRead(optVocabulary);
}	break;}
    case 3: { /* __genSym#1 =; */
{
  if(getBoolOpt(SET_OPT))
    if(setGet(getStrOpt(SET_OPT))) 
      setUse(getStrOpt(SET_OPT)); 
    else
      smkLog(NULL,254,sevERR,getStrOpt(SET_OPT));
}	break;}
    case 19: { /* <code section> = '%%DECLARATION' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 20: { /* <code section> = '%%CONTEXT' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 21: { /* <code section> = '%%EXPORT' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 22: { /* <code section> = '%%READER' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 23: { /* <code section> = '%%PREHOOK' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 24: { /* <code section> = '%%ACTION' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 25: { /* <code section> = '%%POSTHOOK' <end opt>; */
{
  static int count=0;
  if(count++) smkLog(&smkSySt[smkStkP+1].srcp,262,sevERR,"");
}	break;}
    case 27: { /* <map definition section> = '%%MAP' <maps> <end opt>; */
{
  mapUsed=1;
}	break;}
    case 30: { /* <map> = <class> '=' <class> ';'; */
{
  mapPut(smkSeSt[smkStkP+1].name,smkSeSt[smkStkP+3].name);
}	break;}
    case 34: { /* <definition definition> = <identifier> '=' <selection rule> ';'; */
{
  Definition definition;

  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL) definition=definitionPut(smkSeSt[smkStkP+1].name);
  if(definition->ast)
    smkLog(&smkSeSt[smkStkP+1].srcp,233,sevERR,"");
  else 
    definition->ast=smkSeSt[smkStkP+3].ast;
}	break;}
    case 35: { /* <definition definition> = <identifier> '=' '%%' ';'; */
{
  Definition definition;

  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL) definition=definitionPut(smkSeSt[smkStkP+1].name);
  if(definition->action) 
    smkLog(&smkSeSt[smkStkP+1].srcp,246,sevERR,"");
  else
    definition->action=smkSySt[smkStkP+3].action;
}	break;}
    case 36: { /* <definition definition> = <identifier> '=' <selection rule> '%%' ';'; */
{
  Definition definition;

  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL) definition=definitionPut(smkSeSt[smkStkP+1].name);
  if(definition->ast)
    smkLog(&smkSeSt[smkStkP+1].srcp,233,sevERR,"");
  else 
    definition->ast=smkSeSt[smkStkP+3].ast;
  if(definition->action) 
    smkLog(&smkSeSt[smkStkP+1].srcp,246,sevERR,"");
  else
    definition->action=smkSySt[smkStkP+4].action;
}	break;}
    case 39: { /* <vocabulary section> = '%%VOCABULARY' <external vocabulary name> <scanner sections>; */
{
  if(grmVocabulary) {
    Scanner scanner;
    for(scanner=grmVocabulary->scanners;scanner;scanner=scanner->next) rulePredefinedToMatch(scanner->rules);
    vocabularyCheckTokens(grmVocabulary);
    grmVocabulary=0;
  }
}	break;}
    case 40: { /* <vocabulary section> = '%%VOCABULARY' <internal vocabulary name> <vocabulary definitions> <scanner sections>; */
{
  if(grmVocabulary) {
    Scanner scanner;
    for(scanner=grmVocabulary->scanners;scanner;scanner=scanner->next) rulePredefinedToMatch(scanner->rules);
    vocabularyCheckTokens(grmVocabulary);
    grmVocabulary=0;
  }
}	break;}
    case 41: { /* <external vocabulary name> = <identifier>; */
{
  grmVocabulary=vocabularyGet(vocabularies, smkSeSt[smkStkP+1].name);
  if(grmVocabulary==0) smkLog(&smkSeSt[smkStkP+1].srcp,256,sevERR,"");
}	break;}
    case 42: { /* <internal vocabulary name> = <identifier>; */
{
  grmVocabulary=vocabularyNew(&vocabularies, smkSeSt[smkStkP+1].name);
  if(grmVocabulary)
    grmVocabulary->srcp=smkSeSt[smkStkP+1].srcp;
  else
    smkLog(&smkSeSt[smkStkP+1].srcp,255,sevERR,"");
}	break;}
    case 45: { /* <vocabulary definition> = <token name> '=' <number> ';'; */
{
  if(grmVocabulary) {
    Token token=tokenNew(&grmVocabulary->tokens, smkSeSt[smkStkP+1].name, smkSeSt[smkStkP+3].inumber);
    if(token==0) {
      if(tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name))
	smkLog(&smkSeSt[smkStkP+1].srcp,233,sevERR,"");
      if(tokenGetByCode(grmVocabulary->tokens, smkSeSt[smkStkP+3].inumber))
	smkLog(&smkSeSt[smkStkP+3].srcp,212,sevERR,"");
    }
    else {
      token->srcp=smkSeSt[smkStkP+1].srcp;
      token->vocabulary=grmVocabulary;
    }
  }
}	break;}
    case 48: { /* <scanner section> = '%%SCANNER' <scanner name> <scanner inherit opt> __genSym#2 <screening section opt> <undefine token section opt> <token sections>; */
{
  if(grmScanner) {
    if(grmScanner!=grmVocabulary->scanners) scannerCheckRedefinedPredefined(grmVocabulary->scanners, grmScanner);
    scannerCheckRules(grmScanner);
    grmScanner=0;
  }
}	break;}
    case 49: { /* __genSym#2 =; */
{
  if(grmScanner && grmScanner==grmVocabulary->scanners) {
    Token token;
    for(token=grmVocabulary->tokens;token;token=token->next) 
      if(token->name[0]=='"' || token->name[0]=='\'') {
	Rule rule;
	AST ast;

	if((ast=astString(token->name))) {
	  rule=ruleNew(&grmScanner->rules);
	  rule->srcp=token->srcp;
	  rule->scanner=grmScanner;
	  rule->token=token;
	  rule->ast=ast;
	  rule->type=rulePREDEF;
	}
	else
	  smkLog(&token->srcp,220,sevERR,"");
      }
  }
}	break;}
    case 50: { /* <scanner name> = <identifier>; */
{
  if(grmVocabulary) {
    grmScanner=scannerNew(&grmVocabulary->scanners, smkSeSt[smkStkP+1].name);
    if(grmScanner) {
      grmScanner->srcp=smkSeSt[smkStkP+1].srcp;
      grmScanner->vocabulary=grmVocabulary;
    }
    else
      smkLog(&smkSeSt[smkStkP+1].srcp,257,sevERR,"");
  }
}	break;}
    case 52: { /* <scanner inherit opt> = ':' <identifier>; */
{
  if(grmScanner) {
    Scanner baseScanner=scannerGet(grmVocabulary->scanners, smkSeSt[smkStkP+2].name);
    if(baseScanner)
      scannerCopy(grmScanner, baseScanner);
    else
      smkLog(&smkSeSt[smkStkP+2].srcp,258,sevERR,"");
  }
}	break;}
    case 57: { /* <undefined token name> = <token name> ';'; */
{
  if(grmScanner) {
    Rule rule;
    Token token=tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name);
    for(rule=grmScanner->rules;rule;rule=rule->next)
      if(rule->token==token) rule->type=ruleUNDEF;
  }
}	break;}
    case 60: { /* __genSym#3 =; */
{
   if(grmVocabulary && optScreen) {
     Token token;
     for(token=grmVocabulary->tokens;token;token=token->next) token->screening=NO;
   }
}	break;}
    case 58: { /* <screening section opt> =; */
{
   if(grmVocabulary && optScreen) {
     Token token;
     for(token=grmVocabulary->tokens;token;token=token->next) token->screening=YES;
   }
}	break;}
    case 63: { /* <screening definition> = <token name> ';'; */
{
  if(grmScanner && optScreen) {
    Token token=tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name);
    if(token) token->screening=YES;
  }
}	break;}
    case 68: { /* __genSym#4 =; */
 grmRuleType=ruleMATCH; 	break;}
    case 69: { /* __genSym#5 =; */
 grmRuleType=ruleSKIP;  	break;}
    case 72: { /* <token> = <token name> '=' <lookahead rule> <action opt> ';'; */
{
  if(grmScanner) {
    Token token=tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name);
    if(token==0 && grmRuleType==ruleSKIP) {
      token=tokenNew(&grmVocabulary->tokens, smkSeSt[smkStkP+1].name, codeSKIP);
      token->srcp=smkSeSt[smkStkP+1].srcp;
      token->vocabulary=grmVocabulary;
    }
    if(token) {
      Rule rule=rulePredefined(grmScanner->rules, smkSeSt[smkStkP+1].name);
      if(rule==0) rule=ruleNew(&grmScanner->rules);
      rule->srcp=smkSeSt[smkStkP+1].srcp;
      rule->scanner=grmScanner;
      rule->token=token;
      rule->type=grmRuleType;
      rule->ast=smkSeSt[smkStkP+3].ast;
      rule->action=smkSeSt[smkStkP+4].action;
    }
    else
      smkLog(&smkSeSt[smkStkP+1].srcp,259,sevERR,"");
  }
}	break;}
    case 73: { /* <token> = <token name> '=' '_ENDOFTEXT' <action opt> ';'; */
{
  if(grmScanner) {
    Token token=tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name);
    if(token==0 && grmRuleType==ruleSKIP) {
      token=tokenNew(&grmVocabulary->tokens, smkSeSt[smkStkP+1].name, codeSKIP);
      token->srcp=smkSeSt[smkStkP+1].srcp;
      token->vocabulary=grmVocabulary;
    }
    if(token) {
      Rule rule=rulePredefined(grmScanner->rules, smkSeSt[smkStkP+1].name);
      if(rule==0) rule=ruleNew(&grmScanner->rules);
      rule->srcp=smkSeSt[smkStkP+1].srcp;
      rule->scanner=grmScanner;
      rule->token=token;
      rule->type=grmRuleType;
      rule->ast=astEOT;
      rule->action=smkSeSt[smkStkP+4].action;
    }
    else
      smkLog(&smkSeSt[smkStkP+1].srcp,259,sevERR,"");
  }
}	break;}
    case 74: { /* <token> = <token name> '=' '_UNKNOWN' <action opt> ';'; */
{
  if(grmScanner) {
    Token token=tokenGetByName(grmVocabulary->tokens, smkSeSt[smkStkP+1].name);
    if(token==0 && grmRuleType==ruleSKIP) {
      token=tokenNew(&grmVocabulary->tokens, smkSeSt[smkStkP+1].name, codeSKIP);
      token->srcp=smkSeSt[smkStkP+1].srcp;
      token->vocabulary=grmVocabulary;
    }
    if(token) {
      Rule rule=ruleNew(&grmScanner->rules);
      rule->srcp=smkSeSt[smkStkP+1].srcp;
      rule->scanner=grmScanner;
      rule->token=token;
      rule->type=grmRuleType;
      rule->ast=astUNKNOWN;
      rule->action=smkSeSt[smkStkP+4].action;
    }
    else
      smkLog(&smkSeSt[smkStkP+1].srcp,259,sevERR,"");
  }
}	break;}
    case 79: { /* <action opt> = '%%'; */
{
  smkSeSt[smkStkP+1].action=smkSySt[smkStkP+1].action;
}	break;}
    case 78: { /* <action opt> = '%%DO' <identifier>; */
{
  Definition definition;
  
  definition=definitionGet(smkSeSt[smkStkP+2].name);
  if(definition==NULL || definition->action==NULL)
    smkLog(&smkSeSt[smkStkP+2].srcp,245,sevERR,"");
  else
    smkSeSt[smkStkP+1].action=definition->action;
}	break;}
    case 77: { /* <action opt> =; */
{
  smkSeSt[smkStkP+1].action=NULL;
}	break;}
    case 81: { /* <lookahead rule> = <selection rule> '/' <selection rule>; */
{
  smkSeSt[smkStkP+1].ast=astLookahead(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+3].ast);
}	break;}
    case 83: { /* <selection rule> = <selection rule> '!' <concat rule>; */
{
  smkSeSt[smkStkP+1].ast=astSelect(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+3].ast);
}	break;}
    case 85: { /* <concat rule> = <concat rule> <closure rule>; */
{
  smkSeSt[smkStkP+1].ast=astConcat(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+2].ast);
}	break;}
    case 87: { /* <closure rule> = <operand> '*'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,-1);
}	break;}
    case 88: { /* <closure rule> = <operand> '+'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,1,-1);
}	break;}
    case 89: { /* <closure rule> = <operand> '?'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,1);
}	break;}
    case 90: { /* <closure rule> = <operand> '{' <number> '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,smkSeSt[smkStkP+3].inumber);
}	break;}
    case 91: { /* <closure rule> = <operand> '{' '-' <number> '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,smkSeSt[smkStkP+4].inumber);
}	break;}
    case 92: { /* <closure rule> = <operand> '{' <number> '-' '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,-1);
}	break;}
    case 93: { /* <closure rule> = <operand> '{' <number> '-' <number> '}'; */
{
  if(smkSeSt[smkStkP+3].inumber>smkSeSt[smkStkP+5].inumber)
    smkLog(&smkSeSt[smkStkP+5].srcp,237,sevERR,"");
  else
    smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,smkSeSt[smkStkP+5].inumber);
}	break;}
    case 94: { /* <operand> = <identifier>; */
{
  Definition definition;
  
  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL || definition->ast==NULL)
    smkLog(&smkSeSt[smkStkP+1].srcp,239,sevERR,"");
  else
    smkSeSt[smkStkP+1].ast=definition->ast;
}	break;}
    case 95: { /* <operand> = <string>; */
{
  AST ast;

  if((ast=astString(smkSeSt[smkStkP+1].name)))
    smkSeSt[smkStkP+1].ast=ast;
  else
    smkLog(&smkSeSt[smkStkP+1].srcp,220,sevERR,"");
}	break;}
    case 96: { /* <operand> = <class>; */
{
  AST ast;

  if((ast=astClass(smkSeSt[smkStkP+1].name)))
    smkSeSt[smkStkP+1].ast=ast;
  else
    smkLog(&smkSeSt[smkStkP+1].srcp,238,sevERR,"");
}	break;}
    case 97: { /* <operand> = '.'; */
{
  smkSeSt[smkStkP+1].ast=astCut();
}	break;}
    case 98: { /* <operand> = '(' <selection rule> ')'; */
{
  smkSeSt[smkStkP+1].ast=smkSeSt[smkStkP+2].ast;
}	break;}
    case 99: { /* <identifier> = Identifier; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name;}	break;}
    case 100: { /* <string> = String; */
{ 
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; 
  smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name;
}	break;}
    case 101: { /* <number> = Number; */
{ 
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; 
  smkSeSt[smkStkP+1].inumber=smkSySt[smkStkP+1].inumber; 
}	break;}
    case 102: { /* <class> = Class; */
{
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp;
  smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name;
}	break;}
    default: break; }
}/*smkPaSema()*/

