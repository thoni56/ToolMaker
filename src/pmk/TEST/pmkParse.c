/*----------------------------------------------------------------------*\

	pmkParse.c

	ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include <stdio.h>

#include "pws.h"
#include "pmkList.h"
#include "pwsLexCode.h"
#include "set.h"
#include "pmk_i.h"
#include "tmk.h"
#include "pwSymSet.h"
#include "pwsGrm.h"
#include "pmkScan.h"
extern pmkContext pmkCtxt;
/* END %%IMPORT */

#include <strings.h>
#include <memory.h>
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
#define SccMax 33		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 33		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 83		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 95		/* Number of productions */
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
    ContRec cont[83];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[427];		/* Action table */
    UByte1 actCheck[452];	/* Row Displacement Check Vector*/
    UByte2 actRix[83];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{4,627,627,627,755,154,627,162,627,627,627,627,627,627,227,627,627,627,603
,603,603,755,609,603,762,603,603,603,603,603,603,474,603,666,682,755,610
,153,690,666,682,762,755,755,202,755,755,195,755,755,755,755,755,755,755
,762,755,755,553,755,755,170,755,755,755,755,755,755,755,154,146,162,179
,577,762,755,755,442,755,755,19,755,755,755,755,755,755,522,762,755,755
,105,755,755,59,755,755,755,755,755,755,19,19,122,19,19,441,19,19,19,19
,19,19,593,491,59,59,449,641,665,361,649,59,59,59,633,657,627,627,627,154
,146,162,185,627,627,65,627,627,283,283,627,627,627,563,563,563,218,290
,211,89,563,563,394,563,563,458,211,563,666,682,154,146,162,154,146,162
,521,233,627,393,627,201,505,513,627,627,627,563,563,563,154,146,162,329
,563,563,521,563,563,0,0,563,666,682,154,146,162,371,154,146,162,233,627
,555,627,201,243,555,627,627,627,0,690,666,682,371,371,371,0,371,371,0,0
,371,154,146,162,0,243,627,169,233,674,627,243,201,489,0,627,627,627,563
,563,563,0,169,563,377,563,618,563,249,563,427,0,563,563,563,563,563,563
,481,169,563,409,563,169,563,658,563,0,0,563,563,563,627,627,627,154,146
,162,0,627,627,0,627,627,0,0,627,627,627,154,146,162,154,146,162,0,233,154
,146,162,201,627,0,627,627,627,627,627,627,154,146,162,0,627,299,0,0,627
,627,0,627,627,627,563,563,563,755,154,146,162,563,154,146,162,563,563,299
,563,666,682,755,0,314,43,0,0,762,755,755,154,146,162,0,169,755,465,755
,0,417,482,762,323,755,466,625,43,450,762,755,755,755,43,43,43,0,755,755
,755,0,323,323,323,83,323,323,0,154,323,162,579,762,579,755,755,0,690,666
,682,755,755,755,587,0,587,83,0,0,690,666,682,83,98,83,762,0,755,154,146
,162,0,169,755,345}
,
{1,15,15,15,8,8,15,8,15,15,15,15,15,15,74,15,15,15,16,16,16,79,74,16,8,16
,16,16,16,16,16,50,16,16,16,80,27,17,27,27,27,79,79,79,71,79,79,71,79,79
,79,79,79,79,81,80,80,80,67,80,80,68,80,80,80,80,80,80,82,59,59,59,69,69
,81,81,81,42,81,81,0,81,81,81,81,81,81,11,82,82,82,11,82,82,2,82,82,82,82
,82,82,0,0,70,0,0,53,0,0,0,0,0,0,72,6,2,2,54,2,2,43,2,2,2,2,2,2,30,30,30
,22,22,22,21,30,30,6,30,30,64,64,30,30,30,31,31,31,73,64,73,9,31,31,58,31
,31,46,73,31,31,31,32,32,32,65,65,65,60,32,32,47,32,32,61,61,32,32,32,34
,34,34,75,75,75,39,34,34,63,34,34,83,83,34,34,34,35,35,35,52,52,52,52,35
,35,14,35,35,4,14,35,35,35,83,14,14,14,52,52,52,83,52,52,83,83,52,13,13
,13,83,4,13,23,13,23,13,4,13,4,83,13,13,13,10,10,10,83,45,10,45,10,29,10
,29,10,57,83,10,10,10,12,12,12,57,49,12,49,12,19,12,19,12,83,83,12,12,12
,28,28,28,18,18,18,83,28,28,83,28,28,83,83,28,28,28,26,26,26,40,40,40,83
,26,44,44,44,26,26,83,26,26,26,24,24,24,48,48,48,83,24,5,83,83,24,24,83
,24,24,24,25,25,25,66,66,66,66,25,51,51,51,25,25,5,25,25,25,38,83,5,76,83
,83,66,78,66,20,20,20,83,56,66,56,66,83,38,38,38,37,38,38,76,76,38,78,78
,78,77,76,76,76,83,78,78,78,83,37,37,37,3,37,37,83,7,37,7,36,77,36,77,62
,83,36,36,36,77,77,77,33,83,33,3,83,83,33,33,33,3,3,3,62,83,62,55,55,55
,83,41,62,41,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83
,83,83,83,83,83}
,
{80,0,94,386,207,318,114,389,4,145,241,81,258,224,198,0,17,29,278,260,352
,125,129,224,309,326,292,23,275,241,126,143,160,396,177,194,384,365,344
,176,295,417,71,112,300,239,150,162,312,256,25,334,198,101,109,419,350,248
,147,68,166,167,397,186,133,163,330,53,57,66,97,40,106,143,8,180,347,374
,351,21,35,54,68}
,
{
{{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{2,2}
,{1,1}
,{6,6}
,{2,2}
,{7,7}
,{2,2}
,{7,7}
,{7,7}
,{2,2}
,{2,2}
,{9,9}
,{2,2}
,{10,10}
,{2,2}
,{9,9}
,{2,2}
,{10,10}
,{2,2}
,{2,2}
,{14,14}
,{14,14}
,{2,2}
,{10,10}
,{2,2}
,{2,2}
,{10,10}
,{10,10}
,{2,2}
,{10,10}
,{10,10}
,{1,1}
,{1,1}
,{9,9}
,{2,2}
,{10,10}
,{7,7}
,{9,9}
,{2,2}
,{10,10}
,{7,7}
,{9,9}
,{2,2}
,{10,10}
,{7,7}
,{2,2}
,{1,1}
,{6,6}
,{9,9}
,{2,2}
,{10,10}
,{7,7}
,{7,7}
,{2,2}
,{2,2}
,{7,7}
,{1,1}
,{2,2}
,{7,7}
,{2,2}
,{1,1}
,{6,6}
,{5,5}
,{7,7}
,{7,7}
,{8,8}
,{8,8}
,{7,7}
,{7,7}
,{2,2}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
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
    UByte2 gto[203];		/* Goto table */
    UByte1 gtoRix[83];		/* Goto row mapping */
    UByte1 lhs[95];		/* Left hand side symbols */
    UByte1 rhsz[95];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{0,0,0,0,306,250,129,546,385,634,34,634,362,354,129,634,258,634,281,145
,177,145,177,497,17,145,177,145,177,353,634,25,241,137,330,346,321,538,338
,97,145,177,130,642,434,642,473,209,266,642,49,642,129,217,650,634,650,265
,113,26,650,130,650,545,642,145,177,129,274,257,634,74,289,722,561,650,634
,138,730,617,145,177,33,130,569,402,145,177,113,642,738,585,433,130,514
,402,138,498,90,130,650,545,433,130,642,410,594,305,106,594,642,537,594
,193,601,650,81,297,138,378,121,650,186,225,425,130,313,410,138,386,130
,50,410,530,138,337,57,506,138,73,369,138,66,130,138,410,114,138,570,698
,594,570,706,401,570,130,130,418,410,81,138,273,130,529,410,138,457,130
,714,234,746,0,161,0,0,0,530,0,138,0,10,0,0,0,0,138,0,0,0,41,138,138,570
,0,0,0,0,138,0,0,0,0,138}
,
{0,6,34,131,0,79,45,136,93,6,37,5,7,104,0,17,67,4,157,4,150,4,98,4,31,2
,107,8,2,3,53,6,145,46,21,101,61,89,0,1,120,1,1,1,125,1,1,1,138,1,1,78,88
,1,1,151,1,4,0,37,5,0,1,37,35,56,94,0,57,31,0,70,0,92,95,162,0,127,138,145
,148,164,166}
,
{58,65,65,82,44,44,79,79,83,92,92,66,89,89,86,41,39,39,74,74,51,87,87,55
,55,56,56,61,61,84,84,52,52,45,67,67,91,91,62,71,71,68,68,68,68,46,80,80
,75,48,49,49,76,76,72,70,69,63,47,42,60,60,37,37,35,57,36,36,34,85,85,64
,64,81,81,81,81,50,50,43,43,77,53,88,54,40,73,78,90,59,59,59,59,38,38}
,
{3,0,2,2,0,2,0,2,4,0,3,1,1,2,5,1,1,1,1,1,1,0,5,0,1,0,1,0,2,0,4,1,3,2,0,1
,0,3,1,0,2,1,1,1,1,2,1,2,7,1,1,3,0,2,5,1,5,1,5,1,0,3,1,2,4,1,1,3,2,0,2,3
,5,1,3,5,3,0,2,1,1,4,1,4,1,1,2,2,2,1,1,1,2,0,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[33];
			     
static VocTab voc = {{1,255,255,"EndOfText",""}
,{2,1,1,"IDENTIFIER","identifier"}
,{3,1,1,"STRING",""}
,{4,1,1,"ANG_BRACK_STRING",""}
,{5,1,1,"INTEGER",""}
,{6,1,1,"'='",""}
,{7,1,1,"';'",""}
,{8,1,1,"','",""}
,{9,1,1,"'('",""}
,{10,1,1,"')'",""}
,{11,1,1,"'!'",""}
,{12,1,1,"'|'",""}
,{13,1,1,"'{'",""}
,{14,1,1,"'}'",""}
,{15,1,1,"'=>'",""}
,{16,1,1,"'%%'",""}
,{17,1,1,"'%+'",""}
,{18,1,1,"'%-'",""}
,{19,1,1,"'META'",""}
,{20,1,1,"'SKIP'",""}
,{21,1,1,"'%%END'",""}
,{22,1,1,"'%%CODE'",""}
,{23,1,1,"'%%RULES'",""}
,{24,1,1,"'FIDUCIAL'",""}
,{25,1,1,"'%%EXPORT'",""}
,{26,1,1,"SKIPHEADER",""}
,{27,1,1,"'SEPARATOR'",""}
,{28,1,1,"'%%SCANNER'",""}
,{29,1,1,"'%%RECOVERY'",""}
,{30,1,1,"'%%TERMINALS'",""}
,{31,1,1,"'%%ATTRIBUTES'",""}
,{32,1,1,"'%%DECLARATIONS'",""}
,{33,1,1,"'%%INSERTSYMBOL'",""}
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
static UByte1 scIndex[33 + 1]; /* Converts scanner code to internal value */
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

extern void pmkRPoi();	/* Error recovery - restart point  */
extern void pmkISym();	/* Error recovery - insert symbol  */
extern void pmkDSym();	/* Error recovery - delete symbol  */
extern void pmkMess();	/* Error recovery - error message  */

/* External functions */
void pmkPaSema();

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(token, eClass, severity) 
PmkToken *token;		/* IN current token */
short eClass;			/* IN error classification */
short severity;			/* IN error severity code */
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
 *	      token on the symbol stack.
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
 *		     t = current token
 *		     y = unprocessed input
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
PmkToken *token;			/* INOUT symbol to delete, new symbol */
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
static void inSym(isym, gen_symb)
short isym;			/* IN symbol code to insert */
PmkToken *gen_symb;		/* OUT created symbol */
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
 *	      the continuation grammar.
 *----------------------------------------------------------------------------
 */
static void acceptbl(sym, stack, stack_p, token, found, point)
UByte1 sym;			/* IN terminal symbol code */
ParseStack stack;		/* IN parse stack */
short stack_p;			/* IN stack pointer */
PmkToken *token;			/* IN current token */
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
PmkToken *token;			/* INOUT current symbol */
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
PmkToken *token;			/* INOUT current symbol */
REC_POI *point;			/* IN recovery point descriptor */
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
static void multiple(err_stk, err_stkp, err_tok, newstat)
ParseStack err_stk;		/* INOUT current parse stack */
short *err_stkp;		/* INOUT current stack pointer */
PmkToken *err_tok;		/* INOUT current token */
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
PmkToken *curtok;			/* IN current token */
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
PmkToken *token;			/* OUT constructed token */
{
    inSym(sym, token);
}/*_pmInsert()*/


/*----------------------------------------------------------------------------
 * _pmReplace
 *----------------------------------------------------------------------------
 */
static void _pmReplace(sym, token)
UByte1 sym;			/* IN replacement symbol code */
PmkToken *token;			/* OUT constructed token */
{
    delSym(token);
    inSym(sym, token);
}/*_pmReplace()*/


/*----------------------------------------------------------------------------
 * _pmDelete
 *----------------------------------------------------------------------------
 */

static void _pmDelete(token)
PmkToken *token;			/* OUT new token */
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
static void single(leg_sys, err_stk, err_stkp, token, newstat)
TermSet leg_sys;		/* IN legal symbols in current state */
ParseStack err_stk;		/* INOUT current parser stack */
short *err_stkp;		/* INOUT current stack pointer */
PmkToken *token;		/* INOUT current token */
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
static void recover(err_stk, err_stkp, err_symb, rec_stat)
ParseStack err_stk;		/* INOUT updated parse stack */
short *err_stkp;		/* INOUT updated stack pointer */
PmkToken *err_symb;		/* INOUT current token */
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
void pmkParse()
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

