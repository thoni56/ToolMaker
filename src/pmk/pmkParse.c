/*----------------------------------------------------------------------*\

    pmkParse.c

    ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pws.h"
#include "pmkList.h"
#include "pwsLexCode.h"
#include "pwsOrd.h"
#include "set.h"
#include "pmk_i.h"
#include "tmk.h"
#include "pwSymSet.h"
#include "pwsGrm.h"
#include "pmkScan.h"
extern pmkScContext pmkCtxt;

/* END %%IMPORT */

#include <string.h>
#include <setjmp.h>

#include "pmkParse.h"

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
#include "pmkCommon.h"

/* %%ATTRIBUTES - The semantic attributes for grammar symbols */
typedef struct pmkGrammar {
    prod_elnode *rule_elnode_last;
    prod_elnode *rule_elnode /* list of rhs elements (see prod_elnode's def) */;
    rhs_node *rhslist_last /* last element in the list above. This used to
                                        to avoid making a reversed list */;
    rhs_node *rhslist /* list of alternative righthand sides */;
    altr_lst *altr_last;
    altr_lst *altr_node /* list of alternatives (in EBNF alternation) */;
    SymSet nored_set /* modifier sets */;
    SymSet red_set /* modifier sets */;
    int code /* terminals code value given in TERMINAL section */;
    int dcost /* Delete cost given in TERMINAL section */;
    int icost /* Insert cost given in TERMINAL section */;
    Boolean nullf /* null flag */;
    Boolean q_str /* quoted_ string flag */;
    TmkSrcp srcp;
    char *sval2;
    char *sval;
    int ival;
} pmkGrammar;

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
#define SccMax 128		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 35		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 85		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 98		/* Number of productions */
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
    ContRec cont[85];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[602];		/* Action table */
    UByte1 actCheck[617];	/* Row Displacement Check Vector*/
    UByte2 actRix[85];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{403,202,194,210,313,730,202,194,210,4,611,330,611,323,323,779,459,441,706
,722,403,403,403,403,403,403,233,403,403,403,403,403,403,403,403,169,514
,786,779,498,779,355,482,779,779,779,779,779,779,779,202,194,210,202,194
,210,202,194,210,297,305,355,355,355,355,355,355,426,355,355,355,355,355
,355,355,355,667,667,667,97,667,217,667,113,667,667,667,667,667,667,667
,667,275,667,667,659,659,659,97,659,714,659,673,659,659,659,659,659,659
,659,659,506,706,722,779,202,194,210,730,353,587,202,194,210,587,554,73
,779,202,369,210,706,722,202,194,210,786,779,266,779,779,259,779,779,779
,779,779,779,779,786,779,259,779,779,474,779,779,779,779,779,779,779,786
,779,617,779,779,218,779,779,779,779,779,779,779,786,779,193,779,730,170
,779,779,779,779,779,779,779,786,779,642,779,706,722,779,779,779,779,779
,779,779,595,595,595,97,595,129,595,97,595,89,595,97,595,161,595,227,641
,595,595,595,595,595,531,595,531,595,250,595,201,595,243,595,202,595,210
,779,595,595,202,194,210,97,667,698,667,650,521,537,667,779,457,657,489
,313,490,667,667,786,779,145,779,417,0,779,779,779,779,779,779,779,0,786
,779,0,779,0,0,779,779,779,779,779,779,779,667,667,667,0,667,202,194,210
,667,667,0,667,667,0,667,0,0,667,667,667,667,667,0,667,202,194,210,667,667
,0,667,667,0,667,0,0,667,667,595,595,595,0,595,202,194,210,595,595,0,595
,595,0,595,0,0,706,722,202,194,210,0,667,202,194,210,521,667,0,667,457,0
,489,0,0,667,667,595,595,595,0,595,202,194,210,595,595,0,595,595,0,595,0
,779,706,722,202,194,210,0,667,0,0,0,521,667,0,667,457,0,489,0,0,667,667
,786,779,0,779,0,0,779,779,779,779,779,779,779,786,779,0,779,779,0,779,779
,779,779,779,779,779,202,194,210,0,667,0,0,0,521,0,0,0,457,0,489,667,0,667
,667,27,11,27,27,0,27,27,27,27,27,27,27,19,0,19,681,0,19,19,19,19,19,19
,19,321,0,249,0,0,257,346,146,281,241,265,273,667,667,667,0,667,0,0,0,667
,0,0,0,667,667,667,730,0,667,667,595,595,595,0,595,634,0,0,595,706,722,0
,595,595,595,0,0,706,722,202,194,210,0,667,0,0,0,521,0,0,0,457,667,489,0
,0,667,667,667,667,667,0,667,0,0,0,667,0,0,0,667,0,667,667,0,667,667,595
,595,595,0,595,0,0,0,595,0,0,0,595,0,595,595,0,706,722,321,0,249,0,0,257
,346,146,281,241,265,273,730,0,0,0,0,619,0,619,0,0,0,0,0,706,722}
,
{21,21,21,21,37,72,51,51,51,1,72,38,72,38,38,6,26,53,72,72,21,21,21,21,21
,21,26,21,21,21,21,21,21,21,21,6,6,6,6,6,6,5,6,6,6,6,6,6,6,6,54,54,54,28
,28,28,11,11,11,35,35,5,5,5,5,5,5,27,5,5,5,5,5,5,5,5,48,48,48,25,48,25,48
,12,48,48,48,48,48,48,48,48,82,48,48,49,49,49,55,49,55,49,82,49,49,49,49
,49,49,49,49,19,49,49,74,74,74,74,47,42,47,13,13,13,47,44,7,41,41,44,41
,47,47,17,17,17,74,74,81,74,33,81,74,74,74,74,74,74,74,41,41,81,41,36,10
,41,41,41,41,41,41,41,33,33,75,33,29,76,33,33,33,33,33,33,33,36,36,22,36
,63,78,36,36,36,36,36,36,36,29,29,63,29,63,63,29,29,29,29,29,29,29,43,43
,43,14,43,14,43,9,43,9,43,18,43,18,43,77,77,43,43,45,45,45,39,45,39,45,79
,45,23,45,79,45,40,45,40,30,45,45,46,46,46,52,46,52,46,65,46,65,46,31,46
,80,46,34,15,46,46,30,30,16,30,50,85,30,30,30,30,30,30,30,85,31,31,85,31
,85,85,31,31,31,31,31,31,31,64,64,64,85,64,20,20,20,64,64,85,64,64,85,64
,85,85,64,64,66,66,66,85,66,73,73,73,66,66,85,66,66,85,66,85,85,66,66,67
,67,67,85,67,8,8,8,67,67,85,67,67,85,67,85,85,67,67,68,68,68,85,68,83,83
,83,68,68,85,68,68,85,68,85,85,68,68,70,70,70,85,70,24,24,24,70,70,85,70
,70,85,70,85,32,70,70,71,71,71,85,71,85,85,85,71,71,85,71,71,85,71,85,85
,71,71,32,32,85,32,85,85,32,32,32,32,32,32,32,84,84,85,84,84,85,84,84,84
,84,84,84,84,62,62,62,85,62,85,85,85,62,85,85,85,62,85,62,62,85,62,62,0
,4,0,0,85,0,0,0,0,0,0,0,2,85,2,2,85,2,2,2,2,2,2,2,4,85,4,85,85,4,4,4,4,4
,4,4,56,56,56,85,56,85,85,85,56,85,85,85,56,56,56,59,85,56,56,57,57,57,85
,57,59,85,85,57,59,59,85,57,57,57,85,85,57,57,58,58,58,85,58,85,85,85,58
,85,85,85,58,58,58,85,85,58,58,60,60,60,85,60,85,85,85,60,85,85,85,60,85
,60,60,85,60,60,61,61,61,85,61,85,85,85,61,85,85,85,61,85,61,61,85,61,61
,3,85,3,85,85,3,3,3,3,3,3,3,69,85,85,85,85,69,85,69,85,85,85,85,85,69,69
,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85}
,
{421,9,433,552,445,41,15,117,327,200,147,55,74,120,196,248,251,132,204,104
,289,0,171,220,365,71,9,60,52,166,236,250,377,140,253,52,153,3,6,222,232
,127,113,200,118,219,238,113,75,94,253,5,234,8,49,90,479,498,517,490,536
,555,424,174,284,236,303,322,341,582,360,379,0,308,114,158,163,209,173,223
,244,134,85,346,390}
,
{
{{24,24}
,{1,1}
,{24,24}
,{30,30}
,{1,1}
,{1,1}
,{1,1}
,{10,10}
,{2,2}
,{11,11}
,{8,8}
,{2,2}
,{10,10}
,{2,2}
,{11,11}
,{8,8}
,{10,10}
,{2,2}
,{11,11}
,{8,8}
,{2,2}
,{1,1}
,{7,7}
,{10,10}
,{2,2}
,{11,11}
,{8,8}
,{8,8}
,{2,2}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{2,2}
,{8,8}
,{1,1}
,{2,2}
,{8,8}
,{2,2}
,{2,2}
,{1,1}
,{7,7}
,{2,2}
,{8,8}
,{2,2}
,{6,6}
,{8,8}
,{2,2}
,{2,2}
,{10,10}
,{2,2}
,{11,11}
,{10,10}
,{2,2}
,{11,11}
,{2,2}
,{2,2}
,{6,6}
,{15,15}
,{2,2}
,{2,2}
,{6,6}
,{17,17}
,{2,2}
,{11,11}
,{2,2}
,{2,2}
,{6,6}
,{11,11}
,{2,2}
,{6,6}
,{11,11}
,{2,2}
,{1,1}
,{7,7}
,{5,5}
,{8,8}
,{8,8}
,{9,9}
,{9,9}
,{8,8}
,{8,8}
,{2,2}
,{24,24}
}
,
{0,0,0,0,0}
,
{0,0,0,0,0}
,
{0,0,0,0,0}
}
};


/* Non terminal table *\
\* ------------------ */
typedef  struct {
    UByte2 gto[254];		/* Goto table */
    UByte1 gtoRix[85];		/* Goto row mapping */
    UByte1 lhs[98];		/* Left hand side symbols */
    UByte1 rhsz[98];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{570,0,361,0,130,738,178,746,442,754,762,298,290,578,178,209,434,497,538
,289,337,569,185,545,178,401,466,114,33,49,306,465,393,42,593,674,314,529
,34,41,74,345,114,82,49,186,409,433,50,593,106,377,66,186,418,74,90,98,82
,58,122,562,338,186,377,106,137,66,674,394,386,90,98,682,58,122,178,225
,434,409,433,690,329,393,185,17,674,178,105,609,393,674,25,674,362,378,65
,409,433,178,370,450,409,433,409,433,682,625,393,674,473,674,633,649,690
,186,410,665,234,177,409,433,409,433,682,57,186,770,0,682,674,682,690,505
,0,154,0,690,186,690,601,409,433,138,178,393,609,682,674,682,674,553,0,0
,626,690,626,690,0,409,433,409,433,626,481,626,513,546,682,178,522,442,577
,385,626,561,690,0,153,0,178,0,442,186,585,178,682,282,682,81,345,0,162
,186,690,186,690,178,602,442,602,0,186,178,186,442,425,602,186,602,562,0
,449,186,178,0,442,0,602,186,0,0,0,121,186,0,0,0,0,0,0,0,0,0,0,0,186,0,0
,0,0,0,186,0,0,0,0,0,0,0,0,0,0,186}
,
{60,12,12,0,15,84,58,6,175,6,6,94,6,209,5,5,5,164,4,4,71,9,4,4,1,4,31,4
,19,0,1,3,5,6,1,2,8,20,1,63,17,166,1,0,1,13,158,26,10,141,1,192,1,1,198
,1,16,59,149,77,2,82,151,84,6,0,8,100,160,102,121,169,139,82,139,0,90,58
,0,91,0,94,90,180,123}
,
{61,52,68,68,75,75,69,69,69,69,69,69,69,69,69,88,96,70,94,94,89,43,41,41
,80,80,53,90,90,58,58,59,59,64,64,86,54,54,46,71,71,95,65,77,77,72,72,72
,72,47,84,84,81,49,50,50,82,82,78,74,73,66,48,44,63,55,39,39,37,60,38,38
,36,87,87,67,67,85,85,85,85,85,51,51,45,45,83,56,91,57,42,76,79,92,93,62
,40,40}
,
{3,0,0,2,1,2,1,1,1,1,1,1,1,1,1,2,3,1,1,2,5,1,1,1,1,1,1,0,5,0,1,0,1,0,2,4
,1,3,2,0,1,3,1,0,2,1,1,1,1,2,1,2,7,1,1,3,0,2,5,1,5,1,5,1,4,0,1,2,4,1,1,3
,2,0,2,3,5,1,5,5,3,3,0,2,1,1,4,1,4,1,1,2,2,2,2,2,0,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[35];

static VocTab voc = {{1,255,255,"EndOfText",""}
,{2,1,1,"IDENTIFIER",""}
,{3,1,1,"STRING",""}
,{4,1,1,"ANG_BRACK_STRING",""}
,{5,1,1,"INTEGER",""}
,{99,3,2,"'%%'","%%...%%"}
,{100,1,1,"'='",""}
,{101,1,1,"';'",""}
,{102,1,1,"','",""}
,{103,1,1,"'('",""}
,{104,1,1,"')'",""}
,{105,1,1,"'!'",""}
,{106,1,1,"'|'",""}
,{107,1,1,"'{'",""}
,{108,1,1,"'}'",""}
,{109,1,1,"'['",""}
,{110,1,1,"']'",""}
,{111,1,1,"'=>'",""}
,{112,1,1,"'%+'",""}
,{113,1,1,"'%-'",""}
,{114,1,1,"'META'",""}
,{115,1,1,"'SKIP'",""}
,{116,1,1,"'%%END'",""}
,{117,1,1,"'%%RULES'",""}
,{118,1,1,"'FIDUCIAL'",""}
,{119,1,1,"'%%EXPORT'",""}
,{120,1,1,"SKIPHEADER",""}
,{121,1,1,"'SEPARATOR'",""}
,{122,1,1,"'%%SCANNER'",""}
,{123,1,1,"'%%RECOVERY'",""}
,{124,1,1,"'%%TERMINALS'",""}
,{125,1,1,"'%%ATTRIBUTES'",""}
,{126,1,1,"'%%DECLARATIONS'",""}
,{127,1,1,"'%%INSERTSYMBOL'",""}
,{128,1,1,"'%%DELETESYMBOL'",""}
}
;


/* Variables used in the parsing process *\
\* ------------------------------------- */
short pmkStkP;			/* Stack pointer */
PmkToken pmkSySt[PmStkMax];	/* Symbol stack */
pmkGrammar pmkSeSt[PmStkMax];	/* Semantic stack */
static UByte1 currstat;		/* Current state number */
static UByte1 arg;		/* Argument */
static UByte1 action;		/* Action type */
static PmBoolean endparse;	/* Termination flag */
static ParseStack parsStk;	/* Parse stack */
static UByte1 scIndex[128 + 1]; /* Converts scanner code to internal value */
static PmkToken tokenBuf;	/* Scanner token buffer */
static PmkToken *token = &tokenBuf;	/* Pointer to it for readsymb */


/* Error recovery look-ahead buffer *\
\* -------------------------------- */
static PmkToken la_buff[PmLaMax + 1]; /* Buffer */
static int la_ptr;		/* Current pointer */
static int la_end;		/* Last item */

static jmp_buf pmJmpB;		/* Buffer for long jump */

/* Interface routines *\
\* ------------------ */

extern void pmkRPoi(	/* Error recovery - restart point  */
PmkToken *sym			/* IN the restart symbol */
);
extern void pmkISym(	/* Error recovery - insert symbol  */
 int code,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr,			/* IN the terminals print symbol */
PmkToken *sym			/* OUT the created scanner symbol */
);
extern void pmkDSym(	/* Error recovery - delete symbol  */
PmkToken *sym,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr			/* IN terminals print string */
);
extern void pmkMess(	/* Error recovery - error message  */
PmkToken *sym,			/* IN error token */
int method,			/* IN recovery method */
int code,			/* IN error classification */
int severity			/* IN error severity code */
);

/* External functions */
extern void pmkPaSema(
int rule			/* IN production number */
);

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(
PmkToken *token,		/* IN current token */
short eClass,			/* IN error classification */
short severity			/* IN error severity code */
)
{
    pmkMess(token, HALT_REC, eClass, severity);
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
    pmkStkP = 0;
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
#define MOVETOKEN pmkSySt[pmkStkP] = *token
#define pushStatTok()\
{\
    if (++pmkStkP < PmStkMax) {\
    parsStk[pmkStkP] = currstat;\
    MOVETOKEN;\
    } else {\
    token->code = voc[token->code-TermMin].scc;\
    paAbort(token, OFLW_ERR, SYS_SEV);\
    }\
}

#define pushStat()\
{\
    if (++pmkStkP < PmStkMax) {\
    parsStk[pmkStkP] = currstat;\
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
    PmkToken err_tok;
    PmkToken res_tok;
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
PmkToken *token			/* INOUT symbol to delete, new symbol */
)
{
    short  t;

    t = token->code - TermMin;
    token->code = voc[t].scc;
    pmkDSym(token, voc[t].name, voc[t].psym);
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
PmkToken *gen_symb		/* OUT created symbol */
)
{
    pmkISym(voc[isym - TermMin].scc, voc[isym - TermMin].name,
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
PmkToken *token,			/* IN current token */
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
PmkToken *token,			/* INOUT current symbol */
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
PmkToken *token,			/* INOUT current symbol */
REC_POI *point			/* IN recovery point descriptor */
)
{
    UByte1 state;		/* Current state */
    UByte1 cont_sym;		/* Continuation symbol */
    PmkToken gen_symb;		/* Generated symbol */
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
        pmkSySt[*stack_p] = gen_symb;
        break;

      case SHIFTRED_ACT:
        sepaAccept = PMTRUE;
        inSym(cont_sym, &gen_symb);
        ePush(state, stack, stack_p);
        pmkSySt[*stack_p] = gen_symb;
        goto reduce;

      case REDUCE_ACT:
        reduce:
        do {
        *stack_p = *stack_p - gto.rhsz[arg-ProdMin];
        pmkPaSema(arg);
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
PmkToken *err_tok,		/* INOUT current token */
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
PmkToken *curtok			/* IN current token */
)
{
    int i;
    PmkToken tokbuf;
    PmkToken *token = &tokbuf;

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
             pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else {
        token->code = scIndex[token->code];
        }/*if*/
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
PmkToken *token			/* OUT constructed token */
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
PmkToken *token			/* OUT constructed token */
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
PmkToken *token			/* OUT new token */
)
{
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
PmkToken *token,		/* INOUT current token */
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
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
PmkToken *err_symb,		/* INOUT current token */
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
    pmkMess(&errdescr.err_tok, errdescr.method, errdescr.eClass,
           errdescr.severity);
    } else {
    pmkMess(&errdescr.err_tok, errdescr.method, SYN_ERR, errdescr.severity);
    }/*if*/
    errdescr.res_tok = *err_symb;
    errdescr.res_tok.code = voc[errdescr.res_tok.code - TermMin].scc;
    pmkRPoi(&errdescr.res_tok);
}/*recover()*/


/*----------------------------------------------------------------------------
 * pmkParse - Parser routine, entry point
 *----------------------------------------------------------------------------
 */
void pmkParse(void)
{
    paInit();
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
        recover(parsStk, &pmkStkP, token, &currstat);
        if (pmkStkP == 0) endparse = PMTRUE;
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
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
         pmkScan(pmkCtxt, token);


        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        pmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
        }
    } while (token->code == ERR_SYM);
    }
}
        goto reduce;

    case REDUCE_ACT:
      reduce:
        do {
        pmkStkP -= gto.rhsz[arg - ProdMin];
        pmkPaSema(arg);
        gtoTbl(parsStk[pmkStkP], gto.lhs[arg - ProdMin], &action, &arg);
        pushStat();
        } while (action != SHIFT_ACT);

        currstat = arg;
        parsStk[pmkStkP] = currstat;
        break;

    case ACCEPT_ACT:
        endparse = PMTRUE;
        break;
    }/*switch*/
    }/*while*/
}/*pmkParse()*/

