/*----------------------------------------------------------------------*\

	impScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

#include "impScan.h"

/* %%DECLARATION */

  
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


/* END %%DECLARATION */

int impScReader(smThis,smBuffer,smLength)
     impScContext smThis;
     unsigned char *smBuffer;
     unsigned int smLength;
{


  return read(this->fd,smBuffer,smLength);


}    


int impScAction(smThis,smInternalCode,smToken)
     impScContext smThis;
     int smInternalCode;
     TmToken *smToken;
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case   1:		/* '%%IF'*/ 
  case   2:		/* '%%SET'*/ 
  case   5:		/* '%%ESET'*/ 
  case   7:		/* '%%LOOP'*/ 
  case   9:		/* '%%ELSIF'*/ 
  case  10:		/* '%%BEGIN'*/ 
  case  12:		/* '%%MESSAGE'*/ 
  case  13:		/* '%%INCLUDE'*/ 
  case  14:		/* '%%PROCESS'*/ 
  case  15:		/* '%%EINCLUDE'*/ 
    { lexColumn=this->smColumn;this->smScanner=imp_imp_Scanner; 
}
    break;

  case  22:		/* TEXT*/ 
  case  59:		/* QUOT_STRING*/ 
  case  60:		/* QUOT_STRING*/ 
  case  65:		/* QUOT_STRING*/ 
  case  70:		/* '%%KEEP'*/ 
  case  71:		/* '%%KEEP'*/ 
  case  76:		/* '%%COMMENT'*/ 
  case  77:		/* '%%COMMENT'*/ 
    { goto smContinue; 
}
    break;

  case  49:		/* INTEGER*/ 
  case  50:		/* UNQUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}
}
    break;

  case   6:		/* '%%ELSE'*/ 
  case   8:		/* '%%ENDIF'*/ 
    { {
  register int skip;

  skip=1;
  if(this->smColumn>1) while(this->smText[this->smLength-skip]<=' ') skip++;
  if(skip>1) impSkip(this,-skip+1);
} 
}
    break;

  case   4:		/* '%%KEEP'*/ 
    { 
  lexColumn=this->smColumn;
  this->smText = this->smText+this->smLength;
  this->smLength = 0;
  PUSH(imp_main_Scanner);
  this->smScanner=imp_keep_Scanner; 
  goto smContinue;

}
    break;

  case  16:		/* '%%COMMENT'*/ 
    { 
  lexColumn=this->smColumn;PUSH(imp_main_Scanner);this->smScanner=imp_comment_Scanner; goto smContinue;

}
    break;

  case  18:		/* '%%--'*/ 
    { 
  if ((this->smColumn == 1) && (this->smText[this->smLength] == '\n'))
    impSkip(this,1);

}
    break;

  case   0:		/* '%%('*/ 
    { lexColumn=this->smColumn; PUSH(imp_main_Scanner);this->smScanner=imp_imp_Scanner; 
}
    break;

  case   3:		/* '%%END'*/ 
    { lexColumn=1;this->smScanner=imp_imp_Scanner; 
}
    break;

  case  11:		/* '%%ENDLOOP'*/ 
    { lexColumn=1;this->smScanner=imp_imp_Scanner; 
}
    break;

  case  19:		/* TEXT*/ 
    {{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}
}
    break;

  case  20:		/* TEXT*/ 
    {{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}
}
    break;

  case  21:		/* TEXT*/ 
    {{
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
}
}
    break;

  case  24:		/* '('*/ 
    { if(BALANCE) PUSH(imp_imp_Scanner); else PUSH(imp_main_Scanner); 
}
    break;

  case  25:		/* ')'*/ 
    {
  this->smScanner=POP; 
  if(this->smScanner==imp_string_Scanner || lexColumn>1) 
    impSkip(this,-(this->smLength-1)); 
  if(this->smText[this->smLength-1]==impEsc) impSkip(this,1); 
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;

}
    break;

  case  48:		/* '%%('*/ 
    { PUSH(imp_imp_Scanner); 
}
    break;

  case  51:		/* QUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength-1);
  impCopy(this,smToken->text,1,this->smLength-1);
  smToken->text[this->smLength-2]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-3;
}
}
    break;

  case  52:		/* QUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
}
}
    break;

  case  53:		/* QUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,1,this->smLength);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
  this->smScanner=imp_string_Scanner;
}
}
    break;

  case  56:		/* BLANK*/ 
    { glue=0; 
}
    break;

  case  58:		/* '%%('*/ 
    {  PUSH(imp_string_Scanner);this->smScanner=imp_imp_Scanner;
}
    break;

  case  61:		/* QUOT_STRING*/ 
    {{
    smToken->text=(char *)malloc(this->smLength+1);
    impCopy(this,smToken->text,0,this->smLength);
    smToken->text[this->smLength]=0;
    smToken->begin=this->smPosition;
    smToken->end=this->smLength+this->smPosition-1;
}
}
    break;

  case  62:		/* QUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength);
  impCopy(this,smToken->text,0,this->smLength-1);
  smToken->text[this->smLength-1]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-2;
  this->smScanner=imp_imp_Scanner;
}
}
    break;

  case  63:		/* QUOT_STRING*/ 
    {{
  smToken->text=(char *)malloc(this->smLength+1);
  impCopy(this,smToken->text,0,this->smLength);
  smToken->text[this->smLength]=0;
  smToken->begin=this->smPosition;
  smToken->end=this->smLength+this->smPosition-1;
  this->smScanner=imp_imp_Scanner;
}
}
    break;

  case  64:		/* QUOT_STRING*/ 
    { this->smScanner=imp_main_Scanner;printf("UNMATCHED STRING\n"); 
}
    break;

  case  66:		/* '%%KEEP'*/ 
    {{
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
}
}
    break;

  case  67:		/* '%%KEEP'*/ 
    { 
  if (POP==imp_keep_Scanner) {
    TmSrcp srcp;
    srcp.file = this->fileNo;
    srcp.col = this->smNextColumn;
    srcp.line = this->smNextLine;
    impLog(&srcp, 101, sevERR, "'%%ENDKEEP'");
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
    impLog(&srcp, 101, sevERR, "'%%ENDKEEP'");
    this->smScanner = imp_main_Scanner;
    smToken->text=(char *)malloc(this->smLength+1);
    impCopy(this,smToken->text,0,this->smLength);
    smToken->text[this->smLength]=0;
    smToken->begin=this->smPosition;
    smToken->end=this->smLength+this->smPosition-1;
  }

}
    break;

  case  68:		/* '%%KEEP'*/ 
    { PUSH(imp_keep_Scanner); goto smContinue;
}
    break;

  case  69:		/* '%%KEEP'*/ 
    { 
		if(this->smText[this->smLength-1]==impEsc) 
		  impSkip(this,1); 
		this->endPos = this->smLength;
		goto smContinue;

}
    break;

  case  72:		/* '%%COMMENT'*/ 
    { 
  if(POP==imp_comment_Scanner) goto smContinue;
  this->smScanner=TOP; 

}
    break;

  case  73:		/* '%%COMMENT'*/ 
    { 
  this->smScanner=imp_main_Scanner;
  printf("UNMATCHED COMMENT\n"); 

}
    break;

  case  74:		/* '%%COMMENT'*/ 
    {
  PUSH(imp_comment_Scanner); 
  goto smContinue;

}
    break;

  case  75:		/* '%%COMMENT'*/ 
    { 
  if (this->smText[this->smLength-1] == impEsc) 
    impSkip(this,1);
  goto smContinue;

}
    break;
  }
  return smToken->code;
}

int impScPostHook(smThis,smToken)
     impScContext smThis;
     TmToken *smToken;
{
  enum {
    smSkipToken		= -1
  };


/*  printf("TOKEN %d LENGTH %d AT %d %d (%d)\n",smCode,this->smLength,this->smLine,this->smColumn,this->smPosition);*/
  smToken->srcp.file = this->fileNo;


  return smToken->code;
}

