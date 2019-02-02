-- pmk.lex			Date: 1993-04-23/tools@lion 14:35:41/toolmake
--
-- pmk - ScannerMaker lexical description file
--


%%OPTIONS

	Escape '`';
	Target 'c';
	LIBRARY '../..';

%%DECLARATIONS

#include "pws.h"
#include "pwsLexCode.h"

#define DECL 0
#define CODE 1
#define ACTION 2
#define SKIP 3

extern char pmkEscape;


#define gch() (n++ < this->smLength? *(s++): ((n = smSkip(this,1000000000)) == 0? EOF:\
((n = this->smLength - n), (s = (char *)&this->smText[n]), n++, *(s++))))

static char *newStr(this, skip)
  register pmkContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  pmkCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}


%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(this->fd,smBuffer,smLength);

%%PREHOOK

  smToken->srcp.file = 0;

%%MAP

  [a-z]		= [A-Z];

%%DEFINITIONS

  Letter	= [A-Z\xC0-\xD6\xD8-\xF6\xF8-\xFF];
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
    %%SCANNER main
	%%RULES

	    IDENTIFIER       = Identifier    	%% smToken->sval = newStr(this, 0); %%;
	    INTEGER 	   = Number ! hexint	%% smToken->ival = atoi(this->smText); %%;
	    STRING	   = String		%% smToken->sval = newStr(this, 0); %%;
	    ANG_BRACK_STRING = '<' [^>]* '>'	%% smToken->sval = newStr(this, 0); %%;	
	    '%%DECLARATIONS' = '%%DECLARATIONS'
	  %%
	    /* Read past declarations
	     */
	    code_spec.udata_line = this->smLine;
	    tmkSkipCode(NOSTRS_SKIP, this, &code_spec.udata_start, 
		        &code_spec.udata_cnt, pmkEscape);
	  %%
	;

	    '%%CODE' = '%%CODE'
	  %%
	    /* Read past code
	     */
	    code_spec.ucode_line = this->smLine;
	    tmkSkipCode(NOSTRS_SKIP, this, &code_spec.ucode_start, 
		        &code_spec.ucode_cnt, pmkEscape);
	  %%
	;
	    '%%EXPORT' = '%%EXPORT'
	%%
          tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	%%;
	    '%%SCANNER' = '%%SCANNER'
	%%
	  tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	%%;
	    '%%INSERTSYMBOL' = '%%INSERTSYMBOL'
	%%
	  tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	%%;

	    SKIPHEADER    = Skiphead1
      %%
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), pmkEscape);
      %%;
	    SKIPHEADER    = Skiphead2
      %%
	tmkSkipCode(STRSKP_SKIP, this,&(smToken->fpos), &(smToken->length),  pmkEscape);
      %%;

	    '%%' = '%%'
	  %%
	    /* Read past action
	     */
	    tmkSkipCode(SEM_SKIP, this, &(smToken->fpos), &(smToken->length), pmkEscape);
	    smToken->sval = newStr(this, 2);
	    smToken->sval[smToken->length] = '\0';
	  %%
	;

	    Unknown	= _Unknown;
	    EndOfText     = _EndOfText;

	%%SKIP
	    comment	= '%%COMMENT';
	    comment	= '--'[^\n]*'\n';
	    blank		= [- \x7F-]+;
%%END
