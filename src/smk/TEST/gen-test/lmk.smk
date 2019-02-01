-- lmk.lex                      Date: 1993-04-23/tools@lion 14:35:41/toolmake
--
-- lmk - ScannerMaker lexical description file
--
%%OPTIONS

	LIBRARY '../..';

%%DECLARATIONS

#include "lmk_i.h"


static char *newStr(this, skip)
  register lmkContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  lmkCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(this->fd,smBuffer,smLength);

%%PREHOOK

  smToken->srcp.file = 1;

%%MAP

  [a-z]         = [A-Z];

%%DEFINITIONS

  Letter        = [A-Z\xC0-\xD6\xD8-\xF6\xF8-\xFF];
  Digit         = [0-9];

  String        = ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
  Identifier    = Letter([_]?(Letter!Digit))*;
  Number        = [0-9]+;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?;

  Skiphead1     = '%%IMPORT' ! '%%SRCP' ! '%%TOKEN';
  Skiphead2     = '%%OPTIONS';

%%VOCABULARY main
    %%SCANNER main
	 %%RULES

	    IDENTIFIER    = Identifier    %% smToken->sval = newStr(this, 0); %%;
	    NUMBER        = Number        %% smToken->ival = atoi(this->smText); %%;
	    STRING        = String        %% smToken->sval = newStr(this, 1); %%;
	    SKIPHEADER    = Skiphead1
      %%
        tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
                    &(smToken->length), lmkEscape);
      %%;
	    SKIPHEADER    = Skiphead2
      %%
        tmkSkipCode(STRSKP_SKIP, this,&(smToken->fpos),
                    &(smToken->length),  lmkEscape);
      %%;

	    Unknown       = _Unknown;
	    EndOfText     = _EndOfText;

	%%SKIP
	    comment       = '%%COMMENT';
	    comment       = '--'[^\n]*'\n';
	    blank         = [- \x7F-]+;
%%END
