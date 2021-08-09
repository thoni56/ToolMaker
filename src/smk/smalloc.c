/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-07-11
 *
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/smalloc.c,v 1.1 2002/06/25 20:04:51 Thomas Nilsson Exp $
 *
 * $Log: smalloc.c,v $
 * Revision 1.1  2002/06/25 20:04:51  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:28  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:24:56  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:52:39  tools
 * Initial revision
 *
 *
 */

#include <malloc.h>
#include <stdio.h>
#include "common.h"
#include "smalloc.h"

char *smalloc(unsigned int size)
{
  char *buffer;


  buffer=(char *)malloc(size);
  if(buffer==NULL)
    fprintf(stderr,"\n\t241 F : Out of Memory\n"),exit(1);
  return buffer;
}

char *srealloc(char *buffer, unsigned int size)
{
  buffer=(char *)realloc(buffer,size);
  if(buffer==NULL)
    fprintf(stderr,"\n\t241 F : Out of Memory\n"),exit(1);
  return buffer;
}
