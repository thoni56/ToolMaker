%%OPTIONS

--        Trace;
	No Screening;

%%DECLARATION
  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include "impMacro.h"
#include "impList.h"

/* Scanner stack operations. */
#define PUSH(scanner) (lexScanner[lexBalance++] = scanner)
#define POP (lexScanner[--lexBalance])
#define TOP (lexScanner[lexBalance])

/* Test of balanced parenthesis. */
#define BALANCE (lexBalance > 0)

static int lexBalance = 0;
static int lexScanner[512];
static int lexColumn = 0;

%%POSTHOOK

  smToken->srcp.file = smThis->fileNo;

%%CONTEXT

  int fd;
  int fileNo;
  int endPos;

%%READER

  return read(smThis->fd, smBuffer, smLength);

%%MAP

  [a-z] = [A-Z];

%%DEFINITIONS

  char 		= [A-Z_];
  letter 	= [A-Z];
  digit		= [0-9];
  imp 		= '%%'[ \t\n]*;
  blanks 	= ([ \t]*[\n])?;

  impScanner = 
  %% 
    lexColumn = smThis->smColumn;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  %%
  ;
  
  literal = 
  %%
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
  %%
  ;
  
  blanks = 
  %%
    register int skip;

    skip = 1;
    if (smThis->smColumn > 1) 
      while (smThis->smText[smThis->smLength - skip] <= ' ') 
        skip++;
    if (skip > 1) impScSkip(smThis, -skip + 1);
  %%
  ;

%%VOCABULARY main 

%%SCANNER main 

%%UNDEFINE 

  -- Undefine tokens that are defined in the other scanners bot not
  -- in this one.

  '(';
  ')'; 
  'NOT'; 
  'AND'; 
  'OR';
  'BITAND'; 
  'BITOR';
  'MOD';
  '<'; 
  '>'; 
  '<='; 
  '>='; 
  '=';
  '#'; 
  '+';
  '-';
  '*';
  '/';
  '?R';
  '?V';
  '?';
  '[';
  ']';
  '{';
  '}';
  'IMP$SYSTEM';
  'IMP$STRLEN';
  'IMP$STRSEARCH';
  ',';
  '%%KEEP';

%%SKIP

  Keep	= imp'KEEP'blanks
  %% 
    lexColumn = smThis->smColumn;
    smThis->smText = smThis->smText + smThis->smLength;
    smThis->smLength = 0;
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_KEEP_Scanner; 
    return smContinueToken;
  %%
  ;
  
  Comment = imp'COMMENT'	
  %% 
    lexColumn = smThis->smColumn;
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_COMMENT_Scanner; 
    return smContinueToken;
  %%
  ;

  SingleLineComment = imp'--'[\n];

  SingleLineComment = imp'--'[^\n]* 
  %% 
    if ((smThis->smColumn == 1) && (smThis->smText[smThis->smLength] == '\n'))
      impScSkip(smThis, 1);
  %%
  ;

%%RULES 

  '%%INCLUDE' 	= imp'INCLUDE'		%%DO impScanner;
  '%%EINCLUDE' 	= imp'EINCLUDE'		%%DO impScanner;
  '%%PROCESS' 	= imp'PROCESS'		%%DO impScanner;

  '%%(' = imp'('	
  %% 
    lexColumn = smThis->smColumn; 
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  %%
  ;

  '%%BEGIN' 	= imp'BEGIN'		%%DO impScanner;
  '%%ELSE' 	= imp'ELSE'blanks	%%DO blanks;
  '%%ELSIF' 	= imp'ELSIF'		%%DO impScanner;

  '%%END' = imp'END'	
  %% 
    lexColumn = 1;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  %%
  ;

  '%%ENDIF'	= imp'ENDIF'blanks 	%%DO blanks;

  '%%ENDLOOP' = imp'ENDLOOP'	
  %% 
    lexColumn = 1;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  %%
  ;

  '%%ESET'	= imp'ESET'	%%DO impScanner;
  '%%IF'	= imp'IF'	%%DO impScanner;
  '%%LOOP'	= imp'LOOP'	%%DO impScanner;
  '%%MESSAGE'	= imp'MESSAGE'  %%DO impScanner;
  '%%EXIT'	= imp'EXIT'     %%DO impScanner;
  '%%SET'	= imp'SET'	%%DO impScanner;
  
  TEXT = [^%]+ 	
  %%
    if (smThis->smText[smThis->smLength - 1] == impEsc) 
      impScSkip(smThis, 1); 
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
  %%
  ;

  TEXT = imp char+
  %%
    if (smThis->smText[smThis->smLength - 1] == impEsc) 
      impScSkip(smThis, 1); 
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
  %%
  ;

  TEXT = '%'
  %%
    if (smThis->smText[smThis->smLength - 1] == impEsc) 
      impScSkip(smThis, 1); 
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
  %%
  ;

  TEXT = _Unknown
  %%
    return smContinueToken;
  %%
  ;

  EndOfText = _EndOfText;


%%SCANNER imp 

%%RULES
  
  '(' = '('
  %%
    if (BALANCE) PUSH(imp_MAIN_IMP_Scanner); 
    else PUSH(imp_MAIN_MAIN_Scanner); 
  %%
  ;

  ')' = ')'blanks
  %%
    smThis->smScanner = POP; 
    if (smThis->smScanner == imp_MAIN_STRING_Scanner || lexColumn > 1) 
      impScSkip(smThis, -(smThis->smLength - 1)); 
    if (smThis->smText[smThis->smLength - 1] == impEsc) impScSkip(smThis, 1); 
    smToken->text = (char *)malloc(smThis->smLength + 1);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 1;
  %%
  ;

  'NOT'		= 'NOT';
  'AND'		= 'AND';
  'OR'		= 'OR';
--'XOR'		= 'XOR';
  '<' 		= '<';
  '>' 		= '>';
  '<=' 		= '<=';
  '>=' 		= '>=';
  '=' 		= '=';
  '#' 		= '#';
  '+' 		= '+';
  '-' 		= '-';
  'BITAND'      = 'BITAND';
  'BITOR'       = 'BITOR';
  '*' 		= '*';
  '/' 		= '/';
  'MOD'		= 'MOD';
--'REM'		= 'REM';
  ',' 		= ',';
  '?R' 		= '?R';
  '?V' 		= '?V';
  '?' 		= '?';
  '[' 		= '[';
  ']' 		= ']';
  '{' 		= '{';
  '}' 		= '}';
  'IMP$SYSTEM'	= 'IMP$SYSTEM';
  'IMP$STRLEN'  = 'IMP$STRLEN';
  'IMP$STRSEARCH' = 'IMP$STRSEARCH';

  '%%('	= imp'('		
  %% 
    PUSH(imp_MAIN_IMP_Scanner); 
  %%
  ;

  INTEGER	= digit+				%%DO literal;
--FLOAT		= digit+[.]digit+([E][+\-]digit+)?	%%DO literal;
--FLOAT		= digit+([.]digit+)?[E][+\-]digit+	%%DO literal;
  UNQUOT_STRING	= (letter!digit![_])+			%%DO literal;

  QUOT_STRING = ["][^%"]*["]
  %%
    smToken->text = (char *)malloc(smThis->smLength - 1);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength - 1);
    smToken->text[smThis->smLength - 2] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 3;
  %%
  ;
  
  QUOT_STRING = ["][^%"]*["]/["]
  %%
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
  %%
  ;

  QUOT_STRING = ["][^%"]*/[%]
  %%
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
    smThis->smScanner = imp_MAIN_STRING_Scanner;
  %%
  ;

  Unknown = _Unknown;
  EndOfText = _EndOfText;

 %%SKIP

  Blank	= [ \t\n];
 
  Comment = imp'--'[^\n]*[\n];


%%SCANNER string 

%%RULES

  '%%('	= '%%('
  %%
    PUSH(imp_MAIN_STRING_Scanner);
    smThis->smScanner = imp_MAIN_IMP_Scanner;
  %%
  ;

  QUOT_STRING = '%%'
  %%
    return smContinueToken;
  %%
  ;

  QUOT_STRING = '%'
  %%
    return smContinueToken;
  %%
  ;

  QUOT_STRING = [^%"]*/[%]
  %%
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
  %%
  ;

  QUOT_STRING = [^%"]*["]
  %%
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength - 1);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
    smThis->smScanner = imp_MAIN_IMP_Scanner;
  %%
  ;

  QUOT_STRING = [^%"]*["]/["]
  %%
    smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
    if (smThis->smBufferOverflow == 0) {
      impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
      smToken->text[smThis->smLength] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smLength + smThis->smPosition - 1;
    } else {
      off_t old_offs;
      old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
      lseek(smThis->fd, smThis->smPosition, SEEK_SET);
      read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
      lseek(smThis->fd, old_offs, SEEK_SET);
      smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
      smToken->begin = smThis->smPosition;
      smToken->end = smThis->smNextPosition - 1;
    }
    smThis->smScanner = imp_MAIN_IMP_Scanner;
  %%
  ;

  QUOT_STRING = _EndOfText
  %%
    smThis->smScanner = imp_MAIN_MAIN_Scanner;
    printf("UNMATCHED STRING\n"); 
  %%
  ;

  QUOT_STRING = _Unknown
  %%
    return smContinueToken;
  %%
  ;

%%SCANNER keep 

%%RULES

  '%%KEEP' = imp'ENDKEEP'blanks
  %%
    if (POP == imp_MAIN_KEEP_Scanner) {
      if (smThis->smText[smThis->smLength] == '%')
        smThis->endPos = smThis->smLength;
      return smContinueToken; 
    }
    smThis->smScanner = TOP;
    smToken->text = (char *)malloc(smThis->endPos + 1);
    impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->endPos);
    smToken->text[smThis->endPos] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->endPos + smThis->smPosition - 1;
  %%
  ;

  '%%KEEP' = _EndOfText		
  %% 
    if (POP == imp_MAIN_KEEP_Scanner) {
      TmSrcp srcp;
      srcp.file = smThis->fileNo;
      srcp.col = smThis->smNextColumn;
      srcp.line = smThis->smNextLine;
      impLog(&srcp, 101, sevERR, `"`'`%`%ENDKEEP``'");
      smThis->smScanner = TOP;
      smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
      if (smThis->smBufferOverflow == 0) {
        impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
        smToken->text[smThis->smLength] = 0;
        smToken->begin = smThis->smPosition;
        smToken->end = smThis->smLength + smThis->smPosition - 1;
      } else {
        off_t old_offs;
        old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
        lseek(smThis->fd, smThis->smPosition, SEEK_SET);
        read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
        lseek(smThis->fd, old_offs, SEEK_SET);
        smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
        smToken->begin = smThis->smPosition;
        smToken->end = smThis->smNextPosition - 1;
      }
    } else {
      TmSrcp srcp;
      srcp.file = smThis->fileNo;
      srcp.col = smThis->smNextColumn;
      srcp.line = smThis->smNextLine;
      impLog(&srcp, 101, sevERR, `"`'`%`%ENDKEEP`'`");
      smThis->smScanner = imp_MAIN_MAIN_Scanner;
      smToken->text = (char *)malloc(smThis->smLength + 1 + smThis->smBufferOverflow);
      if (smThis->smBufferOverflow == 0) {
        impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength);
        smToken->text[smThis->smLength] = 0;
        smToken->begin = smThis->smPosition;
        smToken->end = smThis->smLength + smThis->smPosition - 1;
      } else {
        off_t old_offs;
        old_offs = lseek(smThis->fd, 0L, SEEK_CUR);
        lseek(smThis->fd, smThis->smPosition, SEEK_SET);
        read(smThis->fd, smToken->text, smThis->smLength + smThis->smBufferOverflow);
        lseek(smThis->fd, old_offs, SEEK_SET);
        smToken->text[smThis->smLength + smThis->smBufferOverflow] = 0;
        smToken->begin = smThis->smPosition;
        smToken->end = smThis->smNextPosition - 1;
      }
  }
  %%
  ;

  '%%KEEP' = imp'KEEP'
  %% 
    PUSH(imp_MAIN_KEEP_Scanner); 
    return smContinueToken;
  %%
  ;

  '%%KEEP' = [^%]+ 		
  %% 
    if(smThis->smText[smThis->smLength-1] == impEsc) 
      impScSkip(smThis, 1); 
    smThis->endPos = smThis->smLength;
    return smContinueToken;
  %%
  ;

  '%%KEEP' = [%]+
  %%
    return smContinueToken;
  %%
  ;

  '%%KEEP' = _Unknown
  %%
    return smContinueToken;
  %%
  ;


%%SCANNER comment 

%%SKIP

  Comment = imp'ENDCOMMENT'blanks	
  %% 
    if (POP == imp_MAIN_COMMENT_Scanner) return smContinueToken;
    smThis->smScanner = TOP; 
  %%
  ;

  Comment = _EndOfText
  %% 
    smThis->smScanner = imp_MAIN_MAIN_Scanner;
    printf("UNMATCHED COMMENT\n"); 
  %%
  ;
  
  Comment = imp'COMMENT'
  %%
    PUSH(imp_MAIN_COMMENT_Scanner); 
    return smContinueToken;
  %%
  ;

  Comment = [^%]+
  %% 
    if (smThis->smText[smThis->smLength - 1] == impEsc) 
      impScSkip(smThis, 1);
    return smContinueToken;
  %%
  ;

  Comment = [%]+
  %%
    return smContinueToken;
  %%
  ;

  Comment = _Unknown
  %%
    return smContinueToken;
  %%
  ;

