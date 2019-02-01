/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-05-27/tools@eeyore
 * CREATED: 1990-06-27
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/action.h,v 1.1 2002/06/25 20:04:39 Thomas Nilsson Exp $
 *
 * $Log: action.h,v $
 * Revision 1.1  2002/06/25 20:04:39  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/05/27 08:41:35  tools
 * Sorry, previous change (%%CODE) was WRONG!
 * This section is removed again.
 *
 * Revision 1.2  1993/04/30  12:32:24  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:29  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:22:53  tools
 * Initial revision
 * 
 *
 */

#ifndef _ACTION_H_
#define _ACTION_H_

typedef struct Action *Action;

#include "token.h"

typedef enum ActionType {
  actionNONE,
  actionSEMANTIC,
  actionDECLARATION,
/*
  actionCODE,
*/
  actionCONTEXT,
  actionEXPORT,
  actionREADER,
  actionACTION,
  actionPREHOOK,
  actionPOSTHOOK
  } ActionType;

typedef struct Action {
  int code;
  ActionType type;
  int start;
  int stop;
  Action next;
} ActionItem;

extern Action actionRoot;
extern int actionSize;

extern Action actionPut(ActionType type, int start, int stop);

#endif
