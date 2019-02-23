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
#define liSUM   (1<<0)      /* Summary */
#define liMSG   (1<<1)      /* Source lines with messages*/
#define liOK    (1<<2)      /* Correct source lines */
#define liINCL  (1<<3)      /* Look also in PUSHed files */
#define liHEAD  (1<<4)      /* Heading */

#define liTINY (liSUM|liMSG|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum pmkMessages {
    pmk_ENGLISH_Messages,
    pmk_AMOS_Messages
} pmkMessages;


extern void pmkLiInit();
extern void pmkLog();
extern void pmkLiOff();
extern void pmkLiOn();
extern void pmkLiPage();
extern pmkSev pmkSeverity();
extern pmkSev pmkLocSeverity();
extern void pmkResLocSeverity();
extern void pmkListm();
extern int pmkMsg();
extern void pmkLiPrint();
extern void pmkSkipLines();
extern void pmkLiTerminate();


#endif

