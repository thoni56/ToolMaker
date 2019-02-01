/*----------------------------------------------------------------------*\

	smkPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include <stdio.h>
#include "smk_i.h"
#include "smkScan.h"
#include "smkList.h"
#include "ast.h"
#include "definition.h"
#include "name.h"
#include "scanner.h"
#include "token.h"
#include "voc.h"
#include "set.h"
#include "map.h"
#include "pack.h"
#include "action.h"
extern smkContext lexContext;
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

extern Scanner grmScanner;		/* Current scanner */
extern TokenType grmTokenType;		/* Current token type */

/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * smkPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void smkPaSema(rule)
int rule;			/* IN production number */
{
    switch (rule) {
          case 2: { /* __genSym#0 =; */
{
  vocRead(optVocabulary);
}	break;}
    case 27: { /* <map section> = '%%MAP' <maps> <end opt>; */
{
  mapUsed=1;
}	break;}
    case 30: { /* <map> = <class> '=' <class> ';'; */
{
  mapPut(smkSeSt[smkStkP+1].name,smkSeSt[smkStkP+3].name);
}	break;}
    case 34: { /* <definition rule> = <identifier> '=' <selection rule opt> <action opt> ';'; */
{
  register Definition definition;

  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL) definition=definitionPut(smkSeSt[smkStkP+1].name);
  if(smkSeSt[smkStkP+3].ast)
    if(definition->ast)
      smkLog(&smkSeSt[smkStkP+1].srcp,233,sevERR,"");
    else 
      definition->ast=smkSeSt[smkStkP+3].ast;
  if(smkSeSt[smkStkP+4].action)
    if(definition->action) 
      smkLog(&smkSeSt[smkStkP+1].srcp,246,sevERR,"");
    else
      definition->action=smkSeSt[smkStkP+4].action;
}	break;}
    case 36: { /* <selection rule opt> = <selection rule>; */
{
  smkSeSt[smkStkP+1].ast=smkSeSt[smkStkP+1].ast;
}	break;}
    case 35: { /* <selection rule opt> =; */
{
  smkSeSt[smkStkP+1].ast=NULL;
}	break;}
    case 37: { /* <scanner section> = '%%SCANNER' <scanner name> <auto opt> <vocabulary section opt> <screening section opt> <token sections>; */
{
  if(grmScanner) {
    vocCheck(grmScanner);
    tokenCheck(grmScanner);
  }
}	break;}
    case 38: { /* <scanner section> = <scanner copy> <screening section opt> <token sections>; */
{
  if(grmScanner) {
    vocCheck(grmScanner);
    tokenCheck(grmScanner);
  }
}	break;}
    case 39: { /* <scanner name> = <identifier>; */
{
  grmScanner=scannerPut(&smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name);
}	break;}
    case 40: { /* <scanner copy> = '%%SCANNER' <scanner name> ':' <identifier>; */
{
  register Scanner scanner;

  if(grmScanner) {
    scanner=scannerGet(smkSeSt[smkStkP+4].name);
    if(scanner) {
      vocCopyAll(grmScanner,scanner->voc);
      tokenCopyAll(grmScanner,scanner->token);
      grmScanner->vocLock=1;
    }
    else
      smkLog(&smkSeSt[smkStkP+4].srcp,234,sevERR,"");
  }
}	break;}
    case 42: { /* <auto opt> = 'AUTO'; */
{
  if(grmScanner) grmScanner->vocAuto=1;
}	break;}
    case 43: { /* <auto opt> = 'NO' 'AUTO'; */
{
  if(grmScanner) grmScanner->vocAuto=0;
}	break;}
    case 41: { /* <auto opt> =; */
{
  if(grmScanner) grmScanner->vocAuto=1;
}	break;}
    case 46: { /* <vocabulary section opt> = '%%VOCABULARY' <token definitions>; */
{
  if(grmScanner) grmScanner->vocLock=1;
}	break;}
    case 45: { /* <vocabulary section opt> = '%%VOCABULARY' <identifier>; */
{
  register Scanner scanner;

  if(grmScanner) {
    scanner=scannerGet(smkSeSt[smkStkP+2].name);
    if(scanner) {
      vocCopyAll(grmScanner,scanner->voc);
      grmScanner->vocLock=1;
    }
    else
      smkLog(&smkSeSt[smkStkP+2].srcp,234,sevERR,"");
  }
}	break;}
    case 49: { /* <token definition> = <token name> '=' <number> ';'; */
{
  if(grmScanner) {
    vocPut(grmScanner, &smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name, &smkSeSt[smkStkP+3].srcp, smkSeSt[smkStkP+3].inumber);
  }
}	break;}
    case 55: { /* <screening definition> = <token name> 'NO' 'SCREENING' ';'; */
{
  register Voc voc;

  voc=vocGet(grmScanner,smkSeSt[smkStkP+1].name);
  if(voc)
    voc->screening=0;
  else if((voc=vocPut(grmScanner, &smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name, NULL, -1))==NULL)
    smkLog(&smkSeSt[smkStkP+1].srcp,213,sevERR,"");
  else
    voc->screening=0;
}	break;}
    case 54: { /* <screening definition> = <token name> 'SCREENING' ';'; */
{
  register Voc voc;

  voc=vocGet(grmScanner,smkSeSt[smkStkP+1].name);
  if(voc)
    voc->screening=optScreen>0 ? 1 : 0;
  else if((voc=vocPut(grmScanner, &smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name, NULL, -1))==NULL)
    smkLog(&smkSeSt[smkStkP+1].srcp,213,sevERR,"");
  else
    voc->screening=optScreen>0 ? 1 : 0;
}	break;}
    case 60: { /* __genSym#1 =; */
 grmTokenType=tokenRULE; 	break;}
    case 61: { /* __genSym#2 =; */
 grmTokenType=tokenSKIP; 	break;}
    case 65: { /* <token> = <token name> '=' <lookahead rule> <action opt2> ';'; */
{
  if(grmScanner) {
    register Token token;
  
    if(token=tokenPut(grmScanner,grmTokenType,&smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name)) {
      token->a.ast=smkSeSt[smkStkP+3].ast;
      token->action=smkSeSt[smkStkP+4].action;
      token->sequence=astToName(token->a.ast);
    }
  }
}	break;}
    case 66: { /* <token> = <token name> '=' '_ENDOFTEXT' <action opt2> ';'; */
{
  if(grmScanner) {
    register Token token;
  
    if(token=tokenPut(grmScanner,grmTokenType,&smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name)) {
      token->type|=tokenEOT;
      token->a.ast=NULL;
      token->action=smkSeSt[smkStkP+4].action;
    }
  }
}	break;}
    case 67: { /* <token> = <token name> '=' '_UNKNOWN' <action opt2> ';'; */
{
  if(grmScanner) {
    register Token token;

    if(token=tokenPut(grmScanner,grmTokenType,&smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name)) {
      token->type|=tokenUNKNOWN;
      token->a.ast=NULL;
      token->action=smkSeSt[smkStkP+4].action;
    }
  }
}	break;}
    case 64: { /* <token> = <token name> ';'; */
{
  if(tokenRemove(grmScanner,grmTokenType,smkSeSt[smkStkP+1].name)<0)
    smkLog(&smkSeSt[smkStkP+1].srcp,211,sevERR,"");
}	break;}
    case 72: { /* <screen token> = <screen token name> '=' <identifier> <action opt> ';'; */
{
  if(grmScanner) {
    register Token token;
    register Voc voc;

    if(voc=vocGet(grmScanner,smkSeSt[smkStkP+3].name)) {
      if(token=tokenPut(grmScanner,tokenSCREEN,&smkSeSt[smkStkP+1].srcp, smkSeSt[smkStkP+1].name)) {
	token->a.screen=voc;
	token->action=smkSeSt[smkStkP+4].action;
      }
    }
    else
      smkLog(&smkSeSt[smkStkP+3].srcp,236,sevERR,"");
  }
}	break;}
    case 75: { /* <action opt2> = '%%'; */
{
  smkSeSt[smkStkP+1].action=smkSySt[smkStkP+1].action;
}	break;}
    case 76: { /* <action opt2> = '%%DO' <identifier>; */
{
  register Definition definition;
  
  definition=definitionGet(smkSeSt[smkStkP+2].name);
  if(definition==NULL || definition->action==NULL)
    smkLog(&smkSeSt[smkStkP+2].srcp,245,sevERR,"");
  else
    smkSeSt[smkStkP+1].action=definition->action;
}	break;}
    case 74: { /* <action opt2> =; */
{
  smkSeSt[smkStkP+1].action=NULL;
}	break;}
    case 78: { /* <action opt> = '%%'; */
{
  smkSeSt[smkStkP+1].action=smkSySt[smkStkP+1].action;
}	break;}
    case 77: { /* <action opt> =; */
{
  smkSeSt[smkStkP+1].action=NULL;
}	break;}
    case 80: { /* <lookahead rule> = <selection rule> '/' <selection rule>; */
{
  smkSeSt[smkStkP+1].ast=astLookahead(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+3].ast);
}	break;}
    case 82: { /* <selection rule> = <selection rule> '!' <concat rule>; */
{
  smkSeSt[smkStkP+1].ast=astSelect(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+3].ast);
}	break;}
    case 84: { /* <concat rule> = <concat rule> <closure rule>; */
{
  smkSeSt[smkStkP+1].ast=astConcat(smkSeSt[smkStkP+1].ast, smkSeSt[smkStkP+2].ast);
}	break;}
    case 86: { /* <closure rule> = <operand> '*'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,-1);
}	break;}
    case 87: { /* <closure rule> = <operand> '+'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,1,-1);
}	break;}
    case 88: { /* <closure rule> = <operand> '?'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,1);
}	break;}
    case 89: { /* <closure rule> = <operand> '{' <number> '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,smkSeSt[smkStkP+3].inumber);
}	break;}
    case 90: { /* <closure rule> = <operand> '{' '-' <number> '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,0,smkSeSt[smkStkP+4].inumber);
}	break;}
    case 91: { /* <closure rule> = <operand> '{' <number> '-' '}'; */
{
  smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,-1);
}	break;}
    case 92: { /* <closure rule> = <operand> '{' <number> '-' <number> '}'; */
{
  if(smkSeSt[smkStkP+3].inumber>smkSeSt[smkStkP+5].inumber)
    smkLog(&smkSeSt[smkStkP+5].srcp,237,sevERR,"");
  else
    smkSeSt[smkStkP+1].ast=astClosure(smkSeSt[smkStkP+1].ast,smkSeSt[smkStkP+3].inumber,smkSeSt[smkStkP+5].inumber);
}	break;}
    case 93: { /* <operand> = <identifier>; */
{
  register Definition definition;
  
  definition=definitionGet(smkSeSt[smkStkP+1].name);
  if(definition==NULL || definition->ast==NULL)
    smkLog(&smkSeSt[smkStkP+1].srcp,239,sevERR,"");
  else
    smkSeSt[smkStkP+1].ast=definition->ast;
}	break;}
    case 94: { /* <operand> = <string>; */
{
  register AST ast;

  if(ast=astString(smkSeSt[smkStkP+1].name))
    smkSeSt[smkStkP+1].ast=ast;
  else
    smkLog(&smkSeSt[smkStkP+1].srcp,220,sevERR,"");
}	break;}
    case 95: { /* <operand> = <class>; */
{
  register AST ast;

  if(ast=astClass(smkSeSt[smkStkP+1].name))
    smkSeSt[smkStkP+1].ast=ast;
  else
    smkLog(&smkSeSt[smkStkP+1].srcp,238,sevERR,"");
}	break;}
    case 96: { /* <operand> = '.'; */
{
  smkSeSt[smkStkP+1].ast=astCut();
}	break;}
    case 97: { /* <operand> = '(' <selection rule> ')'; */
{
  smkSeSt[smkStkP+1].ast=smkSeSt[smkStkP+2].ast;
}	break;}
    case 98: { /* <identifier> = Identifier; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 99: { /* <identifier> = 'ADA'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 100: { /* <identifier> = 'AUTO'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 101: { /* <identifier> = 'BYTE'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 102: { /* <identifier> = 'C'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 103: { /* <identifier> = 'COL'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 104: { /* <identifier> = 'DES'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 105: { /* <identifier> = 'DFA'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 106: { /* <identifier> = 'ERR'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 107: { /* <identifier> = 'ESCAPE'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 108: { /* <identifier> = 'EXCLUDE'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 109: { /* <identifier> = 'GCS'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 110: { /* <identifier> = 'K'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 111: { /* <identifier> = 'LES'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 112: { /* <identifier> = 'LIST'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 113: { /* <identifier> = 'M'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 114: { /* <identifier> = 'MAP'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 115: { /* <identifier> = 'NFA'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 116: { /* <identifier> = 'NO'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 117: { /* <identifier> = 'POS'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 118: { /* <identifier> = 'POSITION'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 119: { /* <identifier> = 'RDS'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 120: { /* <identifier> = 'ROWCOL'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 121: { /* <identifier> = 'ROW'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 122: { /* <identifier> = 'SCR'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 123: { /* <identifier> = 'SCREENING'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 124: { /* <identifier> = 'SET'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 125: { /* <identifier> = 'TOK'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 126: { /* <identifier> = 'TOKEN'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 127: { /* <identifier> = 'TRACE'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 128: { /* <identifier> = 'VERBOSE'; */
{ smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name; }	break;}
    case 129: { /* <string> = String; */
{ 
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; 
  smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name;
}	break;}
    case 130: { /* <number> = Number; */
{ 
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp; 
  smkSeSt[smkStkP+1].inumber=smkSySt[smkStkP+1].inumber; 
}	break;}
    case 131: { /* <class> = Class; */
{
  smkSeSt[smkStkP+1].srcp=smkSySt[smkStkP+1].srcp;
  smkSeSt[smkStkP+1].name=smkSySt[smkStkP+1].name;
}	break;}
    default: break; }
}/*smkPaSema()*/

