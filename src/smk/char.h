/*
 * AUTHOR: Tony Olsson
 * DATE: 1993-04-30/tools@wolf
 * CREATED: 1990-06-11
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/char.h,v 1.1 2002/06/25 20:04:41 Thomas Nilsson Exp $
 *
 * $Log: char.h,v $
 * Revision 1.1  2002/06/25 20:04:41  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:34  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:40  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:22:56  tools
 * Initial revision
 * 
 *
 */

#ifndef _CHAR_H_
#define _CHAR_H_

extern short charSize;
extern short charTable[256];
extern short charMinTable[256];
extern short charMaxTable[256];


extern char *charClass(char *string);
extern int charIsRevClass(char *class);
extern int charString(unsigned char *string1);
extern short charDequote(unsigned char *string);
extern short charQuoteLength(char *string);
extern void charDumpClass(char *class);

#endif
