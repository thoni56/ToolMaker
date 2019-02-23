#ifndef _pmkParse_h_
#define _pmkParse_h_
/*----------------------------------------------------------------------*\

  pmkParse.h

  Parser interface

\*----------------------------------------------------------------------*/


/* Token and Srcp definition */
#include "pmkCommon.h"

/* External functions */
extern void pmkParse(void); /* Parser */

/* Export */
#line 34 "pmk.pmk"


extern TmkSrcp
    rulesSrcp,
    declarationsSrcp,
    exportSrcp,
    scannerSrcp,
    insertsymbolSrcp,
    deletesymbolSrcp;


#endif
