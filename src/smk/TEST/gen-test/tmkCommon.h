#ifndef _tmkCommon_H_
#define _tmkCommon_H_
/* tmkCommon.h

   Common definitions for tmk

   This file is generated from information in 'tmk.tmk'

*/

/* The import section (%%IMPORT) */

typedef int TmkNatural;

/* The source position type (%%SRCP) */

typedef struct TmkSrcp {
    TmkNatural line;
    TmkNatural col;
    TmkNatural file;
} TmkSrcp;


/* The token type (%%TOKEN) */

typedef struct TmkToken {
    int code;
    TmkSrcp srcp;
    char *sval				/* string value */;
    int ival				/* integer value */;
    long fpos				/* file pos of target language code */;
    long length			     /* length of target language code */;
} TmkToken;

#endif

