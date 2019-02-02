/*		@(#)pwSymSet.c	1.2 (90/11/07 09:49:12)		*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pws.h"
#include "pwSymSet.h"
#include "pwsGrm.h"

static void SymSetExpand(s)
SymSet s;
{
    SETPTR ss;
    int curLen;

    if (s->curLen < sym_max) {
	curLen = s->curLen;
	ss = s->ss;
	s->curLen = sym_max;
	s->ss = (SETPTR)malloc(SETLEN(sym_max));
	SetClear(s->ss, s->curLen);
	memcpy((char *)s->ss, (char *)ss, SETLEN(curLen));
	free((char *)ss);
    }/*if*/
}/*SymSetExpand()*/

SymSet SymSetAlloc()
{
    SymSet temp;

    temp = (SymSet)malloc(sizeof(SymSetStruct));
    temp->curLen = sym_max;
    temp->ss = (SETPTR)malloc(SETLEN(sym_max));
    SymSetClear(temp);
    return temp;
}/*SymSetAlloc()*/

void SymSetClear(s)
SymSet s;
{
    SymSetExpand(s);
    SetClear(s->ss, s->curLen);
}/*SymSetClear()*/

void SymSetDel(s, i)
SymSet s;
int i;
{
    SymSetExpand(s);
    SetDel(s->ss, i);
}/*SymSetDel()*/

void SymSetIns(s, i)
SymSet s;
int i;
{
    SymSetExpand(s);
    SetIns(s->ss, i);
}/*SymSetIns()*/

Boolean SymSetMem(s, i)
SymSet s;
int i;
{
    SymSetExpand(s);
    return SetMem(s->ss, i);
}/*SymSetMem()*/

Boolean SymSetEq(s1, s2)
SymSet s1;
SymSet s2;
{
    SymSetExpand(s1);
    SymSetExpand(s2);
    return !memcmp((char *)s1->ss, (char *)s2->ss, SETLEN(s1->curLen));
}/*SymSetEq()*/

Boolean SymSetEmpty(s)
SymSet s;
{
    SymSetExpand(s);
    return SetEmpty(s->ss, s->curLen);
}/*SymSetEmpty()*/

void SymSetUnion(s1, s2, sout)
SymSet s1;
SymSet s2;
SymSet sout;
{
    SymSetExpand(s1);
    SymSetExpand(s2);
    SymSetExpand(sout);
    SetUnion(s1->ss, s2->ss, sout->ss, sout->curLen);
}/*SymSetUnion()*/

void SymSetInter(s1, s2, sout)
SymSet s1;
SymSet s2;
SymSet sout;
{
    SymSetExpand(s1);
    SymSetExpand(s2);
    SymSetExpand(sout);
    SetInter(s1->ss, s2->ss, sout->ss, sout->curLen);
}/*SymSetInter()*/
