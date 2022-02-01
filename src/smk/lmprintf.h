/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-07-11
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/lmprintf.h,v 1.1 2002/06/25 20:04:43 Thomas Nilsson Exp $
 *
 * $Log: lmprintf.h,v $
 * Revision 1.1  2002/06/25 20:04:43  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:49  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:56  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:00  tools
 * Initial revision
 *
 *
 */

#ifndef _LMPRINTF_H_
#define _LMPRINTF_H_

extern void lmPrintf(char *format, ...);
extern void lmFlush(void);

#endif
