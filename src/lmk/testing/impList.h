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
#define liSUM   (1<<0)		/* Summary */
#define liERR   (1<<1)		/* Erroneous source lines */
#define liOK    (1<<2)		/* Correct source lines */
#define liINCL  (1<<3)		/* Look also in PUSHed files */
#define liHEAD  (1<<4)		/* Heading */

#define liTINY (liSUM|liERR|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum impMessages {
    imp_ENGLISH_Messages
} impMessages;


extern void impLiInit();
extern void impLog();
extern void impLiOff();
extern void impLiOn();
extern void impLiEnter();
extern void impLiExit();
extern void impLiPage();
extern impSev impSeverity();
extern impSev impLocSeverity();
extern void impResLocSeverity();
extern void impList();
extern int impMsg();
extern void impLiPrint();
extern void impSkipLines();
extern void impLiTerminate();


#endif

