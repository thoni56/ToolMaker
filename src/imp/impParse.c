/*----------------------------------------------------------------------*\

    impParse.c

    ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */

/* .pmk-import */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "impScan.h"
#include "impList.h"
extern impScContext impcontext;
/* END %%IMPORT */

#include <string.h>
#include <setjmp.h>

#include "impParse.h"

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
#include "impCommon.h"

/* %%ATTRIBUTES - The semantic attributes for grammar symbols */
typedef struct impGrammar {
    Ast last         /* Pointer to last node in a list */;
    Ast seq         /* Sequence of nodes              */;
    Ast ast         /* An abstract syntax tree        */;
    TmSrcp srcp      /* Source position                */;
} impGrammar;

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
#define SccMax 51		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 51		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 182		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 125		/* Number of productions */
#define PmStkMax 128		/* Parse stack size */
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
    ContRec cont[182];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[1244];		/* Action table */
    UByte1 actCheck[1245];	/* Row Displacement Check Vector*/
    UByte2 actRix[182];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{4,811,811,811,811,811,811,811,1201,811,811,811,811,811,811,875,177,538
,811,811,811,619,409,33,811,745,811,290,1305,875,811,49,113,562,745,786
,673,811,971,971,971,971,971,971,1009,971,971,971,971,842,971,265,971,745
,971,971,971,338,217,33,971,633,971,1313,283,283,971,697,49,113,185,235
,1177,971,153,979,979,979,979,979,979,994,979,979,979,979,570,979,265,979
,922,979,979,979,1033,217,979,979,746,979,170,33,1049,979,73,330,49,113
,1065,818,979,779,779,779,779,779,779,779,979,779,779,779,779,97,779,947
,265,842,779,779,779,377,354,217,779,394,779,697,299,1289,779,235,713,49
,113,178,33,779,779,779,779,779,779,779,779,578,779,779,779,779,97,779,19
,265,411,779,779,779,73,1089,217,779,842,779,593,737,594,779,1409,42,1113
,411,378,465,779,33,761,321,322,649,489,19,745,1353,146,537,19,1329,609
,362,19,19,1209,19,585,297,441,403,353,651,651,651,651,651,651,1129,65,651
,651,129,449,651,307,1305,403,651,651,651,586,761,1153,651,617,233,602,361
,1185,651,659,659,659,659,659,659,651,65,659,659,129,305,659,858,386,1217
,659,659,659,657,393,1249,659,505,233,1265,1273,370,659,667,667,667,667
,667,667,659,65,667,667,129,274,667,194,498,506,667,667,667,514,522,1337
,667,530,233,154,249,721,667,675,675,675,675,675,675,667,65,675,675,129
,162,675,1385,1393,969,675,675,675,250,337,1425,675,985,233,1441,1449,553
,675,643,643,643,643,643,643,675,65,643,643,129,258,643,0,0,27,643,643,643
,0,0,27,643,0,233,27,27,0,643,0,27,27,27,27,27,643,27,27,27,27,27,27,27
,153,27,27,0,0,0,27,27,33,0,0,27,27,27,27,27,818,27,27,27,27,27,27,27,0
,27,27,947,947,0,27,27,0,0,842,27,27,27,27,27,0,27,27,27,0,27,27,27,33,27
,881,739,0,739,739,739,739,0,739,739,739,739,27,0,0,0,0,739,27,739,73,0
,27,27,842,739,27,27,27,739,27,27,0,27,0,27,739,27,27,27,185,27,0,27,153
,867,0,33,0,27,0,0,33,27,27,818,33,0,27,27,922,27,27,0,818,27,27,0,27,27
,27,27,27,842,73,27,27,27,842,314,27,27,842,27,27,0,0,27,27,0,27,27,27,27
,27,0,0,27,27,0,33,0,27,27,0,27,27,0,818,27,27,27,27,27,27,27,27,0,0,27
,27,33,73,0,27,27,842,27,27,818,0,0,27,27,27,27,27,867,27,929,0,0,0,913
,921,0,185,842,0,281,153,907,907,153,0,0,897,905,33,0,0,33,0,1169,0,907
,922,0,0,818,0,0,33,746,0,777,793,809,825,0,73,49,113,73,842,961,241,842
,1025,857,929,841,0,0,627,627,0,929,842,0,281,265,49,113,153,33,0,281,217
,963,963,153,33,818,1169,0,0,0,929,33,818,1169,265,0,0,0,0,818,281,217,33
,842,153,0,73,0,961,241,842,1025,33,73,1169,961,241,842,1025,929,818,0,0
,635,635,0,0,33,842,281,929,49,113,153,73,818,961,241,842,1025,281,33,0
,1169,153,0,0,754,0,818,0,265,33,842,1169,49,113,0,217,929,818,0,0,73,0
,961,241,842,1025,281,201,611,569,153,73,265,961,241,842,1025,281,33,217
,0,153,0,0,0,0,818,0,0,33,0,0,777,793,809,825,0,818,49,113,73,0,961,241
,842,1025,857,0,841,201,611,73,0,0,241,842,201,611,265,281,186,0,201,153
,0,217,281,0,49,113,153,33,281,0,0,33,153,201,33,818,0,0,0,818,33,0,818
,281,265,0,0,153,818,73,0,217,241,842,201,33,73,842,0,241,842,201,73,818
,281,241,842,0,153,0,0,281,0,0,0,153,33,73,467,0,241,842,201,33,818,0,49
,113,0,201,0,818,281,0,0,467,153,0,73,281,467,241,842,153,33,73,265,0,241
,842,201,33,818,217,0,33,0,201,0,818,281,0,0,818,153,0,73,281,0,241,842
,153,33,73,475,0,241,842,201,33,818,842,49,113,0,201,0,818,281,0,0,475,153
,0,73,281,475,241,842,153,33,73,265,0,241,842,201,33,818,217,0,33,0,201
,0,818,281,0,0,818,153,0,73,281,0,241,842,153,33,73,451,0,241,842,201,33
,818,842,49,113,0,201,0,818,281,0,0,451,153,0,73,281,451,241,842,153,33
,73,265,0,241,842,201,33,818,217,0,33,0,201,0,818,281,0,0,818,153,0,73,281
,0,241,842,153,33,73,0,0,241,842,0,33,818,842,867,521,0,0,201,818,0,0,0
,185,201,0,73,153,281,241,842,0,153,73,281,33,241,842,153,0,33,0,0,922,0
,201,33,0,818,0,33,0,0,0,818,281,0,73,818,153,201,842,73,0,0,241,842,33
,73,201,281,241,842,0,153,818,842,33,0,281,0,0,33,153,201,818,0,0,0,73,818
,33,241,842,281,0,0,0,153,818,0,483,0,842,73,201,33,241,842,49,113,0,867
,73,818,281,241,842,483,153,0,185,0,483,0,153,185,33,73,265,153,241,842
,33,491,818,217,0,33,0,0,922,49,113,0,0,922,346,0,73,0,491,241,842,867,73
,491,459,0,842,73,0,265,185,842,49,113,153,33,217,0,0,266,0,459,33,818,0
,1369,459,49,113,0,922,0,265,49,113,33,0,73,0,217,0,842,33,818,73,0,0,265
,842,0,818,33,0,265,217,33,0,73,33,818,217,842,33,818,73,0,818,33,842,0
,818,33,0,73,0,818,0,842,0,818,73,842,0,0,842,0,0,0,842,0,0,0,0,842,0,0
,0,842}
,
{1,16,16,16,16,16,16,16,148,16,16,16,16,16,16,20,20,117,16,16,16,49,49,16
,16,148,16,164,164,20,16,12,12,123,117,12,82,16,9,9,9,9,9,9,124,9,9,9,9
,16,9,12,9,82,9,9,9,41,12,9,9,77,9,152,152,152,9,84,77,77,22,84,84,9,22
,8,8,8,8,8,8,9,8,8,8,8,126,8,77,8,22,8,8,8,127,77,8,8,25,8,69,135,129,8
,22,42,25,25,131,135,8,10,10,10,10,10,10,10,8,10,10,10,10,10,10,57,25,135
,10,10,10,45,45,25,10,79,10,87,153,153,10,87,87,79,79,71,57,10,17,17,17
,17,17,17,17,133,17,17,17,17,17,17,2,79,93,17,17,17,57,134,79,17,57,17,72
,90,136,17,167,2,137,93,56,56,17,2,93,38,38,2,2,2,90,167,2,2,2,2,2,53,2
,2,2,2,2,2,2,118,2,6,6,6,6,6,6,139,6,6,6,6,54,6,161,161,118,6,6,6,141,118
,142,6,75,6,144,43,146,6,14,14,14,14,14,14,6,14,14,14,14,36,14,19,58,150
,14,14,14,80,47,154,14,61,14,156,157,48,14,27,27,27,27,27,27,14,27,27,27
,27,159,27,85,110,111,27,27,27,112,113,165,27,114,27,63,29,88,27,33,33,33
,33,33,33,27,33,33,33,33,65,33,171,172,119,33,33,33,174,40,176,33,121,33
,178,179,67,33,35,35,35,35,35,35,33,35,35,35,35,181,35,182,182,83,35,35
,35,182,182,83,35,182,35,83,83,182,35,182,83,83,83,83,83,35,83,83,83,91
,83,83,83,175,83,91,182,182,182,91,91,175,182,182,91,91,91,91,91,175,91
,91,91,149,91,91,91,182,91,149,55,55,182,149,149,182,182,175,149,149,149
,149,149,182,149,149,149,182,149,149,149,55,149,108,108,182,108,108,108
,108,182,108,108,108,108,86,182,182,182,182,108,86,108,55,182,86,86,55,108
,0,86,86,108,86,86,182,86,182,86,108,86,86,86,18,86,182,0,18,18,182,140
,182,0,182,182,18,0,0,140,143,182,0,0,18,0,0,182,143,155,0,182,0,0,0,155
,0,140,18,155,155,155,18,37,155,155,143,155,155,182,182,170,155,182,155
,155,155,170,155,182,182,170,170,182,37,182,170,170,182,170,170,182,37,177
,170,170,170,170,170,177,170,182,182,177,177,151,37,182,177,177,37,177,177
,151,182,182,177,177,177,177,177,109,177,115,182,182,182,109,109,182,109
,151,182,115,109,23,23,115,182,182,109,109,109,182,182,115,182,115,182,23
,109,182,182,115,182,182,23,116,182,116,116,116,116,182,109,116,116,115
,109,115,115,115,115,116,147,116,182,182,52,52,182,81,23,182,147,116,52
,52,147,60,182,81,116,59,59,81,147,60,147,182,182,182,92,81,147,81,52,182
,182,182,182,81,92,52,59,60,92,182,147,182,147,147,147,147,92,81,92,81,81
,81,81,94,92,182,182,51,51,182,182,158,59,94,89,51,51,94,92,158,92,92,92
,92,89,94,182,94,89,182,182,31,182,94,182,51,89,158,89,31,31,182,51,145
,89,182,182,94,182,94,94,94,94,145,68,68,68,145,89,31,89,89,89,89,68,145
,31,182,68,182,182,182,182,145,182,182,68,182,182,95,95,95,95,182,68,95
,95,145,182,145,145,145,145,95,182,95,46,46,68,182,182,68,68,70,70,95,46
,4,182,26,46,182,95,70,182,4,4,70,46,26,182,182,160,26,11,70,46,182,182
,182,160,26,182,70,11,4,182,182,11,26,46,182,4,46,46,28,11,70,160,182,70
,70,30,26,11,28,26,26,182,28,182,182,30,182,182,182,30,28,11,101,182,11
,11,32,30,28,182,101,101,182,13,182,30,32,182,182,101,32,182,28,13,101,28
,28,13,32,30,101,182,30,30,34,13,32,101,182,162,182,96,182,13,34,182,182
,162,34,182,32,96,182,32,32,96,34,13,103,182,13,13,98,96,34,162,103,103
,182,100,182,96,98,182,182,103,98,182,34,100,103,34,34,100,98,96,103,182
,96,96,102,100,98,103,182,163,182,104,182,100,102,182,182,163,102,182,98
,104,182,98,98,104,102,100,97,182,100,100,106,104,102,163,97,97,182,5,182
,104,106,182,182,97,106,182,102,5,97,102,102,5,106,104,97,182,104,104,15
,5,106,97,182,166,182,50,182,5,15,182,182,166,15,182,106,50,182,106,106
,50,15,5,182,182,5,5,182,50,15,166,62,62,182,182,3,50,182,182,182,62,7,182
,15,62,3,15,15,182,3,50,7,62,50,50,7,182,3,182,182,62,182,73,7,182,3,182
,122,182,182,182,7,73,182,62,122,73,76,62,3,182,182,3,3,73,7,168,76,7,7
,182,76,73,122,125,182,168,182,182,76,168,78,125,182,182,182,73,76,168,73
,73,78,182,182,182,78,168,182,105,182,125,76,24,78,76,76,105,105,182,64
,168,78,24,168,168,105,24,182,64,182,105,182,64,21,24,78,105,21,78,78,64
,107,24,105,182,21,182,182,64,107,107,182,182,21,44,182,24,182,107,24,24
,39,64,107,99,182,64,21,182,107,39,21,99,99,39,44,107,182,182,74,182,99
,39,44,182,169,99,74,74,182,39,182,99,169,169,120,182,44,182,99,182,44,128
,120,39,182,182,74,39,182,128,130,182,169,74,173,182,120,138,130,169,120
,66,173,128,182,138,132,128,182,66,180,182,130,182,132,182,130,182,180,138
,173,182,182,138,182,182,182,66,182,182,182,182,132,182,182,182,180,182
}
,
{444,0,162,1010,767,953,207,1016,73,36,110,785,21,841,236,974,0,147,447
,235,13,1108,59,567,1097,96,770,265,806,292,813,691,834,294,862,323,248
,495,186,1145,314,55,103,234,1138,130,757,256,263,19,981,667,610,197,219
,393,180,123,250,625,600,260,1005,290,1103,305,1185,322,715,98,764,143,173
,1037,1163,231,1052,58,1076,133,256,614,34,323,33,242,413,103,293,675,173
,347,635,162,664,737,869,941,890,1148,897,829,918,885,925,1092,946,1125
,417,553,279,280,284,285,288,556,589,15,205,310,1158,316,1020,31,41,1047
,84,93,1165,99,1174,105,1190,153,166,78,174,177,1181,212,442,226,227,451
,232,704,235,607,6,371,252,516,62,136,257,466,234,263,650,276,761,220,845
,901,25,287,957,175,1061,1169,488,268,309,1178,313,353,315,510,280,321,1194
,334}
,
{
{{1,1}
,{1,1}
,{1,1}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{3,3}
,{2,2}
,{46,46}
,{15,15}
,{46,46}
,{3,3}
,{46,46}
,{2,2}
,{2,2}
,{17,17}
,{17,17}
,{3,3}
,{46,46}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{2,2}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{46,46}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{50,50}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{50,50}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{46,46}
,{3,3}
,{2,2}
,{46,46}
,{4,4}
,{46,46}
,{3,3}
,{2,2}
,{46,46}
,{3,3}
,{18,18}
,{39,39}
,{39,39}
,{18,18}
,{39,39}
,{2,2}
,{46,46}
,{3,3}
,{18,18}
,{46,46}
,{3,3}
,{46,46}
,{5,5}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{46,46}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{46,46}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{50,50}
,{4,4}
,{50,50}
,{3,3}
,{4,4}
,{50,50}
,{3,3}
,{2,2}
,{50,50}
,{4,4}
,{50,50}
,{4,4}
,{50,50}
,{3,3}
,{4,4}
,{50,50}
,{3,3}
,{4,4}
,{46,46}
,{4,4}
,{50,50}
,{3,3}
,{4,4}
,{50,50}
,{3,3}
,{46,46}
,{2,2}
,{46,46}
,{3,3}
,{18,18}
,{2,2}
,{50,50}
,{3,3}
,{3,3}
,{3,3}
,{18,18}
,{30,30}
,{2,2}
,{50,50}
,{3,3}
,{50,50}
,{3,3}
,{50,50}
,{50,50}
,{3,3}
,{2,2}
,{50,50}
,{19,19}
,{46,46}
,{3,3}
,{18,18}
,{42,42}
,{2,2}
,{50,50}
,{3,3}
,{50,50}
,{3,3}
,{18,18}
,{42,42}
,{2,2}
,{50,50}
,{3,3}
}
,
{0,0,0,0,0,0,0}
,
{0,0,0,0,0,0,0}
,
{0,0,0,0,0,0,0}
}
};


/* Non terminal table *\
\* ------------------ */
typedef  struct {
    UByte2 gto[943];		/* Goto table */
    UByte2 gtoRix[182];		/* Goto row mapping */
    UByte1 lhs[125];		/* Left hand side symbols */
    UByte1 rhsz[125];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{17,289,89,0,0,682,0,714,0,873,0,665,938,689,202,210,10,977,769,681,705
,145,546,554,762,930,730,953,418,25,914,770,25,89,1233,137,850,1041,289
,89,1417,1001,682,434,714,850,873,826,729,81,137,850,145,1057,1241,769,834
,850,145,546,554,1105,826,730,953,418,137,850,834,0,137,850,137,850,1137
,289,89,1081,826,682,434,714,826,873,826,945,137,850,850,0,1145,242,937
,226,1002,145,546,554,826,834,730,953,418,986,25,0,25,137,850,137,850,0
,289,89,1121,1377,682,434,714,826,873,826,1193,137,850,0,0,218,25,769,1433
,0,145,546,554,826,1257,730,953,418,25,473,0,25,289,89,137,850,682,25,714
,0,873,954,434,794,0,1297,826,0,0,769,481,850,145,546,554,0,0,730,753,418
,0,457,826,0,289,89,137,850,682,0,714,0,873,954,434,0,137,850,826,0,0,769
,481,850,145,546,554,0,826,730,0,426,0,0,826,0,289,89,137,850,682,0,714
,0,873,0,434,794,0,1321,826,0,0,769,1161,0,145,546,554,289,89,730,0,682
,0,714,0,738,0,1017,137,850,0,0,0,0,425,0,442,145,137,850,826,0,730,0,34
,137,850,0,0,0,826,137,850,497,401,0,313,826,122,90,137,850,577,826,50,98
,138,114,0,0,58,130,826,106,66,82,74,289,89,0,345,682,0,714,369,738,137
,850,0,137,850,0,0,1225,425,0,0,145,826,289,89,826,730,682,0,714,0,738,433
,0,0,137,850,1281,401,0,425,137,850,145,0,0,385,826,730,0,137,850,0,826
,0,289,89,137,850,682,401,714,826,738,0,0,0,0,561,826,137,850,641,0,0,145
,0,289,89,0,730,682,826,714,0,738,0,0,0,137,850,0,0,0,257,0,0,145,0,289
,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0,41,0,0,145,0,289,89,826
,730,682,0,714,0,738,0,0,0,137,850,0,0,0,417,0,0,145,0,289,89,826,730,682
,0,714,0,738,0,0,0,137,850,0,0,0,105,0,0,145,0,289,89,826,730,682,0,714
,0,738,0,0,0,137,850,0,0,0,785,0,0,145,0,289,89,826,730,682,0,714,0,738
,0,0,0,137,850,0,0,0,801,0,0,145,0,289,89,826,730,682,0,714,0,738,0,0,0
,137,850,0,0,0,817,0,0,145,0,289,89,826,730,682,0,714,0,738,0,0,0,137,850
,0,0,0,833,0,0,145,0,289,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0
,849,0,0,145,0,289,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0,865,0
,0,145,0,289,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0,209,0,0,145
,0,289,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0,601,0,0,145,0,289
,89,826,730,682,0,714,0,738,0,0,0,137,850,0,0,0,625,0,0,145,0,289,89,826
,730,682,0,714,0,738,0,0,0,137,850,0,0,0,1361,0,0,145,0,225,89,826,730,682
,0,714,0,738,0,0,0,137,850,0,0,0,0,0,0,145,0,121,89,826,730,682,0,714,0
,738,0,0,0,137,850,0,0,0,0,0,0,145,545,273,89,826,730,682,802,714,0,738
,0,0,0,137,850,0,1073,0,0,0,0,145,0,57,89,826,730,682,0,714,0,738,0,137
,850,137,850,0,0,137,850,882,1345,145,169,826,898,826,730,137,850,826,0
,0,0,329,0,137,850,930,89,826,0,698,914,714,0,738,0,826,0,0,0,193,850,137
,850,882,0,145,169,0,898,89,730,826,706,826,714,0,738,513,0,137,850,930
,0,0,0,0,914,882,145,0,169,826,898,730,882,193,850,169,0,898,0,889,137,850
,0,930,0,826,529,0,914,0,930,1097,826,0,0,914,882,193,850,169,0,898,0,0
,193,850,0,0,89,826,161,690,0,714,930,738,826,1401,0,914,0,0,0,0,137,850
,993,145,193,850,89,0,730,722,890,714,826,738,0,898,826,137,850,1457,0,0
,0,0,0,145,137,850,930,826,730,0,0,914,0,137,850,0,826,137,850,0,193,850
,0,0,0,826,0,0,0,826,137,850,826,0,0,0,0,0,0,0,0,0,826}
,
{0,17,248,388,16,740,14,860,5,58,9,432,11,696,11,776,9,16,847,11,11,885
,4,52,586,11,674,10,799,10,366,9,718,9,882,9,9,268,9,756,6,5,5,5,296,5,290
,5,5,5,410,4,4,4,4,159,4,127,4,21,265,4,792,4,823,3,716,3,312,2,230,2,2
,608,2,2,630,2,344,1,1,0,1,3,1,0,75,2,0,37,0,77,143,0,175,0,454,0,476,0
,498,0,520,0,542,0,564,0,0,816,0,0,0,0,0,74,0,0,0,0,15,0,878,0,0,239,0,0
,35,0,51,0,732,0,0,843,0,0,88,0,72,0,0,224,0,207,0,111,0,111,0,305,0,34
,0,120,0,0,325,0,153,0,722,217,0,0,758,0,652,0,99,0,0,869,0,31,0,114,0,0
,895,0}
,
{52,68,81,81,62,62,62,62,62,62,62,62,62,62,62,62,62,82,77,77,83,83,88,76
,64,64,71,71,65,65,84,84,91,89,86,86,72,72,92,92,92,92,94,94,94,94,93,93
,85,63,63,79,79,80,80,95,95,95,95,95,95,95,95,95,95,95,95,95,95,74,74,75
,75,75,75,98,98,90,90,70,70,70,70,70,53,53,53,53,57,57,59,59,59,59,61,61
,67,67,56,56,54,54,87,87,99,99,73,69,69,58,58,55,55,60,60,60,60,66,66,66
,78,96,96,97,97}
,
{1,1,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,6,5,6,3,7,1,2,5,6,0,2,11,11,4,11
,0,3,0,2,3,4,4,7,3,4,4,7,4,6,6,1,3,1,3,1,2,3,3,3,3,3,3,4,4,4,4,4,3,1,1,6
,6,8,8,8,8,0,1,1,3,1,3,3,3,3,1,3,3,3,1,2,1,1,3,4,2,2,0,3,1,3,1,1,1,2,1,1
,3,0,1,1,3,1,1,1,1,1,2,0,1,1,2,0,2,1,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[51];

static VocTab voc = {{1,255,255,"EndOfText",""}
,{2,1,1,"'('",""}
,{3,1,1,"')'",""}
,{4,1,1,"','",""}
,{5,1,1,"'='",""}
,{6,1,1,"'#'",""}
,{7,1,1,"'>'",""}
,{8,1,1,"'<'",""}
,{9,1,1,"'?'",""}
,{10,1,1,"'*'",""}
,{11,1,1,"'+'",""}
,{12,1,1,"'-'",""}
,{13,1,1,"'/'",""}
,{14,1,1,"'['",""}
,{15,1,1,"']'",""}
,{16,1,1,"'{'",""}
,{17,1,1,"'}'",""}
,{18,1,1,"TEXT",""}
,{19,1,1,"'<='",""}
,{20,1,1,"'OR'",""}
,{21,1,1,"'>='",""}
,{22,1,1,"'?R'",""}
,{23,1,1,"'?V'",""}
,{24,1,1,"'%%('",""}
,{25,1,1,"'AND'",""}
,{26,1,1,"'NOT'",""}
,{27,1,1,"'MOD'",""}
,{28,1,1,"'%%IF'",""}
,{29,1,1,"'%%SET'",""}
,{30,1,1,"'%%END'",""}
,{31,1,1,"'BITOR'",""}
,{32,1,1,"INTEGER",""}
,{33,1,1,"'%%KEEP'",""}
,{34,1,1,"'%%ESET'",""}
,{35,1,1,"'%%ELSE'",""}
,{36,1,1,"'%%LOOP'",""}
,{37,1,1,"'%%EXIT'",""}
,{38,1,1,"'BITAND'",""}
,{39,1,1,"'%%ENDIF'",""}
,{40,1,1,"'%%ELSIF'",""}
,{41,1,1,"'%%BEGIN'",""}
,{42,1,1,"'%%ENDLOOP'",""}
,{43,1,1,"'%%MESSAGE'",""}
,{44,1,1,"'%%INCLUDE'",""}
,{45,1,1,"'%%PROCESS'",""}
,{46,1,1,"QUOT_STRING",""}
,{47,1,1,"'%%EINCLUDE'",""}
,{48,1,1,"'IMP$SYSTEM'",""}
,{49,1,1,"'IMP$STRLEN'",""}
,{50,1,1,"UNQUOT_STRING",""}
,{51,1,1,"'IMP$STRSEARCH'",""}
}
;


/* Variables used in the parsing process *\
\* ------------------------------------- */
short impStkP;			/* Stack pointer */
TmToken impSySt[PmStkMax];	/* Symbol stack */
impGrammar impSeSt[PmStkMax];	/* Semantic stack */
static UByte1 currstat;		/* Current state number */
static UByte1 arg;		/* Argument */
static UByte1 action;		/* Action type */
static PmBoolean endparse;	/* Termination flag */
static ParseStack parsStk;	/* Parse stack */
static UByte1 scIndex[51 + 1]; /* Converts scanner code to internal value */
static TmToken tokenBuf;	/* Scanner token buffer */
static TmToken *token = &tokenBuf;	/* Pointer to it for readsymb */


/* Error recovery look-ahead buffer *\
\* -------------------------------- */
static TmToken la_buff[PmLaMax + 1]; /* Buffer */
static int la_ptr;		/* Current pointer */
static int la_end;		/* Last item */

static jmp_buf pmJmpB;		/* Buffer for long jump */

/* Interface routines *\
\* ------------------ */

extern void impRPoi(	/* Error recovery - restart point  */
TmToken *sym			/* IN the restart symbol */
);
extern void impISym(	/* Error recovery - insert symbol  */
 int code,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr,			/* IN the terminals print symbol */
TmToken *sym			/* OUT the created scanner symbol */
);
extern void impDSym(	/* Error recovery - delete symbol  */
TmToken *sym,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr			/* IN terminals print string */
);
extern void impMess(	/* Error recovery - error message  */
TmToken *sym,			/* IN error token */
int method,			/* IN recovery method */
int code,			/* IN error classification */
int severity			/* IN error severity code */
);

/* External functions */
extern void impPaSema(
int rule			/* IN production number */
);

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(
TmToken *token,		/* IN current token */
short eClass,			/* IN error classification */
short severity			/* IN error severity code */
)
{
    impMess(token, HALT_REC, eClass, severity);
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
#define SetClear(set, length) memset((void *)set, 0, (size_t)((length) + 7) >> 3)

/*----------------------------------------------------------------------------
 * SetMem - Check member inclusion
 *----------------------------------------------------------------------------
 */
#define SetMem(set, n) ((set)[(n) >> 3] & (0x80 >> ((n) & 0x7)))


/*----------------------------------------------------------------------------
 * paInit - Initialize the parsing process
 *----------------------------------------------------------------------------
 */
static void paInit(void)
{
    short i;

    la_ptr = 0;
    la_end = 0;
    impStkP = 0;
    currstat = 1;
    endparse = PMFALSE;
    parsStk[0] = 1;

    /* Scanner interface */
    for (i = 0; i <= SccMax; i++) scIndex[i] = ERR_SYM;
    for (i = TermMin; i <= Terms; i++) scIndex[voc[i - TermMin].scc] = (UByte1)i;
}/*paInit()*/


/*----------------------------------------------------------------------------
 * pushStat[Tok] - Push the current state on the stack and possibly push current
 *        token on the symbol stack.
 *----------------------------------------------------------------------------
 */
#define MOVETOKEN impSySt[impStkP] = *token
#define pushStatTok()\
{\
    if (++impStkP < PmStkMax) {\
    parsStk[impStkP] = currstat;\
    MOVETOKEN;\
    } else {\
    token->code = voc[token->code-TermMin].scc;\
    paAbort(token, OFLW_ERR, SYS_SEV);\
    }\
}

#define pushStat()\
{\
    if (++impStkP < PmStkMax) {\
    parsStk[impStkP] = currstat;\
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
 *           t = current token
 *           y = unprocessed input
 *----------------------------------------------------------------------------
 */

typedef struct {
    TmToken err_tok;
    TmToken res_tok;
    short method;
    short eClass;
    short severity;
} ERR_REC;

static ERR_REC errdescr;


/*----------------------------------------------------------------------------
 * ePush - Push a state during error recovery
 *----------------------------------------------------------------------------
 */
static void ePush(
UByte1 state,			/* IN state to push */
UByte1 stack[],			/* INOUT parser stack */
short *sp			/* INOUT current stack pointer */
)
{
    if (++(*sp) < PmStkMax) stack[*sp] = state;
    else paAbort(&errdescr.err_tok, OFLW_ERR, SYS_SEV);
}/*ePush()*/


/*----------------------------------------------------------------------------
 * legalAct - Check if a symbol is legal to shift in current state
 *----------------------------------------------------------------------------
 */
static PmBoolean legalAct(
UByte1 stack[],			/* IN current stack */
short stack_p,			/* IN current stack pointer */
UByte1 sym			/* IN symbol code */
)				/* RET true if "symbol" is read (shifted) */
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
static void gLegSym(
ParseStack stack,		/* IN current stack */
short stack_p,			/* IN current stack pointer */
TermSet legals			/* OUT legal symbols in current state */
)
{
    short sym;			/* Loop index */

    SetClear(legals, Terms + 1);
    for (sym = 1; sym <= Terms; sym++) {
    if (legalAct(stack, stack_p, sym)) SetIns(legals, sym);
    }/*for*/
}/*gLegSym()*/


/*----------------------------------------------------------------------------
 * backup - Backup the parse stack until current symbol is accepted (shifted)
 *      or the parse stack becomes empty
 *----------------------------------------------------------------------------
 */
static short backup(
ParseStack stack,		/* IN current stack */
short stack_p,			/* IN current stack pointer */
UByte1 sym	/* IN recovery symbol */
)				/* RET new stack pointer, 0 if symbol is */
                /*     not accepted */
{
    while ((stack_p > 0) && (!legalAct(stack, stack_p, sym))) stack_p--;
    return(stack_p);
}/*backup()*/


/*----------------------------------------------------------------------------
 * delSym - Delete a symbol in the input stream
 *----------------------------------------------------------------------------
 */
static void delSym(
TmToken *token			/* INOUT symbol to delete, new symbol */
)
{
    short  t;

    t = token->code - TermMin;
    token->code = voc[t].scc;
    impDSym(token, voc[t].name, voc[t].psym);
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
static void inSym(
short isym,			/* IN symbol code to insert */
TmToken *gen_symb		/* OUT created symbol */
)
{
    impISym(voc[isym - TermMin].scc, voc[isym - TermMin].name,
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
 *        the continuation grammar.
 *----------------------------------------------------------------------------
 */
static void acceptbl(
UByte1 sym,			/* IN terminal symbol code */
ParseStack stack,		/* IN parse stack */
short stack_p,			/* IN stack pointer */
TmToken *token,			/* IN current token */
PmBoolean *found,		/* OUT "symbol" accepted? */
REC_POI *point			/* OUT recovery point description */
)
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
static void search(
ParseStack stack,		/* IN current stack */
short *stack_p,			/* INOUT current stack pointer */
TmToken *token,			/* INOUT current symbol */
REC_POI *point			/* OUT descriptor of where to restart */
                /*     the parser */
)
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
static void reach(
ParseStack stack,		/* INOUT current stack */
short *stack_p,			/* INOUT current stack pointer */
TmToken *token,			/* INOUT current symbol */
REC_POI *point			/* IN recovery point descriptor */
)
{
    UByte1 state;		/* Current state */
    UByte1 cont_sym;		/* Continuation symbol */
    TmToken gen_symb;		/* Generated symbol */
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
        impSySt[*stack_p] = gen_symb;
        break;

      case SHIFTRED_ACT:
        sepaAccept = PMTRUE;
        inSym(cont_sym, &gen_symb);
        ePush(state, stack, stack_p);
        impSySt[*stack_p] = gen_symb;
        goto reduce;

      case REDUCE_ACT:
        reduce:
        do {
        *stack_p = *stack_p - gto.rhsz[arg-ProdMin];
        impPaSema(arg);
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
static void multiple(
ParseStack err_stk,		/* INOUT current parse stack */
short *err_stkp,		/* INOUT current stack pointer */
TmToken *err_tok,		/* INOUT current token */
UByte1 *newstat		/* OUT state after recovery */
)
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
static void readLa(
TmToken *curtok			/* IN current token */
)
{
    int i;
    TmToken tokbuf;
    TmToken *token = &tokbuf;

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
             impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else {
        token->code = scIndex[token->code];
        }/*if*/
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
        }/*if*/
    } while (token->code == ERR_SYM);
    la_buff[la_end] = *token;
    }/*while*/
}/*readLa()*/


/*----------------------------------------------------------------------------
 * rdLaSym - Fetches the i:th look-ahead symbol code from the look-ahead set
 *----------------------------------------------------------------------------
 */
static UByte1 rdLaSym(
char index			/* IN i:th look-ahead symbol */
)				/* RET token code */
{
    if (index > la_end) return(ENDMARK);
    else return(la_buff[(int)index].code);
}/*rdLaSym()*/


/*----------------------------------------------------------------------------
 * laParse - Continue the parsing process by reading tokens from the
 *       look-ahead set. The parse is terminated when:
 *       - out of read ahead
 *       - a new error is encountered
 *       Note! No semantic actions are carried out
 *----------------------------------------------------------------------------
 */
static void laParse(
UByte1 sym,			/* IN current terminal symbol */
char next_la,			/* IN index to next look-ahead symbol */
ParseStack stack,		/* IN parse stack */
short stack_p,			/* IN current stack pointer */
short *cost			/* OUT adaption cost */
)
{
    PmBoolean done ;		/* Terminator flag */
    char sh_cnt;		/* Number of shifted symbols */
    UByte1 state;		/* Current state number */
    UByte1 action;		/* Parser action */
    UByte1 arg;      /* Parser argument */
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
static void tryIn(
TermSet legals,			/* IN set of legal symbols */
ParseStack stack,		/* IN current parser stack */
short stack_p,			/* IN current stack pointer */
UByte1 *sym,			/* OUT best insertion symbol */
short *cost,			/* OUT best cost so far */
short *choice			/* OUT best choice so far */
)
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
 *      x t y  => x s y, where s becomes current symbol
 *----------------------------------------------------------------------------
 */
static void tryRep(
TermSet legals,			/* IN set of legal symbols */
ParseStack stack,		/* IN current parser stack */
short stack_p,			/* IN current stack pointer */
UByte1 *sym,			/* OUT best replacement symbol */
short *cost,			/* OUT best cost so far */
short *choice			/* OUT best choice so far */
)
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
static void tryDel(
ParseStack stack,		/* IN current parser stack */
short stack_p,			/* IN current stack pointer */
short *cost,			/* INOUT best cost so far */
short *choice			/* INOUT best choice so far */
)
{
    short mod_cost;		/* Modification cost */
    short ad_cost;          /* Adaption cost */
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
static void _pmInsert(
UByte1 sym,			/* IN symbol code to insert */
TmToken *token			/* OUT constructed token */
)
{
    inSym(sym, token);
}/*_pmInsert()*/


/*----------------------------------------------------------------------------
 * _pmReplace
 *----------------------------------------------------------------------------
 */
static void _pmReplace(
UByte1 sym,			/* IN replacement symbol code */
TmToken *token			/* OUT constructed token */
)
{
    delSym(token);
    inSym(sym, token);
}/*_pmReplace()*/


/*----------------------------------------------------------------------------
 * _pmDelete
 *----------------------------------------------------------------------------
 */

static void _pmDelete(
TmToken *token			/* OUT new token */
)
{
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
static void single(
TermSet leg_sys,		/* IN legal symbols in current state */
ParseStack err_stk,		/* INOUT current parser stack */
short *err_stkp,		/* INOUT current stack pointer */
TmToken *token,		/* INOUT current token */
UByte1 *newstat		/* OUT recovery state */
)
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
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
static void recover(
ParseStack err_stk,		/* INOUT updated parse stack */
short *err_stkp,		/* INOUT updated stack pointer */
TmToken *err_symb,		/* INOUT current token */
UByte1 *rec_stat		/* OUT state after recovery */
)
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
    impMess(&errdescr.err_tok, errdescr.method, errdescr.eClass,
           errdescr.severity);
    } else {
    impMess(&errdescr.err_tok, errdescr.method, SYN_ERR, errdescr.severity);
    }/*if*/
    errdescr.res_tok = *err_symb;
    errdescr.res_tok.code = voc[errdescr.res_tok.code - TermMin].scc;
    impRPoi(&errdescr.res_tok);
}/*recover()*/


/*----------------------------------------------------------------------------
 * impParse - Parser routine, entry point
 *----------------------------------------------------------------------------
 */
void impParse(void)
{
    paInit();
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
        recover(parsStk, &impStkP, token, &currstat);
        if (impStkP == 0) endparse = PMTRUE;
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
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
         impScan(impcontext, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        impMess(token, DEL_REC, LEX_ERR, FAT_SEV);
        }
    } while (token->code == ERR_SYM);
    }
}
        goto reduce;

    case REDUCE_ACT:
      reduce:
        do {
        impStkP -= gto.rhsz[arg - ProdMin];
        impPaSema(arg);
        gtoTbl(parsStk[impStkP], gto.lhs[arg - ProdMin], &action, &arg);
        pushStat();
        } while (action != SHIFT_ACT);

        currstat = arg;
        parsStk[impStkP] = currstat;
        break;

    case ACCEPT_ACT:
        endparse = PMTRUE;
        break;
    }/*switch*/
    }/*while*/
}/*impParse()*/

