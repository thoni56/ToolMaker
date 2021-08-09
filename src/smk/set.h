/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-25
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/set.h,v 1.1 2002/06/25 20:04:51 Thomas Nilsson Exp $
 *
 * $Log: set.h,v $
 * Revision 1.1  2002/06/25 20:04:51  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:26  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/27  14:21:57  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.1  1993/03/24  09:24:51  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.3  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.2  91/07/10  14:20:01  tools
 * New SET handling
 *
 * Revision 1.1  1991/01/10  12:23:17  tools
 * Initial revision
 *
 *
 */

#ifndef _SET_H_
#define _SET_H_

typedef struct Set *Set;

#include "name.h"
#include "smkScan.h"

typedef struct Set {
  Name name;
  short code[256];
  struct Set *next;
} SetItem;

extern short *setTable;
extern short setSkip;
extern short setUsed;

extern Set setPut(Name name);
extern Set setGet(Name name);
extern Set setUse(Name name);
extern void setDump();
extern void setPrint();
extern void setRead(smkScContext context);
extern void setCheck(Name name, short *code);
extern void setInit(void);

#endif
