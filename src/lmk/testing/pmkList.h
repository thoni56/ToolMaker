#ifndef _pmkList_H_
#define _pmkList_H_
/*----------------------------------------------------------------------*\

	pmkList.h

	Header file for ListerMaker generated error message and listing
	handler

\*----------------------------------------------------------------------*/

#include "pmkCommon.h"


/* Insert string separator */
#define pmkSEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int pmkSev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int pmkTyp;
#define liNONE  0
#define liSUM   (1<<0)		/* Summary */
#define liERR   (1<<1)		/* Erroneous source lines */
#define liOK    (1<<2)		/* Correct source lines */
#define liINCL  (1<<3)		/* Look also in PUSHed files */
#define liHEAD  (1<<4)		/* Heading */

#define liTINY (liSUM|liERR|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum pmkMessages {
    pmk_ENGLISH_Messages
} pmkMessages;


/* UNINITIALISED: */
/* Initialise the pmkLister System */
extern void pmkLiInit(char header[],
				 char src[],
				 pmkMessages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void pmkLog(TmkSrcp *pos,
				int ecode,
				pmkSev sev,
				char *istrs);

/* Log a message at a source position using va_arg handling */
extern void pmkLogv(TmkSrcp *pos,
				int ecode,
				pmkSev sev,
				...);

/* Turn listing completely off after a particular source position */
extern void pmkLiOff(TmkSrcp *pos);

/* Turn listing on again at a particular source position */
extern void pmkLiOn(TmkSrcp *pos);


/* (Un)conditionally skip to a new page at a source position */
extern void pmkLiPage(TmkSrcp *pos,
				 int lins);

/* Read worst severity logged so far */
extern pmkSev pmkSeverity(void);
extern pmkSev pmkLocSeverity(void);
extern void pmkResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of multiple input files in a listing file or on screen */
extern void pmkListm(char ofnm[],
				  int lins,
				  int cols,
				  pmkTyp typ,
				  pmkSev sevs,
				  char *fnms[]);

/* Return the i'th formatted message, return 0 if not found */
extern int pmkMsg(int i,
			       TmkSrcp *pos,
			       char *msg);

/* Print a string on a line in the output file */
extern void pmkLiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void pmkSkipLines(int lins);

/* Terminate the pmkLister system */
extern void pmkLiTerminate(void);


#endif

