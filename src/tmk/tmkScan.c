/*----------------------------------------------------------------------*\

	tmkScan.c

	ScannerMaker generated scanner

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include "tmk.h"
#include "tmk_i.h"

/* END %%IMPORT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tmkScan.h"

/* Local imports */
extern int tmkScReader( tmkScContext smThis, unsigned char *smBuffer, unsigned int smLength );
extern int tmkScPreHook( tmkScContext smThis, TmkToken *smToken );
extern int tmkScAction( tmkScContext smThis, int smInternalCode, TmkToken *smToken );

/* System dependencies */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;


/* START of scanning tables */


/*
 * MAP
 *
 * [character] -> character
 *
 */

static UByte1 smMap[256]={
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79
,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
,96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79
,80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127
,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143
,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159
,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175
,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191
,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207
,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223
,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207
,208,209,210,211,212,213,214,247,216,217,218,219,220,221,222,255
}
;


/*
 * SCANNER
 *
 * [scanner] -> state
 */

static UByte1 smScanner[1]={
0
}
;

/*
 * ACCEPT (internal token code)
 *
 * [state] -> icode
 */

static UByte1 smAccept[113]={
0,28,2,19,1,18,4,20,27,3,23,5,7,9,6,8
,10,21,11,12,13,14,15,16,22,17,0,18,23,0,18,23
,0,18,23,0,18,23,0,18,23,18,23,18,23,18,23,18
,23,18,18,23,18,23,18,23,18,23,18,23,18,23,18,23
,18,23,23,23,18,23,18,23,18,23,18,23,18,23,18,23
,23,23,18,23,18,23,23,23,23,23,23,18,23,18,23,23
,23,23,18,23,18,23,23,23,18,23,18,23,18,23,18,23
,23
}
;

/*
 * EXTERNAL TOKEN CODE
 *
 * [icode] -> ecode
 */

static UByte1 smTokenCode[28]={
3,4,5,6,7,10,11,12,13,14,15,16,17,18,19,22
,23,21,8,9,20,20,20,1,2,0,0,0
}
;

/*
 * EOT and Unknown
 *
 * [scanner] -> icode
 *
 */

static UByte1 smEOTCode[1]={
24
}
;
static UByte1 smUnknownCode[1]={
23
}
;

/*
 * DFA
 */

static UByte2 smDFArow[113]={
0,33,66,99,66,132,165,66,198,231,264,231,231,231,231,231
,264,264,264,231,264,264,231,264,264,231,297,330,363,396,429,462
,495,528,561,594,627,660,693,726,759,792,825,858,891,924,957,990
,1023,1056,1089,1122,1155,1188,1221,1254,1287,1320,1353,1386,1419,1452,1485,1518
,1551,1584,1617,1650,1683,1716,1749,1782,1815,1848,1881,1914,1947,1980,2013,2046
,2079,2112,2145,2178,2211,2244,2277,2310,2343,2376,2409,2442,2475,2508,2541,2574
,2607,2640,2673,2706,2739,2772,2805,2838,2871,2904,2937,2970,3003,3036,231,3069
,3102
}
;
static UByte1 smDFAcol[256]={
0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,2,2,2,2,3,2,4,2,2,2,2,5,6,2,2
,7,7,7,7,7,7,7,7,7,7,2,8,2,2,2,2
,2,9,10,11,12,13,14,15,15,16,15,17,18,19,20,21
,22,15,23,24,25,26,27,28,15,29,15,2,30,2,2,31
,2,9,10,11,12,13,14,15,15,16,15,17,18,19,20,21
,22,15,23,24,25,26,27,28,15,29,15,2,2,2,2,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
,32,32,32,32,32,32,32,0,32,32,32,32,32,32,32,0
,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
,32,32,32,32,32,32,32,0,32,32,32,32,32,32,32,0
}
;
  
static UByte1 smDFAval[3135]={
1,1,113,26,29,2,32,3,4,5,110,68,110,110,70,110
,110,110,110,110,27,110,104,50,72,110,110,110,110,110,113,113
,30,
1,1,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,1,
113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,
113,113,113,113,113,113,113,3,113,113,113,113,113,113,113,113
,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,108,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,112,51,10,10
,92,10,10,10,10,99,10,83,69,85,10,10,10,10,113,113
,10,
8,113,8,8,8,8,8,8,8,8,8,8,8,8,8,8
,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
,8,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,6,113,113,113,113,113,113,113,113,113,113,113,113
,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,
113,113,113,113,113,113,113,110,113,56,110,110,110,110,110,110
,110,110,110,110,110,9,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,16,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
29,113,29,29,7,29,29,29,29,29,29,29,29,29,29,29
,29,29,29,29,29,29,29,29,29,29,29,29,29,29,35,29
,29,
1,1,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,30,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,17,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,8,113,113,113,113,113,113,113,113,113
,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113
,113,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,11,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,18,10,10,10,10,10,10,10,113,113
,10,
29,113,29,29,29,29,29,29,29,29,29,29,29,29,29,29
,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29
,29,
113,113,113,113,113,113,113,110,113,110,110,110,110,12,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,17,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,113
,110,
113,113,113,113,113,113,113,110,113,110,110,110,110,13,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,20,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,14,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,21,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,15,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,23,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,19,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,24,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,22,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,24,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,25,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,33,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,28,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,36,110,110,110
,110,110,74,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,31,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,39,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,34,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,41,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,37,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,43,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,40,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,45,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,42,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,47,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,44,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,49,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,46,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,48,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,48,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,52,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,53,10,10,10,10,10,55,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,54,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,57,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,58,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,59,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,60,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,61,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,62,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,63,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,64,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,65,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,66,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,67,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,76,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,101,10,10
,10,10,10,10,10,10,10,10,10,10,71,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,78,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,105,10,10
,10,10,10,10,10,73,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,75,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,77,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,79,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,80,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,81,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,82,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,86,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,84,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,87,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,88,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,89,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,10,10,90,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,91,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,94,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,93,110,110,110,110,110,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,95,10,10,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,96,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,97,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,98,110,110,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,10,10,10,102,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,100,110,110,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,10,10,10,10,103,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,110,113,110,110,110,110,110,110,110
,110,110,110,110,110,110,110,110,110,106,110,110,110,110,113,38
,110,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,10,10
,107,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,10,109,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10,
113,113,113,113,113,113,113,113,113,10,10,10,10,111,10,10
,10,10,10,10,10,10,10,10,10,10,10,10,10,10,113,113
,10
}
;
  


/* END of scanning tables */






/*
 * Source position calculation 
 */

static void smSourcePosition(
     tmkScContext smThis,
     unsigned char *smAt,
     unsigned char *smEnd)
{
  if(smThis->smPosContinue<smEnd) {
    if(smThis->smPosContinue>smAt) smAt=smThis->smPosContinue;
    smThis->smNextPosition+=smEnd-smAt;
    for(;smAt<smEnd;smAt++) 
      if(*smAt==10) {
	smThis->smPosLine=smAt;
	smThis->smNextLine++;
      }

    smThis->smNextColumn=smEnd-smThis->smPosLine;
    smThis->smPosContinue=smEnd;
  }
}

static void smRewindSourcePosition(
     tmkScContext smThis,
     unsigned char *smAt,
     unsigned char *smEnd)
{
  if(smThis->smPosContinue>smEnd) return;
  smThis->smNextPosition-=smEnd-smAt;
  while(smAt<smEnd--) if(*smEnd==10) smThis->smNextLine--;
  while(smThis->smBegining<smEnd) 
    if(*smEnd==10) {
      smThis->smPosLine=smEnd;
      break; 
    }
    else smEnd--;
  if(smAt<smThis->smPosLine) smThis->smPosLine=smThis->smPosPrevLine;
  smThis->smNextColumn=smAt-smThis->smPosLine;
  smThis->smPosContinue=smAt;
}


/*
 * int smReadBuffer(SMContext smThis)
 *
 * SmThis function reads charcters using the reader into the buffer in a
 * context. The buffer is enlarged if the current buffer is full
 * (smEnd-smText==smSize) or reduced if current buffer is larger than
 * the standard buffer size and the token may fit the standard buffer
 * (smEnd-smText<smTokenSize AND smSize>smTokenSize). The function
 * returns the number of characters read into the buffer.
 *
 */

static int smReadBuffer(tmkScContext smThis)
{
  long length;
  int size;
  long mod;

  if(smThis->smBegining!=smThis->smText) {
    /* Move data to beginning of buffer */
    length=smThis->smEnd-smThis->smText;
    memcpy((void *)smThis->smBegining,(void *)smThis->smText,(size_t)length);
    if(length<1024 && smThis->smSize>1024) {
      /* Reduce buffer size */
      smThis->smSize=1024;
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,(size_t)1024+1);
    }
  }
  else if(smThis->smBegining+smThis->smSize==smThis->smEnd) {
    /* Try to enlarge buffer */
    if(smThis->smSize==524288) {
      /* Cut Buffer */
      smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
      memcpy((void *)smThis->smBegining,(void *)(smThis->smEnd-1024),(size_t)1024);
      mod=smThis->smEnd-smThis->smBegining-1024;
      smThis->smContinue-=mod;
      smThis->smEnd-=mod;
      smThis->smPosPrevLine-=mod;
      smThis->smPosLine-=mod;
      smThis->smPosContinue-=mod;
      smThis->smBufferOverflow+=mod;
    }
    else {
      unsigned char *begining = smThis->smBegining;
      size=smThis->smSize*1.5;
      if(size>524288) size=524288;
      /* Enlarge buffer */
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,(size_t)size+1);
      if(smThis->smBegining==NULL) {
	/* Cut Buffer */
	smThis->smBegining = begining;	/* Restore to original buffer */
	smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
	memcpy((void *)smThis->smBegining, (void *)(smThis->smEnd-1024), (size_t)1024);
	mod=smThis->smEnd-smThis->smBegining-1024;
	smThis->smContinue-=mod;
	smThis->smEnd-=mod;
	smThis->smPosPrevLine-=mod;
	smThis->smPosLine-=mod;
	smThis->smPosContinue-=mod;
        smThis->smBufferOverflow+=mod;
      }
      else
	smThis->smSize=size;
    }
  }
  if(smThis->smBegining!=smThis->smText) {
    mod=smThis->smText-smThis->smBegining;
    smThis->smContinue-=mod;
    smThis->smEnd-=mod;
    smThis->smPosPrevLine-=mod;
    smThis->smPosLine-=mod;
    smThis->smPosContinue-=mod;
    smThis->smText-=mod;
  }
  length=smThis->smSize-(smThis->smEnd-smThis->smBegining);
  length=tmkScReader(smThis,smThis->smEnd,(unsigned int)length);
  if(length<0) return length;
  smThis->smEnd+=length;
  return length;
}

/*
 * SMContext SMNew( tmkScScanner scanner )
 *
 * Create a new context.
 *
 */

tmkScContext tmkScNew(tmkScScanner smScanner)
{
  tmkScContext smThis;

  smThis=(tmkScContext)malloc((size_t)sizeof(tmkScContextItem));
  if(smThis==NULL) {
    return NULL;
  }
  smThis->smBegining=(unsigned char *)malloc((size_t)1024+1);
  if(smThis->smBegining==NULL) {
    free((char *)smThis);
    return NULL;
  }
  smThis->smSize=1024;
  smThis->smContinue=smThis->smBegining;
  smThis->smEnd=smThis->smBegining;
  smThis->smPosPrevLine=smThis->smBegining-1;
  smThis->smPosLine=smThis->smBegining-1;
  smThis->smPosContinue=smThis->smBegining;
  smThis->smText=smThis->smBegining;
  
  smThis->smLength=0;
  smThis->smNextLine=1;
  smThis->smNextColumn=1;
  smThis->smNextPosition=0;
  smThis->smLine=1;
  smThis->smColumn=1;
  smThis->smPosition=0;
  smThis->smScanner=smScanner;
  smThis->smBegining[0]=0;
  return smThis;
}

/*
 * void SMDelete( SMContext smThis )
 *
 * Destroy a context and associated buffer.
 *
 */

void tmkScDelete(tmkScContext smThis)
{
  free((char *)smThis->smBegining);
  free((char *)smThis);
}

/*
 * int SMSkip( SMContext smThis, int smLength )
 *
 * Enlarge/reduce the current token in a context with length characters.
 * If length is less than zero reduce the token, if length is greater
 * than zero enlarge the token.
 *
 */

int tmkScSkip(
     tmkScContext smThis,
     int smLength)
{
  int empty;

  if(smLength>0) {
    empty=smThis->smEnd-smThis->smContinue;
    if(empty<smLength) {
      empty=smReadBuffer(smThis);
      if(empty<0) return empty;
      empty=smThis->smEnd-smThis->smContinue;
      if(empty<smLength) smLength=empty;
    }
    smSourcePosition(smThis,smThis->smContinue,smThis->smContinue+smLength);
    smThis->smContinue+=smLength;
    smThis->smLength+=smLength;
  }
  else if(smLength<0) {
    smLength= -smLength;
    if(smLength>smThis->smLength) smLength=smThis->smLength;
    smRewindSourcePosition(smThis,smThis->smContinue-smLength,smThis->smContinue);
    smThis->smContinue-=smLength;
    smThis->smLength-=smLength;
    }
  return smLength;
}

int tmkScModify(
     tmkScContext smThis,
     unsigned char *smBuffer,
     int smLength)
{
  if(smLength<0) {
/* This code is identical to smSkip but no source position is rewinded */
    smLength= -smLength;
    if(smLength>smThis->smLength) smLength=smThis->smLength;
    smThis->smContinue-=smLength;
    smThis->smLength-=smLength;
/***********************************************************************/
    memcpy((void *)smThis->smContinue,(void *)smBuffer,(size_t)smLength);
    return smLength;
  }
  else if(smLength>0) {
    int length1;
    int length2;
    
    for(length2=smLength;(length1=tmkScSkip(smThis,length2));length2-=length1) {
      if(length1<0) return length1;
      memcpy((void *)(smThis->smContinue-length1),(void *)smBuffer,(size_t)length1);
      smBuffer+=length1;
    }
    return smLength-length2;
  }
  return smLength;
}

int tmkScCopy(
     tmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smFrom,
     unsigned int smTo)
{
  if(smFrom>smThis->smLength) smFrom=smThis->smLength;
  if(smTo>smThis->smLength) smTo=smThis->smLength;
  memcpy((void *)smBuffer,(void *)(smThis->smText+smFrom),(size_t)smTo-smFrom);
  return smTo-smFrom;
}

int tmkScMapCopy(
     tmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smFrom,
     unsigned int smTo)
{
  int n;
  int len;
  unsigned char *at;

  if(smFrom>smThis->smLength) smFrom=smThis->smLength;
  if(smTo>smThis->smLength) smTo=smThis->smLength;
  len=0;
  for(n=smFrom,at=smThis->smText+smFrom;n<smTo;n++) {
*smBuffer++=smMap[*at++];
    len++;
  }
  return len;
}

void tmkScScrScanner(
     tmkScScanner smScanner,
     int smOnOff)
{
}

void tmkScScrToken(
     tmkScScanner smScanner,
     int smCode,
     int smOnOff)
{
}

void tmkScScrRule(
     tmkScScanner smScanner,
     int smCode,
     int smOnOff)
{
}

int tmkScan(
     tmkScContext smThis,
     TmkToken *smToken)
{
  unsigned char *at;
  unsigned char *end;
  unsigned char *rew_at;
  unsigned char ch;
  int state;
  int rew_state;
  int code;

  do {				/* Skip loop */
    smThis->smLine=smThis->smNextLine;
    smThis->smColumn=smThis->smNextColumn;
    smThis->smPosition=smThis->smNextPosition;
    tmkScPreHook(smThis,smToken);
    end=(smThis->smEnd);
    smThis->smText=smThis->smContinue;
    smThis->smBufferOverflow=0;
    smToken->srcp.line=smThis->smNextLine;
    smToken->srcp.col=smThis->smNextColumn;
    smThis->smPosPrevLine=smThis->smPosLine;
    rew_at=smThis->smText;
    do {			/* Continue loop */
      rew_state=113;
      rew_at++;
      at=(smThis->smContinue);
      state=smScanner[smThis->smScanner];
      for (;;) {
	if(at==end) {
	  int mod;
	  
	  if(state>=113) state-=113+1;
	  smThis->smContinue=end;
	  mod=smReadBuffer(smThis);
	  if(mod<0) return mod;
	  rew_at-=end-smThis->smContinue;
	  at=smThis->smContinue;
	  end=smThis->smEnd;
          if(at==end) 
	    break;
        }
	  ch = *at++;
{

  
    
      
  state=smDFAval[smDFArow[state]+smDFAcol[ch]];
      
    
  
}
	  if(state>=113) break;
	  if(smAccept[state]>0) {
	    rew_state=state;
	    rew_at=at;
	  }
      }
      if(rew_state==113) {
        if(rew_at>end) {
  	  code=smEOTCode[smThis->smScanner];
	  rew_at=end;
        }
        else
	  code=smUnknownCode[smThis->smScanner];
      }	
      else
	code=smAccept[rew_state]-1;	
      smThis->smContinue=rew_at;
      smThis->smLength=smThis->smContinue-smThis->smText;
      smSourcePosition(smThis,smThis->smText,smThis->smContinue);
      smToken->code=smTokenCode[code]-1;
      code=tmkScAction(smThis,code,smToken);
    } while(code<-1);
  } while(code<0);
  return smToken->code=code;
}
