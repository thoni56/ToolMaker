/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-27
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/action.c,v 1.1 2002/06/25 20:04:39 Thomas Nilsson Exp $
 *
 * $Log: action.c,v $
 * Revision 1.1  2002/06/25 20:04:39  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:22  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:27  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  12:58:06  tools
 * *** empty log message ***
 *
 * Revision 1.1  91/01/10  13:50:52  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include "smalloc.h"
#include "action.h"

Action actionRoot=NULL;
int actionSize=0;

static Action actionEnd=NULL;

Action actionPut(ActionType type, int start, int stop)
{
  Action action;

  action=(Action)smalloc(sizeof(ActionItem));
  action->code=actionSize++;
  action->type=type;
  action->start=start;
  action->stop=stop;
  action->next=NULL;
  if(actionRoot)
    actionEnd=actionEnd->next=action;
  else
    actionEnd=actionRoot=action;
  return action;
}
