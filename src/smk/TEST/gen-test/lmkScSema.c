/*----------------------------------------------------------------------*\

	lmkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

#include "lmkScan.h"

/* %%DECLARATION */


#include "lmk_i.h"


static char *newStr(this, skip)
  register lmkContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  lmkCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}


/* END %%DECLARATION */

int lmkScReader(
     lmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smLength)
{


  return read(this->fd,smBuffer,smLength);


}    

int lmkScPreHook(
     lmkScContext smThis,
     LmkToken *smToken)
{


  smToken->srcp.file = 1;


  return -1;
}

int lmkScAction(
     lmkScContext smThis,
     int smInternalCode,
     LmkToken *smToken)
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case   3:		/* IDENTIFIER*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case   4:		/* NUMBER*/ 
    { smToken->ival = atoi(this->smText); 
}
    break;

  case   5:		/* STRING*/ 
    { smToken->sval = newStr(this, 1); 
}
    break;

  case   6:		/* SKIPHEADER*/ 
    {
        tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
                    &(smToken->length), lmkEscape);
      
}
    break;

  case   7:		/* SKIPHEADER*/ 
    {
        tmkSkipCode(STRSKP_SKIP, this,&(smToken->fpos),
                    &(smToken->length),  lmkEscape);
      
}
    break;
  }
  return smToken->code;
}


