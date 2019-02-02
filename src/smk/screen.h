/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-17
 * 
 * SoftLab ab (c) 1990-1993
 *
 * $Header: /Repository/ToolMaker/src/smk/screen.h,v 1.1 2002/06/25 20:04:50 Thomas Nilsson Exp $
 *
 * $Log: screen.h,v $
 * Revision 1.1  2002/06/25 20:04:50  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:23  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:12:48  tools
 * Totaly rewritten to correctly handle vocabularies and rules.
 *
 * Revision 1.1  1993/03/24  09:24:47  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:15  tools
 * Initial revision
 * 
 *
 */

#ifndef _screen_h_
#define _screen_h_

#include "tmkCommon.h"
#include "common.h"

extern int *screenCheckScan;
extern int *screenCheckCode;
extern int *screenCheckCodeScan;
extern int *screenTableBegin;
extern int *screenTableEnd;
extern int *screenTokenLength;
extern int *screenTokenStart;
extern int *screenTokenCode;
extern int *screenTokens;

extern int screenCheckScanSize;
extern int screenCheckCodeSize;
extern int screenTableSize;
extern int screenTokenSize;
extern int screenTokensSize;
extern int screenTokensPackedSize;

extern Bool screenHasScreening;

extern void screenCreate();
extern void screenDump();

#endif
