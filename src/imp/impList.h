#ifndef _impList_H_
#define _impList_H_
/*----------------------------------------------------------------------*\

    impList.h

    Header file for ListerMaker generated error message and listing
    handler

\*----------------------------------------------------------------------*/

#include "impCommon.h"


/* Insert string separator */
#define impSEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int impSev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int impTyp;
#define liNONE  0
#define liSUM   (1<<0)      /* Summary */
#define liMSG   (1<<1)      /* Source lines with messages*/
#define liOK    (1<<2)      /* Correct source lines */
#define liINCL  (1<<3)      /* Look also in PUSHed files */
#define liHEAD  (1<<4)      /* Heading */

#define liTINY (liSUM|liMSG|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum impMessages {
    imp_ENGLISH_Messages
} impMessages;


/* UNINITIALISED: */
/* Initialise the impLister System */
extern void impLiInit(char header[],
                 char src[],
                 impMessages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void impLog(TmSrcp *pos,
                int ecode,
                impSev sev,
                char *istrs);

/* Log a message at a source position using va_arg handling */
extern void impLogv(TmSrcp *pos,
                int ecode,
                impSev sev,
                ...);

/* Turn listing completely off after a particular source position */
extern void impLiOff(TmSrcp *pos);

/* Turn listing on again at a particular source position */
extern void impLiOn(TmSrcp *pos);

/* Start reading an included file at a particular source position */
extern void impLiEnter(TmSrcp *pos,
                  TmSrcp *start,
                  char fnm[]);

/* Stop reading from an included file prematurely */
extern void impLiExit(TmSrcp *pos);

/* (Un)conditionally skip to a new page at a source position */
extern void impLiPage(TmSrcp *pos,
                 int lins);

/* Read worst severity logged so far */
extern impSev impSeverity(void);
extern impSev impLocSeverity(void);
extern void impResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of a selected type in a file or the screen */
extern void impList(char ofnm[],
                 int lins,
                 int cols,
                 impTyp typ,
                 impSev sevs);

/* Return the i'th formatted message, return 0 if not found */
extern int impMsg(int i,
                   TmSrcp *pos,
                   char *msg);

/* Print a string on a line in the output file */
extern void impLiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void impSkipLines(int lins);

/* Terminate the impLister system */
extern void impLiTerminate(void);


#endif

