/*----------------------------------------------------------------------*\

	pmkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include "pws.h"
#include "pwsLexCode.h"

#define DECL 0
#define CODE 1
#define ACTION 2
#define SKIP 3

extern char pmkEscape;

/* END %%IMPORT */
#include "pmkScan.h"

/* %%DECLARATION */


#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#endif

#define gch() (n++ < smThis->smLength? *(s++): ((n = smSkip(smThis,1000000000)) == 0? EOF:\
((n = smThis->smLength - n), (s = (char *)&smThis->smText[n]), n++, *(s++))))

static char *newStr(smThis, skip)
  register pmkScContext smThis;
  register int skip;
{
  char *temp = (char *) malloc(smThis->smLength+1-2*skip);

  pmkScCopy(smThis,(unsigned char *)temp, skip, smThis->smLength-skip);
  temp[smThis->smLength-2*skip] = 0;
  return temp;
}



/* END %%DECLARATION */

int pmkScReader(smThis,smBuffer,smLength)
     pmkScContext smThis;
     unsigned char *smBuffer;
     unsigned int smLength;
{


  return read(smThis->fd,smBuffer,smLength);


}    

int pmkScPreHook(smThis,smToken)
     pmkScContext smThis;
     PmkToken *smToken;
{


  smToken->srcp.file = 0;


  return -1;
}

int pmkScAction(smThis,smInternalCode,smToken)
     pmkScContext smThis;
     int smInternalCode;
     PmkToken *smToken;
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case  29:		/* IDENTIFIER*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  30:		/* INTEGER*/ 
    { smToken->ival = atoi(smThis->smText); 
}
    break;

  case  31:		/* STRING*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  32:		/* ANG_BRACK_STRING*/ 
    { smToken->sval = newStr(smThis, 0); 
}
    break;

  case  26:		/* '%%DECLARATIONS'*/ 
    {
	    /* Read past declarations */
	    tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	  
}
    break;

  case  20:		/* '%%EXPORT'*/ 
    {
          tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  22:		/* '%%SCANNER'*/ 
    {
	  tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  27:		/* '%%INSERTSYMBOL'*/ 
    {
	  tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  28:		/* '%%DELETESYMBOL'*/ 
    {
	  tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  33:		/* SKIPHEADER*/ 
    {
	tmkSkipCode(NOSTRS_SKIP, smThis, &(smToken->fpos), &(smToken->length), pmkEscape);
      
}
    break;

  case  34:		/* SKIPHEADER*/ 
    {
	tmkSkipCode(STRSKP_SKIP, smThis,&(smToken->fpos), &(smToken->length),  pmkEscape);
      
}
    break;

  case   0:		/* '%%'*/ 
    {
	    /* Read past action */
	    tmkSkipCode(SEM_SKIP, smThis, &(smToken->fpos), &(smToken->length), pmkEscape);
	    smToken->sval = newStr(smThis, 2);
	    smToken->sval[smToken->length] = '\0';
	  
}
    break;
  }
  return smToken->code;
}


