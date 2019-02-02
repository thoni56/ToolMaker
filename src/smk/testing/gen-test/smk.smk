%%OPTIONS
	LIBRARY '../..';
%%DECLARATIONS

#include <stdio.h>
#include "smk_i.h"
#include "name.h"
#include "smkList.h"
#include "action.h"

extern double atof();

smkContext lexContext;


/*
 * Skip characters until '`%%' and write them to optTable
 */

static Action lexWriteAction(this,type,skip)
     register smkContext this;
     register ActionType type;
     register int skip;
{
  register Action action;
  register unsigned char *ch;
  register int at;
  register int state;

  if(type!=actionNONE)
    action=actionPut(type,this->smNextPosition,0);
  else
    action=NULL;
  state=0;
  while(smkSkip(this,10000)) {
    ch=this->smText+2;
    for(at=2;at<this->smLength;at++,ch++)
      switch(state) {
      case 0:
	if(*ch=='%') state=1;
	else if(*ch==smkEscape) state=3;
	break;
      case 1:
	if(*ch=='%') state=2;
	else if(*ch==smkEscape) state=3;
	else state=0;
	break;
      case 2:
	goto Exit;
      case 3:
	state=0;
	break;
      }
  }
  skip=0;
 Exit:
  smkSkip(this,at-this->smLength-skip);
  if(type!=actionNONE) action->stop=this->smNextPosition-3+skip;
  return action;
}

static Name lexName(this)
     register smkContext this;
{
  register char rem;
  register Name name;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  name=nameSearch(this->smText);
  this->smText[this->smLength]=rem;
  return name;
}
 
static int lexNumber(this)
     register smkContext this;
{
  register char rem;
  register int inumber;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  inumber=atoi(this->smText);
  this->smText[this->smLength]=rem;
  return inumber;
}

static double lexFloat(this)
     register smkContext this;
{
  register char rem;
  register double fnumber;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  fnumber=atof(this->smText);
  this->smText[this->smLength]=rem;
  return fnumber;
}

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(this->fd,smBuffer,smLength);

%%POSTHOOK

  smToken->srcp.file=1;

%%SET IBMSET

-- 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
------------------------------------------------------------------------
   00  01  02  03  ..  09  ..  7F  ..  ..  ..  0B  0C  0D  0E  0F  -- 0
   10  11  12  13  ..  ..  08  ..  18  19  ..  ..  ..  ..  ..  ..  -- 1
   ..  ..  1C  ..  ..  0A  17  1B  ..  ..  ..  ..  ..  05  06  07  -- 2
   ..  ..  ..  ..  ..  ..  ..  04  ..  ..  ..  ..  14  15  ..  16  -- 3
   20  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  .   <   (   +   ..  -- 4
   &   ..  ..  ..  ..  ..  ..  ..  ..  ..  !   $   *   )   ;   ..  -- 5
   -   /   ..  ..  ..  ..  ..  ..  ..  ..  |   ,   %   _   >   ?   -- 6
   ..  ..  ..  ..  ..  ..  ..  ..  ..  `   :   #   @   '   =   "   -- 7
   ..  a   b   c   d   e   f   g   h   i   ..  ..  ..  ..  ..  ..  -- 8
   ..  j   k   l   m   n   o   p   q   r   ..  ..  ..  ..  ..  ..  -- 9
   ..  ~   s   t   u   v   w   x   y   z   ..  ..  ..  ..  ..  ..  -- A
   ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  ..  -- B
   {   A   B   C   D   E   F   G   H   I   ..  ..  ..  ..  ..  ..  -- C
   }   J   K   L   M   N   O   P   Q   R   ..  ..  ..  ..  ..  ..  -- D
   \   ..  S   T   U   V   W   X   Y   Z   ..  ..  ..  ..  ..  ..  -- E
   0   1   2   3   4   5   6   7   8   9   ..  ..  ..  ..  ..  ..  -- F

%%MAP

  [a-z]		= [A-Z];

%%DEFINITIONS

  Letter	= [A-Z\xC0-\xD6\xD8-\xF6\xF8-\xFF];
  Digit		= [0-9];

  String	= ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
  Identifier	= Letter([_]?(Letter!Digit))*;
  Number	= [0-9]+				%% smToken->inumber=lexNumber(this); %%;
  Float         = [0-9]+('.'[0-9]+)?('E'[+\-][0-9]+)?   %% smToken->fnumber=lexFloat(this); %%;

-- Define Commonly used actions!

  Name     = %% smToken->name=lexName(this); %%;

%%VOCABULARY main
    %%SCANNER main
	 %%RULES

	    'ADA'		= 'ADA'			%%DO Name;
	    'AUTO'	= 'AUTO'		%%DO Name;
	    'BYTE'	= 'BYTE'		%%DO Name;
	    'C' 		= 'C'			%%DO Name;
	    'COL'		= 'COL'			%%DO Name;
	    'DES'		= 'DES'			%%DO Name;
	    'DFA'		= 'DFA'			%%DO Name;
	    'ERR'		= 'ERR'			%%DO Name;
	    'ESCAPE'	= 'ESCAPE'		%%DO Name;
	    'EXCLUDE'	= 'EXCLUDE'		%%DO Name;
	    'GCS'		= 'GCS'			%%DO Name;
	    'K' 		= 'K'			%%DO Name;
	    'LES'		= 'LES'			%%DO Name;
	    'LIST'	= 'LIST'		%%DO Name;
	    'M' 		= 'M'			%%DO Name;
	    'MAP'		= 'MAP'			%%DO Name;
	    'NFA'		= 'NFA'			%%DO Name;
	    'NO'		= 'NO'			%%DO Name;
	    'POS'		= 'POS'			%%DO Name;
	    'POSITION'	= 'POSITION'		%%DO Name;
	    'RDS'		= 'RDS'			%%DO Name;
	    'ROWCOL'	= 'ROWCOL'		%%DO Name;
	    'ROW'		= 'ROW'			%%DO Name;
	    'SCR'		= 'SCR'			%%DO Name;
	    'SCREENING'	= 'SCREENING'		%%DO Name;
	    'SET'		= 'SET'			%%DO Name;
	    'TOK'		= 'TOK'			%%DO Name;
	    'TOKEN'	= 'TOKEN'		%%DO Name;
	    'TRACE'	= 'TRACE'		%%DO Name;
	    'VERBOSE'	= 'VERBOSE'		%%DO Name;

	    Class		= '[' ( '\\' [^\n] ! [^\\\n\]] )* ']'	%%DO Name;
	    String	= String	%%DO Name;
	    Identifier	= Identifier	%%DO Name;
	    Number	= Number	%%DO Number;
--	    Float         = Float		%%DO Float;

	    '%%DO'	    = '%%DO'('ES')?;
	    '%%ACTION'	    = '%%ACTION''S'?		%% smToken->action=lexWriteAction(this,actionACTION,2); %%;
	    '%%CODE'	    = '%%CODE''S'?		%% smToken->action=lexWriteAction(this,actionCODE,2); %%;
	    '%%READER'	    = '%%READER''S'?		%% smToken->action=lexWriteAction(this,actionREADER,2); %%;
	    '%%CONTEXT'	    = '%%CONTEXT''S'?		%% smToken->action=lexWriteAction(this,actionCONTEXT,2); %%;
	    '%%DECLARATION'   = '%%DECLARATION''S'? 	%% smToken->action=lexWriteAction(this,actionDECLARATION,2); %%;
	    '%%DEFINITION'    = '%%DEFINITION''S'?;
	    '%%END'	    = '%%END''S'?		%% smToken->action=lexWriteAction(this,actionNONE,2); %%;
	    '%%EXPORT'	    = '%%EXPORT'?		%% smToken->action=lexWriteAction(this,actionEXPORT,2); %%;
	    '%%MAP'	    = '%%MAP''S'?;
	    '%%POSTHOOK'	    = '%%POSTHOOK''S'?		%% smToken->action=lexWriteAction(this,actionPOSTHOOK,2); %%;
	    '%%PREHOOK'	    = '%%PREHOOK''S'?		%% smToken->action=lexWriteAction(this,actionPREHOOK,2); %%;
	    '%%RULE'	    = '%%RULE''S'?;
	    '%%SCANNER'	    = '%%SCANNER''S'?;
	    '%%SCREENING'	    = '%%SCREENING';
	    '%%SET'	    = '%%SET''S'?		%% setRead(lexContext); %%;
	    '%%SKIP'	    = '%%SKIP''S'?;
	    '%%VOCABULARY'    = '%%VOCABULARY''S'?;

	    SKIPHEADER	    = '%%OPTION''S'?
	%% {
	  long fpos, length;
	  tmkSkipCode(STRSKP_SKIP, this, &fpos, &length,  smkEscape);
	}%%;

	    SKIPHEADER	    = '%%IMPORT'? ! '%%SRCP'? ! '%%TOKEN'?
	%% {
	  long fpos, length;
	  tmkSkipCode(NOSTRS_SKIP, this, &fpos, &length,  smkEscape);
	}%%;

	    '%%' 		    = '%%'			%% smToken->action=lexWriteAction(this,actionSEMANTIC,0); %%;

	    Unknown	    = _Unknown;
	    EndOfText	    = _EndOfText;

 %%SKIP

	    comment	    = '%%COMMENT''S'?			%% lexWriteAction(this,actionNONE,2); %%;
	    comment	    = '--'[^\n]*'\n';
	    blank		    = [- \x7F-]+;

%%VOCABULARY vocabulary

	    EndOfText	= 0;
	    Number	= 2;
	    Identifier	= 3;
	    String        = 4;
	    NewLine	= 5;
	    EOT 		= 6;

    %%SCANNER main
	%%RULES

	    Number 	= Number	%%DO Number;
	    String	= String	%%DO Name;
	    Identifier	= Identifier	%%DO Name;

	    EndOfText	= _EndOfText;
	    EOT 		= '$';
	    NewLine       = [\n];

	%%SKIP
	    
	    Unknown	= _Unknown;
	    Blank         = [\t ]+;

%%VOCABULARY set

	    EndOfText	= 0;
	    UnKnown       = 1;
	    Identifier	= 2;
	    Number	= 3;
	    Undefined	= 4;
	    Character	= 5;
	    EOS 		= 6;

    %%SCANNER main
	%%RULES

	    Number        = [0-9A-F][0-9A-F] 		%%DO Name;
	    Undefined	= [.][.];
	    Character	= [^\x00- ] 			%%Do Name;
	    Identifier	= Letter([_\-]?(Letter!Digit))+	%%DO Name;
	    EOS 		= '%%'				%% smkSkip(this,-2); %%;

	    EndOfText	= _EndOfText;
	    UnKnown	= _UnKnown;

	%%SKIP

	    Blank		= [ \t\n];
	    Comment	= '--'[^\n]*[\n];

%%END



