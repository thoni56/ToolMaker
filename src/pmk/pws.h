#ifndef _pws
#define _pws

#include <stdio.h>
#include "pmkList.h"
#include "tmk.h"

#define pws_width_max 79
#define pws_bits_max 16

#define SeriousErr (pmkSeverity() & (sevERR | sevFAT | sevSYS))

#define min(a, b) ((a) < (b)? (a): (b))
#define max(a, b) ((a) > (b)? (a): (b))
/*-----------------------------------------------------------------------------
 * nofi - Computes the number of figures in an integer.
 *-----------------------------------------------------------------------------
 */
#define nofi(n) ((n) < 10? 1: ((n) < 100? 2: ((n) < 1000? 3: ((n) < 10000? 4:\
((n) < 100000? 5: 6)))))

extern int pwsGrm;
char *inFiles[3];
extern FILE *pwsLog;
extern FILE *pmTbl;
extern char *vocFileName;

#endif
