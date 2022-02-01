/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-11
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/definition.h,v 1.1 2002/06/25 20:04:42 Thomas Nilsson Exp $
 *
 * $Log: definition.h,v $
 * Revision 1.1  2002/06/25 20:04:42  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:41  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:44  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.3  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.2  91/07/08  16:50:23  tools
 * Added named semantic actions
 *
 * Revision 1.1  1991/01/10  12:22:57  tools
 * Initial revision
 *
 *
 */

#ifndef _DEFINITION_H_
#define _DEFINITION_H_

typedef struct Definition *Definition;

#include "name.h"
#include "ast.h"
#include "action.h"

typedef struct Definition {
  Name name;
  short code;
  AST ast;
  Action action;
  Definition next;
} DefinitionItem;

extern Definition definitionGet(Name name);
extern Definition definitionPut(Name name);
extern void definitionFix();
extern void definitionDump();
extern void definitionPrint();

#endif
