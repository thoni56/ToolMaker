/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-11
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/definition.c,v 1.1 2002/06/25 20:04:41 Thomas Nilsson Exp $
 *
 * $Log: definition.c,v $
 * Revision 1.1  2002/06/25 20:04:41  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:32:39  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:42  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.4  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.3  91/07/11  10:38:37  tools
 * Added Inherited scanners and Undefined tokens
 * 
 * Revision 1.2  1991/07/08  16:50:23  tools
 * Added named semantic actions
 *
 * Revision 1.1  1991/01/10  13:06:22  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include "definition.h"
#include "lmprintf.h"
#include "smalloc.h"
#include "smkList.h"
#include "smk_i.h"

Definition *definitionTable=NULL;

static Definition definitionRoot=NULL;
static Definition definitionEnd=NULL;
static int definitionSize=0;

/*
 * Locate definition. If the definition does not exist return NULL!
 */

Definition definitionGet(Name name)
{
  Definition definition;

  for(definition=definitionRoot;definition;definition=definition->next)
    if(definition->name==name) return definition;
  return NULL;
}

/*
 * Insert a new definition. If the definition does exist return NULL!
 */

Definition definitionPut(Name name)
{
  Definition definition;

  for(definition=definitionRoot;definition;definition=definition->next)
    if(definition->name==name) return NULL;
  definition=(Definition)smalloc(sizeof(DefinitionItem));
  definition->name=name;
  definition->code=definitionSize++;
  definition->ast=NULL;
  definition->action=NULL;
  definition->next=NULL;
  if(definitionRoot) 
    definitionEnd=(definitionEnd->next=definition);
  else
    definitionRoot=definitionEnd=definition;
  return definition;
}

/*
 * Create a definition table of the definition list.
 */

void definitionFix()
{
  Definition definition;

  if(definitionTable==NULL) free((char *)definitionTable);
  definitionTable=(Definition *)smalloc((unsigned int)(sizeof(Definition)*definitionSize));
  for(definition=definitionRoot;definition;definition=definition->next)
    if(definition->code<definitionSize) definitionTable[definition->code]=definition;
}

void definitionDump()
{
  Definition definition;
  
  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("Defined Defintions\n\n");
  for(definition=definitionRoot;definition;definition=definition->next)
    lmPrintf("\t%4d %s\n",definition->code,definition->name);
  lmFlush();
}

void definitionPrint()
{
  Definition definition;
  
  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("Definitions\n\n");
  for(definition=definitionRoot;definition;definition=definition->next)
    lmPrintf("\t%s\n",definition->name);
  lmFlush();
}
