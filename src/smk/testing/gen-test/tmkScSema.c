/*----------------------------------------------------------------------*\

	tmkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

#include "tmkScan.h"

/* %%DECLARATION */

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



/* END %%DECLARATION */

int tmkScReader(smThis,smBuffer,smLength)
     tmkScContext smThis;
     unsigned char *smBuffer;
     unsigned int smLength;
{


  return read(this->fd, smBuffer, smLength);


}    

int tmkScPreHook(smThis,smToken)
     tmkScContext smThis;
     TmkToken *smToken;
{


  smToken->srcp.file = tmkEnv->fileNo;


  return -1;
}

int tmkScAction(smThis,smInternalCode,smToken)
     tmkScContext smThis;
     int smInternalCode;
     TmkToken *smToken;
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case  16:		/* 'ATTRIBUTES'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   5:		/* 'NAME'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   6:		/* 'CODE'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   7:		/* 'SRCP'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   4:		/* 'ROW'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  11:		/* 'COLUMN'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   8:		/* 'FILE'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  14:		/* 'POSITION'*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  17:		/* IDENTIFIER*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  18:		/* NUMBER*/ 
    { smToken->ival = atoi(this->smText); 
}
    break;

  case  19:		/* STRING*/ 
    { smToken->sval = newStr(this, 1); 
}
    break;

  case  13:		/* '%%IMPORT'*/ 
    {
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  20:		/* SKIPHEADER*/ 
    {
	/* Skip a section where ToolMaker strings and semantic actions exist */
	tmkSkipCode(RULES_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  21:		/* SKIPHEADER*/ 
    {
	/* Skip a section where ToolMaker strings exists */
	tmkSkipCode(STRSKP_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  22:		/* SKIPHEADER*/ 
    {
	/* Skip a section where no ToolMaker strings exists */
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case   3:		/* '%%'*/ 
    {
	tmkSkipCode(SEM_SKIP, this, &(smToken->fpos), &(smToken->length), tmkEscape);
        smToken->sval = newStr(this, 2);
      
}
    break;
  }
  return smToken->code;
}


