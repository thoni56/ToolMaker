/*----------------------------------------------------------------------*\

	impParse.c

	ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */

/* .pmk-import */
#include <stdio.h>
#include "ast.h"
#include "impScan.h"
#include "impList.h"
extern impContext impcontext;
/* END %%IMPORT */

#include <strings.h>
#include <memory.h>
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
    Ast ast         /* An abstract syntax tree */;
    TmSrcp srcp      /* Source position         */;
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
#define SccMax 45		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 45		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 147		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 108		/* Number of productions */
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
    ContRec cont[147];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[930];		/* Action table */
    UByte1 actCheck[930];	/* Row Displacement Check Vector*/
    UByte2 actRix[147];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{4,691,691,691,691,691,691,691,427,691,691,691,691,691,691,609,49,113,691
,691,691,250,833,33,691,427,841,243,243,722,427,835,835,835,835,835,835
,561,835,835,835,835,721,835,714,835,761,835,835,835,49,113,33,835,897,843
,843,843,843,843,843,705,843,843,843,843,634,843,881,843,858,843,843,843
,49,113,843,843,659,659,659,659,659,659,659,897,659,659,659,659,97,659,338
,393,843,659,659,659,259,817,490,659,659,659,659,659,659,659,659,865,659
,659,659,659,97,659,33,897,33,659,659,659,722,265,722,659,563,563,563,563
,563,563,226,65,563,563,129,714,563,714,49,113,563,563,563,138,755,177,563
,571,571,571,571,571,571,298,65,571,571,129,755,571,33,641,33,571,571,571
,722,146,722,571,555,555,555,555,555,555,290,65,555,555,129,714,555,714
,19,665,555,555,555,481,19,234,555,19,19,249,282,19,19,19,19,19,19,19,34
,19,19,19,689,19,33,49,113,537,417,666,289,130,465,585,681,187,857,601,19
,513,225,369,154,281,19,267,833,19,19,531,337,19,19,19,19,19,19,19,34,19
,19,19,322,19,33,305,314,537,417,162,521,130,465,585,681,187,857,601,19
,513,225,369,377,281,19,745,738,19,19,210,545,19,19,777,19,19,34,19,450
,19,19,19,33,19,458,537,417,466,474,130,465,482,681,195,19,601,233,513,225
,369,19,281,801,19,19,19,346,19,19,218,19,1121,34,19,321,19,19,19,33,19
,1137,537,417,657,178,130,465,506,681,1161,19,601,330,513,225,369,19,281
,514,19,19,433,0,19,19,0,19,0,34,19,19,19,19,19,33,19,0,537,417,0,0,130
,465,0,681,0,19,601,737,513,225,369,19,281,0,19,19,0,0,19,19,306,19,0,34
,19,19,19,19,19,33,19,0,537,417,19,0,130,465,0,681,0,33,601,793,513,225
,369,722,281,0,33,19,11,0,0,0,722,19,0,73,19,19,714,0,19,19,0,19,73,34,19
,714,19,19,19,33,19,0,537,417,0,0,130,465,0,681,0,0,601,0,513,225,369,0
,281,1033,627,1081,627,627,627,627,747,627,627,627,627,217,1065,1073,1081
,153,627,0,627,153,0,0,0,33,217,1049,1057,33,153,722,0,539,539,722,0,0,33
,1081,1177,49,113,73,722,1113,714,73,33,217,714,747,1081,153,722,0,73,0
,1113,714,0,33,217,1177,153,0,153,722,0,714,0,0,33,0,33,1081,1177,0,722
,73,722,1113,714,811,811,217,193,523,497,153,73,0,73,714,1113,714,217,33
,0,1177,153,0,0,722,33,0,1081,0,33,0,722,0,0,153,722,73,217,1113,714,363
,153,33,73,547,547,714,73,722,33,714,1177,49,113,0,722,634,363,929,945,961
,977,913,714,49,113,0,73,0,1113,714,0,1009,0,993,193,523,929,945,961,977
,0,355,49,113,217,193,523,193,153,0,1009,0,993,0,193,217,33,217,355,153
,0,153,722,913,217,0,0,33,153,33,193,0,0,722,73,722,33,714,0,193,217,193
,722,0,153,73,193,73,714,217,714,217,33,153,73,153,217,714,722,0,153,33
,0,33,0,0,193,722,33,722,73,0,0,714,722,0,217,193,0,73,153,73,714,0,714
,0,73,217,33,714,193,153,0,435,722,0,0,193,0,33,217,49,113,0,153,722,73
,217,0,714,435,153,33,193,193,435,0,73,722,33,714,0,811,217,217,722,33,153
,153,0,73,0,722,714,0,33,33,73,193,0,714,722,722,33,0,193,0,714,217,722
,747,449,153,73,73,217,714,714,193,153,33,73,0,153,714,193,722,33,217,0
,33,33,153,722,0,217,722,722,73,153,33,714,747,0,0,73,722,33,714,73,193
,714,714,722,0,153,787,787,73,0,217,714,0,33,153,73,153,747,714,722,787
,153,33,0,33,0,0,33,722,33,722,73,0,722,714,722,0,827,827,0,73,0,73,714
,443,714,403,73,714,274,714,170,49,113,49,113,33,0,33,49,113,443,722,403
,722,411,443,0,403,33,33,0,419,49,113,722,722,714,33,714,49,113,411,0,722
,0,33,411,73,419,714,714,722,0,419,33,0,0,0,714,0,722,0,0,0,0,0,714,0,0
,0,0,0,0,0,0,714}
,
{1,16,16,16,16,16,16,16,122,16,16,16,16,16,16,74,122,122,16,16,16,105,105
,16,16,122,76,76,76,16,122,9,9,9,9,9,9,68,9,9,9,9,88,9,16,9,86,9,9,9,88
,88,9,9,68,8,8,8,8,8,8,86,8,8,8,8,24,8,108,8,9,8,8,8,24,24,8,8,10,10,10
,10,10,10,10,108,10,10,10,10,10,10,47,47,8,10,10,10,77,77,136,10,17,17,17
,17,17,17,17,106,17,17,17,17,17,17,57,136,92,17,17,17,57,31,92,17,6,6,6
,6,6,6,65,6,6,6,6,57,6,92,65,65,6,6,6,54,20,20,6,14,14,14,14,14,14,32,14
,14,14,14,20,14,75,78,99,14,14,14,75,56,99,14,25,25,25,25,25,25,33,25,25
,25,25,75,25,99,69,81,25,25,25,58,69,83,25,69,69,29,29,69,69,69,69,69,69
,69,70,69,69,69,84,69,70,12,12,70,70,12,34,70,70,70,70,70,70,70,109,70,70
,70,60,70,109,102,102,109,109,40,40,109,109,109,109,109,109,109,110,109
,109,109,44,109,110,36,36,110,110,62,63,110,110,110,110,110,110,110,72,110
,110,110,45,110,72,91,19,72,72,93,66,72,72,95,72,72,73,72,129,72,72,72,73
,72,130,73,73,131,132,73,73,133,73,73,79,73,27,73,73,73,79,73,98,79,79,79
,49,79,79,100,79,138,80,79,38,79,79,79,80,79,140,80,80,80,71,80,80,142,80
,143,89,80,39,80,80,80,89,80,145,89,89,52,147,89,89,147,89,147,90,89,89
,89,89,89,90,89,147,90,90,147,147,90,90,147,90,147,96,90,90,90,90,90,96
,90,147,96,96,147,147,96,96,35,96,147,97,96,96,96,96,96,97,96,147,97,97
,0,147,97,97,147,97,147,35,97,97,97,97,97,35,97,147,139,0,2,147,147,147
,139,0,147,35,0,0,35,147,0,0,147,0,139,2,0,139,0,0,0,2,0,147,2,2,147,147
,2,2,147,2,147,147,2,147,2,2,2,147,2,127,127,146,127,127,127,127,128,127
,127,127,127,146,128,128,67,146,127,147,127,128,147,147,147,146,67,128,128
,128,67,146,147,43,43,128,147,147,67,111,67,43,43,146,67,146,146,128,101
,111,128,30,113,111,101,147,67,147,67,67,147,111,113,111,30,147,113,111
,147,101,147,147,30,147,113,107,113,147,30,111,113,111,111,46,46,107,59
,59,59,107,30,147,113,30,113,113,59,107,147,107,59,147,147,107,46,147,134
,147,59,147,46,147,147,94,59,107,134,107,107,112,134,94,46,42,42,46,59,94
,134,59,134,42,42,147,134,135,112,135,135,135,135,112,94,135,135,147,134
,147,134,134,147,135,147,135,61,61,114,114,114,114,147,137,114,114,61,37
,37,64,61,147,114,147,114,147,3,37,61,64,137,37,147,64,61,137,3,147,147
,37,3,64,7,147,147,37,61,64,3,61,147,23,7,11,3,147,7,37,26,64,37,23,64,11
,7,23,3,11,26,3,7,147,26,23,147,11,147,147,13,23,26,11,7,147,147,7,26,147
,13,115,147,23,13,11,23,147,11,147,26,115,13,26,117,115,147,124,13,147,147
,119,147,115,117,124,124,147,117,115,13,119,147,13,124,119,117,121,123,124
,147,115,117,119,115,147,48,121,123,119,103,121,123,147,117,147,103,117
,147,121,123,119,125,147,119,121,123,48,147,41,147,103,125,48,53,53,125
,121,123,41,121,123,87,41,125,48,147,53,48,5,125,41,87,147,104,53,87,41
,147,5,104,53,125,5,87,125,55,147,147,41,87,5,41,53,15,104,53,5,147,55,22
,22,87,147,15,87,147,55,15,5,18,18,5,55,22,21,15,147,18,147,147,22,15,21
,18,55,147,22,55,21,147,50,50,147,15,147,18,15,126,18,116,21,22,28,21,4
,126,126,116,116,51,147,50,4,4,126,51,116,50,118,126,147,116,82,28,147,120
,118,118,82,28,51,85,50,120,120,118,147,85,147,141,118,28,120,82,28,141
,147,120,144,147,147,147,85,147,144,147,147,147,147,147,141,147,147,147
,147,147,147,147,147,144}
,
{403,0,421,636,862,787,124,652,53,29,77,663,203,688,147,812,0,101,814,258
,144,819,817,661,64,170,668,303,860,196,512,121,153,176,217,387,252,627
,320,338,235,767,584,494,248,269,544,90,743,312,848,846,348,771,143,803
,167,93,190,548,228,616,255,257,629,130,277,478,35,169,189,298,249,267,14
,139,25,96,161,285,303,186,859,191,209,868,43,780,40,321,339,272,95,275
,561,279,357,375,309,141,315,488,231,726,770,19,108,537,66,209,229,501,580
,514,615,699,857,712,876,719,883,735,6,736,714,760,855,463,469,284,290,293
,294,297,568,596,98,622,318,396,325,876,333,334,885,344,465}
,
{
{{1,1}
,{1,1}
,{1,1}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{3,3}
,{2,2}
,{42,42}
,{15,15}
,{42,42}
,{3,3}
,{42,42}
,{2,2}
,{2,2}
,{17,17}
,{17,17}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{3,3}
,{42,42}
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
,{42,42}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{45,45}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{45,45}
,{2,2}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{42,42}
,{3,3}
,{2,2}
,{42,42}
,{3,3}
,{18,18}
,{35,35}
,{35,35}
,{18,18}
,{35,35}
,{2,2}
,{45,45}
,{3,3}
,{3,3}
,{3,3}
,{18,18}
,{29,29}
,{2,2}
,{45,45}
,{3,3}
,{2,2}
,{45,45}
,{19,19}
,{42,42}
,{3,3}
,{18,18}
,{38,38}
,{2,2}
,{45,45}
,{3,3}
,{45,45}
,{3,3}
,{18,18}
,{38,38}
,{2,2}
,{45,45}
,{3,3}
,{45,45}
,{3,3}
,{45,45}
,{45,45}
,{3,3}
,{2,2}
,{42,42}
,{3,3}
,{18,18}
,{35,35}
,{42,42}
,{3,3}
,{42,42}
,{5,5}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{42,42}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{3,3}
,{42,42}
,{3,3}
,{3,3}
,{3,3}
,{2,2}
,{45,45}
,{4,4}
,{45,45}
,{3,3}
,{4,4}
,{45,45}
,{3,3}
,{42,42}
}
,
{0,0,0,0,0,0}
,
{0,0,0,0,0,0}
,
{0,0,0,0,0,0}
}
};


/* Non terminal table *\
\* ------------------ */
typedef  struct {
    UByte2 gto[850];		/* Goto table */
    UByte2 gtoRix[147];		/* Goto row mapping */
    UByte1 lhs[108];		/* Left hand side symbols */
    UByte1 rhsz[108];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{17,209,89,0,0,578,0,602,0,1025,0,553,0,0,642,650,921,682,145,498,633,0
,618,1105,370,25,649,569,593,729,137,730,889,209,89,385,730,578,386,602
,866,1025,698,873,818,137,730,706,921,850,145,498,409,730,618,1105,370,698
,81,625,785,89,137,730,698,209,89,730,769,578,386,602,0,1025,698,1097,0
,145,706,0,1089,0,145,498,0,0,618,1105,370,137,730,0,209,89,137,730,578
,0,602,401,1025,698,386,0,0,0,698,921,818,145,498,0,0,618,905,370,409,730
,0,209,89,137,730,578,730,602,0,1025,698,386,674,0,825,698,921,706,145,498
,770,0,618,0,378,778,0,0,209,89,137,730,578,241,602,802,626,0,386,794,137
,730,698,353,0,145,0,185,730,618,0,0,698,273,26,0,202,137,730,698,329,137
,730,0,106,82,0,1129,489,698,42,90,122,698,0,50,114,0,98,58,74,66,209,89
,0,0,578,1153,602,0,626,674,0,849,0,137,730,353,0,145,209,89,0,618,578,297
,602,698,626,0,0,137,730,0,329,353,0,145,0,137,730,618,505,698,0,361,26
,0,577,137,730,698,329,137,730,0,106,82,473,0,313,698,42,90,122,698,0,50
,114,0,98,58,74,66,209,89,0,0,578,0,602,0,1025,0,0,0,137,730,0,921,0,145
,498,0,0,618,26,0,698,0,0,0,0,137,730,0,106,82,0,0,0,394,42,90,122,698,26
,50,114,0,98,58,74,66,0,0,106,82,0,0,0,0,42,90,122,26,0,50,114,0,98,58,74
,66,0,106,82,0,0,0,0,42,90,122,26,0,50,114,0,98,58,74,66,0,106,82,0,0,0
,0,42,90,122,26,0,50,114,0,98,58,74,66,0,106,82,617,0,0,0,42,90,122,0,0
,50,114,0,98,58,74,66,209,89,0,0,578,753,602,425,626,673,209,89,137,730
,578,345,602,145,626,0,0,618,0,0,698,105,809,145,0,137,730,618,0,137,730
,137,730,137,730,137,730,698,209,89,0,698,578,698,602,698,626,698,209,89
,137,730,578,201,602,145,626,0,0,618,0,0,698,713,1145,145,0,137,730,618
,0,0,0,0,1169,0,0,137,730,698,209,89,0,0,578,0,602,697,626,698,209,89,137
,730,578,937,602,145,626,0,0,618,137,730,698,953,0,145,0,137,730,618,0,0
,698,137,730,0,0,137,730,698,209,89,0,0,578,698,602,0,626,698,209,89,0,0
,578,969,602,145,626,0,0,618,0,0,0,985,0,145,0,137,730,618,0,0,0,0,0,0,0
,137,730,698,209,89,0,0,578,0,602,0,626,698,209,89,0,0,578,1001,602,145
,626,0,0,618,0,0,0,1017,0,145,0,137,730,618,0,0,0,0,0,0,0,137,730,698,209
,89,0,0,578,0,602,0,626,698,209,89,0,0,578,529,602,145,626,0,0,618,0,0,0
,41,0,145,0,137,730,618,0,0,0,0,0,0,0,137,730,698,121,89,0,0,578,0,602,0
,626,698,57,89,0,0,578,0,602,145,626,0,0,618,0,0,0,0,0,145,0,137,730,618
,0,0,0,0,0,0,0,137,730,698,89,0,0,610,0,602,0,626,0,698,0,0,0,0,0,0,145
,0,762,89,618,169,594,778,602,0,626,0,137,730,257,0,0,802,0,145,0,794,0
,618,698,0,0,0,0,185,730,137,730,762,0,0,169,0,778,762,0,698,169,698,778
,161,0,0,802,0,0,441,794,0,802,0,0,0,794,0,185,730,0,0,0,762,185,730,169
,0,778,762,698,0,169,0,778,1041,698,0,802,0,0,457,794,0,802,0,0,0,794,0
,185,730,0,0,0,0,185,730,89,0,0,586,698,602,0,626,0,0,698,0,0,0,0,0,145
,0,0,0,618,0,0,0,0,0,0,0,137,730,0,0,0,0,0,0,0,0,0,0,698}
,
{0,16,361,618,14,660,13,807,19,9,0,408,12,650,12,710,93,1,739,11,11,135
,36,440,11,11,691,11,149,10,708,9,9,9,9,221,9,217,7,6,5,398,5,5,5,5,22,4
,86,4,5,404,4,745,4,777,4,254,2,145,2,199,1,1,608,1,1,0,1,2,234,1,3,284
,0,381,30,3,0,1,304,0,406,0,0,488,0,450,0,4,323,0,402,0,59,0,35,342,0,423
,0,128,0,15,207,0,0,32,0,7,162,91,0,118,0,482,0,492,0,524,0,534,0,566,0
,576,0,0,771,0,0,0,0,0,64,0,0,0,0,183,0,465,0,0,475,0,271}
,
{46,71,71,56,56,56,56,56,56,56,56,56,56,56,56,72,67,67,73,73,77,66,58,58
,58,74,74,80,78,75,75,63,63,81,81,81,81,83,83,83,83,82,82,57,57,69,69,70
,70,84,84,84,84,84,84,84,84,84,84,84,84,84,65,65,87,87,79,79,62,62,62,47
,47,47,51,51,53,53,53,55,55,60,60,50,50,48,76,76,88,88,88,64,61,61,52,52
,49,49,54,54,59,59,59,68,85,85,86,86}
,
{1,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,5,6,5,6,3,7,0,2,6,11,11,4,11,0,3,0,2,3
,4,4,7,3,4,4,7,4,6,1,3,1,3,1,2,3,3,3,3,3,3,4,4,4,4,4,3,1,6,6,0,1,1,3,1,3
,3,1,3,3,1,2,1,1,3,2,2,0,3,1,3,1,1,2,1,1,1,3,0,1,1,3,1,1,1,1,0,1,1,2,0,2
,1,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[45];
			     
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
,{27,1,1,"'%%IF'",""}
,{28,1,1,"'%%SET'",""}
,{29,1,1,"'%%END'",""}
,{30,1,1,"INTEGER",""}
,{31,1,1,"'%%KEEP'",""}
,{32,1,1,"'%%ESET'",""}
,{33,1,1,"'%%ELSE'",""}
,{34,1,1,"'%%LOOP'",""}
,{35,1,1,"'%%ENDIF'",""}
,{36,1,1,"'%%ELSIF'",""}
,{37,1,1,"'%%BEGIN'",""}
,{38,1,1,"'%%ENDLOOP'",""}
,{39,1,1,"'%%MESSAGE'",""}
,{40,1,1,"'%%INCLUDE'",""}
,{41,1,1,"'%%PROCESS'",""}
,{42,1,1,"QUOT_STRING",""}
,{43,1,1,"'%%EINCLUDE'",""}
,{44,1,1,"'IMP$SYSTEM'",""}
,{45,1,1,"UNQUOT_STRING",""}
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
static UByte1 scIndex[45 + 1]; /* Converts scanner code to internal value */
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

extern void impRPoi();	/* Error recovery - restart point  */
extern void impISym();	/* Error recovery - insert symbol  */
extern void impDSym();	/* Error recovery - delete symbol  */
extern void impMess();	/* Error recovery - error message  */

/* External functions */
void impPaSema();

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(token, eClass, severity) 
TmToken *token;		/* IN current token */
short eClass;			/* IN error classification */
short severity;			/* IN error severity code */
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
 *	      token on the symbol stack.
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
 *		     t = current token
 *		     y = unprocessed input
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
TmToken *token;			/* INOUT symbol to delete, new symbol */
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
static void inSym(isym, gen_symb)
short isym;			/* IN symbol code to insert */
TmToken *gen_symb;		/* OUT created symbol */
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
 *	      the continuation grammar.
 *----------------------------------------------------------------------------
 */
static void acceptbl(sym, stack, stack_p, token, found, point)
UByte1 sym;			/* IN terminal symbol code */
ParseStack stack;		/* IN parse stack */
short stack_p;			/* IN stack pointer */
TmToken *token;			/* IN current token */
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
TmToken *token;			/* INOUT current symbol */
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
TmToken *token;			/* INOUT current symbol */
REC_POI *point;			/* IN recovery point descriptor */
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
static void multiple(err_stk, err_stkp, err_tok, newstat)
ParseStack err_stk;		/* INOUT current parse stack */
short *err_stkp;		/* INOUT current stack pointer */
TmToken *err_tok;		/* INOUT current token */
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
TmToken *curtok;			/* IN current token */
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
TmToken *token;			/* OUT constructed token */
{
    inSym(sym, token);
}/*_pmInsert()*/


/*----------------------------------------------------------------------------
 * _pmReplace
 *----------------------------------------------------------------------------
 */
static void _pmReplace(sym, token)
UByte1 sym;			/* IN replacement symbol code */
TmToken *token;			/* OUT constructed token */
{
    delSym(token);
    inSym(sym, token);
}/*_pmReplace()*/


/*----------------------------------------------------------------------------
 * _pmDelete
 *----------------------------------------------------------------------------
 */

static void _pmDelete(token)
TmToken *token;			/* OUT new token */
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
static void single(leg_sys, err_stk, err_stkp, token, newstat)
TermSet leg_sys;		/* IN legal symbols in current state */
ParseStack err_stk;		/* INOUT current parser stack */
short *err_stkp;		/* INOUT current stack pointer */
TmToken *token;		/* INOUT current token */
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
static void recover(err_stk, err_stkp, err_symb, rec_stat)
ParseStack err_stk;		/* INOUT updated parse stack */
short *err_stkp;		/* INOUT updated stack pointer */
TmToken *err_symb;		/* INOUT current token */
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
void impParse()
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

