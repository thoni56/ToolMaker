-- pmk.smk
--
-- pmk - ScannerMaker lexical description file
--

%%OPTIONS

    Escape '`';
    Target 'c';

%%IMPORT

#include <unistd.h>
#include "pws.h"
#include "pwsLexCode.h"

#define DECL 0
#define CODE 1
#define ACTION 2
#define SKIP 3

extern char pmkEscape;

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(smThis->fd,smBuffer,smLength);

%%PREHOOK

  smToken->srcp.file = 0;

%%DECLARATIONS

#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

#define gch() (n++ < smThis->smLength? *(s++): ((n = smSkip(smThis,1000000000)) == 0? EOF:\
((n = smThis->smLength - n), (s = (char *)&smThis->smText[n]), n++, *(s++))))

static char *newStr(smThis, skip)
  register pmkScContext smThis;
  register int skip;
{
  char *temp = (char *) malloc(smThis->smLength+1-2*skip);

  pmkScCopy(smThis,(unsigned char *)temp, skip, smThis->smLength-skip);
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
  hexdigit	= [0-9]![A-F];
  hexint        = '#' hexdigit+;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?;

  Skiphead1     = '%%IMPORT' ! '%%SRCP' ! '%%TOKEN';
  Skiphead2     = '%%OPTIONS';


%%VOCABULARY main

%%SCANNER main %%RULES

  IDENTIFIER       = Identifier     %% smToken->sval = newStr(smThis, 0); %%;
  INTEGER      = Number ! hexint	%% smToken->ival = atoi((char *)smThis->smText); %%;
  STRING	   = String		%% smToken->sval = newStr(smThis, 0); %%;
  ANG_BRACK_STRING = '<' [^>\n]* '>'	%% smToken->sval = newStr(smThis, 0); %%;
  '%%DECLARATIONS' = '%%DECLARATIONS'
      %%
        /* Read past declarations */
        tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                  &(smToken->length), pmkEscape);
      %%
    ;

  '%%EXPORT' = '%%EXPORT'
    %%
          tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                  &(smToken->length), pmkEscape);
    %%;
  '%%SCANNER' = '%%SCANNER'
    %%
      tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                  &(smToken->length), pmkEscape);
    %%;
  '%%INSERTSYMBOL' = '%%INSERTSYMBOL'
    %%
      tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                  &(smToken->length), pmkEscape);
    %%;

  '%%DELETESYMBOL' = '%%DELETESYMBOL'
    %%
      tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                  &(smToken->length), pmkEscape);
    %%;

  SKIPHEADER    = Skiphead1
      %%
    tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), pmkEscape);
      %%;
  SKIPHEADER    = Skiphead2
      %%
    tmkSkipCode(STRSKP_SKIP, smThis,&(smToken->fpos), &(smToken->length),  pmkEscape);
      %%;

  '%%' = '%%'
      %%
        /* Read past action */
        tmkSkipCode(SEM_SKIP, smThis, &(smToken->fpos), &(smToken->length), pmkEscape);
        smToken->sval = newStr(smThis, 2);
        smToken->sval[smToken->length] = '\0';
      %%
    ;

  Unknown	= _Unknown;
  EndOfText     = _EndOfText;

%%SKIP
  comment	= '%%COMMENT';
  comment	= '--'[^\n]*;
  blank		= [ \t\n\r]+;
