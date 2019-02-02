/*----------------------------------------------------------------------*\

	pmkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

#include "pmkScan.h"

/* %%DECLARATION */


#include "pws.h"
#include "pwsLexCode.h"

#define DECL 0
#define CODE 1
#define ACTION 2
#define SKIP 3

extern char pmkEscape;


#define gch() (n++ < this->smLength? *(s++): ((n = smSkip(this,1000000000)) == 0? EOF:\
((n = this->smLength - n), (s = (char *)&this->smText[n]), n++, *(s++))))

static char *newStr(this, skip)
  register pmkContext this;
  register int skip;
{
  char *temp = (char *) malloc(this->smLength+1-2*skip);

  pmkCopy(this,(unsigned char *)temp, skip, this->smLength-skip);
  temp[this->smLength-2*skip] = 0;
  return temp;
}



/* END %%DECLARATION */

int pmkScReader(smThis,smBuffer,smLength)
     pmkScContext smThis;
     unsigned char *smBuffer;
     unsigned int smLength;
{


  return read(this->fd,smBuffer,smLength);


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
  case  27:		/* IDENTIFIER*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  28:		/* INTEGER*/ 
    { smToken->ival = atoi(this->smText); 
}
    break;

  case  29:		/* STRING*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  30:		/* ANG_BRACK_STRING*/ 
    { smToken->sval = newStr(this, 0); 
}
    break;

  case  25:		/* '%%DECLARATIONS'*/ 
    {
	    /* Read past declarations
	     */
	    code_spec.udata_line = this->smLine;
	    tmkSkipCode(NOSTRS_SKIP, this, &code_spec.udata_start, 
		        &code_spec.udata_cnt, pmkEscape);
	  
}
    break;

  case  16:		/* '%%CODE'*/ 
    {
	    /* Read past code
	     */
	    code_spec.ucode_line = this->smLine;
	    tmkSkipCode(NOSTRS_SKIP, this, &code_spec.ucode_start, 
		        &code_spec.ucode_cnt, pmkEscape);
	  
}
    break;

  case  19:		/* '%%EXPORT'*/ 
    {
          tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  21:		/* '%%SCANNER'*/ 
    {
	  tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  26:		/* '%%INSERTSYMBOL'*/ 
    {
	  tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos),
	              &(smToken->length), pmkEscape);
	
}
    break;

  case  31:		/* SKIPHEADER*/ 
    {
	tmkSkipCode(NOSTRS_SKIP, this, &(smToken->fpos), &(smToken->length), pmkEscape);
      
}
    break;

  case  32:		/* SKIPHEADER*/ 
    {
	tmkSkipCode(STRSKP_SKIP, this,&(smToken->fpos), &(smToken->length),  pmkEscape);
      
}
    break;

  case  10:		/* '%%'*/ 
    {
	    /* Read past action
	     */
	    tmkSkipCode(SEM_SKIP, this, &(smToken->fpos), &(smToken->length), pmkEscape);
	    smToken->sval = newStr(this, 2);
	    smToken->sval[smToken->length] = '\0';
	  
}
    break;
  }
  return smToken->code;
}


