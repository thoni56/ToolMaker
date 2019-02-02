/*		@(#)pwSymSet.h	1.2 (90/11/07 09:49:12)		*/

#ifndef _pwSymSet
#define _pwSymSet

#include "pws.h"
#include "set.h"

typedef struct {
    int curLen;			/* Current length of the symbol set */
    SETPTR ss;			/* The symbol set itself */
} SymSetStruct, *SymSet;

extern SymSet SymSetAlloc();
extern void SymSetDel(); 
extern void SymSetIns();
extern Boolean SymSetMem();
extern void SymSetClear();
extern Boolean SymSetEq();
extern Boolean SymSetEmpty();
extern void SymSetUnion();
extern void SymSetInter();

#define SymSetSize(s) (s)->curLen

#endif
