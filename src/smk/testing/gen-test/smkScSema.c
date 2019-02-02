/*----------------------------------------------------------------------*\

	smkScSema.c

	ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

#include "smkScan.h"

/* %%DECLARATION */


#include <stdio.h>
#include "smk_i.h"
#include "name.h"
#include "smkList.h"
#include "action.h"

extern double atof();

smkContext lexContext;


/*
 * Skip characters until '%%' and write them to optTable
 */

static Action lexWriteAction(this,type,skip)
     register smkContext this;
     register ActionType type;
     register int skip;
{
  register Action action;
  register unsigned char *ch;
  register int at;
  register int state;

  if(type!=actionNONE)
    action=actionPut(type,this->smNextPosition,0);
  else
    action=NULL;
  state=0;
  while(smkSkip(this,10000)) {
    ch=this->smText+2;
    for(at=2;at<this->smLength;at++,ch++)
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
  smkSkip(this,at-this->smLength-skip);
  if(type!=actionNONE) action->stop=this->smNextPosition-3+skip;
  return action;
}

static Name lexName(this)
     register smkContext this;
{
  register char rem;
  register Name name;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  name=nameSearch(this->smText);
  this->smText[this->smLength]=rem;
  return name;
}
 
static int lexNumber(this)
     register smkContext this;
{
  register char rem;
  register int inumber;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  inumber=atoi(this->smText);
  this->smText[this->smLength]=rem;
  return inumber;
}

static double lexFloat(this)
     register smkContext this;
{
  register char rem;
  register double fnumber;

  rem=this->smText[this->smLength];
  this->smText[this->smLength]=0;
  fnumber=atof(this->smText);
  this->smText[this->smLength]=rem;
  return fnumber;
}


/* END %%DECLARATION */

int smkScReader(
     smkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smLength)
{


  return read(this->fd,smBuffer,smLength);


}    


int smkScAction(
     smkScContext smThis,
     int smInternalCode,
     SmkToken *smToken)
{
  enum {
    smSkipToken		= -1,
    smContinueToken	= -2
  };
  switch(smInternalCode) {
  case  68:		/* NUMBER*/ 
  case  76:		/* NUMBER*/ 
    { smToken->inumber=lexNumber(this); 
}
    break;

    { smToken->fnumber=lexFloat(this); 
}
    break;

  case  14:		/* 'C'*/ 
  case  15:		/* 'K'*/ 
  case  16:		/* 'M'*/ 
  case  17:		/* 'NO'*/ 
  case  19:		/* 'ADA'*/ 
  case  20:		/* 'COL'*/ 
  case  21:		/* 'DES'*/ 
  case  22:		/* 'DFA'*/ 
  case  23:		/* 'ERR'*/ 
  case  24:		/* 'GCS'*/ 
  case  25:		/* 'LES'*/ 
  case  26:		/* 'MAP'*/ 
  case  27:		/* 'NFA'*/ 
  case  28:		/* 'POS'*/ 
  case  29:		/* 'RDS'*/ 
  case  30:		/* 'ROW'*/ 
  case  31:		/* 'SCR'*/ 
  case  32:		/* 'SET'*/ 
  case  33:		/* 'TOK'*/ 
  case  34:		/* 'AUTO'*/ 
  case  36:		/* 'BYTE'*/ 
  case  37:		/* 'LIST'*/ 
  case  41:		/* 'TOKEN'*/ 
  case  42:		/* 'TRACE'*/ 
  case  46:		/* 'ESCAPE'*/ 
  case  47:		/* 'ROWCOL'*/ 
  case  48:		/* 'EXCLUDE'*/ 
  case  49:		/* 'VERBOSE'*/ 
  case  54:		/* 'POSITION'*/ 
  case  58:		/* 'SCREENING'*/ 
  case  65:		/* CLASS*/ 
  case  66:		/* STRING*/ 
  case  67:		/* IDENTIFIER*/ 
  case  77:		/* STRING*/ 
  case  78:		/* IDENTIFIER*/ 
  case  84:		/* NUMBER*/ 
  case  86:		/* CHARACTER*/ 
  case  87:		/* IDENTIFIER*/ 
    { smToken->name=lexName(this); 
}
    break;

  case  52:		/* '%%ACTION'*/ 
    { smToken->action=lexWriteAction(this,actionACTION,2); 
}
    break;

  case  43:		/* '%%CODE'*/ 
    { smToken->action=lexWriteAction(this,actionCODE,2); 
}
    break;

  case  51:		/* '%%READER'*/ 
    { smToken->action=lexWriteAction(this,actionREADER,2); 
}
    break;

  case  55:		/* '%%CONTEXT'*/ 
    { smToken->action=lexWriteAction(this,actionCONTEXT,2); 
}
    break;

  case  64:		/* '%%DECLARATION'*/ 
    { smToken->action=lexWriteAction(this,actionDECLARATION,2); 
}
    break;

  case  38:		/* '%%END'*/ 
    { smToken->action=lexWriteAction(this,actionNONE,2); 
}
    break;

  case  50:		/* '%%EXPORT'*/ 
    { smToken->action=lexWriteAction(this,actionEXPORT,2); 
}
    break;

  case  59:		/* '%%POSTHOOK'*/ 
    { smToken->action=lexWriteAction(this,actionPOSTHOOK,2); 
}
    break;

  case  56:		/* '%%PREHOOK'*/ 
    { smToken->action=lexWriteAction(this,actionPREHOOK,2); 
}
    break;

  case  39:		/* '%%SET'*/ 
    { setRead(lexContext); 
}
    break;

  case  69:		/* SKIPHEADER*/ 
    { {
	  long fpos, length;
	  tmkSkipCode(STRSKP_SKIP, this, &fpos, &length,  smkEscape);
	}
}
    break;

  case  70:		/* SKIPHEADER*/ 
    { {
	  long fpos, length;
	  tmkSkipCode(NOSTRS_SKIP, this, &fpos, &length,  smkEscape);
	}
}
    break;

  case  18:		/* '%%'*/ 
    { smToken->action=lexWriteAction(this,actionSEMANTIC,0); 
}
    break;

  case  73:		/* COMMENT*/ 
    { lexWriteAction(this,actionNONE,2); 
}
    break;

  case  88:		/* EOS*/ 
    { smkSkip(this,-2); 
}
    break;
  }
  return smToken->code;
}

int smkScPostHook(
     smkScContext smThis,
     SmkToken *smToken)
{
  enum {
    smSkipToken		= -1
  };


  smToken->srcp.file=1;


  return smToken->code;
}

