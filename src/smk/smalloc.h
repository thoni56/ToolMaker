/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-07-11
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/smalloc.h,v 1.1 2002/06/25 20:04:52 Thomas Nilsson Exp $
 *
 * $Log: smalloc.h,v $
 * Revision 1.1  2002/06/25 20:04:52  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:30  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:24:58  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:37  tools
 * Initial revision
 * 
 *
 */

#ifndef _SMALLOC_H_
#define _SMALLOC_H_

extern char *smalloc(unsigned int size);
extern char *srealloc(char *buffer, unsigned int size);

#endif
