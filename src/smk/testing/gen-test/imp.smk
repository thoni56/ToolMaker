%%OPTIONS
	NO SCREENING;
	LIBRARY '../..';
%%DECLARATION
  
#include <stdio.h>
#include "impMacro.h"
#include "impList.h"
#define PUSH(scanner) (lexScanner[lexBalance++]=scanner)
#define POP (lexScanner[--lexBalance])
#define TOP (lexScanner[lexBalance])
#define BALANCE (lexBalance>0)

  static int lexBalance=0;
  static int lexScanner[512];
  static int lexColumn=0;
  static int glue=0;

%%POSTHOOK

/*  printf("TOKEN %d LENGTH %d AT %d %d (%d)\n",smCode,this->smLength,this->smLine,this->smColumn,this->smPosition);*/
  smToken->srcp.file = this->fileNo;

%%CONTEXT

  int fd;
  int fileNo;
  int endPos;
%%READER

  return read(this->fd,smBuffer,smLength);

%%MAP

  [a-z] = [A-Z];

%%DEFINITIONS

  char		= [A-Z_];
  letter	= [A-Z];
  digit		= [0-9];
  imp 		= '%%'[ \t\n]*;
  blanks	= ([ \t]*[\n])?;

  impScanner	= %% lexColumn=this->smColumn;this->smScanner=imp_imp_Scanner; %%;
  continue	= %% goto smContinue; %%;
  literal	=
%%{
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}%%;
  blanks	=
%% {
  register int skip;

  skip=1;
  if(this->smColumn>1) while(this->smText[this->smLength-skip]<=' ') skip++;
  if(skip>1) impSkip(this,-skip+1);
} %%;

%%VOCABULARY main
    %%SCANNER main
	%%UNDEFINE
		'(';	')'; 	'NOT';	'AND';	'OR';	'<';	'>';	'<=';	'>=';
		'=';	'#';	'+';	'-';	'*';	'/';	',';	'?R';	'?V';
		'?';	'[';	']';	'{';	'}';	'IMP$SYSTEM';	
	%%SKIP

	    '%%KEEP'	= imp'KEEP'blanks
%% 
  lexColumn=this->smColumn;
  this->smText = this->smText+this->smLength;
  this->smLength = 0;
  PUSH(imp_main_Scanner);
  this->smScanner=imp_keep_Scanner; 
  goto smContinue;
%%;

	    '%%COMMENT'	= imp'COMMENT'	
%% 
  lexColumn=this->smColumn;PUSH(imp_main_Scanner);this->smScanner=imp_comment_Scanner; goto smContinue;
%%;
	    '%%--'	= imp'--'[\n];
	    '%%--'	= imp'--'[^\n]* 
%% 
  if ((this->smColumn == 1) && (this->smText[this->smLength] == '\n'))
    impSkip(this,1);
%%;

	%%RULES 

	    '%%INCLUDE'	= imp'INCLUDE'	%%DO impScanner;
	    '%%EINCLUDE'	= imp'EINCLUDE'	%%DO impScanner;
	    '%%PROCESS'	= imp'PROCESS'	%%DO impScanner;
	    '%%('		= imp'('	%% lexColumn=this->smColumn; PUSH(imp_main_Scanner);this->smScanner=imp_imp_Scanner; %%;
	    '%%BEGIN'	= imp'BEGIN'	%%DO impScanner;
	    '%%ELSE'	= imp'ELSE'blanks %%DO blanks;
	    '%%ELSIF'	= imp'ELSIF'	%%DO impScanner;
	    '%%END'	= imp'END'	%% lexColumn=1;this->smScanner=imp_imp_Scanner; %%;
	    '%%ENDIF'	= imp'ENDIF'blanks %%DO blanks;
	    '%%ENDLOOP'	= imp'ENDLOOP'	%% lexColumn=1;this->smScanner=imp_imp_Scanner; %%;
	    '%%ESET'	= imp'ESET'	%%DO impScanner;
	    '%%IF'	= imp'IF'	%%DO impScanner;
	    '%%LOOP'	= imp'LOOP'	%%DO impScanner;
	    '%%MESSAGE'	= imp'MESSAGE'  %%DO impScanner;
	    '%%SET'	= imp'SET'	%%DO impScanner;
	    
	    TEXT		= [^%]+ 	
%%{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}%%;
	    TEXT		= imp char+
%%{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}%%;
	    TEXT		= '%'
%%{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}%%;
	    TEXT		= _Unknown	%%DO continue;

	    EndOfText	= _EndOfText;


    %%SCANNER imp
	%%RULES

	    '(' 		= '(' 		%% if(BALANCE) PUSH(imp_imp_Scanner); else PUSH(imp_main_Scanner); %%;
	    ')' 		= ')'blanks
%%
  this->smScanner=POP; 
  if(this->smScanner==imp_string_Scanner || lexColumn>1) 
    impSkip(this,-(this->smLength-1)); 
  if(this->smText[this->smLength-1]==impEsc) impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
%%;

	    'NOT'		= 'NOT';
	    'AND'		= 'AND';
	    'OR'		= 'OR';
	    '<' 		= '<';
	    '>' 		= '>';
	    '<=' 		= '<=';
	    '>=' 		= '>=';
	    '=' 		= '=';
	    '#' 		= '#';
	    '+' 		= '+';
	    '-' 		= '-';
	    '*' 		= '*';
	    '/' 		= '/';
	    ',' 		= ',';
	    '?R' 		= '?R';
	    '?V' 		= '?V';
	    '?' 		= '?';
	    '[' 		= '[';
	    ']' 		= ']';
	    '{' 		= '{';
	    '}' 		= '}';
	    'IMP$SYSTEM'	= 'IMP$SYSTEM';
	    '%%('		= imp'('		%% PUSH(imp_imp_Scanner); %%;

	    INTEGER	= digit+				%%DO literal;
	    UNQUOT_STRING	= (letter!digit![_])+			%%DO literal;
	    QUOT_STRING	= ["][^%"]*["]
%%{
  smToken->text=(char *)malloc(this->smLength-1);
  impCopy(this,smToken->text,1,this->smLength-1);
  smToken->text[this->smLength-2]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-3;
}%%;
	    QUOT_STRING	= ["][^%"]*["]/["]
%%{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
}%%;
	    QUOT_STRING	= ["][^%"]*/[%]
%%{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
  this->smScanner=imp_string_Scanner;
}%%;

	    Unknown	= _Unknown;
	    EndOfText	= _EndOfText;

 %%SKIP

	    blank		= [ \t\n]				%% glue=0; %%;
	    comment	= imp'--'[^\n]*[\n];

    %%SCANNER string
	%%RULES

	    '%%('		= '%%('		%%  PUSH(imp_string_Scanner);this->smScanner=imp_imp_Scanner;%%;
	    QUOT_STRING   = '%%'		%%DO continue;
	    QUOT_STRING   = '%'		%%DO continue;
	    QUOT_STRING	= [^%"]*/[%]
%%{
    smToken->text=(char *)malloc(this->smLength+1);
    impCopy(this,smToken->text,0,this->smLength);
    smToken->text[this->smLength]=0;
    smToken->begin=this->smPosition;
    smToken->end=this->smLength+this->smPosition-1;
}%%;
	    QUOT_STRING	= [^%"]*["]
%%{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,0,this->smLength-1);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
  this->smScanner=imp_imp_Scanner;
}%%;
	    QUOT_STRING	= [^%"]*["]/["]
%%{
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
  this->smScanner=imp_imp_Scanner;
}%%;
	    QUOT_STRING	= _EndOfText	%% this->smScanner=imp_main_Scanner;printf("UNMATCHED STRING\n"); %%;
	    QUOT_STRING	= _Unknown	%%DO continue;
    %%SCANNER keep
	 %%RULE

	    '%%KEEP'	= imp'ENDKEEP'blanks 	
%%{
  if(POP==imp_keep_Scanner) {
    if (this->smText[this->smLength] == '%')
      this->endPos = this->smLength;
    goto smContinue; 
  }
  this->smScanner=TOP;
  smToken->text=(char *)malloc(this->endPos+1);
  impCopy(this,smToken->text,0,this->endPos);
  smToken->text[this->endPos]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->endPos+this->smPosition-1;
}%%;
	    '%%KEEP'	= _EndOfText		
%% 
  if (POP==imp_keep_Scanner) {
    TmSrcp srcp;
    srcp.file = this->fileNo;
    srcp.col = this->smNextColumn;
    srcp.line = this->smNextLine;
    impLog(&srcp, 101, sevERR, `"`'`%`%ENDKEEP``'");
    this->smScanner=TOP;
    smToken->text=(char *)malloc(this->smLength+1);
    impCopy(this,smToken->text,0,this->smLength);
    smToken->text[this->smLength]=0;
    smToken->begin=this->smPosition;
    smToken->end=this->smLength+this->smPosition-1;
  } else  {
    TmSrcp srcp;
    srcp.file = this->fileNo;
    srcp.col = this->smNextColumn;
    srcp.line = this->smNextLine;
    impLog(&srcp, 101, sevERR, `"`'`%`%ENDKEEP`'`");
    this->smScanner = imp_main_Scanner;
    smToken->text=(char *)malloc(this->smLength+1);
    impCopy(this,smToken->text,0,this->smLength);
    smToken->text[this->smLength]=0;
    smToken->begin=this->smPosition;
    smToken->end=this->smLength+this->smPosition-1;
  }
%%;
	    '%%KEEP'	= imp'KEEP'		%% PUSH(imp_keep_Scanner); goto smContinue;%%;
	    '%%KEEP'	= [^%]+ 		
%% 
		if(this->smText[this->smLength-1]==impEsc) 
		  impSkip(this,1); 
		this->endPos = this->smLength;
		goto smContinue;
%%;
	    '%%KEEP'	= [%]+			%%DO continue;
	    '%%KEEP'	= _Unknown		%%DO continue;


    %%SCANNER comment
	 %%SKIP
	    '%%COMMENT'	= imp'ENDCOMMENT'blanks	
%% 
  if(POP==imp_comment_Scanner) goto smContinue;
  this->smScanner=TOP; 
%% ;
	    '%%COMMENT'	= _EndOfText
%% 
  this->smScanner=imp_main_Scanner;
  printf("UNMATCHED COMMENT\n"); 
%%;
	    '%%COMMENT'	= imp'COMMENT'
%%
  PUSH(imp_comment_Scanner); 
  goto smContinue;
%%;
	    '%%COMMENT' 	= [^%]+
%% 
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1);
  goto smContinue;
%%;
	    '%%COMMENT' 	= [%]+ 			%%DO continue;
	    '%%COMMENT'	= _Unknown		%%DO continue;
