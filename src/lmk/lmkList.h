#ifndef _lmkList_H_
#define _lmkList_H_
/*----------------------------------------------------------------------*\

    lmkList.h

    Header file for ListerMaker generated error message and listing
    handler

\*----------------------------------------------------------------------*/

#include "lmkCommon.h"


/* Insert string separator */
#define lmkSEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int lmkSev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int lmkTyp;
#define liNONE  0
#define liSUM   (1<<0)		/* Summary */
#define liMSG   (1<<1)		/* Source lines with messages*/
#define liOK    (1<<2)		/* Correct source lines */
#define liINCL  (1<<3)		/* Look also in PUSHed files */
#define liHEAD  (1<<4)		/* Heading */

#define liTINY (liSUM|liMSG|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum lmkMessages {
    lmk_ENGLISH_Messages,
    lmk_AMOS_Messages
} lmkMessages;


/* UNINITIALISED: */
/* Initialise the lmkLister System */
extern void lmkLiInit(char header[],
                 char src[],
                 lmkMessages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void lmkLog(TmkSrcp *pos,
                int ecode,
                lmkSev sev,
                char *istrs);

/* Log a message at a source position using va_arg handling */
extern void lmkLogv(TmkSrcp *pos,
                int ecode,
                lmkSev sev,
                ...);

/* Turn listing completely off after a particular source position */
extern void lmkLiOff(TmkSrcp *pos);

/* Turn listing on again at a particular source position */
extern void lmkLiOn(TmkSrcp *pos);

/* Start reading an included file at a particular source position */
extern void lmkLiEnter(TmkSrcp *pos,
                  TmkSrcp *start,
                  char fnm[]);

/* Stop reading from an included file prematurely */
extern void lmkLiExit(TmkSrcp *pos);

/* (Un)conditionally skip to a new page at a source position */
extern void lmkLiPage(TmkSrcp *pos,
                 int lins);

/* Read worst severity logged so far */
extern lmkSev lmkSeverity(void);
extern lmkSev lmkLocSeverity(void);
extern void lmkResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of multiple input files in a listing file or on screen */
extern void lmkListm(char ofnm[],
                  int lins,
                  int cols,
                  lmkTyp typ,
                  lmkSev sevs,
                  char *fnms[]);

/* Return the i'th formatted message, return 0 if not found */
extern int lmkMsg(int i,
                   TmkSrcp *pos,
                   char *msg);

/* Print a string on a line in the output file */
extern void lmkLiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void lmkSkipLines(int lins);

/* Terminate the lmkLister system */
extern void lmkLiTerminate(void);


#endif

