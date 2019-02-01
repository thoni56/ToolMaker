#ifndef _smkList_H_
#define _smkList_H_
/*----------------------------------------------------------------------*\

	smkList.h

	Header file for ListerMaker generated error message and listing
	handler

\*----------------------------------------------------------------------*/

#include "smkCommon.h"


/* Insert string separator */
#define smkSEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int smkSev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int smkTyp;
#define liNONE  0
#define liSUM   (1<<0)		/* Summary */
#define liERR   (1<<1)		/* Erroneous source lines */
#define liOK    (1<<2)		/* Correct source lines */
#define liINCL  (1<<3)		/* Look also in PUSHed files */
#define liHEAD  (1<<4)		/* Heading */

#define liTINY (liSUM|liERR|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum smkMessages {
    smk_ENGLISH_Messages,
    smk_AMOS_Messages
} smkMessages;


/* UNINITIALISED: */
/* Initialise the smkLister System */
extern void smkLiInit(char header[],
				 char src[],
				 smkMessages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void smkLog(TmkSrcp *pos,
				int ecode,
				smkSev sev,
				char *istrs);

/* Log a message at a source position using va_arg handling */
extern void smkLogv(TmkSrcp *pos,
				int ecode,
				smkSev sev,
				...);

/* Turn listing completely off after a particular source position */
extern void smkLiOff(TmkSrcp *pos);

/* Turn listing on again at a particular source position */
extern void smkLiOn(TmkSrcp *pos);


/* (Un)conditionally skip to a new page at a source position */
extern void smkLiPage(TmkSrcp *pos,
				 int lins);

/* Read worst severity logged so far */
extern smkSev smkSeverity(void);
extern smkSev smkLocSeverity(void);
extern void smkResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of multiple input files in a listing file or on screen */
extern void smkListm(char ofnm[],
				  int lins,
				  int cols,
				  smkTyp typ,
				  smkSev sevs,
				  char *fnms[]);

/* Return the i'th formatted message, return 0 if not found */
extern int smkMsg(int i,
			       TmkSrcp *pos,
			       char *msg);

/* Print a string on a line in the output file */
extern void smkLiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void smkSkipLines(int lins);

/* Terminate the smkLister system */
extern void smkLiTerminate(void);


#endif

