/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 *
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/vocabulary.c,v 1.1 2002/06/25 20:05:03 Thomas Nilsson Exp $
 *
 * $Log: vocabulary.c,v $
 * Revision 1.1  2002/06/25 20:05:03  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.5  1997/06/26 11:53:52  hakan
 * <CR><LF> problematiken åtgärdad
 *
 * Revision 1.4  1997/01/22 16:28:10  gunilla
 * Adapted for WIN32
 *
 * Revision 1.3  1993/06/04 12:52:32  tools
 * Changed back xScScan to xScan
 *
 * Revision 1.2  1993/04/30  12:34:02  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/04/23  10:34:34  tools
 * Initial revision.
 *
 */

#include <stdio.h>
#include <fcntl.h>
#ifdef WIN32
#include <io.h>
#endif
#include "common.h"
#include "lmprintf.h"
#include "smalloc.h"
#include "smkList.h"
#include "smkScan.h"
#include "smk_i.h"
#include "token.h"
#include "vocabulary.h"

Vocabulary vocabularies=0;

Vocabulary vocabularyGet(Vocabulary vocabularies, Name name)
{
  for(;vocabularies;vocabularies=vocabularies->next)
    if(vocabularies->name==name) return vocabularies;
  return 0;
}

Vocabulary vocabularyNew(Vocabulary* vocabularies, Name name)
{
  Vocabulary vocabulary;
  if((*vocabularies)==0) {
    *vocabularies=vocabulary=(Vocabulary)smalloc(sizeof(VocabularyItem));
    vocabulary->name=name;
    vocabulary->tokens=0;
    vocabulary->scanners=0;
    vocabulary->next=0;
    return vocabulary;
  }
  else for(vocabulary=(*vocabularies);;) {
    if(vocabulary->name==name)
      return 0;
    else if(vocabulary->next)
      vocabulary=vocabulary->next;
    else {
      vocabulary=(vocabulary->next=(Vocabulary)smalloc(sizeof(VocabularyItem)));
      vocabulary->name=name;
      vocabulary->tokens=0;
      vocabulary->scanners=0;
      vocabulary->next=0;
      return vocabulary;
    }
  }
}

Bool vocabularyCheckTokens(Vocabulary vocabulary)
{
  Bool undefined=NO;
  if(vocabulary->scanners) {
    Scanner scanner;
    Token token;
    Rule rule;
    for(token=vocabulary->tokens;token;token=token->next) token->defined=NO;
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next) rule->token->defined=YES;
    for(token=vocabulary->tokens;token;token=token->next)
      if(token->defined==NO) {
  undefined=YES;
  smkLog(&token->srcp,236,sevERR,"");
      }
  }
  return undefined;
}

static Bool store(Name vocabularyName, Name tokenName, Code tokenCode)
{
  Vocabulary vocabulary;
  vocabulary=vocabularyGet(vocabularies, vocabularyName);
  if(vocabulary==0) vocabulary=vocabularyNew(&vocabularies, vocabularyName);
  return tokenNew(&vocabulary->tokens, tokenName, tokenCode) ? YES : NO;
}

void vocabularyRead(Name file)
{
  smkScContext context;
  SmkToken line;
  SmkToken ecode;
  SmkToken token;
  SmkToken vocabulary;
  int oldVocabulary;

  context=smkScNew(smk_VOCABULARY_MAIN_Scanner);
  if((context->fd=open(file,OFLAG))<0) {
    smkLog(NULL,223,sevWAR,file);
    return;
  }
  oldVocabulary=0;
  while(1) {

    smkScan(context,&line);
    line.srcp.file=0;
    if(line.code==smk_VOCABULARY_ENDOFTEXT_Token) break;
    if(line.code!=smk_VOCABULARY_NUMBER_Token) smkLog(&line.srcp,224,sevERR,"");
    if(line.code==smk_VOCABULARY_NEWLINE_Token) continue;

    smkScan(context,&ecode);
    ecode.srcp.file=0;
    if(ecode.code==smk_VOCABULARY_ENDOFTEXT_Token) break;
    if(ecode.code!=smk_VOCABULARY_NUMBER_Token) smkLog(&ecode.srcp,225,sevERR,"");
    if(ecode.code==smk_VOCABULARY_NEWLINE_Token) continue;

    smkScan(context,&token);
    token.srcp.file=0;
    if(token.code==smk_VOCABULARY_ENDOFTEXT_Token) break;
    if(token.code==smk_VOCABULARY_EOT_Token) {
      token.name=nameSearch("ENDOFTEXT");
      smkLog(&token.srcp,226,sevINF,"");
    }
    else if(token.code!=smk_VOCABULARY_IDENTIFIER_Token &&
      token.code!=smk_VOCABULARY_STRING_Token) smkLog(&token.srcp,227,sevERR,"");
    if(token.code==smk_VOCABULARY_NEWLINE_Token) continue;

    smkScan(context,&vocabulary);
    vocabulary.srcp.file=0;
    if(vocabulary.code==smk_VOCABULARY_ENDOFTEXT_Token) break;
    if(vocabulary.code==smk_VOCABULARY_NEWLINE_Token) {
      vocabulary.srcp.col=0;
      vocabulary.srcp.line=0;
      vocabulary.name=nameSearch("MAIN");
      if(!oldVocabulary) {
  smkLog(&vocabulary.srcp,228,sevINF,"");
  store(vocabulary.name, nameSearch("UNKNOWN"), 0);
  {
    Vocabulary voc=vocabularyGet(vocabularies,vocabulary.name);
    Token tok=tokenGetByName(voc->tokens,nameSearch("UNKNOWN"));
    tok->srcp=vocabulary.srcp;
    tok->vocabulary=voc;
  }
  smkLog(&vocabulary.srcp,244,sevINF,"");
  oldVocabulary=1;
      }
      goto EnterToken;
    }
    if(vocabulary.code!=smk_VOCABULARY_IDENTIFIER_Token) smkLog(&vocabulary.srcp,229,sevERR,"");

    smkScan(context,&line);
    line.srcp.file=0;
    if(line.code==smk_VOCABULARY_ENDOFTEXT_Token) break;
    if(line.code!=smk_VOCABULARY_NEWLINE_Token) smkLog(&line.srcp,230,sevERR,"");

  EnterToken:
    if(store(vocabulary.name, token.name, ecode.inumber)==NO)
      smkLog(&token.srcp,233,sevERR,"");
    else {
      Vocabulary voc=vocabularyGet(vocabularies,vocabulary.name);
      Token tok=tokenGetByName(voc->tokens,token.name);
      voc->srcp=vocabulary.srcp;
      tok->srcp=token.srcp;
      tok->vocabulary=voc;
    }
  }
  close(context->fd);
  smkScDelete(context);
}

void vocabularyDump(Vocabulary vocabulary)
{
  Token token;
  Scanner scanner;
  printf("%%VOCABULARY name='%s' %s\n",
   vocabulary->name,
   vocabulary->external ? "EXTERNAL DEFINED" : "INTERNAL DEFINED");
  for(token=vocabulary->tokens;token;token=token->next)
    tokenDump(token);
  for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
    scannerDump(scanner);
}

void vocabularyPrint()
{
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;

  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next) {
    smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
    lmPrintf("Vocabulary: %s\n", vocabulary->name);
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      lmPrintf("    Scanner: %2d %s\n", scanner->code, scanner->name);
      for(rule=scanner->rules;rule;rule=rule->next) {
  if(rule->code == codeSKIP)
    lmPrintf("\tSKIP");
  else
    lmPrintf("\t%4d",rule->code);
  if(rule->token->code == codeSKIP)
    lmPrintf(" SKIP %-15s", rule->token->name);
  else
    lmPrintf(" %4d %-15s", rule->token->code, rule->token->name);
  if(rule->screening)
    lmPrintf(" SCREENED");
  if(rule->screens)
    lmPrintf(" SCREENS A TOKEN");
  lmPrintf("\n");
      }
    }
  }
}
