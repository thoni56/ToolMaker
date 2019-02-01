#ifndef _lmkCommon_H_
#define _lmkCommon_H_
/* lmkCommon.h

   Common definitions for lmk

   This file is generated from information in 'lmk.tmk'

*/

/* The import section (%%IMPORT) */

#include "../tmk/tmkCommon.h"

/* The source position type (%%SRCP) */

      /* ... must be imported! */


/* The token type (%%TOKEN) */

typedef struct LmkToken {
    int code;
    TmkSrcp srcp;
    char *sval;
    int ival;
    long fpos;
    long length;
} LmkToken;

#endif


