#ifndef _pwGe
#define _pwGe

#include "pws.h"
#include "set.h"

/* Parser states. Note that there are assumptions that error = 0!
 */
#define error 0
#define shift 1
#define shiftReduce 2
#define reduce 3
#define accept 4

extern int **actTbl;		/* Action table */
extern int **gtoTbl;		/* Goto table */
extern SETPTR *dontCare;	/* Don't care symbols */
extern int stateCnt;		/* Number of parser states */
extern int actRowCnt;		/* Number of rows in the action table */
extern int actColCnt;		/* Number of columns in the action table */
extern int actMax;		/* Largest value in action table */
extern int gtoRowCnt;		/* Number of rows in the goto table */
extern int gtoColCnt;		/* Number of columns in the goto table */
extern int gtoMax;		/* Largest value in goto table */
extern int tableFactor;		/* Divide factor in tables */

typedef struct {
    int tsym;			/* Normal continuation */
    int ssym;			/* Separator continuation */
} ContRec;

extern ContRec *contTbl;	/* Continuation function */

typedef struct {		/* Representation of one state */
    int istart;			/* Start of item set */
    int setsz;			/* Set size */
    int top;			/* Top of stack */
} StateRepr;

extern StateRepr *stateList;	/* States */

typedef enum ItemKind {		/* Item classification */
    tTrans,			/* Terminal transition */
    ntTrans,			/* Non terminal transition */
    complete			/* Completed item */
} ItemKind;

typedef struct {
    int prod;			/* Production number */
    int dot;			/* Position of the dot */
} ItemSpec;

typedef struct pi {		/* Predecessor representation */
    struct pi *nxt;		/* Next predecessor in chain */
    int pred;			/* Definition */
} PredItem;

typedef struct {		/* Representation of one item */
    ItemSpec item;		/* Item */
    int afterDot;		/* Symbol after the dot */
    int succState;		/* Sucessor state */
    ItemKind typ;		/* Transition type */
    Boolean sr;			/* Shift reduce item */
    PredItem *predList;		/* Predecessors */
    SETPTR laPtr;		/* Look-ahead set */
} ItemRepr;

extern ItemRepr *accItem;	/* Item Table */

/*-----------------------------------------------------------------------------
 * nrBytes - Returns the number of bytes a value will occupy. Note that it is
 *       assumed that there is an unsigned 8-bit data type on the target
 *       machine.
 *-----------------------------------------------------------------------------
 */
#define nrBytes(val) ((val) < 256? 1: ((val) < 65536? 2: 4))

/* The number of bytes a pointer value occupies
 */
#define pointerSize 4

extern void pwGenTab();

#endif
