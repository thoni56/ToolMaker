#ifndef _impCommon_H_
#define _impCommon_H_
/* impCommon.h

   Common definitions for imp

   This file is generated from information in 'imp.tmk'

*/

/* The import section (%%IMPORT) */

/* .tmk-import */
typedef int TmNatural;

/* The source position type (%%SRCP) */

typedef struct TmSrcp {
    TmNatural line;
    TmNatural col;
    TmNatural file;
} TmSrcp;


/* The token type (%%TOKEN) */

typedef struct TmToken {
    int code;
    TmSrcp srcp;
    char *text;
    int begin;
    int end;
} TmToken;

#endif

