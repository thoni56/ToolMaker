/*----------------------------------------------------------------------*\

	tmkScan.c

	ScannerMaker generated scanner

\*----------------------------------------------------------------------*/


#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "tmkScan.h"

/* Local imports */
extern int tmkScReader( /* SMContext smThis, unsigned char smBuffer, unsigned int smLength */ );
extern int tmkScPreHook( /* SMContext smThis, TMToken *smToken */ );
extern int tmkScAction( /* SMContext smThis, int smInternalCode, TMToken *smToken */ );

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
,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239
,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
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

static UByte1 smAccept[114]={
0,28,2,19,1,18,4,20,3,23,27,5,7,9,6,8
,10,21,11,12,13,14,15,16,22,17,0,18,23,0,18,23
,0,18,23,0,18,23,0,18,23,0,18,23,18,23,18,23
,18,23,18,18,23,18,23,18,23,18,23,18,23,18,23,18
,23,18,23,23,23,18,23,18,23,18,23,18,23,18,23,18
,23,23,23,18,23,18,23,23,23,23,23,23,18,23,18,23
,23,23,23,18,23,18,23,23,23,18,23,18,23,18,23,18
,23,23
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

static UByte2 smDFArow[114]={
0,33,66,99,66,132,165,66,198,231,66,198,198,198,198,198
,231,231,231,198,231,231,198,231,231,198,264,297,330,363,396,429
,462,495,528,561,594,627,660,693,726,759,792,825,858,891,924,957
,990,1023,1056,1089,1122,1155,1188,1221,1254,1287,1320,1353,1386,1419,1452,1485
,1518,1551,1584,1617,1650,1683,1716,1749,1782,1815,1848,1881,1914,1947,1980,2013
,2046,2079,2112,2145,2178,2211,2244,2277,2310,2343,2376,2409,2442,2475,2508,2541
,2574,2607,2640,2673,2706,2739,2772,2805,2838,2871,2904,2937,2970,3003,3036,198
,3069,3102
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
,32,32,32,32,32,32,32,0,32,32,32,32,32,32,32,32
,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
,32,32,32,32,32,32,32,0,32,32,32,32,32,32,32,32
}
;
  
static UByte1 smDFAval[3135]={
1,1,114,26,29,2,32,3,4,5,111,69,111,111,71,111
,111,111,111,111,27,111,105,51,73,111,111,111,111,111,114,114
,30,
1,1,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,1,
114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,
114,114,114,114,114,114,114,3,114,114,114,114,114,114,114,114
,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,109,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,113,52,9,9
,93,9,9,9,9,100,9,84,70,86,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,6,114,114,114,114,114,114,114,114,114,114,114,114
,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,
114,114,114,114,114,114,114,111,114,57,111,111,111,111,111,111
,111,111,111,111,111,8,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,16,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
29,114,29,29,7,29,29,29,29,29,29,29,29,29,29,29
,29,29,29,29,29,29,29,29,29,29,29,29,29,29,35,29
,29,
1,1,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,30,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,17,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,38,114,114,114,114,114,114,114,114,114
,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114
,114,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,11,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,18,9,9,9,9,9,9,9,114,114
,9,
29,114,29,29,29,29,29,29,29,29,29,29,29,29,29,29
,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29
,29,
114,114,114,114,114,114,114,111,114,111,111,111,111,12,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,17,9,9,9,9,9,114,114
,9,
38,10,38,38,38,38,38,38,38,38,38,38,38,38,38,38
,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38
,38,
114,114,114,114,114,114,114,111,114,111,111,111,111,13,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,20,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,114
,111,
114,114,114,114,114,114,114,111,114,111,111,111,111,14,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,21,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,15,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,23,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,19,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,24,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,22,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,24,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,25,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,33,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,28,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,36,111,111,111
,111,111,75,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,31,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,39,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,34,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,42,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,37,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,44,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,40,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,46,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,43,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,48,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,45,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,50,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,47,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,49,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,49,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,53,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,54,9,9,9,9,9,56,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,55,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,58,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,59,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,60,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,61,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,62,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,63,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,64,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,65,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,66,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,67,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,68,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,77,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,102,9,9
,9,9,9,9,9,9,9,9,9,9,72,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,79,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,106,9,9
,9,9,9,9,9,74,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,76,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,78,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,80,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,81,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,82,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,83,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,87,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,85,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,88,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,89,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,90,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,9,9,91,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,92,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,95,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,94,111,111,111,111,111,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,96,9,9,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,97,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,98,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,99,111,111,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,103,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,101,111,111,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,9,9,9,9,104,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,111,114,111,111,111,111,111,111,111
,111,111,111,111,111,111,111,111,111,107,111,111,111,111,114,41
,111,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,9,9
,108,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,9,110,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9,
114,114,114,114,114,114,114,114,114,9,9,9,9,112,9,9
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,114,114
,9
}
;
  


/* END of scanning tables */






/*
 * Source position calculation 
 */

static void smSourcePosition(smThis,smAt,smEnd) 
     tmkScContext smThis;
     unsigned char *smAt;
     unsigned char *smEnd;
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

static void smRewindSourcePosition(smThis,smAt,smEnd)
     tmkScContext smThis;
     unsigned char *smAt;
     unsigned char *smEnd;
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

static int smReadBuffer(smThis)
     tmkScContext smThis;
{
  long length;
  int size;
  long mod;

  if(smThis->smBegining!=smThis->smText) {
    /* Move data to beginning of buffer */
    length=smThis->smEnd-smThis->smText;
    memcpy((void *)smThis->smBegining,(void *)smThis->smText,length);
    if(length<1024 && smThis->smSize>1024) {
      /* Reduce buffer size */
      smThis->smSize=1024;
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,1024+1);
    }
  }
  else if(smThis->smBegining+smThis->smSize==smThis->smEnd) {
    /* Try to enlarge buffer */
    if(smThis->smSize==524288) {
      /* Cut Buffer */
      smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
      memcpy((void *)smThis->smBegining,(void *)(smThis->smEnd-1024),1024);
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
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,size+1);
      if(smThis->smBegining==NULL) {
	/* Cut Buffer */
	smThis->smBegining = begining;	/* Restore to original buffer */
	smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
	memcpy((void *)smThis->smBegining, (void *)(smThis->smEnd-1024), 1024);
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

tmkScContext tmkScNew(smScanner)
	tmkScScanner smScanner;
{
  tmkScContext smThis;

  smThis=(tmkScContext)malloc(sizeof(tmkScContextItem));
  if(smThis==NULL) {
    return NULL;
  }
  smThis->smBegining=(unsigned char *)malloc(1024+1);
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

void tmkScDelete(smThis)
     tmkScContext smThis;
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

int tmkScSkip(smThis,smLength)
     tmkScContext smThis;
     int smLength;
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

int tmkScModify(smThis,smBuffer,smLength)
     tmkScContext smThis;
     unsigned char *smBuffer;
     int smLength;
{
  if(smLength<0) {
/* This code is identical to smSkip but no source position is rewinded */
    smLength= -smLength;
    if(smLength>smThis->smLength) smLength=smThis->smLength;
    smThis->smContinue-=smLength;
    smThis->smLength-=smLength;
/***********************************************************************/
    memcpy((void *)smThis->smContinue,(void *)smBuffer,smLength);
    return smLength;
  }
  else if(smLength>0) {
    int length1;
    int length2;
    
    for(length2=smLength;(length1=tmkScSkip(smThis,length2));length2-=length1) {
      if(length1<0) return length1;
      memcpy((void *)(smThis->smContinue-length1),(void *)smBuffer,length1);
      smBuffer+=length1;
    }
    return smLength-length2;
  }
  return smLength;
}

int tmkScCopy(smThis,smBuffer,smFrom,smTo)
     tmkScContext smThis;
     unsigned char *smBuffer;
     unsigned int smFrom;
     unsigned int smTo;
{
  if(smFrom>smThis->smLength) smFrom=smThis->smLength;
  if(smTo>smThis->smLength) smTo=smThis->smLength;
  memcpy((void *)smBuffer,(void *)(smThis->smText+smFrom),smTo-smFrom);
  return smTo-smFrom;
}

int tmkScMapCopy(smThis,smBuffer,smFrom,smTo)
     tmkScContext smThis;
     unsigned char *smBuffer;
     unsigned int smFrom;
     unsigned int smTo;
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

void tmkScScrScanner(smScanner, smOnOff)
     tmkScScanner smScanner;
     int smOnOff;
{
}

void tmkScScrToken(smScanner, smCode, smOnOff)
     tmkScScanner smScanner;
     int smCode;
     int smOnOff;
{
}

void tmkScScrRule(smScanner, smCode, smOnOff)
     tmkScScanner smScanner;
     int smCode;
     int smOnOff;
{
}

int tmkScan(smThis,smToken)
     tmkScContext smThis;
     TmkToken *smToken;
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
      rew_state=114;
      rew_at++;
      at=(smThis->smContinue);
      state=smScanner[smThis->smScanner];
      for (;;) {
	if(at==end) {
	  int mod;
	  
	  if(state>=114) state-=114+1;
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
	  if(state>=114) break;
	  if(smAccept[state]>0) {
	    rew_state=state;
	    rew_at=at;
	  }
      }
      if(rew_state==114) {
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
