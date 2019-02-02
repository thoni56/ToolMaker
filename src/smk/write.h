/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-27
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/write.h,v 1.1 2002/06/25 20:05:05 Thomas Nilsson Exp $
 *
 * $Log: write.h,v $
 * Revision 1.1  2002/06/25 20:05:05  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:34:09  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/27  14:22:27  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.1  1993/03/24  09:25:38  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  10:36:19  tools
 * Initial revision
 * 
 *
 */

#ifndef _WRITE_H_
#define _WRITE_H_

extern void writeAll(Pack pack, int *size, int *maxsize, int unoptsize);

#endif
