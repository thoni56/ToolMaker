

/*----------------------------------------------------------------------*\

	impScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/


#include "impScan.h"



/* %%DECLARATION */

  
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



/* END %%DECLARATION */



int impScReader(
     impScContext smThis,
     unsigned char *smBuffer,
     unsigned int smLength)

{



  return read(smThis->fd, smBuffer, smLength);




}    





int impScAction(
     impScContext smThis,
     int smInternalCode,
     TmToken *smToken)

{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };


  switch(smInternalCode) {
  case   1:		/* '%%IF'*/ 
  case   2:		/* '%%SET'*/ 
  case   4:		/* '%%ESET'*/ 
  case   6:		/* '%%LOOP'*/ 
  case   7:		/* '%%EXIT'*/ 
  case   9:		/* '%%ELSIF'*/ 
  case  10:		/* '%%BEGIN'*/ 
  case  12:		/* '%%MESSAGE'*/ 
  case  13:		/* '%%INCLUDE'*/ 
  case  14:		/* '%%PROCESS'*/ 
  case  15:		/* '%%EINCLUDE'*/ 
    { 
    lexColumn = smThis->smColumn;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  
}
    break;

  case  55:		/* INTEGER*/ 
  case  56:		/* UNQUOT_STRING*/ 
    {
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
    break;

  case   5:		/* '%%ELSE'*/ 
  case   8:		/* '%%ENDIF'*/ 
    {
    register int skip;

    skip = 1;
    if (smThis->smColumn > 1) 
      while (smThis->smText[smThis->smLength - skip] <= ' ') 
        skip++;
    if (skip > 1) impScSkip(smThis, -skip + 1);
  
}
    break;

  case  16:		/* KEEP*/ 
    { 
    lexColumn = smThis->smColumn;
    smThis->smText = smThis->smText + smThis->smLength;
    smThis->smLength = 0;
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_KEEP_Scanner; 
    return smContinueToken;
  
}
    break;

  case  17:		/* COMMENT*/ 
    { 
    lexColumn = smThis->smColumn;
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_COMMENT_Scanner; 
    return smContinueToken;
  
}
    break;

  case  19:		/* SINGLELINECOMMENT*/ 
    { 
    if ((smThis->smColumn == 1) && (smThis->smText[smThis->smLength] == '\n'))
      impScSkip(smThis, 1);
  
}
    break;

  case   0:		/* '%%('*/ 
    { 
    lexColumn = smThis->smColumn; 
    PUSH(imp_MAIN_MAIN_Scanner);
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  
}
    break;

  case   3:		/* '%%END'*/ 
    { 
    lexColumn = 1;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  
}
    break;

  case  11:		/* '%%ENDLOOP'*/ 
    { 
    lexColumn = 1;
    smThis->smScanner = imp_MAIN_IMP_Scanner; 
  
}
    break;

  case  20:		/* TEXT*/ 
    {
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
  
}
    break;

  case  21:		/* TEXT*/ 
    {
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
  
}
    break;

  case  22:		/* TEXT*/ 
    {
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
  
}
    break;

  case  23:		/* TEXT*/ 
    {
    return smContinueToken;
  
}
    break;

  case  25:		/* '('*/ 
    {
    if (BALANCE) PUSH(imp_MAIN_IMP_Scanner); 
    else PUSH(imp_MAIN_MAIN_Scanner); 
  
}
    break;

  case  26:		/* ')'*/ 
    {
    smThis->smScanner = POP; 
    if (smThis->smScanner == imp_MAIN_STRING_Scanner || lexColumn > 1) 
      impScSkip(smThis, -(smThis->smLength - 1)); 
    if (smThis->smText[smThis->smLength - 1] == impEsc) impScSkip(smThis, 1); 
    smToken->text = (char *)malloc(smThis->smLength + 1);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 1;
  
}
    break;

  case  54:		/* '%%('*/ 
    { 
    PUSH(imp_MAIN_IMP_Scanner); 
  
}
    break;

  case  57:		/* QUOT_STRING*/ 
    {
    smToken->text = (char *)malloc(smThis->smLength - 1);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength - 1);
    smToken->text[smThis->smLength - 2] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 3;
  
}
    break;

  case  58:		/* QUOT_STRING*/ 
    {
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
  
}
    break;

  case  59:		/* QUOT_STRING*/ 
    {
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 1, smThis->smLength);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
    smThis->smScanner = imp_MAIN_STRING_Scanner;
  
}
    break;

  case  64:		/* '%%('*/ 
    {
    PUSH(imp_MAIN_STRING_Scanner);
    smThis->smScanner = imp_MAIN_IMP_Scanner;
  
}
    break;

  case  65:		/* QUOT_STRING*/ 
    {
    return smContinueToken;
  
}
    break;

  case  66:		/* QUOT_STRING*/ 
    {
    return smContinueToken;
  
}
    break;

  case  67:		/* QUOT_STRING*/ 
    {
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
    break;

  case  68:		/* QUOT_STRING*/ 
    {
    smToken->text = (char *)malloc(smThis->smLength);
    impScCopy(smThis, (unsigned char *)smToken->text, 0, smThis->smLength - 1);
    smToken->text[smThis->smLength - 1] = 0;
    smToken->begin = smThis->smPosition;
    smToken->end = smThis->smLength + smThis->smPosition - 2;
    smThis->smScanner = imp_MAIN_IMP_Scanner;
  
}
    break;

  case  69:		/* QUOT_STRING*/ 
    {
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
  
}
    break;

  case  70:		/* QUOT_STRING*/ 
    {
    smThis->smScanner = imp_MAIN_MAIN_Scanner;
    printf("UNMATCHED STRING\n"); 
  
}
    break;

  case  71:		/* QUOT_STRING*/ 
    {
    return smContinueToken;
  
}
    break;

  case  72:		/* '%%KEEP'*/ 
    {
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
  
}
    break;

  case  73:		/* '%%KEEP'*/ 
    { 
    if (POP == imp_MAIN_KEEP_Scanner) {
      TmSrcp srcp;
      srcp.file = smThis->fileNo;
      srcp.col = smThis->smNextColumn;
      srcp.line = smThis->smNextLine;
      impLog(&srcp, 101, sevERR, "'%%ENDKEEP'");
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
      impLog(&srcp, 101, sevERR, "'%%ENDKEEP'");
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
  
}
    break;

  case  74:		/* '%%KEEP'*/ 
    { 
    PUSH(imp_MAIN_KEEP_Scanner); 
    return smContinueToken;
  
}
    break;

  case  75:		/* '%%KEEP'*/ 
    { 
    if(smThis->smText[smThis->smLength-1] == impEsc) 
      impScSkip(smThis, 1); 
    smThis->endPos = smThis->smLength;
    return smContinueToken;
  
}
    break;

  case  76:		/* '%%KEEP'*/ 
    {
    return smContinueToken;
  
}
    break;

  case  77:		/* '%%KEEP'*/ 
    {
    return smContinueToken;
  
}
    break;

  case  78:		/* COMMENT*/ 
    { 
    if (POP == imp_MAIN_COMMENT_Scanner) return smContinueToken;
    smThis->smScanner = TOP; 
  
}
    break;

  case  79:		/* COMMENT*/ 
    { 
    smThis->smScanner = imp_MAIN_MAIN_Scanner;
    printf("UNMATCHED COMMENT\n"); 
  
}
    break;

  case  80:		/* COMMENT*/ 
    {
    PUSH(imp_MAIN_COMMENT_Scanner); 
    return smContinueToken;
  
}
    break;

  case  81:		/* COMMENT*/ 
    { 
    if (smThis->smText[smThis->smLength - 1] == impEsc) 
      impScSkip(smThis, 1);
    return smContinueToken;
  
}
    break;

  case  82:		/* COMMENT*/ 
    {
    return smContinueToken;
  
}
    break;

  case  83:		/* COMMENT*/ 
    {
    return smContinueToken;
  
}
    break;
  }


  return smToken->code;
}




int impScPostHook(
     impScContext smThis,
     TmToken *smToken)

{
  enum {
    smSkipToken		= -1
  };



  smToken->srcp.file = smThis->fileNo;




  return smToken->code;
}



