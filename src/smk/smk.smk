%%OPTIONS

    Pack;

%%IMPORT
#include <stdio.h>
#include "common.h"
#include "action.h"
#include "name.h"
#include "set.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"


extern double atof();

extern smkScContext lexContext;

%%CONTEXT

  char *fileName;
  int fd;

%%READER

  return read(smThis->fd,smBuffer,smLength);

%%DECLARATIONS

#ifdef WIN32
#include <io.h>
#endif


/*
 * Skip characters until '`%%' and write them to optTable
 */

static Action lexWriteAction(
     smkScContext smThis,
     ActionType type,
     int skip)
{
  Action action;
  unsigned char *ch;
  int at;
  int state;

  if(type!=actionNONE)
    action=actionPut(type,smThis->smNextPosition,0);
  else
    action=NULL;
  state=0;
  at=2;
  while(smkScSkip(smThis,10000)) {
    ch=smThis->smText+at;
    for(;at<smThis->smLength;at++,ch++)
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
  smkScSkip(smThis,at-smThis->smLength-skip);
  if(type!=actionNONE) action->stop=smThis->smNextPosition-3+skip;
  return action;
}

static Name lexName(
     smkScContext smThis)
{
  unsigned char rem;
  Name name;

  rem=smThis->smText[smThis->smLength];
  smThis->smText[smThis->smLength]=0;
  name=nameSearch(smThis->smText);
  smThis->smText[smThis->smLength]=rem;
  return name;
}

static Name lexMapName(
     smkScContext smThis)
{
  unsigned char *text;
  Name name;

  text=(unsigned char *)smalloc((smThis->smLength+1)*sizeof(char));
  smkScMapCopy(smThis, text, 0, smThis->smLength);
  text[smThis->smLength]=0;
  name=nameSearch(text);
  free(text);
  return name;
}

static int lexNumber(
     smkScContext smThis)
{
  char rem;
  int inumber;

  rem=smThis->smText[smThis->smLength];
  smThis->smText[smThis->smLength]=0;
  inumber=atoi((char *)(smThis->smText));
  smThis->smText[smThis->smLength]=rem;
  return inumber;
}

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
    [\xe0-\xf6]	= [\xC0-\xD6];
    [\xf8-\xfe]	= [\xD8-\xDE];

%%DEFINITIONS

    Letter		= [A-Z\xC0-\xD6\xD8-\xDE];
    Digit		= [0-9];

    String		= ['] ( '\\' [^\n] ! [^\\\n'] )* ['];
    Identifier	= Letter([_]?(Letter!Digit))*;
    Number		= [0-9]+;

-- Define Commonly used actions!

    Number		= %% smToken->inumber=lexNumber(smThis); %%;
    Name		= %% smToken->name=lexName(smThis); %%;
    MapName		= %% smToken->name=lexMapName(smThis); %%;
    StrSkipHeader	=
%%{
  long fpos, length;
  tmkSkipCode(STRSKP_SKIP, smThis, &fpos, &length,  smkEscape);
}%%;
    SkipHeader	=
%%{
  long fpos, length;
  tmkSkipCode(NOSTRS_SKIP, smThis, &fpos, &length,  smkEscape);
}%%;

%%VOCABULARY main

    %%SCANNER main %%RULES

    Class		= '[' ( '\\' [^\n] ! [^\\\n\]] )* ']'	%%DO Name;
    String		= String		%%DO Name;
    Identifier	= Identifier		%%DO MapName;
    Number		= Number		%%DO Number;

    '%%DO'		= '%%DO'('ES')?;
    '%%ACTION'	= '%%ACTION''S'?	%% smToken->action=lexWriteAction(smThis,actionACTION,2); %%;
    '%%READER'	= '%%READER''S'?	%% smToken->action=lexWriteAction(smThis,actionREADER,2); %%;
    '%%CONTEXT'	= '%%CONTEXT''S'?	%% smToken->action=lexWriteAction(smThis,actionCONTEXT,2); %%;
    '%%DECLARATION'	= '%%DECLARATION''S'?   %% smToken->action=lexWriteAction(smThis,actionDECLARATION,2); %%;
    '%%DEFINITION'	= '%%DEFINITION''S'?;
    '%%END'		= '%%END''S'?		%% smToken->action=lexWriteAction(smThis,actionNONE,2); %%;
    '%%EXPORT'	= '%%EXPORT''S'?	%% smToken->action=lexWriteAction(smThis,actionEXPORT,2); %%;
    '%%MAP'		= '%%MAP''S'?;
    '%%POSTHOOK'	= '%%POSTHOOK''S'?	%% smToken->action=lexWriteAction(smThis,actionPOSTHOOK,2); %%;
    '%%PREHOOK'	= '%%PREHOOK''S'?	%% smToken->action=lexWriteAction(smThis,actionPREHOOK,2); %%;
    '%%RULE'	= '%%RULE''S'?;
    '%%SCANNER'	= '%%SCANNER''S'?;
    '%%SCREENING'	= '%%SCREENING';
    '%%SET'		= '%%SET''S'?		%% setRead(lexContext); %%;
    '%%SKIP'	= '%%SKIP''S'?;
    '%%VOCABULARY'	= '%%VOCABULARY''S'?;

    SKIPHEADER	= '%%OPTION''S'?	%%Do StrSkipHeader;
    SKIPHEADER	= '%%IMPORT''S'?
            ! '%%SRCP''S'?
            ! '%%TOKEN''S'?		%%Do SkipHeader;

    '%%'        = '%%'			%% smToken->action=lexWriteAction(smThis,actionSEMANTIC,0); %%;

    Unknown		= _Unknown;
    EndOfText	= _EndOfText;

    %%SKIP

    comment		= '%%COMMENT''S'?	%% lexWriteAction(smThis,actionNONE,2); %%;
    comment		= '--'[^\n]*;
    blank		= [- \x7F-]+;

%%VOCABULARY vocabulary

    EndOfText	= 0;
    Number		= 2;
    Identifier	= 3;
    String		= 4;
    NewLine		= 5;
    EOT         = 6;

    %%SCANNER main %%RULES

    Number		= Number		%%DO Number;
    String		= String		%%DO Name;
    Identifier	= Identifier		%%DO MapName;

    EndOfText	= _EndOfText;
    EOT		= '$';
    NewLine		= [\n];

    %%SKIP

    Unknown		= _Unknown;
    Blank		= [\t ]+;

%%VOCABULARY set

    EndOfText	= 0;
    UnKnown		= 1;
    Identifier	= 2;
    Number		= 3;
    Undefined	= 4;
    Character	= 5;
    EOS		= 6;

    %%SCANNER main %%RULES

    Number		= [0-9A-F][0-9A-F]  %%DO Name;
    Undefined	= [.][.];
    Character	= [^\x00- ]         %%Do Name;
    Identifier	= Letter([_\-]?(Letter!Digit))+	%%DO MapName;
    EOS		= '%%'			%% smkScSkip(smThis,-2); %%;

    EndOfText	= _EndOfText;
    UnKnown		= _UnKnown;

    %%SKIP

    Blank		= [ \t\n\r]		%% return smSkipToken; %%;
    Comment		= '--'[^\n]*;

%%END
