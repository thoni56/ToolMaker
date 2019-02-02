-- tmk.lex			Date: 1993-04-23/tools@lion 14:35:41/toolmake
--
-- tmk - ScannerMaker lexical description file
--


%%OPTIONS
	Escape '`';
	Target 'c';
	LIBRARY '../..';
	
%%DECLARATIONS
#include "tmk_i.h"
tmkContext tmkCext;


static char *newStr(this, skip)
  register tmkContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  tmkCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}


%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(this->fd, smBuffer, smLength);

%%PREHOOK

  smToken->srcp.file = tmkEnv->fileNo;

%%MAP

  [a-z]		= [A-Z];

%%DEFINITIONS

  Letter	= [A-Z\xC0-\xD6\xD8-\xF6\xF8-\xFF];
  Digit		= [0-9];

  String	= ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
  Identifier	= Letter([_]?(Letter!Digit))*;
  Number	= [0-9]+;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?;

  Skiphead1     = '%%RULES' ! '%%SKIP';
  Skiphead2     = '%%TERMINALS' ! '%%RECOVERY' ! '%%DEFINITIONS';
  Skiphead3     = '%%'Letter+;

%%VOCABULARY main
    %%SCANNER main
	%%RULES

	    'ATTRIBUTES'  = 'ATTRIBUTES'  %% smToken->sval = newStr(this, 0); %%;
	    'NAME'        = 'NAME'        %% smToken->sval = newStr(this, 0); %%;
	    'CODE'        = 'CODE'        %% smToken->sval = newStr(this, 0); %%;
	    'SRCP'        = 'SRCP'        %% smToken->sval = newStr(this, 0); %%;
	    'ROW'         = 'ROW'         %% smToken->sval = newStr(this, 0); %%;
	    'COLUMN'      = 'COLUMN'      %% smToken->sval = newStr(this, 0); %%;
	    'FILE'        = 'FILE'        %% smToken->sval = newStr(this, 0); %%;
	    'POSITION'    = 'POSITION'    %% smToken->sval = newStr(this, 0); %%;
	    IDENTIFIER    = Identifier    %% smToken->sval = newStr(this, 0); %%;
	    NUMBER 	= Number	%% smToken->ival = atoi(this->smText); %%;
	    STRING	= String	%% smToken->sval = newStr(this, 1); %%;
	    '%%IMPORT'    = '%%IMPORT'
      %%
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
	    SKIPHEADER    = Skiphead1
      %%
	/* Skip a section where ToolMaker strings and semantic actions exist */
	tmkSkipCode(RULES_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
	    SKIPHEADER    = Skiphead2
      %%
	/* Skip a section where ToolMaker strings exists */
	tmkSkipCode(STRSKP_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
	    SKIPHEADER    = Skiphead3
      %%
	/* Skip a section where no ToolMaker strings exists */
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      %%;
	    '%%' 		= '%%'
      %%
	tmkSkipCode(SEM_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
        smToken->sval = newStr(this, 2);
      %%;
	    Unknown	= _Unknown;
	    EndOfText     = _EndOfText;

	%%SKIP
	    comment	= '%%COMMENT';
	    comment	= '--'[^\n]*'\n';
	    blank		= [- \x7F-]+;
%%END
