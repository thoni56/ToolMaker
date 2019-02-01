/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1991-01-10
 * 
 * SoftLab ab (c) 1991
 *
 * $Header: /Repository/ToolMaker/src/smk/time.c,v 1.1 2002/06/25 20:05:00 Thomas Nilsson Exp $
 *
 * $Log: time.c,v $
 * Revision 1.1  2002/06/25 20:05:00  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1997/01/22 16:30:11  gunilla
 * Adapted for WIN32
 *
 * Revision 1.2  1993/04/30 12:33:47  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:25:14  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:45:14  tools
 * Initial revision
 * 
 *
 */

#include <stdio.h>
#include <sys/types.h>
#ifdef WIN32
#include <time.h>
#else
#include <sys/times.h>
#endif
#include "time.h"

/*
 * 
 * Timer functions
 *
 */

void tistart(Time tb)
{
#ifdef WIN32
    tb->proc_user_time = clock();
    tb->proc_system_time = 0;
    tb->child_user_time = 0;
    tb->child_system_time = 0;
#else
    times((struct tms *)tb);
#endif
    tb->pu_start = tb->proc_user_time+tb->proc_system_time;;
    tb->cu_start = tb->child_user_time+tb->child_system_time;
}

void tirestart(Time tb)
{
#ifdef WIN32
    tb->proc_user_time = clock();
    tb->proc_system_time = 0;
    tb->child_user_time = 0;
    tb->child_system_time = 0;
#else
    times((struct tms *)tb);
#endif
    tb->pu_start = tb->proc_user_time+tb->proc_system_time - tb->pu_elapsed;
    tb->cu_start = tb->child_user_time+tb->child_system_time - tb->cu_elapsed;
}

int tistop(Time tb)
{
#ifdef WIN32
    tb->proc_user_time = clock();
    tb->proc_system_time = 0;
    tb->child_user_time = 0;
    tb->child_system_time = 0;
#else
    times((struct tms *)tb);
#endif
    tb->pu_elapsed = tb->proc_user_time+tb->proc_system_time - tb->pu_start;
    tb->cu_elapsed = tb->child_user_time+tb->child_system_time - tb->cu_start;
    return tb->pu_elapsed+tb->cu_elapsed;
}

char *tistr(int time)
{
  static char buffer[9];

  sprintf(buffer,"%2d:%02d.%02d",time/(60*TI_HZ),((int)(time/TI_HZ))%60,((int)(time*100/TI_HZ))%100);
  return buffer;
}

