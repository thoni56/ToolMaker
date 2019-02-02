/*----------------------------------------------------------------------*\

	smkParse.c

	ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include <stdio.h>
#include "smk_i.h"
#include "smkScan.h"
#include "smkList.h"
#include "ast.h"
#include "definition.h"
#include "name.h"
#include "scanner.h"
#include "token.h"
#include "voc.h"
#include "set.h"
#include "map.h"
#include "pack.h"
#include "action.h"
extern smkContext lexContext;
/* END %%IMPORT */

#include <strings.h>
#include <memory.h>
#include <setjmp.h>

#include "smkParse.h"

#define PMTRUE 1
#define PMFALSE 0
typedef unsigned char PmBoolean; /* For logical values */

/* System dependencies */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;

/* Token definition */
#include "smkCommon.h"

/* %%ATTRIBUTES - The semantic attributes for grammar symbols */
typedef struct smkGrammar {
    Action action;
    AST ast;
    Name name;
    double fnumber;
    int inumber;
    TmkSrcp srcp;
} smkGrammar;

/* END %%ATTRIBUTES */

/* Parser constants *\
\* ---------------- */
#define ERROR_ACT 0			/* Action - Error */
#define SHIFT_ACT 1			/* Action - Shift */
#define SHIFTRED_ACT 2		/* Action - Shift_Reduce */
#define REDUCE_ACT 3		/* Action - Reduce */
#define ACCEPT_ACT 4		/* Action - Accept */

#define ERR_SYM 0		/* Error token */
#define ENDMARK 1		/* End of file token code */

/* Recovery method *\
\* --------------- */
#define NONE_REC 0		/* No recovery found */
#define IN_REC 1		/* Insertion of symbol(s) */
#define DEL_REC 2		/* Deletion of symbol(s) */
#define REP_REC 3		/* Replacement of symbol(s) */
#define BAK_REC 4		/* Stack backup */
#define HALT_REC 5		/* System halted */

/* Error class *\
\* ----------- */
#define LEX_ERR 1		/* Non valid scanner symbol found */
#define SYN_ERR 2		/* Normal syntax error */
#define OFLW_ERR 3		/* Parse stack overflow */
#define TAB_ERR 4		/* Parse table error */
	   
/* Error severity *\
\* -------------- */
#define WAR_SEV 1		/* Warnings */
#define ERR_SEV 2		/* Repairable error */
#define FAT_SEV 3		/* Fatal error */
#define SYS_SEV 4		/* System & limit error */

/* Parser constants *\
\* ---------------- */
#define SccMax 71		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 71		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 84		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 131		/* Number of productions */
#define PmStkMax 32		/* Parse stack size */
#define	PmLaMax 5		/* Look-ahead length */
#define	PmCost 5		/* Shifting cost */

/* Types *\
\* ----- */
typedef unsigned char TermSet[(Terms + TermMin + 7) >> 3]; /* Terminal set */
typedef UByte1 ParseStack[PmStkMax]; /* Parse stack */

/* Terminal table *\
\* -------------- */

typedef struct {
    UByte1 tsym;		/* Normal continuation */
    UByte1 ssym;		/* Separator continuation */
} ContRec;

typedef struct {
    ContRec cont[84];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[1552];		/* Action table */
    UByte1 actCheck[1585];	/* Row Displacement Check Vector*/
    UByte2 actRix[84];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{11,529,683,434,683,683,690,698,706,257,161,514,683,683,683,683,683,683
,683,683,683,683,683,683,683,683,683,683,683,683,683,683,683,683,683,683
,683,683,683,683,683,714,273,442,291,683,683,233,547,274,683,683,683,683
,1050,659,4,659,659,683,683,291,585,81,683,770,305,659,818,882,906,930,659
,794,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,1050,802,659
,810,898,1034,409,363,363,81,1010,1018,299,129,345,858,962,866,1026,1050
,651,242,651,651,786,946,363,401,730,986,770,305,651,818,882,906,930,651
,794,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,1050,802,651
,810,898,1034,1042,129,345,738,1010,1018,129,345,233,858,962,866,1026,449
,393,1042,299,778,786,946,289,770,305,986,818,882,906,930,394,794,826,834
,842,850,874,890,914,922,938,954,970,978,994,1002,1050,802,1042,810,898
,1034,1042,355,355,346,1010,1018,138,619,131,858,962,866,1026,483,722,530
,99,209,786,946,355,505,417,986,626,193,522,131,483,483,483,483,131,483
,483,483,483,483,483,483,483,483,483,483,483,483,483,483,538,483,0,483,483
,483,0,483,561,0,483,483,0,483,483,483,483,483,483,499,0,595,0,0,483,483
,0,83,483,483,0,0,83,0,499,499,499,499,602,499,499,499,499,499,499,499,499
,499,499,499,499,499,499,499,0,499,185,499,499,499,0,499,403,403,499,499
,0,499,499,499,499,499,499,131,0,595,0,0,499,499,0,369,499,499,0,0,0,0,818
,882,906,930,602,794,826,834,842,850,874,890,914,922,938,954,970,978,994
,1002,0,802,185,810,898,1034,0,138,403,403,1010,1018,0,131,131,858,962,866
,1026,491,0,595,0,0,786,946,0,369,131,986,0,0,0,0,491,491,491,491,602,491
,491,491,491,491,491,491,491,491,491,491,491,491,491,491,0,491,185,491,491
,491,0,491,0,0,491,491,0,491,491,491,491,491,491,499,0,0,0,0,491,491,0,0
,491,491,0,0,0,0,499,499,499,499,0,499,499,499,499,499,499,499,499,499,499
,499,499,499,499,499,0,499,0,499,499,499,0,499,0,0,499,499,0,499,499,499
,499,499,499,131,0,0,0,0,499,499,0,0,499,499,0,0,0,0,818,882,906,930,0,794
,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,0,802,0,810,898
,1034,0,138,0,0,1010,1018,307,131,131,858,962,866,1026,0,283,0,0,0,786,946
,0,0,131,986,770,305,0,818,882,906,930,283,794,826,834,842,850,874,890,914
,922,938,954,970,978,994,1002,1050,802,0,810,898,1034,0,129,345,0,1010,1018
,0,0,0,858,962,866,1026,0,0,0,307,0,786,946,0,770,305,986,818,882,906,930
,0,794,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,1050,802
,0,810,898,1034,0,0,0,0,1010,1018,0,0,0,858,962,866,1026,0,0,0,0,0,786,946
,0,770,305,986,818,882,906,930,0,794,826,834,842,850,874,890,914,922,938
,954,970,978,994,1002,1050,802,0,810,898,1034,0,0,0,0,1010,1018,0,0,0,858
,962,866,1026,0,0,0,0,0,786,946,0,0,0,986,818,882,906,930,0,794,826,834
,842,850,874,890,914,922,938,954,970,978,994,1002,0,802,0,810,898,1034,0
,0,0,0,1010,1018,0,371,371,858,962,866,1026,0,635,0,329,233,786,946,0,0
,0,986,770,305,371,818,882,906,930,635,794,826,834,842,850,874,890,914,922
,938,954,970,978,994,1002,1050,802,635,810,898,1034,0,0,0,0,1010,1018,0
,0,0,858,962,866,1026,0,0,0,0,0,786,946,0,0,0,986,818,882,906,930,0,794
,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,0,802,0,810,898
,1034,0,0,0,0,1010,1018,0,411,411,858,962,866,1026,0,0,0,0,0,786,946,0,0
,0,986,818,882,906,930,0,794,826,834,842,850,874,890,914,922,938,954,970
,978,994,1002,0,802,0,810,898,0,0,138,0,0,1010,1018,0,0,0,858,962,866,1026
,0,0,0,0,0,786,946,0,0,131,986,818,882,906,930,0,794,826,834,842,850,874
,890,914,922,938,954,970,978,994,1002,0,802,0,810,898,1034,0,0,0,0,1010
,1018,0,0,0,858,962,866,1026,0,0,0,0,0,786,946,0,0,0,986,818,882,906,930
,0,794,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,0,802,0
,810,898,1034,0,0,0,0,1010,1018,0,0,0,858,962,866,1026,0,0,0,0,0,786,946
,0,0,0,986,818,882,906,930,0,794,826,834,842,850,874,890,914,922,938,954
,970,978,994,1002,0,802,0,810,898,0,0,0,0,0,1010,1018,0,0,0,858,962,866
,1026,0,0,0,0,0,786,946,0,0,0,986,818,882,906,930,0,794,826,834,842,850
,874,890,914,922,938,954,970,978,994,1002,0,802,0,810,898,0,0,0,0,0,1010
,1018,0,0,0,858,962,866,1026,0,0,0,0,0,786,946,0,0,0,986,818,882,906,930
,0,794,826,834,842,850,874,890,914,922,938,954,970,978,994,1002,0,802,0
,810,898,0,0,0,0,0,1010,1018,0,0,0,858,962,866,1026,0,0,0,0,0,786,946,0
,0,0,986,818,882,906,930,0,794,826,834,842,850,874,890,914,922,938,954,970
,978,994,1002,0,802,0,810,898,0,1050,138,131,131,1010,1018,131,138,0,858
,962,866,1026,131,131,131,131,0,786,946,131,131,131,986,131,0,0,131,131
,131,27,27,0,131,27,0,0,0,0,0,0,27,27,27,27,0,0,0,27,27,27,0,27,0,0,27,0
,27,138,131,131,0,0,131,0,0,0,0,0,0,0,131,131,131,0,0,0,131,131,131,0,131
,0,0,131,0,131,138,131,131,0,0,131,0,0,0,0,0,0,0,131,131,131,0,0,0,131,131
,131,0,131,0,0,131,0,131,138,131,131,0,0,131,0,0,0,0,0,0,0,131,131,131,0
,0,0,131,131,131,0,131,0,0,131,0,131,138,131,131,0,0,131,0,0,0,0,0,0,0,131
,131,131,0,0,0,131,131,131,0,131,0,0,131,0,131,138,131,131,0,0,131,0,0,0
,0,0,0,0,131,131,131,0,0,0,131,131,131,0,131,0,0,131,0,131,138,131,131,0
,0,131,0,0,0,0,0,0,0,131,131,131,0,0,0,131,131,131,0,131,0,0,131,0,131,138
,131,131,0,0,131,0,0,0,0,0,0,0,131,131,131,0,0,465,131,131,131,0,131,0,0
,131,0,131,138,131,131,0,473,131,0,0,0,0,0,0,0,131,131,131,0,0,0,131,131
,131,338,131,0,0,131,0,131,19,19,0,0,19,331,331,0,0,0,0,673,19,19,19,0,0
,0,19,19,19,0,19,0,331,19,331,19,51,51,0,0,51,0,0,0,0,0,0,0,51,51,51,0,0
,0,51,51,51,643,51,0,233,51,0,51,601,67,0,0,633,0,0,0,0,0,643,0,625,641
,657,0,0,0,617,649,67,0,665,0,0,67,0,609,643}
,
{8,64,30,48,30,30,30,30,30,30,18,18,30,30,30,30,30,30,30,30,30,30,30,30
,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,32,32,50,68,30,30,68
,52,67,30,30,30,30,69,29,1,29,29,30,30,68,71,8,30,29,29,29,29,29,29,29,29
,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,49,52,52
,7,29,29,14,60,60,29,29,29,29,72,39,73,39,39,29,29,52,47,33,29,39,39,39
,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39
,39,39,33,14,14,34,39,39,13,13,38,39,39,39,39,54,47,55,14,38,39,39,31,19
,19,39,19,19,19,19,56,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19
,35,19,19,19,31,11,11,58,19,19,74,66,74,19,19,19,19,15,36,24,6,19,19,19
,11,6,11,19,66,19,21,74,15,15,15,15,74,15,15,15,15,15,15,15,15,15,15,15
,15,15,15,15,26,15,84,15,15,15,84,15,5,84,15,15,84,15,15,15,15,15,15,16
,84,25,84,84,15,15,84,5,15,15,84,84,5,84,16,16,16,16,25,16,16,16,16,16,16
,16,16,16,16,16,16,16,16,16,84,16,25,16,16,16,84,16,59,59,16,16,84,16,16
,16,16,16,16,17,84,20,84,84,16,16,84,59,16,16,84,84,84,84,17,17,17,17,20
,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,84,17,20,17,17,17,84,17,12
,12,17,17,84,17,17,17,17,17,17,42,84,23,84,84,17,17,84,12,17,17,84,84,84
,84,42,42,42,42,23,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,84,42,23
,42,42,42,84,42,84,84,42,42,84,42,42,42,42,42,42,43,84,84,84,84,42,42,84
,84,42,42,84,84,84,84,43,43,43,43,84,43,43,43,43,43,43,43,43,43,43,43,43
,43,43,43,84,43,84,43,43,43,84,43,84,84,43,43,84,43,43,43,43,43,43,44,84
,84,84,84,43,43,84,84,43,43,84,84,84,84,44,44,44,44,84,44,44,44,44,44,44
,44,44,44,44,44,44,44,44,44,84,44,84,44,44,44,84,44,84,84,44,44,61,44,44
,44,44,44,44,84,65,84,84,84,44,44,84,84,44,44,65,65,84,65,65,65,65,65,65
,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,84,65,65,65,84,61,61,84
,65,65,84,84,84,65,65,65,65,84,84,84,61,84,65,65,84,28,28,65,28,28,28,28
,84,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,84,28,28,28,84,84
,84,84,28,28,84,84,84,28,28,28,28,84,84,84,84,84,28,28,84,40,40,28,40,40
,40,40,84,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,84,40,40,40
,84,84,84,84,40,40,84,84,84,40,40,40,40,84,84,84,84,84,40,40,84,84,84,40
,53,53,53,53,84,53,53,53,53,53,53,53,53,53,53,53,53,53,53,53,84,53,84,53
,53,53,84,84,84,84,53,53,84,53,53,53,53,53,53,84,27,84,27,27,53,53,84,84
,84,53,37,37,53,37,37,37,37,27,37,37,37,37,37,37,37,37,37,37,37,37,37,37
,37,37,37,27,37,37,37,84,84,84,84,37,37,84,84,84,37,37,37,37,84,84,84,84
,84,37,37,84,84,84,37,46,46,46,46,84,46,46,46,46,46,46,46,46,46,46,46,46
,46,46,46,84,46,84,46,46,46,84,84,84,84,46,46,84,46,46,46,46,46,46,84,84
,84,84,84,46,46,84,84,84,46,63,63,63,63,84,63,63,63,63,63,63,63,63,63,63
,63,63,63,63,63,84,63,84,63,63,84,84,63,84,84,63,63,84,84,84,63,63,63,63
,84,84,84,84,84,63,63,84,84,63,63,51,51,51,51,84,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,84,51,84,51,51,51,84,84,84,84,51,51,84,84,84,51,51
,51,51,84,84,84,84,84,51,51,84,84,84,51,45,45,45,45,84,45,45,45,45,45,45
,45,45,45,45,45,45,45,45,45,84,45,84,45,45,45,84,84,84,84,45,45,84,84,84
,45,45,45,45,84,84,84,84,84,45,45,84,84,84,45,57,57,57,57,84,57,57,57,57
,57,57,57,57,57,57,57,57,57,57,57,84,57,84,57,57,84,84,84,84,84,57,57,84
,84,84,57,57,57,57,84,84,84,84,84,57,57,84,84,84,57,62,62,62,62,84,62,62
,62,62,62,62,62,62,62,62,62,62,62,62,62,84,62,84,62,62,84,84,84,84,84,62
,62,84,84,84,62,62,62,62,84,84,84,84,84,62,62,84,84,84,62,22,22,22,22,84
,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,84,22,84,22,22,84,84,84,84
,84,22,22,84,84,84,22,22,22,22,84,84,84,84,84,22,22,84,84,84,22,9,9,9,9
,84,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,84,9,84,9,9,84,70,83,83,83,9,9,83,70,84
,9,9,9,9,83,83,83,83,84,9,9,83,83,83,9,83,84,84,83,70,83,0,0,84,70,0,84
,84,84,84,84,84,0,0,0,0,84,84,84,0,0,0,84,0,84,84,0,84,0,75,75,75,84,84
,75,84,84,84,84,84,84,84,75,75,75,84,84,84,75,75,75,84,75,84,84,75,84,75
,76,76,76,84,84,76,84,84,84,84,84,84,84,76,76,76,84,84,84,76,76,76,84,76
,84,84,76,84,76,77,77,77,84,84,77,84,84,84,84,84,84,84,77,77,77,84,84,84
,77,77,77,84,77,84,84,77,84,77,78,78,78,84,84,78,84,84,84,84,84,84,84,78
,78,78,84,84,84,78,78,78,84,78,84,84,78,84,78,79,79,79,84,84,79,84,84,84
,84,84,84,84,79,79,79,84,84,84,79,79,79,84,79,84,84,79,84,79,80,80,80,84
,84,80,84,84,84,84,84,84,84,80,80,80,84,84,84,80,80,80,84,80,84,84,80,84
,80,81,81,81,84,84,81,84,84,84,84,84,84,84,81,81,81,84,84,10,81,81,81,84
,81,84,84,81,84,81,82,82,82,84,10,82,84,84,84,84,84,84,84,82,82,82,84,84
,84,82,82,82,10,82,84,84,82,84,82,2,2,84,84,2,10,10,84,84,84,84,2,2,2,2
,84,84,84,2,2,2,84,2,84,10,2,10,2,3,3,84,84,3,84,84,84,84,84,84,84,3,3,3
,84,84,84,3,3,3,41,3,84,41,3,84,3,4,4,84,84,4,84,84,84,84,84,41,84,4,4,4
,84,84,84,4,4,4,84,4,84,84,4,84,4,41,84,84,84,84,84,84,84,84,84,84,84,84
,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84}
,
{1164,56,1424,1452,1480,209,150,34,0,1136,1424,150,313,105,100,210,264,318
,9,156,318,221,1086,372,210,264,243,736,583,53,0,156,31,106,140,152,201
,736,150,106,633,1514,372,426,480,936,786,97,1,30,41,886,47,683,159,121
,173,986,164,259,53,527,1036,836,0,533,202,47,42,19,1142,61,72,107,161,1193
,1222,1251,1280,1309,1338,1367,1396,1136}
,
{
{{44,44}
,{1,1}
,{44,44}
,{44,44}
,{45,45}
,{64,64}
,{64,64}
,{64,64}
,{1,1}
,{60,60}
,{49,49}
,{49,49}
,{49,49}
,{49,49}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{3,3}
,{60,60}
,{3,3}
,{3,3}
,{60,60}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{60,60}
,{3,3}
,{3,3}
,{42,42}
,{11,11}
,{11,11}
,{11,11}
,{42,42}
,{11,11}
,{60,60}
,{15,15}
,{3,3}
,{60,60}
,{3,3}
,{1,1}
,{1,1}
,{1,1}
,{60,60}
,{49,49}
,{65,65}
,{3,3}
,{65,65}
,{3,3}
,{60,60}
,{49,49}
,{49,49}
,{2,2}
,{42,42}
,{3,3}
,{60,60}
,{37,37}
,{49,49}
,{49,49}
,{1,1}
,{60,60}
,{64,64}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{36,36}
,{64,64}
,{2,2}
,{36,36}
,{3,3}
,{45,45}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
,{44,44}
}
,
{0,0,0,0,0,0,0,0,0}
,
{0,0,0,0,0,0,0,0,0}
,
{0,0,0,0,0,0,0,0,0}
}
};


/* Non terminal table *\
\* ------------------ */
typedef  struct {
    UByte2 gto[143];		/* Goto table */
    UByte1 gtoRix[84];		/* Goto row mapping */
    UByte1 lhs[131];		/* Left hand side symbols */
    UByte1 rhsz[131];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{0,0,0,762,762,457,754,754,249,249,97,137,250,746,746,554,554,521,521,90
,321,321,546,425,441,441,666,666,225,553,169,762,762,57,754,754,249,249
,258,266,513,746,746,481,554,537,386,378,321,321,433,546,122,385,666,666
,337,313,762,762,74,754,754,249,249,58,458,762,746,746,754,450,249,497,49
,241,506,746,554,474,17,666,674,426,554,546,506,153,554,466,674,546,481
,385,33,546,226,153,569,577,314,114,234,73,145,577,34,106,353,218,89,450
,65,121,361,105,177,25,610,201,322,489,217,418,458,377,113,41,265,545,281
,297,593,210,146,154,162,170,178,186,194,202,42}
,
{79,8,85,88,43,1,64,68,19,87,0,66,80,84,39,0,88,82,3,0,97,2,105,100,2,103
,2,1,55,64,1,123,1,125,1,126,1,29,1,56,28,1,96,98,72,78,38,1,1,1,1,10,1
,9,1,0,1,107,1,75,44,97,4,5,0,1,115,0,0,96,102,0,129,0,126,127,128,129,130
,131,132,133,134,135}
,
{73,81,110,110,93,111,111,103,103,104,104,120,120,107,107,79,79,94,94,94
,94,94,94,94,94,89,90,74,74,72,115,108,108,106,116,116,105,105,95,96,82
,82,82,121,121,121,112,112,109,118,118,119,119,117,117,101,101,99,99,83
,84,88,88,76,76,76,76,87,87,113,113,97,114,91,91,91,86,86,102,102,100,100
,92,92,98,98,98,98,98,98,98,98,80,80,80,80,80,85,85,85,85,85,85,85,85,85
,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,78,77
,75}
,
{7,0,0,2,2,0,2,0,1,0,1,0,1,1,2,0,1,2,2,2,2,2,2,2,2,2,3,1,2,4,3,1,2,5,0,1
,6,3,1,4,0,1,2,0,2,2,1,2,4,0,2,1,2,3,4,1,2,4,4,0,0,0,2,2,5,5,5,1,1,0,2,5
,1,0,1,2,0,1,1,3,1,3,1,2,1,2,2,2,4,5,5,6,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1
,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[71];
			     
static VocTab voc = {{1,255,255,"EndOfText",""}
,{2,1,1,"'='",""}
,{3,1,1,"';'",""}
,{4,1,1,"':'",""}
,{5,1,1,"'/'",""}
,{6,1,1,"'!'",""}
,{7,1,1,"'*'",""}
,{8,1,1,"'+'",""}
,{9,1,1,"'?'",""}
,{10,1,1,"'{'",""}
,{11,1,1,"'}'",""}
,{12,1,1,"'-'",""}
,{13,1,1,"'.'",""}
,{14,1,1,"'('",""}
,{15,1,1,"')'",""}
,{16,1,1,"'C'",""}
,{17,1,1,"'K'",""}
,{18,1,1,"'M'",""}
,{19,1,1,"'NO'",""}
,{20,1,1,"'%%'",""}
,{21,1,1,"'ADA'",""}
,{22,1,1,"'COL'",""}
,{23,1,1,"'DES'",""}
,{24,1,1,"'DFA'",""}
,{25,1,1,"'ERR'",""}
,{26,1,1,"'GCS'",""}
,{27,1,1,"'LES'",""}
,{28,1,1,"'MAP'",""}
,{29,1,1,"'NFA'",""}
,{30,1,1,"'POS'",""}
,{31,1,1,"'RDS'",""}
,{32,1,1,"'ROW'",""}
,{33,1,1,"'SCR'",""}
,{34,1,1,"'SET'",""}
,{35,1,1,"'TOK'",""}
,{36,1,1,"Class",""}
,{37,1,1,"'AUTO'",""}
,{38,1,1,"'%%DO'",""}
,{39,1,1,"'BYTE'",""}
,{40,1,1,"'LIST'",""}
,{41,1,1,"String",""}
,{42,1,1,"Number",""}
,{43,1,1,"'%%END'",""}
,{44,1,1,"'%%SET'",""}
,{45,1,1,"'%%MAP'",""}
,{46,1,1,"'TOKEN'",""}
,{47,1,1,"'TRACE'",""}
,{48,1,1,"'%%CODE'",""}
,{49,1,1,"'%%RULE'",""}
,{50,1,1,"'%%SKIP'",""}
,{51,1,1,"'ESCAPE'",""}
,{52,1,1,"'ROWCOL'",""}
,{53,1,1,"'EXCLUDE'",""}
,{54,1,1,"'VERBOSE'",""}
,{55,1,1,"SKIPHEADER",""}
,{56,1,1,"'%%EXPORT'",""}
,{57,1,1,"'%%READER'",""}
,{58,1,1,"'%%ACTION'",""}
,{59,1,1,"'_UNKNOWN'",""}
,{60,1,1,"Identifier",""}
,{61,1,1,"'POSITION'",""}
,{62,1,1,"'%%CONTEXT'",""}
,{63,1,1,"'%%PREHOOK'",""}
,{64,1,1,"'%%SCANNER'",""}
,{65,1,1,"'SCREENING'",""}
,{66,1,1,"'%%POSTHOOK'",""}
,{67,1,1,"'_ENDOFTEXT'",""}
,{68,1,1,"'%%SCREENING'",""}
,{69,1,1,"'%%DEFINITION'",""}
,{70,1,1,"'%%VOCABULARY'",""}
,{71,1,1,"'%%DECLARATION'",""}
}
;


/* Variables used in the parsing process *\
\* ------------------------------------- */
short smkStkP;			/* Stack pointer */
SmkToken smkSySt[PmStkMax];	/* Symbol stack */
smkGrammar smkSeSt[PmStkMax];	/* Semantic stack */ 
static UByte1 currstat;		/* Current state number */
static UByte1 arg;		/* Argument */
static UByte1 action;		/* Action type */
static PmBoolean endparse;	/* Termination flag */
static ParseStack parsStk;	/* Parse stack */
static UByte1 scIndex[71 + 1]; /* Converts scanner code to internal value */
static SmkToken tokenBuf;	/* Scanner token buffer */
static SmkToken *token = &tokenBuf;	/* Pointer to it for readsymb */


/* Error recovery look-ahead buffer *\
\* -------------------------------- */
static SmkToken la_buff[PmLaMax + 1]; /* Buffer */
static int la_ptr;		/* Current pointer */
static int la_end;		/* Last item */

static jmp_buf pmJmpB;		/* Buffer for long jump */

/* Interface routines *\
\* ------------------ */

extern void smkRPoi();	/* Error recovery - restart point  */
extern void smkISym();	/* Error recovery - insert symbol  */
extern void smkDSym();	/* Error recovery - delete symbol  */
extern void smkMess();	/* Error recovery - error message  */

/* External functions */
void smkPaSema();

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(token, eClass, severity) 
SmkToken *token;		/* IN current token */
short eClass;			/* IN error classification */
short severity;			/* IN error severity code */
{
    smkMess(token, HALT_REC, eClass, severity);
    longjmp(pmJmpB, PMTRUE);	/* Jump out to top level */
}/*paAbort()*/


/*----------------------------------------------------------------------------
 * SetIns - Add one element to a set
 *----------------------------------------------------------------------------
 */
#define SetIns(set, n) ((set)[(n) >> 3] |= (0x80 >> ((n) & 0x7)))


/*----------------------------------------------------------------------------
 * SetClear - Clear a ParserMaker set
 *----------------------------------------------------------------------------
 */
#define SetClear(set, length) memset((void *)set, 0, ((length) + 7) >> 3)

/*----------------------------------------------------------------------------
 * SetMem - Check member inclusion
 *----------------------------------------------------------------------------
 */
#define SetMem(set, n) ((set)[(n) >> 3] & (0x80 >> ((n) & 0x7)))


/*----------------------------------------------------------------------------
 * paInit - Initialize the parsing process
 *----------------------------------------------------------------------------
 */
static void paInit()
{
    short i;

    la_ptr = 0;
    la_end = 0;
    smkStkP = 0;
    currstat = 1;
    endparse = PMFALSE;
    parsStk[0] = 1;

    /* Scanner interface */
    for (i = 0; i <= SccMax; i++) scIndex[i] = ERR_SYM;
    for (i = TermMin; i <= Terms; i++) scIndex[voc[i - TermMin].scc] = (UByte1)i;
}/*paInit()*/


/*----------------------------------------------------------------------------
 * pushStat[Tok] - Push the current state on the stack and possibly push current
 *	      token on the symbol stack.
 *----------------------------------------------------------------------------
 */
#define MOVETOKEN smkSySt[smkStkP] = *token
#define pushStatTok()\
{\
    if (++smkStkP < PmStkMax) {\
	parsStk[smkStkP] = currstat;\
	MOVETOKEN;\
    } else {\
	token->code = voc[token->code-TermMin].scc;\
	paAbort(token, OFLW_ERR, SYS_SEV);\
    }\
} 

#define pushStat()\
{\
    if (++smkStkP < PmStkMax) {\
	parsStk[smkStkP] = currstat;\
    } else {\
	token->code = voc[token->code-TermMin].scc;\
	paAbort(token, OFLW_ERR, SYS_SEV);\
    }\
} 



/*----------------------------------------------------------------------------
 * actTbl - Do a look-up in the action table
 *----------------------------------------------------------------------------
 */
#define actTbl(st, sy, action, arg)\
{\
    register int actEnt;\
    register int actSt;\
    register int actSy;\
    actSt = st - StateMin;\
    actSy = sy - TermMin;\
    if (act.actCheck[act.actRix[actSt] + actSy] == actSt)\
	actEnt = act.act[act.actRix[actSt] + actSy];\
    else actEnt = ERROR_ACT;\
    *action = actEnt & 0x7;\
    *arg = actEnt >> 3;\
}/*actTbl()*/


/*----------------------------------------------------------------------------
 * gtoTbl - Do a look-up in the goto table
 *----------------------------------------------------------------------------
 */
#define gtoTbl(st, sy, action, arg)\
{\
    register int gtoEnt;\
    register int gtoSt;\
    register int gtoSy;\
    gtoSt = st - StateMin;\
    gtoSy = sy - Terms - 1;\
	gtoEnt = gto.gto[gto.gtoRix[gtoSt] + gtoSy];\
    *action = gtoEnt & 0x7;\
    *arg = gtoEnt >> 3;\
}/*gtoTbl()*/


/*----------------------------------------------------------------------------
 * E R R O R   R E C O V E R Y
 * ---------------------------
 *
 * The error recovery algorithm tries to modify current configuration in such
 * a way that parsing can be resumed correctly. Current configuration is
 * characterized by:
 *
 * w = x t y, where  x = parsed input
 *		     t = current token
 *		     y = unprocessed input
 *----------------------------------------------------------------------------
 */

typedef struct {
    SmkToken err_tok;
    SmkToken res_tok;
    short method;
    short eClass;
    short severity;
} ERR_REC;

static ERR_REC errdescr; 


/*----------------------------------------------------------------------------
 * ePush - Push a state during error recovery
 *----------------------------------------------------------------------------
 */
static void ePush(state, stack, sp)
UByte1 state;			/* IN state to push */
UByte1 stack[];			/* INOUT parser stack */
short *sp;			/* INOUT current stack pointer */
{
    if (++(*sp) < PmStkMax) stack[*sp] = state;
    else paAbort(&errdescr.err_tok, OFLW_ERR, SYS_SEV);
}/*ePush()*/


/*----------------------------------------------------------------------------
 * legalAct - Check if a symbol is legal to shift in current state
 *----------------------------------------------------------------------------
 */
static PmBoolean legalAct(stack, stack_p, sym)
UByte1 stack[];			/* IN current stack */
short stack_p;			/* IN current stack pointer */
UByte1 sym;			/* IN symbol code */
				/* RET true if "symbol" is read (shifted) */
				/*     in current state */
{
    UByte1 state;		/* Current state */
    UByte1 action;		/* Current parser action */
    UByte1 arg;			/* Current parser argument */

    ParseStack t_stk;		/* Temporary parser stack */
    int i;			/* For loop index */

    /* Copy stack
     */
    for (i = 0; i <= stack_p; i++) t_stk[i] = stack[i]; 

    state = stack[stack_p];

    for (;;) {
	actTbl(state, sym, &action, &arg);
	switch (action) {

	case ERROR_ACT:
	    return(PMFALSE);

	case SHIFT_ACT:
	case SHIFTRED_ACT:	
	case ACCEPT_ACT:
	    return(PMTRUE);

	case REDUCE_ACT:
	    do {
		stack_p = stack_p - gto.rhsz[arg - ProdMin];
		gtoTbl(t_stk[stack_p], gto.lhs[arg - ProdMin], &action, &arg);
		ePush(state, t_stk, &stack_p);
	    } while (action != SHIFT_ACT);
	    state = arg; t_stk[stack_p] = state;
	    break;

	}/*switch*/
    }/*for*/
}/*legalAct()*/
			     
	
/*----------------------------------------------------------------------------
 * gLegSym - Get legal symbols
 *----------------------------------------------------------------------------
 */
static void gLegSym(stack, stack_p, legals)
ParseStack stack;		/* IN current stack */
short stack_p;			/* IN current stack pointer */
TermSet legals;			/* OUT legal symbols in current state */
{
    short sym;			/* Loop index */

    SetClear(legals, Terms + 1);
    for (sym = 1; sym <= Terms; sym++) {
	if (legalAct(stack, stack_p, sym)) SetIns(legals, sym);
    }/*for*/
}/*gLegSym()*/


/*----------------------------------------------------------------------------
 * backup - Backup the parse stack until current symbol is accepted (shifted)
 *	    or the parse stack becomes empty
 *----------------------------------------------------------------------------
 */
static short backup(stack, stack_p, sym)
ParseStack stack;		/* IN current stack */
short stack_p;			/* IN current stack pointer */
UByte1 sym;	/* IN recovery symbol */
				/* RET new stack pointer, 0 if symbol is */
				/*     not accepted */
{
    while ((stack_p > 0) && (!legalAct(stack, stack_p, sym))) stack_p--;
    return(stack_p);
}/*backup()*/


/*----------------------------------------------------------------------------
 * delSym - Delete a symbol in the input stream
 *----------------------------------------------------------------------------
 */
static void delSym(token)
SmkToken *token;			/* INOUT symbol to delete, new symbol */
{
    short  t;

    t = token->code - TermMin;
    token->code = voc[t].scc;
    smkDSym(token, voc[t].name, voc[t].psym);
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
    if (errdescr.method == IN_REC) errdescr.method = REP_REC;
    else if (errdescr.method != REP_REC) errdescr.method = DEL_REC;
}/*delSym()*/


/*----------------------------------------------------------------------------
 * inSym - Insert a symbol in the input stream
 *----------------------------------------------------------------------------
 */
static void inSym(isym, gen_symb)
short isym;			/* IN symbol code to insert */
SmkToken *gen_symb;		/* OUT created symbol */
{
    smkISym(voc[isym - TermMin].scc, voc[isym - TermMin].name,
	   voc[isym - TermMin].psym, gen_symb);
    if (errdescr.method == DEL_REC) errdescr.method = REP_REC;
    else if (errdescr.method != REP_REC) errdescr.method = IN_REC; 

    gen_symb->code = isym;
}/*inSym()*/


/*----------------------------------------------------------------------------
 * M U L T I P L E   R E C O V E R Y
 * ---------------------------------
 *
 * The multiple symbols recovery technique is a "true local corrector", i.e.
 * it will always return a legal configuration for any input. Logically the
 * algorithm can be described as follows:
 *
 * 1) Roerich method (Karlsruhe):
 *    a. Find a continuation "u" of "x", such that "xu" is accepted.
 *    b. De composite "ty" into "qsy'", where q is a string.
 *    c. Delete "q".
 *    d. Insert u' (a prefix of u) between "x" and "sy'" giving xu' s y'.
 *
 * 2) Panic mode:
 *    If "q" contains a fiducial symbol "a"  then:
 *    a. Pop stack until "a" is accepted.
 *    b. If not succeeded resume at step 1.
 *----------------------------------------------------------------------------
 */

typedef struct {
    UByte1 r_state;		/* Recovery state */
    PmBoolean r_sepa;		/* Insert separator? */
    UByte1 r_sstat;		/* Where to insert separator */
} REC_POI;


/*----------------------------------------------------------------------------
 * acceptbl - Check whether "symbol" is reachable from current state using
 *	      the continuation grammar.
 *----------------------------------------------------------------------------
 */
static void acceptbl(sym, stack, stack_p, token, found, point)
UByte1 sym;			/* IN terminal symbol code */
ParseStack stack;		/* IN parse stack */
short stack_p;			/* IN stack pointer */
SmkToken *token;			/* IN current token */
PmBoolean *found;		/* OUT "symbol" accepted? */
REC_POI *point;			/* OUT recovery point description */
{
    PmBoolean done;		/* Terminator flag */
    UByte1 state;		/* Current state */
    UByte1 action;		/* Parser action */
    UByte1 sep_act;		/* Parser action separator test */
    UByte1 arg;			/* Parser prod/state */
    UByte1 sep_arg;		/* Parser prod/state separator test */
    PmBoolean sepa_acc;		/* Separator is accepted? */
    ParseStack t_stk;		/* Temporary parser stack */
    short i;			/* Copy loop index */

    for (i = 0; i <= stack_p; i++) t_stk[i] = stack[i];

    state = t_stk[stack_p];
    done = PMFALSE;

    while (!done) {
	actTbl(state, sym, &action, &arg);
	if (legalAct(t_stk, stack_p, sym)) {
	    /* Symbol is directly accepted */
	    done = PMTRUE;
	    *found = PMTRUE;
	    point->r_state = state;
	} else {
	    /* Use the continuation grammar */
	    actTbl(state, act.recover.cont[state - StateMin].tsym, &action,
		   &arg);
	    actTbl(state, act.recover.cont[state - StateMin].ssym, &sep_act,
		   &sep_arg);
	    if ((action != sep_act) || (arg != sep_arg)) {
		/* A separator is legal. Check if current symbol is accepted
		 * behind the separator
		 */
	        ParseStack stk;	/* Temporary stack */
	        short sp;	/* Temporary stack pointer */

		sp = stack_p; 
		for (i = 0; i <= stack_p; i++) stk[i] = t_stk[i];
		sepa_acc = PMFALSE;

		while (!sepa_acc) {
		  actTbl(stk[sp], act.recover.cont[state - StateMin].ssym,
			 &sep_act, &sep_arg);
		    switch (sep_act) {

		    case ERROR_ACT:
		    case ACCEPT_ACT:
			sepa_acc = PMTRUE;
			break;

		    case SHIFT_ACT: 
			sepa_acc = PMTRUE;
			ePush(sep_arg, stk, &sp);
			break;

		    case SHIFTRED_ACT:
			ePush(1, stk, &sp);
			sepa_acc = PMTRUE;
			goto reduce;

		    case REDUCE_ACT:
		      reduce:
			do {
			    sp -= gto.rhsz[sep_arg-ProdMin];
			    gtoTbl(stk[sp], gto.lhs[sep_arg-ProdMin], &sep_act,
				   &sep_arg);
			    ePush(1, stk, &sp);
			} while (sep_act != SHIFT_ACT);

			stk[sp] = sep_arg;
			break;
		    }/*switch*/
		}/*while*/

		if ((sep_act == SHIFT_ACT) || (sep_act == SHIFTRED_ACT)) {
		    if (legalAct(stk, sp, sym)) {
			/* Separator is to be inserted */
			point->r_state = stk[sp];
			point->r_sepa = PMTRUE;
			point->r_sstat = state;
			done = PMTRUE;
			*found = PMTRUE;
		    }/*if*/
		}/*if*/
	    }/*if*/
		  
	    if (!*found) {
		switch (action) {

		case ERROR_ACT: 
		    paAbort(token, TAB_ERR, SYS_SEV);
		    break;

		case ACCEPT_ACT:
		    done = PMTRUE;
		    break;

		case SHIFT_ACT:
		    state = arg;
		    ePush(state, t_stk, &stack_p);
		    break;

		case SHIFTRED_ACT:
		    ePush(state, t_stk, &stack_p);
		    goto reduce2;

		case REDUCE_ACT:
		  reduce2:
		    do {
			stack_p -= gto.rhsz[arg-ProdMin];
			gtoTbl(t_stk[stack_p], gto.lhs[arg-ProdMin], &action,
			       &arg);
			ePush(state, t_stk, &stack_p);
		    } while (action != SHIFT_ACT);

		    state = arg;
		    t_stk[stack_p] = state;
		    break;

		}/*switch*/
	    }/*if*/
	}/*if*/
    }/*while*/
}/*acceptbl()*/


/*----------------------------------------------------------------------------
 * search - Search recovery point
 *----------------------------------------------------------------------------
 */
static void search(stack, stack_p, token, point)
ParseStack stack;		/* IN current stack */
short *stack_p;			/* INOUT current stack pointer */
SmkToken *token;			/* INOUT current symbol */
REC_POI *point;			/* OUT descriptor of where to restart */
				/*     the parser */
{
    UByte1 state;		/* Current state */
    PmBoolean rp_found;		/* Recovery point found? */
    short new_stkp;		/* Temp stack pointer */

    state = stack[*stack_p];
    point->r_state = state;
    point->r_sepa = PMFALSE;
    point->r_sstat = 1;
    rp_found = PMFALSE;

    do {
	if (!SetMem(act.recover.skip, token->code)) {
	    acceptbl(token->code, stack, *stack_p, token, &rp_found, point);
	}/*if*/

	if (!rp_found) {
	    new_stkp = 0;
	    if (SetMem(act.recover.fiduc, token->code)) {
		new_stkp = backup(stack, *stack_p, token->code);
	    }/*if*/
	    if (new_stkp > 0) {
		rp_found = PMTRUE;
		*stack_p = new_stkp;
		point->r_state = stack[*stack_p];
		errdescr.method = BAK_REC;
	    } else 
	        delSym(token);
	}/*if*/
    } while (!rp_found);
}/*search()*/


/*----------------------------------------------------------------------------
 * reach - Use the continuation functions and insert symbols upto curr token.
 *----------------------------------------------------------------------------
 */
static void reach(stack, stack_p, token, point)
ParseStack stack;		/* INOUT current stack */
short *stack_p;			/* INOUT current stack pointer */	
SmkToken *token;			/* INOUT current symbol */
REC_POI *point;			/* IN recovery point descriptor */
{
    UByte1 state;		/* Current state */
    UByte1 cont_sym;		/* Continuation symbol */
    SmkToken gen_symb;		/* Generated symbol */
    UByte1 action;		/* Current parser action */
    UByte1 arg;			/* Current prod/state */
    PmBoolean sepaAccept;	/* Separator accepted yet? */
    PmBoolean useSepa;		/* Use the separator now? */

    state = stack[*stack_p];
    gen_symb = *token;
    useSepa = PMFALSE;
    while (state != point->r_state) {
	if (point->r_sepa)
	    if (state == point->r_sstat) {
		/* Separator state reached, remember to use separator */
		cont_sym = act.recover.cont[state-StateMin].ssym;
		useSepa = PMTRUE;
	    } else cont_sym = act.recover.cont[state-StateMin].tsym;
	else cont_sym = act.recover.cont[state-StateMin].tsym;
	sepaAccept = PMFALSE;

	do {
	  actTbl(state, cont_sym, &action, &arg);
	  switch (action) {

	  case ERROR_ACT:
	    paAbort(token, TAB_ERR, SYS_SEV);
	    break;

	  case ACCEPT_ACT:
	    break;

	  case SHIFT_ACT:
	    sepaAccept = PMTRUE;
	    state = arg;
	    inSym(cont_sym, &gen_symb);
	    ePush(state, stack, stack_p);
	    smkSySt[*stack_p] = gen_symb;
	    break;

	  case SHIFTRED_ACT:
	    sepaAccept = PMTRUE;
	    inSym(cont_sym, &gen_symb);
	    ePush(state, stack, stack_p);
	    smkSySt[*stack_p] = gen_symb;
	    goto reduce;

	  case REDUCE_ACT:
	    reduce:
	    do {
		*stack_p = *stack_p - gto.rhsz[arg-ProdMin];
		smkPaSema(arg);
		gtoTbl(stack[*stack_p], gto.lhs[arg-ProdMin], &action, &arg);
		ePush(state, stack, stack_p);
	    } while (action != SHIFT_ACT);
	    state = arg;
	    stack[*stack_p] = state;
	  }/*switch*/
	} while (useSepa && !sepaAccept);
    }/*while*/
}/*reach()*/


/*----------------------------------------------------------------------------
 * global - Global error recovery
 *----------------------------------------------------------------------------
 */
static void multiple(err_stk, err_stkp, err_tok, newstat)
ParseStack err_stk;		/* INOUT current parse stack */
short *err_stkp;		/* INOUT current stack pointer */
SmkToken *err_tok;		/* INOUT current token */
UByte1 *newstat;		/* OUT state after recovery */	
{
    REC_POI  point;		/* Recovery point descriptor */

    search(err_stk, err_stkp, err_tok, &point);
    reach(err_stk, err_stkp, err_tok, &point);
    *newstat = err_stk[*err_stkp];
}/*multiple()*/


/*----------------------------------------------------------------------------
 * S I N G L E   R E C O V E R Y
 * -----------------------------
 *
 * The single recovery technique tries to REPAIR the error by finding the
 * least cost single symbol correction. One single symbol of:
 * - insertion
 * - deletion
 * - replacement
 * is concidered. The cost of the repair is the sum of the ADAPTION cost and
 * the MODIFICATION cost. The adaption cost indicates how well a correction
 * fits in the context. The modification cost is based on the
 * insertion/deletion cost given in the input. A correction is applied if
 * the cost is below a predefined threshold value.
 *----------------------------------------------------------------------------
 */

#define ShiftCost (PmCost)	/* The cost of shifting one symbol */
#define InfCost (ShiftCost * (PmLaMax)) /* Infinity */
#define Thresh (((PmLaMax) - 3) * ShiftCost) /* Acceptance cost */


/*----------------------------------------------------------------------------
 * readLa - Read tokens to the look-ahead buffer
 *----------------------------------------------------------------------------
 */
static void readLa(curtok)
SmkToken *curtok;			/* IN current token */
{
    int i;
    SmkToken tokbuf;
    SmkToken *token = &tokbuf;

    la_buff[0] = *curtok;
    *token = *curtok;
    for (i = la_ptr + 1; i <= la_end; i++) {
	/* Move old look_ahead to the beginning of the buffer */
	la_buff[i - la_ptr] = la_buff[i];
    }/*for*/
    la_end = la_end - la_ptr;
    la_ptr = -1;

    while ((la_buff[la_end].code != ENDMARK) && (la_end < PmLaMax)) {
	la_end++;
	do {
             smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else {
		token->code = scIndex[token->code];
	    }/*if*/
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
	    }/*if*/
	} while (token->code == ERR_SYM);
	la_buff[la_end] = *token;
    }/*while*/
}/*readLa()*/


/*----------------------------------------------------------------------------
 * rdLaSym - Fetches the i:th look-ahead symbol code from the look-ahead set
 *----------------------------------------------------------------------------
 */
static UByte1 rdLaSym(index)
char index;			/* IN i:th look-ahead symbol */
				/* RET token code */
{
    if (index > la_end) return(ENDMARK);
    else return(la_buff[(int)index].code);
}/*rdLaSym()*/


/*----------------------------------------------------------------------------
 * laParse - Continue the parsing process by reading tokens from the
 *	     look-ahead set. The parse is terminated when:
 *	     - out of read ahead
 *	     - a new error is encountered
 *	     Note! No semantic actions are carried out
 *----------------------------------------------------------------------------
 */
static void laParse(sym, next_la, stack, stack_p, cost)
UByte1 sym;			/* IN current terminal symbol */
char next_la;			/* IN index to next look-ahead symbol */
ParseStack stack;		/* IN parse stack */
short stack_p;			/* IN current stack pointer */
short *cost;			/* OUT adaption cost */
{
    PmBoolean done ;		/* Terminator flag */
    char sh_cnt;		/* Number of shifted symbols */
    UByte1 state;		/* Current state number */
    UByte1 action;		/* Parser action */
    UByte1 arg; 		/* Parser argument */
    short i;			/* Loop index */
    ParseStack t_stk;		/* Temporary stack */

    /* Copy stack
     */
    for (i = 0; i <= stack_p; i++) t_stk[i] = stack[i];	

    done = PMFALSE;
    sh_cnt = 0;
    state = t_stk[stack_p];

    while (!done) {
	actTbl(state, sym, &action, &arg);
	
	switch (action) {

	case ERROR_ACT: 
	    done = PMTRUE;
	    break;

	case SHIFT_ACT:
	    state = arg;
	    ePush(state, t_stk, &stack_p);
	    sh_cnt++;
	    if (sh_cnt == PmLaMax) done = PMTRUE;
	    else {
		sym = rdLaSym(next_la);
		next_la++;
	    }/*if*/
	    break;

	case SHIFTRED_ACT:
	    ePush(state, t_stk, &stack_p);
	    sh_cnt++;
	    if (sh_cnt == PmLaMax) done = PMTRUE;
	    else {
		sym = rdLaSym(next_la);
		if (next_la < PmLaMax) next_la++;
	    }/*if*/
	    goto reduce;

	case REDUCE_ACT:
	  reduce:
	    do {
		stack_p -= gto.rhsz[arg-ProdMin];
		gtoTbl(t_stk[stack_p], gto.lhs[arg-ProdMin], &action, &arg);
		ePush(state, t_stk, &stack_p);
	    } while (action != SHIFT_ACT); 

	    state = arg;
	    t_stk[stack_p] = state;
	    break;

	case ACCEPT_ACT:
	    done = PMTRUE;
	    sh_cnt = PmLaMax;
	    break;

	}/*switch*/
    }/*while*/

    *cost = InfCost - (sh_cnt*ShiftCost);
}/*laParse()*/


/*----------------------------------------------------------------------------
 * tryIn - Tries to insert a symbol from the legal set in front of current
 *	   token: x t y  => x st y, where s becomes current symbol
 *----------------------------------------------------------------------------
 */
static void tryIn(legals, stack, stack_p, sym, cost, choice)
TermSet legals;			/* IN set of legal symbols */
ParseStack stack;		/* IN current parser stack */
short stack_p;			/* IN current stack pointer */
UByte1 *sym;			/* OUT best insertion symbol */
short *cost;			/* OUT best cost so far */
short *choice;			/* OUT best choice so far */
{
    short i;
    short mod_cost;		/* Modification cost */
    short ad_cost;		/* Adaption cost */
    short tot_cost;		/* Total insertion cost */

    for (i = 1; i <= Terms; i++) {
	/* For all legal symbols
	 */
	if (SetMem(legals, i)) {
	    mod_cost = voc[i - TermMin].iCost;
	    if (mod_cost < *cost) {
		laParse(i, 0, stack, stack_p, &ad_cost);
		tot_cost = ad_cost + mod_cost;
		if (tot_cost < *cost) {
		    *cost = tot_cost;
		    *choice = IN_REC;
		    *sym = (UByte1)i;
		}/*if*/
	    }/*if*/
	}/*if*/
    }/*for*/
}/*tryIn()*/


/*----------------------------------------------------------------------------
 * tryRep - Tries to replace currrent symbol with a new terminal:
 *	    x t y  => x s y, where s becomes current symbol
 *----------------------------------------------------------------------------
 */
static void tryRep(legals, stack, stack_p, sym, cost, choice)
TermSet legals;			/* IN set of legal symbols */
ParseStack stack;		/* IN current parser stack */
short stack_p;			/* IN current stack pointer */
UByte1 *sym;			/* OUT best replacement symbol */
short *cost;			/* OUT best cost so far */
short *choice;			/* OUT best choice so far */
{
    short i;
    short mod_cost;		/* Modification cost */
    short ad_cost;		/* Adaption cost */
    short tot_cost;		/* Total replacment cost */

    for (i = 1; i <= Terms; i++) {
	/* For all legal symbols
	 */
	if (SetMem(legals, i)) {
	    mod_cost = (short) (voc[i-TermMin].iCost +
			voc[rdLaSym(0)-TermMin].dCost) / 2 + 1;
	    if (mod_cost < *cost) {
		laParse(i, 1, stack, stack_p, &ad_cost);
		tot_cost = ad_cost + mod_cost;
		if (tot_cost < *cost) {
		    *cost = tot_cost;
		    *choice = REP_REC;
		    *sym = (UByte1)i;
		}/*if*/
	    }/*if*/
	}/*if*/
    }/*for*/
}/*tryRep()*/


/*----------------------------------------------------------------------------
 * tryDel - Tries to delete current symbol: x t y  => x y
 *----------------------------------------------------------------------------
 */
static void tryDel(stack, stack_p, cost, choice)
ParseStack stack;		/* IN current parser stack */
short stack_p;			/* IN current stack pointer */
short *cost;			/* INOUT best cost so far */
short *choice;			/* INOUT best choice so far */
{
    short mod_cost;		/* Modification cost */
    short ad_cost;  		/* Adaption cost */
    short tot_cost;		/* Total deletion cost */

    mod_cost = voc[rdLaSym(0) - TermMin].dCost;
    if (mod_cost < *cost) {
	laParse(rdLaSym(1), 2, stack, stack_p, &ad_cost);
	tot_cost = ad_cost + mod_cost;
	if (tot_cost < *cost) {
	    *cost = tot_cost;
	    *choice = DEL_REC;
	}/*if*/
    }/*if*/
}/*tryDel()*/


/*----------------------------------------------------------------------------
 * _pmInsert
 *----------------------------------------------------------------------------
 */
static void _pmInsert(sym, token)
UByte1 sym;			/* IN symbol code to insert */
SmkToken *token;			/* OUT constructed token */
{
    inSym(sym, token);
}/*_pmInsert()*/


/*----------------------------------------------------------------------------
 * _pmReplace
 *----------------------------------------------------------------------------
 */
static void _pmReplace(sym, token)
UByte1 sym;			/* IN replacement symbol code */
SmkToken *token;			/* OUT constructed token */
{
    delSym(token);
    inSym(sym, token);
}/*_pmReplace()*/


/*----------------------------------------------------------------------------
 * _pmDelete
 *----------------------------------------------------------------------------
 */

static void _pmDelete(token)
SmkToken *token;			/* OUT new token */
{
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
    delSym(token);
}/*_pmDelete()*/


/*----------------------------------------------------------------------------
 * single - Single error recovery
 *----------------------------------------------------------------------------
 */
static void single(leg_sys, err_stk, err_stkp, token, newstat)
TermSet leg_sys;		/* IN legal symbols in current state */
ParseStack err_stk;		/* INOUT current parser stack */
short *err_stkp;		/* INOUT current stack pointer */
SmkToken *token;		/* INOUT current token */
UByte1 *newstat;		/* OUT recovery state */
{
    short choice;		/* Recovery action performed */
    short cost;			/* Best cost so far */
    UByte1 sym;			/* Insert symbol */

    choice = NONE_REC;
    cost = InfCost;
    readLa(token);

    tryIn(leg_sys, err_stk, *err_stkp, &sym, &cost, &choice);
    tryRep(leg_sys, err_stk, *err_stkp, &sym, &cost, &choice);
    tryDel(err_stk, *err_stkp, &cost, &choice);

    if (cost > Thresh) choice = NONE_REC;

    switch (choice) {

    case IN_REC:
	_pmInsert(sym, token);
	break;

    case DEL_REC:  
	_pmDelete(token);
	break;

    case REP_REC: 
	_pmReplace(sym, token);
	break;

    default:
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
    }/*switch*/

    *newstat = err_stk[*err_stkp];
}/*single()*/



/*----------------------------------------------------------------------------
 * recover - From an error
 *----------------------------------------------------------------------------
 */
static void recover(err_stk, err_stkp, err_symb, rec_stat)
ParseStack err_stk;		/* INOUT updated parse stack */
short *err_stkp;		/* INOUT updated stack pointer */
SmkToken *err_symb;		/* INOUT current token */
UByte1 *rec_stat;		/* OUT state after recovery */
{
    TermSet legal_sy;		/* Legal symbols */

    errdescr.err_tok = *err_symb;
    errdescr.err_tok.code = voc[errdescr.err_tok.code - TermMin].scc;
    errdescr.method = NONE_REC;
    errdescr.eClass = SYN_ERR;
    errdescr.severity = ERR_SEV;
    gLegSym(err_stk, *err_stkp, legal_sy);
    single(legal_sy, err_stk, err_stkp, err_symb, rec_stat);
    if (errdescr.method == NONE_REC) {
	multiple(err_stk, err_stkp, err_symb, rec_stat);
	smkMess(&errdescr.err_tok, errdescr.method, errdescr.eClass, 
	       errdescr.severity); 
    } else {
	smkMess(&errdescr.err_tok, errdescr.method, SYN_ERR, errdescr.severity);
    }/*if*/
    errdescr.res_tok = *err_symb;
    errdescr.res_tok.code = voc[errdescr.res_tok.code - TermMin].scc;
    smkRPoi(&errdescr.res_tok);
}/*recover()*/


/*----------------------------------------------------------------------------
 * smkParse - Parser routine, entry point
 *----------------------------------------------------------------------------
 */
void smkParse()
{
    paInit();
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
    pushStatTok()
    if (setjmp(pmJmpB)) return;

    while (!endparse) {
	actTbl(currstat, token->code, &action, &arg);

	switch (action) {

	case ERROR_ACT:
	    recover(parsStk, &smkStkP, token, &currstat);
	    if (smkStkP == 0) endparse = PMTRUE;
	    break;

	case SHIFT_ACT:
	    currstat = arg;
	    pushStatTok();
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
	    break;

	case SHIFTRED_ACT:
	    pushStatTok();
{
    if (la_ptr < la_end) {
	la_ptr++;
	*token = la_buff[la_ptr];
    } else {
	do {
	     smkScan(lexContext, token);

	    if (token->code > SccMax || token->code < 0) {
		token->code = ERR_SYM;
	    } else token->code = scIndex[token->code];
	    if (token->code == ERR_SYM) {
		smkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
		}
	} while (token->code == ERR_SYM);
    }
}
	    goto reduce;

 	case REDUCE_ACT:
	  reduce:
	    do {
		smkStkP -= gto.rhsz[arg - ProdMin];	
		smkPaSema(arg);
		gtoTbl(parsStk[smkStkP], gto.lhs[arg - ProdMin], &action, &arg);
		pushStat();
	    } while (action != SHIFT_ACT);

	    currstat = arg;
	    parsStk[smkStkP] = currstat;
	    break;

	case ACCEPT_ACT:
	    endparse = PMTRUE;
	    break;
	}/*switch*/
    }/*while*/
}/*smkParse()*/

