#ifndef _codeCommon_H_
#define _codeCommon_H_
/* codeCommon.h

   Common definitions for code

   This file is generated from information in 'code.tmk'

*/

/* The import section (%%IMPORT) */

typedef int TmNatural;
typedef int TmCode;

/* The source position type (%%SRCP) */

typedef struct TmSrcp {
    TmNatural line ;
    TmNatural col ;
    TmNatural file ;
} TmSrcp;


/* The token type (%%TOKEN) */

typedef struct TmToken {
    TmCode Code ;
    TmSrcp srcp ;
    double floatValue ;
    char* stringValue ;
} TmToken;

#endif


