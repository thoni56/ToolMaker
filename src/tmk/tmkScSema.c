/*----------------------------------------------------------------------*\

	tmkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include "tmk.h"
#include "tmk_i.h"

/* END %%IMPORT */
#include "tmkScan.h"

/* %%DECLARATION */


#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

tmkScContext tmkCext;

static char *newStr(smThis, skip)
  register tmkScContext smThis;
  register int skip;
{
  char *temp = (char *) malloc(smThis->smLength+1-2*skip);

  tmkScCopy(smThis,(unsigned char *)temp, skip, smThis->smLength-skip);
  temp[smThis->smLength-2*skip] = 0;
  return temp;
}



/* END %%DECLARATION */

int tmkScReader(
     tmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smLength)
{


  return read(smThis->fd, smBuffer, smLength);


}    

int tmkScPreHook(
     tmkScContext smThis,
     TmkToken *smToken)
{


  smToken->srcp.file = tmkEnv->fileNo;


  return -1;
}

int tmkScAction(
     tmkScContext smThis,
     int smInternalCode,
     TmkToken *smToken)
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case  16:		/* 'ATTRIBUTES'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case   5:		/* 'NAME'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case   6:		/* 'CODE'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case   7:		/* 'SRCP'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case   4:		/* 'ROW'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  11:		/* 'COLUMN'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case   8:		/* 'FILE'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  14:		/* 'POSITION'*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  17:		/* IDENTIFIER*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  18:		/* NUMBER*/ 
    { smToken->ival = atoi(smThis->smText); 
}
    break;

  case  19:		/* STRING*/ 
    { smToken->sval = newStr(smThis, 1); 
}
    break;

  case  13:		/* '%%IMPORT'*/ 
    {
	tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  20:		/* SKIPHEADER*/ 
    {
	/* Skip a section where ToolMaker strings and semantic actions exist */
	tmkSkipCode(RULES_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  21:		/* SKIPHEADER*/ 
    {
	/* Skip a section where ToolMaker strings exists */
	tmkSkipCode(STRSKP_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case  22:		/* SKIPHEADER*/ 
    {
	/* Skip a section where no ToolMaker strings exists */
	tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
      
}
    break;

  case   3:		/* '%%'*/ 
    {
	tmkSkipCode(SEM_SKIP, smThis, &(smToken->fpos), &(smToken->length), tmkEscape);
        smToken->sval = newStr(smThis, 2);
      
}
    break;
  }
  return smToken->code;
}


