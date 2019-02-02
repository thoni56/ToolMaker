#ifndef _tmCommon_H_
#define _tmCommon_H_
/* tmCommon.h

   Common definitions for tm

   This file is generated from information in 'tm.tmk'

*/

/* The import section (%%IMPORT) */

typedef int TmNatural;     /* A natural number of "reasonable" length. */
typedef int TmCode;        /* The type of a token code. */

/* The source position type (%%SRCP) */

typedef struct TmSrcp {
    TmNatural line ;
    TmNatural col ;
    TmNatural file ;
} TmSrcp;


/* The token type (%%TOKEN) */

typedef struct TmToken {
    TmCode code ;
    TmSrcp srcp ;
    char stringValue[256] ;
    int integerValue ;
} TmToken;

#endif

