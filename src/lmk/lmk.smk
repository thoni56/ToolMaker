-- lmk.lex                      Date: 1992-04-07 14:35:41/toolmake
--
-- lmk - ScannerMaker lexical description file
--
%%IMPORT

#include "lmk_i.h"

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(smThis->fd,smBuffer,smLength);

%%PREHOOK

  smToken->srcp.file = 1;

%%DECLARATIONS

#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

static char *newStr(this, skip)
  register lmkScContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  lmkScCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}


%%MAP

  [a-z]         = [A-Z];
  [\xe0-\xf6]	= [\xC0-\xD6];
  [\xf8-\xfe]	= [\xD8-\xDE];

%%DEFINITIONS

  Letter        = [A-Z\xC0-\xD6\xD8-\xDE];
  Digit         = [0-9];

  String        = ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
  Identifier    = Letter([_]?(Letter!Digit))*;
  Number        = [0-9]+;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?;

  Skiphead1     = '%%IMPORT' ! '%%SRCP' ! '%%TOKEN';
  Skiphead2     = '%%OPTIONS';


%%VOCABULARY main

%%SCANNER main %%RULES

  IDENTIFIER    = Identifier    %% smToken->sval = newStr(smThis, 0); %%;
  NUMBER        = Number        %% smToken->ival = atoi(smThis->smText); %%;
  STRING        = String        %% smToken->sval = newStr(smThis, 1); %%;
  SKIPHEADER    = Skiphead1
      %%
        tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
                    &(smToken->length), lmkEscape);
      %%;
  SKIPHEADER    = Skiphead2
      %%
        tmkSkipCode(STRSKP_SKIP, smThis,&(smToken->fpos),
                    &(smToken->length),  lmkEscape);
      %%;

  Unknown       = _Unknown;
  EndOfText     = _EndOfText;

%%SKIP
  comment       = '%%COMMENT';
  comment       = '--'[^\n]*;
  blank         = [ \t\n\r]+;
