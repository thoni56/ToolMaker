#ifndef _tmkList_H_
#define _tmkList_H_
/*----------------------------------------------------------------------*\

    tmkList.h

    Header file for ListerMaker generated error message and listing
    handler

\*----------------------------------------------------------------------*/

#include "tmkCommon.h"


/* Insert string separator */
#define tmkSEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int tmkSev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int tmkTyp;
#define liNONE  0
#define liSUM   (1<<0)      /* Summary */
#define liMSG   (1<<1)      /* Source lines with messages*/
#define liOK    (1<<2)      /* Correct source lines */
#define liINCL  (1<<3)      /* Look also in PUSHed files */
#define liHEAD  (1<<4)      /* Heading */

#define liTINY (liSUM|liMSG|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum tmkMessages {
    tmk_ENGLISH_Messages
} tmkMessages;


/* UNINITIALISED: */
/* Initialise the tmkLister System */
extern void tmkLiInit(char header[],
                 char src[],
                 tmkMessages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void tmkLog(TmkSrcp *pos,
                int ecode,
                tmkSev sev,
                char *istrs);

/* Log a message at a source position using va_arg handling */
extern void tmkLogv(TmkSrcp *pos,
                int ecode,
                tmkSev sev,
                ...);

/* Turn listing completely off after a particular source position */
extern void tmkLiOff(TmkSrcp *pos);

/* Turn listing on again at a particular source position */
extern void tmkLiOn(TmkSrcp *pos);

/* Start reading an included file at a particular source position */
extern void tmkLiEnter(TmkSrcp *pos,
                  TmkSrcp *start,
                  char fnm[]);

/* Stop reading from an included file prematurely */
extern void tmkLiExit(TmkSrcp *pos);

/* (Un)conditionally skip to a new page at a source position */
extern void tmkLiPage(TmkSrcp *pos,
                 int lins);

/* Read worst severity logged so far */
extern tmkSev tmkSeverity(void);
extern tmkSev tmkLocSeverity(void);
extern void tmkResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of a selected type in a file or the screen */
extern void tmkList(char ofnm[],
                 int lins,
                 int cols,
                 tmkTyp typ,
                 tmkSev sevs);

/* Return the i'th formatted message, return 0 if not found */
extern int tmkMsg(int i,
                   TmkSrcp *pos,
                   char *msg);

/* Print a string on a line in the output file */
extern void tmkLiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void tmkSkipLines(int lins);

/* Terminate the tmkLister system */
extern void tmkLiTerminate(void);


#endif

