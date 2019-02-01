#ifndef _pmkCommon_H_
#define _pmkCommon_H_
/* pmkCommon.h

   Common definitions for pmk

   This file is generated from information in 'pmk.tmk'

*/

/* The import section (%%IMPORT) */

#include "tmkCommon.h"

/* The source position type (%%SRCP) */

      /* ... must be imported! */


/* The token type (%%TOKEN) */

typedef struct PmkToken {
    int code;
    TmkSrcp srcp;
    char *sval;
    int ival;
    long fpos;
    long length;
} PmkToken;

#endif

