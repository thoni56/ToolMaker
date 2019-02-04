%%OPTIONS

    Library '../../lib/c';
    Escape '`';

%%IMPORT

#include "tmk.h"
#include "tmk_i.h"

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(smThis->fd, smBuffer, smLength);

%%PREHOOK

  smToken->srcp.file = tmkEnv->fileNo;

%%DECLARATIONS

#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

tmkScContext tmkCext;

static char *newStr(smThis, skip)
  register tmkScContext smThis;
  register int skip;
{
  char *temp = (char *) malloc(smThis->smLength+1-2*skip);

  tmkScCopy(smThis,(unsigned char *)temp, skip, smThis->smLength-skip);
  temp[smThis->smLength-2*skip] = 0;
  return temp;
}


%%MAP

  [a-z]		= [A-Z];
  [\xe0-\xf6]	= [\xC0-\xD6];
  [\xf8-\xfe]	= [\xD8-\xDE];

%%DEFINITIONS

  Letter	= [A-Z\xC0-\xD6\xD8-\xDE];
  Digit		= [0-9];

  String	= ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
  Identifier	= Letter([_]?(Letter!Digit))*;
  Number	= [0-9]+;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?;

  Skiphead1     = '%%RULES' ! '%%SKIP';
  Skiphead2     = '%%TERMINALS' ! '%%RECOVERY' ! '%%DEFINITIONS';
  Skiphead3     = '%%'Letter+;

%%VOCABULARY main
%%SCANNER main %%RULES

  'ATTRIBUTES'  = 'ATTRIBUTES'  %% smToken->sval = newStr(smThis, 0); %%;
  'NAME'        = 'NAME'        %% smToken->sval = newStr(smThis, 0); %%;
  'CODE'        = 'CODE'        %% smToken->sval = newStr(smThis, 0); %%;
  'SRCP'        = 'SRCP'        %% smToken->sval = newStr(smThis, 0); %%;
  'ROW'         = 'ROW'         %% smToken->sval = newStr(smThis, 0); %%;
  'COLUMN'      = 'COLUMN'      %% smToken->sval = newStr(smThis, 0); %%;
  'FILE'        = 'FILE'        %% smToken->sval = newStr(smThis, 0); %%;
  'POSITION'    = 'POSITION'    %% smToken->sval = newStr(smThis, 0); %%;
  IDENTIFIER    = Identifier    %% smToken->sval = newStr(smThis, 0); %%;
  NUMBER    = Number	%% smToken->ival = atoi(smThis->smText); %%;
  STRING	= String	%% smToken->sval = newStr(smThis, 1); %%;
  '%%IMPORT'    = '%%IMPORT'
      %%
          tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
  SKIPHEADER    = Skiphead1
      %%
          /* Skip a section where ToolMaker strings and semantic actions exist */
          tmkSkipCode(RULES_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
  SKIPHEADER    = Skiphead2
      %%
          /* Skip a section where ToolMaker strings exists */
          tmkSkipCode(STRSKP_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
  SKIPHEADER    = Skiphead3
      %%
          /* Skip a section where no ToolMaker strings exists */
          tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
  '%%'      = '%%'
      %%
          tmkSkipCode(SEM_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
          smToken->sval = newStr(smThis, 2);
      %%;
  Unknown	= _Unknown;
  EndOfText     = _EndOfText;

%%SKIP
  comment	= '%%COMMENT';
  comment	= '--'[^\n]*;
  blank		= [- \x7F-]+;
