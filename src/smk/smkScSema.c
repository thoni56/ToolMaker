/*----------------------------------------------------------------------*\

    smkScSema.c

    ScannerMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include <stdio.h>
#include "common.h"
#include "action.h"
#include "name.h"
#include "set.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"


extern double atof();

extern smkScContext lexContext;

/* END %%IMPORT */
#include "smkScan.h"

/* %%DECLARATION */


#ifdef WIN32
#include <io.h>
#endif


/*
 * Skip characters until '%%' and write them to optTable
 */

static Action lexWriteAction(
    smkScContext smThis,
    ActionType type,
    int skip)
{
  Action action;
  unsigned char *ch;
  int at;
  int state;

  if(type!=actionNONE)
    action=actionPut(type,smThis->smNextPosition,0);
  else
    action=NULL;
  state=0;
  at=2;
  while(smkScSkip(smThis,10000)) {
    ch=smThis->smText+at;
    for(;at<smThis->smLength;at++,ch++)
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
  smkScSkip(smThis,at-smThis->smLength-skip);
  if(type!=actionNONE) action->stop=smThis->smNextPosition-3+skip;
  return action;
}

static Name lexName(
    smkScContext smThis)
{
  unsigned char rem;
  Name name;

  rem=smThis->smText[smThis->smLength];
  smThis->smText[smThis->smLength]=0;
  name=nameSearch(smThis->smText);
  smThis->smText[smThis->smLength]=rem;
  return name;
}

static Name lexMapName(
     smkScContext smThis)
{
  unsigned char *text;
  Name name;

  text=(unsigned char *)smalloc((smThis->smLength+1)*sizeof(char));
  smkScMapCopy(smThis, text, 0, smThis->smLength);
  text[smThis->smLength]=0;
  name=nameSearch(text);
  free(text);
  return name;
}

static int lexNumber(
    smkScContext smThis)
{
  char rem;
  int inumber;

  rem=smThis->smText[smThis->smLength];
  smThis->smText[smThis->smLength]=0;
  inumber=atoi((char *)(smThis->smText));
  smThis->smText[smThis->smLength]=rem;
  return inumber;
}


/* END %%DECLARATION */

int smkScReader(
    smkScContext smThis,
    unsigned char *smBuffer,
    unsigned int smLength)
{


  return read(smThis->fd,smBuffer,smLength);


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
  case  38:		/* NUMBER*/
  case  46:		/* NUMBER*/
    { smToken->inumber=lexNumber(smThis);
}
    break;

  case  35:		/* CLASS*/
  case  36:		/* STRING*/
  case  47:		/* STRING*/
  case  54:		/* NUMBER*/
  case  56:		/* CHARACTER*/
    { smToken->name=lexName(smThis);
}
    break;

  case  37:		/* IDENTIFIER*/
  case  48:		/* IDENTIFIER*/
  case  57:		/* IDENTIFIER*/
    { smToken->name=lexMapName(smThis);
}
    break;

  case  39:		/* SKIPHEADER*/
    {{
  long fpos, length;
  tmkSkipCode(STRSKP_SKIP, smThis, &fpos, &length,  smkEscape);
}
}
    break;

  case  40:		/* SKIPHEADER*/
    {{
  long fpos, length;
  tmkSkipCode(NOSTRS_SKIP, smThis, &fpos, &length,  smkEscape);
}
}
    break;

  case  23:		/* '%%ACTION'*/
    { smToken->action=lexWriteAction(smThis,actionACTION,2);
}
    break;

  case  22:		/* '%%READER'*/
    { smToken->action=lexWriteAction(smThis,actionREADER,2);
}
    break;

  case  25:		/* '%%CONTEXT'*/
    { smToken->action=lexWriteAction(smThis,actionCONTEXT,2);
}
    break;

  case  34:		/* '%%DECLARATION'*/
    { smToken->action=lexWriteAction(smThis,actionDECLARATION,2);
}
    break;

  case  16:		/* '%%END'*/
    { smToken->action=lexWriteAction(smThis,actionNONE,2);
}
    break;

  case  21:		/* '%%EXPORT'*/
    { smToken->action=lexWriteAction(smThis,actionEXPORT,2);
}
    break;

  case  28:		/* '%%POSTHOOK'*/
    { smToken->action=lexWriteAction(smThis,actionPOSTHOOK,2);
}
    break;

  case  26:		/* '%%PREHOOK'*/
    { smToken->action=lexWriteAction(smThis,actionPREHOOK,2);
}
    break;

  case  17:		/* '%%SET'*/
    { setRead(lexContext);
}
    break;

  case   0:		/* '%%'*/
    { smToken->action=lexWriteAction(smThis,actionSEMANTIC,0);
}
    break;

  case  43:		/* COMMENT*/
    { lexWriteAction(smThis,actionNONE,2);
}
    break;

  case  58:		/* EOS*/
    { smkScSkip(smThis,-2);
}
    break;

  case  61:		/* BLANK*/
    { return smSkipToken;
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
