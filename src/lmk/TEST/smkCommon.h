#ifndef _smkCommon_H_
#define _smkCommon_H_
/* smkCommon.h

   Common definitions for smk

   This file is generated from information in 'smk.tmk'

*/

/* The import section (%%IMPORT) */

#include "tmkCommon.h"
#include "name.h"
#include "action.h"

/* The source position type (%%SRCP) */

      /* ... must be imported! */


/* The token type (%%TOKEN) */

typedef struct SmkToken {
    int code;
    TmkSrcp srcp;
    Action action;
    Name name;
    double fnumber;
    int inumber;
} SmkToken;

#endif


