/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-29/tools@wolf
 * CREATED: 1990-06-13
 *
 * SoftLab ab (c) 1990
 *
 * $Header@
 *
 * $Log: lmprintf.c,v $
 * Revision 1.1  2002/06/25 20:04:43  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:32:46  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:03:54  tools
 * Updated due to changes in ListerMaker
 *
 * Revision 1.1  1993/03/24  09:23:54  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:15:42  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include "common.h"
#include "lmprintf.h"
#include "smkList.h"

static char *eb=NULL;
static char *sb;
static char buffer[512+128];

void lmPrintf(char *format, ...)
{
  va_list args;
  int len;

  va_start(args, format);
  if(eb-buffer>512) smkLiPrint(sb),eb=NULL;
  if(eb==NULL) sb=eb=buffer;
  vsprintf(eb,format,args);
  va_end(args);
  while(*eb)
    if(*eb=='\n') {
      *eb++ =0;
      smkLiPrint(sb);
      sb=eb;
    }
    else
      eb++;
  len=eb-sb;
  memcpy(buffer,sb,len);
  sb=buffer;
  eb=buffer+len;
  *eb=0;
}

void lmFlush()
{
  if(eb!=sb)
    smkLiPrint(buffer);
  eb=NULL;
}
