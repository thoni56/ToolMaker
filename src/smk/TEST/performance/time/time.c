/*
 * AUTHOR : Tony Olsson
 * DATE   : 1990-07-13/tony@whoozle
 *
 * MODIFIED:
 *
 */

#include "time.h"

/*
 * 
 * Timer functions
 *
 */

void tistart(tb)
     register Time tb;
{
    times(tb);
    tb->pu_start = tb->proc_user_time+tb->proc_system_time;;
    tb->cu_start = tb->child_user_time+tb->child_system_time;
}

void tirestart(tb)
     register Time tb;
{
    times(tb);
    tb->pu_start = tb->proc_user_time+tb->proc_system_time - tb->pu_elapsed;
    tb->cu_start = tb->child_user_time+tb->child_system_time - tb->cu_elapsed;
}

int tistop(tb)
     register Time tb;
{
    times(tb);
    tb->pu_elapsed = tb->proc_user_time+tb->proc_system_time - tb->pu_start;
    tb->cu_elapsed = tb->child_user_time+tb->child_system_time - tb->cu_start;
    return tb->pu_elapsed+tb->cu_elapsed;
}

char *tistr(time)
     register int time;
{
  static char buffer[9];

  sprintf(buffer,"%2d:%02d.%03d",time/(60*TI_HZ),(time/TI_HZ)%60,(time*1000/TI_HZ)%1000);
  return buffer;
}

