/*	ask.c			    DATE: 1990-01-17/tools@roo

	ask -- a package for nice(r) user i/o
	Written by Reibert Olsson.

	Requires: ?
		    
	DESCRIPTION -- see ASK.HLP

	Version history:
	  1.00 Minor version				      84-08-22
	  1.01 AskBool, AskLim  			      84-10-29
	  1.02 Better scan, eoln_chars			      84-11-10
	  1.03 AskLong, trace removed (USE symdeb)	      85-10-10
	  1.04 AskGet, AskSet changed, A_NE		      85-12-06
	  1.05 MS-C adaption				      86-01-27
	  2.0  Sun, most rewritten			      89-11-24
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "ask.h"

PRIVATE char *VERSION= "2.0";

/* -- Language dependent information -- */

#ifndef LANGUAGE
#define LANGUAGE ENGLISH
#endif

#if LANGUAGE==ENGLISH
char	      
  *booltab[]= { "YES", "NO", NULL },
  boolhelp[]= "Please answer yes or no!",
  menue1[]=   "One of the following items can be given:",
  nocom[]=    "? Unknown item -- give ?<cr> for further information",
  ambig[]=    "? Ambigiuous item -- please give more characters",
  nohelp[]=   "Sorry! No help is available",
  nodefv[]=   "Sorry! No default is specified -- please give an answer",
  limerr1[]=  "? Range error, value shall be between ",
  limerr2[]=  " and ",
  interr[]=   "? Numeric error -- a number is expected";
#else
#if LANGUAGE==SWEDISH
char
  *booltab[]= { "JA", "NEJ", NULL },
  boolhelp[]= "Var v{nlig svara ja eller nej!",
  menue1[]=   "Ett av dessa kommandon kan ges:",
  nocom[]=    "? Ok{nt kommando",
  ambig[]=    "? Tvetydigt kommando",
  nohelp[]=   "Tyv{rr finns ingen hj{lp",
  nodefv[]=   "Inget standardv{rde givet",
  limerr1[]=  "? Utanf|r intervallet, talet skall vara mellan ",
  limerr2[]=  " och ",
  interr[]=   "? Felaktigt heltal";
#endif
#endif


/* -- Command flags -- */


/* -- Redefinable structures -- */

PRIVATE char
  *helpChars=      "?",		/* User request for help */
  *eolnChars=      ".",		/* Equals user <CR> */
  *startDefChars=  " (",
  *stopDefChars=   ")",
  *comPrChars=     "> ",
  *boolPrChars=    "? ",	
  *numPrChars=     ": ";

PRIVATE boolean
  bufOn= TRUE;                         /* Buffering wanted */

PRIVATE int
  comWidth= 60,                        /* Width of command help text */
  comCols= 6;                          /* #columns to write */


/* -- Internal variables -- */

#define LINESZ 256                      /* Size of user input buffer */
			   
PRIVATE char
  buf[LINESZ],                          /* User input buffer */
  defstr[LINESZ];                       /* Temporary default string */

PRIVATE char
  *bufp= buf,                           /* Scan pointer in buf */
  *answer,                              /* Pointer to last answer */
  *defp,                                /* Default string pointer */
  *helpp,                               /* Help s.p. */
  *errp,                                /* Error s.p. */
  *prp,                                 /* Prompt s.p. */
  *qpr;                                 /* Question s.p. */

PRIVATE int acw;			/* Actual command word */

PRIVATE boolean
  helpFound;                           /* Signal from getAnswer */


/* -- External functions -- */

extern boolean prefix();
extern void putMenue();
extern int getMenue();


/* -- Internal functions --------------------------------------------- */

PRIVATE putPrompt()
/* Writes prompt to user: <qpr>[<default>]<prp> */
{
  printf("%s",qpr);
  if (!(acw&(A_NDV|A_NSD))) 		/* show default? */
    printf("%s%s%s", startDefChars, defp, stopDefChars);
  printf("%s",prp);
}


PRIVATE boolean eoln(p)
/* Returns TRUE if this char is eoln */
char *p;
{ return( p==NULL || !*p || strchr(eolnChars, *p)!=NULL ); }


PRIVATE boolean isstop(p)
/* Returns TRUE if this char is space or eoln */
char *p;
{ return( isspace(*p) || eoln(p) ); }


PRIVATE char *stpblk(s)
char *s;
{
  while(isspace(*s)) s++;
  return(s);
}


PRIVATE char *frontstrip(p)
/* Strips blanks and first eolnChar */
char *p;
{
  p= stpblk(p);
  if (strchr(eolnChars, *p)!= NULL) {  /* Strip one leading eoln */
    p++;
    p= stpblk(p);
  }
  return(p);
}


PRIVATE char *strip(p)
/* Strips blanks (char<=' ') at tail of string */
char *p;
{
  char *pi, *pl;

  if (p!=NULL) {
    for(pi= pl= p; *pi; pi++) if(*pi>' ') pl=pi;
    *(pl+1)= '\0';
  }
  return(p);
}


PRIVATE void flush()
/* Will flush input buffer */
{ bufp= buf; *bufp= '\0'; }


PRIVATE char *getLine(s)
char *s;
{
  int i,c;

  if(acw&A_NE) {			/* no echo == NYI */
    return(fgets(s, LINESZ, stdin));
  } else 				/* echo */
    return(fgets(s, LINESZ, stdin));
}


PRIVATE getAnswer(spaceStop,retHelp,upAnswer)
boolean
  spaceStop, /* Break answer when space found */
  retHelp,   /* Return if help string found */
  upAnswer;  /* Uppercase answer */
{
  int errc= 0;
  boolean xit= FALSE, eol;

  while(!xit) {
    helpFound=FALSE;
    if (!bufOn || *bufp=='\0') {       /* Get answer from user */
      putPrompt();
      if ((bufp=getLine(buf))==NULL)
        { xit= TRUE; errc= -1; if (acw^A_RF) exit(errc); }
      bufp= strip(stpblk(bufp));
    }
    if (eoln(bufp)) {
      if (acw&A_NDV); /* Nescessary! */
      else { answer= defp; xit= TRUE; }
      bufp= frontstrip(bufp);
    } else {
      answer= bufp;
      while(*bufp && !helpFound && !(spaceStop && isstop(bufp))) {
	if (prefix(helpChars,bufp)) {
	  if (!retHelp) puts(helpp);
	  helpFound= TRUE;
	} else bufp++;
      }
      eol= eoln(bufp);
      *bufp= '\0';
      if (!helpFound) {
        bufp++;
        bufp= (eol? stpblk(bufp): frontstrip(bufp) );
      }
      xit= !helpFound || retHelp&&helpFound;
    }
  } /* while(!xit) */
  if (upAnswer && answer != defp) strupr(answer);
  return(errc);
}


PRIVATE getNum(pr, ip, h, e, cw) /* Reads integer */
    char *pr, *h, *e;
    int *ip;
    int cw;
{
    int errc, sc;

    acw= cw;
    if (acw^A_NDV) { defp= defstr; sprintf(defstr, "%d", *ip); }
    qpr=pr; prp=numPrChars;
    helpp= (h==NULL? nohelp: h);
    errp= (e==NULL? interr: e); 
    for (errc=0; errc==0; ) {
	if ((errc=getAnswer(TRUE,FALSE,FALSE))!=0) break; /* Read & ret on fatal err */
	sc=sscanf(answer, "%i", ip);
	if (sc==0)		/* Error: no digs || not only digs */
	    if (acw&A_RE) errc= 1; else { puts(errp); flush(); }
	else break;
    }
    return(errc);
}


PRIVATE getCom(pr,no,ctbl,h,e1,e2,cw) /* Get Command */
    char *pr, *ctbl[], *h, *e1, *e2;
    int *no, cw;
{
    int errc= 0;

    acw= cw;
    if (acw^A_NDV) defp= ctbl[*no];
    qpr= pr;
    for (;;) {
	if ((errc=getAnswer(TRUE,TRUE,TRUE))==0) {
	    if (helpFound) {
		if (h==NULL) {
		    puts(menue1);
		    putMenue(answer, ctbl, comWidth, comCols);
		    puts("");
		} else puts(h);
	    } else switch (getMenue(answer, ctbl, no)) {
	    case 0:
		if (acw&A_RE) return 1;
		else { puts(e1); flush(); }
		break;
	    case 1: return errc;
	    default:
		if (acw&A_RE) return 2;
		else { puts(e2); flush(); }
	    }
	} else return errc;
    }			    
/*    return errc; */
}


/* -- User entrys ---------------------------------------------------- */

PUBLIC int askSet(fun, val)
    AskCommand fun;
    long val;
{
    switch (fun) {
    case askStartDefaultString: startDefChars= (char *)val; break;
    case askStopDefaultString: stopDefChars= (char *)val;  break;
    case askNumericPrompt: numPrChars= (char *)val; break;
    case askCommandPrompt: comPrChars= (char *)val; break;
    case askBooleanPrompt: boolPrChars= (char *)val; break;
    case askHelpWidth: comWidth= (int)val; break;
    case askHelpColumns: comCols= (int)val; break;
    case askHelpCharSet: helpChars= (char *)val;  break;
    case askEolnCharSet: eolnChars= (char *)val;  break;
    case askBuffering: bufOn= (boolean)val; break;
    case askInitBuffer: bufp= strcpy(buf, (char *)val); break;
    case askFlushBuffer: flush(); break;
    default: return 10; break;
    }
    return 0;
}


PUBLIC int askGet(fun, val)
    AskCommand fun;
    long val;
{
    switch (fun) {
    case askVersion: *(char **)val= VERSION; break;
    default: return 20; break;
    }
    return 0;
}


PUBLIC int askInt(pr,i,h,e,cw)
char *pr, *h, *e;
int *i;
int cw;
{
  return getNum(pr, i, h, e, cw);
}


PUBLIC int askLim(pr,i,lo,hi,h,e,cw)
char *pr, *h, *e;
int *i, lo, hi;
int cw;
{
  int errc;
  int j;

  for(j= *i; (errc= getNum(pr, &j, h, e, cw))==0; j= *i)
    if (j<lo || j>hi)
      if (e==NULL) printf("%s%d%s%d\n",limerr1,lo,limerr2,hi);
      else puts(e);
    else break;
  *i=j; 
  return(errc);
}


PUBLIC int askString(pr,s,len,h,cw)
    char *pr, *s, *h;
    int len;
    int cw;
{
    int errc;

    acw= cw;
    if (acw^A_NDV) defp= s;
    qpr= pr;
    prp= numPrChars;
    helpp= (h==NULL? nohelp: h);
    if ((errc=getAnswer(FALSE,FALSE,FALSE))==0) strncpy(s, answer, len);

    return errc;
}


PUBLIC int askCom(pr,no,ctbl,h,cw)
    char *pr, *ctbl[], *h;
    int *no, cw;
{					      
    prp= comPrChars;
    return getCom(pr, no, ctbl, h, nocom, ambig, cw);
}


PUBLIC int askBool(pr,b,h,e,cw)
    char *pr, *h, *e;
    boolean *b;
    int cw;
{
    int errc, no;
    char *bp, *hp, *ep;

    no= (*b? 0: 1);
    prp= boolPrChars;
    hp= (h==NULL? boolhelp: h);
    ep= (e==NULL? boolhelp: e);
    if ((errc= getCom(pr, &no, booltab, hp, ep, ep, cw))==0)
	*b= no==0;
    return errc;
}

/* -- End of ask.c -- */
