/*----------------------------------------------------------------------*\

    tmkParse.c

    ParserMaker generated parser

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include "tmkScan.h"
#include "tmk.h"
extern tmkScContext tmkCext;
/* END %%IMPORT */

#include <string.h>
#include <setjmp.h>

#include "tmkParse.h"

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
#include "tmkCommon.h"

/* %%ATTRIBUTES - The semantic attributes for grammar symbols */
typedef struct tmkGrammar {
    OptNodeP opt;
    TmoNodeP dir;
    TokenAttrListP attr;
    int ival;
    char *sval;
    TmkSrcp srcp;
} tmkGrammar;

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
#define SccMax 22		/* Max scanner code value */
#define TermMin 1		/* Minimum terminal number */
#define Terms 22		/* Number of terminals in grammar */
#define StateMin 1		/* Minimum state number */
#define States 45		/* Number of states */
#define ProdMin 1		/* Minimum production number */
#define Prods 55		/* Number of productions */
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
    ContRec cont[45];		/* Continuation function */
    TermSet sepa;		/* Separator symbols */
    TermSet fiduc;		/* Fiducial symbols */
    TermSet skip;		/* Symbols to skip */
} RecTab;

typedef struct  {
    UByte2 act[318];		/* Action table */
    UByte1 actCheck[318];	/* Row Displacement Check Vector*/
    UByte2 actRix[45];		/* Action row mapping */
    RecTab recover;		/* Error recovery info */
} TermTab;

static TermTab act = {
{91,275,275,353,282,410,242,153,386,394,402,426,98,91,418,91,91,434,91,370
,91,378,226,353,275,410,330,282,386,394,402,426,98,91,418,91,91,434,91,370
,122,378,442,354,410,321,329,386,394,402,426,275,275,418,282,282,434,443
,370,442,378,410,443,443,386,394,402,426,4,275,418,91,282,434,218,370,201
,378,338,185,154,345,249,98,91,225,91,91,273,91,442,275,410,138,282,386
,394,402,426,146,275,418,91,282,434,322,370,234,378,346,73,89,113,130,98
,91,0,91,91,442,91,410,0,137,386,394,402,426,0,0,418,0,0,434,442,370,410
,378,0,386,394,402,426,0,0,418,0,0,434,442,370,410,378,0,386,394,402,426
,0,0,418,0,0,434,442,370,410,378,0,386,394,402,426,0,0,418,0,0,434,442,370
,410,378,0,386,394,402,426,0,0,418,0,0,434,442,370,410,378,0,386,394,402
,426,0,0,418,0,0,434,442,370,410,378,0,386,394,402,426,0,0,418,0,0,434,442
,370,410,378,0,386,394,402,426,0,0,418,0,0,434,442,370,410,378,0,386,394
,402,426,0,0,418,91,0,434,442,370,410,378,67,386,394,402,426,98,91,418,91
,91,434,91,370,67,378,67,67,91,67,201,297,19,185,0,0,249,0,11,225,98,91
,273,91,91,19,91,19,19,0,19,298,0,194,41,0,49,73,89,113,0,0,0,0,0,0,0,0
,0,0,137}
,
{36,19,19,36,19,36,17,17,36,36,36,36,36,36,36,36,36,36,36,36,37,36,12,37
,34,37,26,34,37,37,37,37,37,37,37,37,37,37,37,37,38,37,38,35,38,38,38,38
,38,38,38,25,14,38,25,14,38,43,38,43,38,43,43,43,43,43,43,43,1,28,43,21
,28,43,9,43,21,43,29,21,41,41,21,21,21,21,21,21,21,21,18,11,18,39,11,18
,18,18,18,40,31,18,7,31,18,23,18,15,18,32,7,7,7,44,7,7,45,7,7,22,7,22,45
,7,22,22,22,22,45,45,22,45,45,22,24,22,24,22,45,24,24,24,24,45,45,24,45
,45,24,27,24,27,24,45,27,27,27,27,45,45,27,45,45,27,30,27,30,27,45,30,30
,30,30,45,45,30,45,45,30,33,30,33,30,45,33,33,33,33,45,45,33,45,45,33,8
,33,8,33,45,8,8,8,8,45,45,8,45,45,8,10,8,10,8,45,10,10,10,10,45,45,10,45
,45,10,13,10,13,10,45,13,13,13,13,45,45,13,45,45,13,42,13,42,13,45,42,42
,42,42,45,45,42,5,45,42,16,42,16,42,0,16,16,16,16,5,5,16,5,5,16,5,16,0,16
,0,0,4,0,20,0,2,20,45,45,20,45,3,20,4,4,20,4,4,2,4,2,2,45,2,3,45,3,3,45
,3,6,6,6,45,45,45,45,45,45,45,45,45,45,6}
,
{258,68,279,285,275,251,296,102,191,73,206,90,21,221,51,106,251,5,87,0,272
,71,116,104,131,50,25,146,68,77,161,99,108,176,23,42,0,20,39,92,98,79,236
,56,112}
,
{
{{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{1,1}
,{9,9}
,{1,1}
,{20,20}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{20,20}
,{2,2}
,{9,9}
,{1,1}
,{20,20}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
,{1,1}
,{1,1}
,{2,2}
,{2,2}
,{2,2}
,{2,2}
,{20,20}
,{2,2}
,{2,2}
}
,
{0,0,0}
,
{0,0,0}
,
{0,0,0}
}
};


/* Non terminal table *\
\* ------------------ */
typedef  struct {
    UByte2 gto[53];		/* Goto table */
    UByte1 gtoRix[45];		/* Goto row mapping */
    UByte1 lhs[55];		/* Left hand side symbols */
    UByte1 rhsz[55];		/* Size of the RHS */
} NonTermTab;

static NonTermTab gto = {
{0,0,313,202,161,65,169,313,58,42,74,57,26,50,161,82,129,34,17,106,250,305
,145,314,114,306,25,210,177,337,258,162,290,362,186,33,266,178,81,193,209
,217,233,241,257,265,281,289,97,105,121,170,361}
,
{11,4,19,0,27,23,0,24,36,2,46,35,1,48,2,1,2,1,12,22,24,22,37,1,38,27,1,40
,29,1,42,31,0,44,33,0,0,5,29,0,0,0,49,50,0}
,
{30,39,39,35,35,35,35,38,38,38,33,33,44,44,42,42,42,42,42,23,23,40,36,34
,28,28,26,26,26,26,43,43,41,37,37,31,29,27,27,24,24,24,24,24,32,25,25,25
,25,25,25,25,25,25,25}
,
{2,0,2,1,1,1,1,0,2,3,0,1,1,2,2,3,3,3,3,1,3,2,3,1,1,2,3,4,4,3,1,3,2,0,1,3
,1,1,2,3,4,4,4,4,2,1,1,1,1,1,1,1,1,1,1}
};


/* Vocabulary *\
\* ---------- */
typedef struct {
    UByte1 scc;			/* Scanner code value */
    UByte1 iCost;		/* Insertion cost */
    UByte1 dCost;		/* Deletion cost */
    char *name;			/* Name string */
    char *psym;			/* Print name */
} VocTab[22];

static VocTab voc = {{1,255,255,"EndOfText",""}
,{2,1,1,"';'",""}
,{3,1,1,"','",""}
,{4,1,1,"'NO'",""}
,{5,1,1,"'%%'",""}
,{6,1,1,"'ROW'",""}
,{7,1,1,"NUMBER",""}
,{8,1,1,"STRING",""}
,{9,1,1,"'NAME'",""}
,{10,1,1,"'CODE'",""}
,{11,1,1,"'SRCP'",""}
,{12,1,1,"'FILE'",""}
,{13,1,1,"'%%END'",""}
,{14,1,1,"'%%SRCP'",""}
,{15,1,1,"'COLUMN'",""}
,{16,1,1,"'%%TOKEN'",""}
,{17,1,1,"'%%IMPORT'",""}
,{18,1,1,"'POSITION'",""}
,{19,1,1,"SKIPHEADER",""}
,{20,1,1,"IDENTIFIER",""}
,{21,1,1,"'%%OPTIONS'",""}
,{22,1,1,"'ATTRIBUTES'",""}
}
;


/* Variables used in the parsing process *\
\* ------------------------------------- */
short tmkStkP;			/* Stack pointer */
TmkToken tmkSySt[PmStkMax];	/* Symbol stack */
tmkGrammar tmkSeSt[PmStkMax];	/* Semantic stack */
static UByte1 currstat;		/* Current state number */
static UByte1 arg;		/* Argument */
static UByte1 action;		/* Action type */
static PmBoolean endparse;	/* Termination flag */
static ParseStack parsStk;	/* Parse stack */
static UByte1 scIndex[22 + 1]; /* Converts scanner code to internal value */
static TmkToken tokenBuf;	/* Scanner token buffer */
static TmkToken *token = &tokenBuf;	/* Pointer to it for readsymb */


/* Error recovery look-ahead buffer *\
\* -------------------------------- */
static TmkToken la_buff[PmLaMax + 1]; /* Buffer */
static int la_ptr;		/* Current pointer */
static int la_end;		/* Last item */

static jmp_buf pmJmpB;		/* Buffer for long jump */

/* Interface routines *\
\* ------------------ */

extern void tmkRPoi(	/* Error recovery - restart point  */
TmkToken *sym			/* IN the restart symbol */
);
extern void tmkISym(	/* Error recovery - insert symbol  */
 int code,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr,			/* IN the terminals print symbol */
TmkToken *sym			/* OUT the created scanner symbol */
);
extern void tmkDSym(	/* Error recovery - delete symbol  */
TmkToken *sym,			/* IN terminal code number */
char *sstr,			/* IN terminal string */
char *pstr			/* IN terminals print string */
);
extern void tmkMess(	/* Error recovery - error message  */
TmkToken *sym,			/* IN error token */
int method,			/* IN recovery method */
int code,			/* IN error classification */
int severity			/* IN error severity code */
);

/* External functions */
extern void tmkPaSema(
int rule			/* IN production number */
);

/*----------------------------------------------------------------------------
 * paAbort - Abort the parsing process
 *----------------------------------------------------------------------------
 */
static void paAbort(
TmkToken *token,		/* IN current token */
short eClass,			/* IN error classification */
short severity			/* IN error severity code */
)
{
    tmkMess(token, HALT_REC, eClass, severity);
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
    tmkStkP = 0;
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
#define MOVETOKEN tmkSySt[tmkStkP] = *token
#define pushStatTok()\
{\
    if (++tmkStkP < PmStkMax) {\
    parsStk[tmkStkP] = currstat;\
    MOVETOKEN;\
    } else {\
    token->code = voc[token->code-TermMin].scc;\
    paAbort(token, OFLW_ERR, SYS_SEV);\
    }\
}

#define pushStat()\
{\
    if (++tmkStkP < PmStkMax) {\
    parsStk[tmkStkP] = currstat;\
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
    TmkToken err_tok;
    TmkToken res_tok;
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
TmkToken *token			/* INOUT symbol to delete, new symbol */
)
{
    short  t;

    t = token->code - TermMin;
    token->code = voc[t].scc;
    tmkDSym(token, voc[t].name, voc[t].psym);
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
TmkToken *gen_symb		/* OUT created symbol */
)
{
    tmkISym(voc[isym - TermMin].scc, voc[isym - TermMin].name,
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
TmkToken *token,			/* IN current token */
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
TmkToken *token,			/* INOUT current symbol */
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
TmkToken *token,			/* INOUT current symbol */
REC_POI *point			/* IN recovery point descriptor */
)
{
    UByte1 state;		/* Current state */
    UByte1 cont_sym;		/* Continuation symbol */
    TmkToken gen_symb;		/* Generated symbol */
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
        tmkSySt[*stack_p] = gen_symb;
        break;

      case SHIFTRED_ACT:
        sepaAccept = PMTRUE;
        inSym(cont_sym, &gen_symb);
        ePush(state, stack, stack_p);
        tmkSySt[*stack_p] = gen_symb;
        goto reduce;

      case REDUCE_ACT:
        reduce:
        do {
        *stack_p = *stack_p - gto.rhsz[arg-ProdMin];
        tmkPaSema(arg);
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
TmkToken *err_tok,		/* INOUT current token */
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
TmkToken *curtok			/* IN current token */
)
{
    int i;
    TmkToken tokbuf;
    TmkToken *token = &tokbuf;

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

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else {
        token->code = scIndex[token->code];
        }/*if*/
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
TmkToken *token			/* OUT constructed token */
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
TmkToken *token			/* OUT constructed token */
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
TmkToken *token			/* OUT new token */
)
{
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
TmkToken *token,		/* INOUT current token */
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

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
TmkToken *err_symb,		/* INOUT current token */
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
    tmkMess(&errdescr.err_tok, errdescr.method, errdescr.eClass,
           errdescr.severity);
    } else {
    tmkMess(&errdescr.err_tok, errdescr.method, SYN_ERR, errdescr.severity);
    }/*if*/
    errdescr.res_tok = *err_symb;
    errdescr.res_tok.code = voc[errdescr.res_tok.code - TermMin].scc;
    tmkRPoi(&errdescr.res_tok);
}/*recover()*/


/*----------------------------------------------------------------------------
 * tmkParse - Parser routine, entry point
 *----------------------------------------------------------------------------
 */
void tmkParse(void)
{
    paInit();
{
    if (la_ptr < la_end) {
    la_ptr++;
    *token = la_buff[la_ptr];
    } else {
    do {

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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
        recover(parsStk, &tmkStkP, token, &currstat);
        if (tmkStkP == 0) endparse = PMTRUE;
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

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
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

tmkScan(tmkCext, token);

        if (token->code > SccMax || token->code < 0) {
        token->code = ERR_SYM;
        } else token->code = scIndex[token->code];
        if (token->code == ERR_SYM) {
        tmkMess(token, DEL_REC, LEX_ERR, FAT_SEV);
        }
    } while (token->code == ERR_SYM);
    }
}
        goto reduce;

    case REDUCE_ACT:
      reduce:
        do {
        tmkStkP -= gto.rhsz[arg - ProdMin];
        tmkPaSema(arg);
        gtoTbl(parsStk[tmkStkP], gto.lhs[arg - ProdMin], &action, &arg);
        pushStat();
        } while (action != SHIFT_ACT);

        currstat = arg;
        parsStk[tmkStkP] = currstat;
        break;

    case ACCEPT_ACT:
        endparse = PMTRUE;
        break;
    }/*switch*/
    }/*while*/
}/*tmkParse()*/

