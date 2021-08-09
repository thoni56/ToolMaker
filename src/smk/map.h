/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-25
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/map.h,v 1.1 2002/06/25 20:04:45 Thomas Nilsson Exp $
 *
 * $Log: map.h,v $
 * Revision 1.1  2002/06/25 20:04:45  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:56  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:24:11  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:04  tools
 * Initial revision
 *
 *
 */

#ifndef _MAP_H_
#define _MAP_H_

extern short mapTable[256];
extern short mapSkip;
extern short mapUsed;

extern void mapPut(char *map1, char *map2);
extern void mapDump(void);
extern void mapPrint(void);

#endif
