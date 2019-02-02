/*----------------------------------------------------------------------*\

	smkParse.c

	ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */


/*
 * "Bug" in generated code does not include definition of memset
 */
#include <memory.h>

#include <stdio.h>
#include "common.h"
#include "action.h"
#include "ast.h"
#include "definition.h"
#include "map.h"
#include "name.h"
#include "pack.h"
#include "rule.h"
#include "scanner.h"
#include "set.h"
#include "smkList.h"
#include "smkScan.h"
#include "smk_i.h"
#include "token.h"
#include "vocabulary.h"

extern smkScContext lexContext;

/* END %%IMPORT */

#include <string.h>
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
#define SccMax 138		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 41		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 86		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 102		/* Number of productions */
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
    ContRec cont[86];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[451];		/* Action table */
    UByte1 actCheck[471];	/* Row Displacement Check Vector*/
    UByte2 actRix[86];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{4,691,497,691,457,691,691,698,706,714,289,722,305,691,691,691,691,691,691
,810,146,139,139,411,411,139,139,139,139,362,691,139,139,107,139,411,738
,411,139,139,139,35,35,818,810,35,35,35,35,107,107,35,35,802,35,146,139
,139,35,35,35,139,139,139,578,794,139,139,105,139,146,139,139,139,139,139
,139,139,139,161,377,139,139,339,139,146,139,139,139,139,139,139,139,139
,545,339,139,139,331,139,146,139,139,139,139,139,139,139,139,818,242,139
,139,802,139,146,139,139,139,139,139,139,139,139,794,794,139,139,794,139
,146,139,139,139,139,139,139,139,139,11,585,139,139,794,139,146,139,139
,139,139,139,139,139,139,321,586,139,139,521,139,290,810,282,139,139,139
,19,19,427,427,689,19,19,19,561,81,19,19,81,19,401,625,75,19,19,19,649,657
,673,746,458,641,665,265,681,609,387,810,75,75,633,667,786,667,730,667,667
,778,337,634,818,619,802,778,337,667,818,667,802,161,377,59,59,794,794,217
,59,59,59,387,794,59,59,506,59,387,794,594,59,59,59,659,139,659,193,659
,659,778,337,105,818,0,802,778,337,659,818,659,802,555,802,0,146,0,794,139
,139,563,0,601,794,274,794,0,265,139,0,555,0,555,0,139,555,555,139,563,0
,563,0,555,563,563,555,625,83,547,0,563,555,0,563,0,802,0,146,0,563,139
,139,563,83,83,0,547,794,547,0,139,547,547,0,778,337,139,818,547,802,563
,547,563,0,0,563,563,547,0,0,241,794,563,323,483,563,483,225,0,483,483,563
,491,0,491,0,483,491,491,0,802,483,146,27,491,139,139,0,146,491,139,0,794
,146,139,139,105,139,794,27,27,0,323,443,0,443,139,139,443,443,0,139,139
,0,802,443,146,395,395,139,139,0,778,337,0,818,794,802,643,395,643,395,361
,265,315,778,337,818,818,794,802,146,0,139,643,0,651,0,651,467,467,265,794
,634,634,619,619,0,0,139,139,467,651,425,0,0,0,105,0,217,217,0,0,315}
,
{1,34,60,34,13,34,34,34,34,34,34,36,36,34,34,34,34,34,34,61,85,85,85,13
,13,85,85,85,85,62,34,85,85,6,85,13,37,13,85,85,85,0,0,64,37,0,0,0,0,6,6
,0,0,58,0,78,78,78,0,0,0,78,78,78,25,58,78,78,58,78,79,79,79,78,78,78,79
,79,79,17,17,79,79,63,79,80,80,80,79,79,79,80,80,80,66,63,80,80,63,80,81
,81,81,80,80,80,81,81,81,67,68,81,81,57,81,82,82,82,81,81,81,82,82,82,69
,57,82,82,26,82,83,83,83,82,82,82,83,83,83,8,71,83,83,12,83,84,84,84,83
,83,83,84,84,84,35,28,84,84,7,84,74,35,75,84,84,84,2,2,16,16,2,2,2,2,7,7
,2,2,8,2,16,4,4,2,2,2,4,4,4,38,51,4,4,42,4,72,18,39,4,4,4,33,42,33,40,33
,33,72,72,24,72,24,72,33,33,33,33,33,33,18,18,3,3,9,72,24,3,3,3,18,33,3
,3,55,3,18,56,30,3,3,3,43,21,43,22,43,43,32,32,10,32,86,32,43,43,43,43,43
,43,46,21,86,21,86,32,21,21,47,86,73,43,73,21,86,73,21,86,46,86,46,86,21
,46,46,48,47,86,47,86,46,47,47,46,76,76,19,86,47,46,86,47,86,48,86,48,86
,47,48,48,20,76,76,86,19,48,19,86,48,19,19,86,23,23,48,23,19,23,20,19,20
,86,86,20,20,19,86,86,23,23,20,59,52,20,52,23,86,52,52,20,53,86,53,86,52
,53,53,86,54,52,54,5,53,54,54,86,70,53,70,86,54,77,77,77,59,54,70,5,5,86
,59,49,86,49,70,70,49,49,86,77,77,86,50,49,50,14,14,50,50,86,41,41,86,41
,50,41,31,14,31,14,31,31,11,44,44,65,44,41,44,65,86,65,31,86,45,86,45,15
,15,45,44,27,29,27,29,86,86,65,65,15,45,15,86,86,86,11,86,27,29,86,86,11
,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86}
,
{20,0,145,200,160,338,11,136,139,193,216,411,113,0,371,403,145,56,196,295
,309,242,242,308,208,61,98,429,152,430,234,404,234,200,0,142,0,25,178,178
,193,386,187,240,399,422,259,267,284,362,373,187,323,331,339,230,206,95
,35,340,0,0,26,65,27,398,92,93,107,94,345,138,194,268,157,159,272,350,35
,50,65,80,95,110,125,0}
,
{
{{22,22}
,{1,1}
,{22,22}
,{22,22}
,{23,23}
,{23,23}
,{23,23}
,{40,40}
,{1,1}
,{31,31}
,{34,34}
,{1,1}
,{31,31}
,{24,24}
,{24,24}
,{24,24}
,{24,24}
,{24,24}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{3,3}
,{31,31}
,{4,4}
,{4,4}
,{31,31}
,{4,4}
,{4,4}
,{4,4}
,{4,4}
,{2,2}
,{31,31}
,{2,2}
,{2,2}
,{20,20}
,{12,12}
,{12,12}
,{12,12}
,{20,20}
,{12,12}
,{31,31}
,{16,16}
,{2,2}
,{31,31}
,{2,2}
,{1,1}
,{1,1}
,{1,1}
,{19,19}
,{24,24}
,{4,4}
,{19,19}
,{19,19}
,{24,24}
,{4,4}
,{31,31}
,{31,31}
,{34,34}
,{1,1}
,{3,3}
,{20,20}
,{4,4}
,{34,34}
,{17,17}
,{23,23}
,{3,3}
,{17,17}
,{4,4}
,{31,31}
,{23,23}
,{3,3}
,{31,31}
,{4,4}
,{4,4}
,{4,4}
,{23,23}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
,{22,22}
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
    UByte2 gto[151];		/* Goto table */
    UByte1 gtoRix[86];		/* Goto row mapping */
    UByte1 lhs[102];		/* Left hand side symbols */
    UByte1 rhsz[102];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{0,0,0,770,770,297,762,762,281,281,570,234,610,530,537,754,754,313,218,353
,353,602,185,674,674,257,345,201,770,770,513,762,762,281,281,402,226,610
,529,537,754,754,113,577,353,353,602,489,674,674,369,593,770,770,249,762
,762,281,281,370,481,378,89,465,754,754,258,514,273,153,354,569,674,682
,570,250,610,538,610,434,610,474,610,577,33,602,185,602,417,602,449,602
,489,770,66,42,762,17,281,41,114,298,73,370,97,754,266,329,450,121,122,498
,129,682,90,346,137,385,393,617,473,130,145,409,306,49,25,433,441,522,418
,169,177,378,505,57,65,553,209,626,233,98,210,154,162,170,178,186,194,202
,50}
,
{96,7,75,68,73,125,91,68,91,15,75,33,20,74,101,76,71,43,105,118,115,6,2
,0,120,1,124,122,1,36,1,1,49,90,1,0,1,12,1,102,1,1,1,50,25,1,103,101,70
,74,72,1,115,78,74,1,115,76,31,105,1,129,1,0,36,11,0,134,0,28,68,0,26,0
,0,0,100,135,136,137,138,139,140,141,142,143}
,
{43,51,52,72,72,62,73,73,94,94,88,88,87,87,74,74,49,49,63,63,63,63,63,63
,63,83,84,44,44,42,95,85,85,80,80,80,76,76,75,75,89,90,86,86,81,71,71,70
,53,64,77,77,93,93,91,91,78,82,82,54,92,92,79,68,68,66,66,55,56,59,59,46
,46,46,58,58,60,60,60,69,69,67,67,61,61,65,65,65,65,65,65,65,65,50,50,50
,50,50,57,48,47,45}
,
{7,0,0,0,2,2,0,2,0,1,1,2,0,2,1,1,0,1,2,2,2,2,2,2,2,2,3,1,2,4,3,1,2,4,4,5
,1,2,3,4,1,1,1,2,4,1,2,7,0,1,0,2,0,3,0,2,2,0,4,0,0,2,2,1,2,4,4,0,0,0,2,5
,5,5,1,1,0,2,1,1,3,1,3,1,2,1,2,2,2,4,5,5,6,1,1,1,1,3,1,1,1,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[41];
			     
static VocTab voc = {{1,255,255,"EndOfText",""}
,{99,3,2,"'%%'","%%...%%"}
,{100,1,1,"'='",""}
,{101,1,1,"';'",""}
,{102,1,1,"':'",""}
,{103,1,1,"'/'",""}
,{104,1,1,"'!'",""}
,{105,1,1,"'*'",""}
,{106,1,1,"'+'",""}
,{107,1,1,"'?'",""}
,{108,1,1,"'{'",""}
,{109,1,1,"'}'",""}
,{110,1,1,"'-'",""}
,{111,1,1,"'.'",""}
,{112,1,1,"'('",""}
,{113,1,1,"')'",""}
,{114,1,1,"Class",""}
,{115,1,1,"'%%DO'",""}
,{116,1,1,"String",""}
,{117,1,1,"Number",""}
,{118,1,1,"'%%END'",""}
,{119,1,1,"'%%SET'",""}
,{120,1,1,"'%%MAP'",""}
,{121,1,1,"'%%RULE'",""}
,{122,1,1,"'%%SKIP'",""}
,{123,1,1,"SKIPHEADER",""}
,{124,1,1,"'%%EXPORT'",""}
,{125,1,1,"'%%READER'",""}
,{126,1,1,"'%%ACTION'",""}
,{127,1,1,"'_UNKNOWN'",""}
,{128,1,1,"Identifier",""}
,{129,1,1,"'%%CONTEXT'",""}
,{130,1,1,"'%%PREHOOK'",""}
,{131,1,1,"'%%SCANNER'",""}
,{132,1,1,"'%%POSTHOOK'",""}
,{133,1,1,"'%%UNDEFINE'",""}
,{134,1,1,"'_ENDOFTEXT'",""}
,{135,1,1,"'%%SCREENING'",""}
,{136,1,1,"'%%DEFINITION'",""}
,{137,1,1,"'%%VOCABULARY'",""}
,{138,1,1,"'%%DECLARATION'",""}
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
static UByte1 scIndex[138 + 1]; /* Converts scanner code to internal value */
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

extern void smkRPoi(	/* Error recovery - restart point  */
SmkToken *sym			/* IN the restart symbol */
);
extern void smkISym(	/* Error recovery - insert symbol  */
 int code,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr,			/* IN the terminals print symbol */
SmkToken *sym			/* OUT the created scanner symbol */
);
extern void smkDSym(	/* Error recovery - delete symbol  */
SmkToken *sym,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr			/* IN terminals print string */
);
extern void smkMess(	/* Error recovery - error message  */
SmkToken *sym,			/* IN error token */
int method,			/* IN recovery method */
int code,			/* IN error classification */
int severity			/* IN error severity code */
);

/* External functions */
extern void smkPaSema(
int rule			/* IN production number */
);

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(
SmkToken *token,		/* IN current token */
short eClass,			/* IN error classification */
short severity			/* IN error severity code */
)
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
 *	    or the parse stack becomes empty
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
SmkToken *token			/* INOUT symbol to delete, new symbol */
)
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
static void inSym(
short isym,			/* IN symbol code to insert */
SmkToken *gen_symb		/* OUT created symbol */
)
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
static void acceptbl(
UByte1 sym,			/* IN terminal symbol code */
ParseStack stack,		/* IN parse stack */
short stack_p,			/* IN stack pointer */
SmkToken *token,			/* IN current token */
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
SmkToken *token,			/* INOUT current symbol */
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
SmkToken *token,			/* INOUT current symbol */
REC_POI *point			/* IN recovery point descriptor */
)
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
static void multiple(
ParseStack err_stk,		/* INOUT current parse stack */
short *err_stkp,		/* INOUT current stack pointer */
SmkToken *err_tok,		/* INOUT current token */
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
SmkToken *curtok			/* IN current token */
)
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
static UByte1 rdLaSym(
char index			/* IN i:th look-ahead symbol */
)				/* RET token code */
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
 *	    x t y  => x s y, where s becomes current symbol
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
static void _pmInsert(
UByte1 sym,			/* IN symbol code to insert */
SmkToken *token			/* OUT constructed token */
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
SmkToken *token			/* OUT constructed token */
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
SmkToken *token			/* OUT new token */
)
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
static void single(
TermSet leg_sys,		/* IN legal symbols in current state */
ParseStack err_stk,		/* INOUT current parser stack */
short *err_stkp,		/* INOUT current stack pointer */
SmkToken *token,		/* INOUT current token */
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
static void recover(
ParseStack err_stk,		/* INOUT updated parse stack */
short *err_stkp,		/* INOUT updated stack pointer */
SmkToken *err_symb,		/* INOUT current token */
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
void smkParse(void)
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

