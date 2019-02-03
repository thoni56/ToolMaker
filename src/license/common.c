/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#ifdef __hpux

/* This is for compilation on hp, for which neither gethostid() or
   sysinfo() is avilible. 
   */

#include <stdlib.h>
#include <sys/utsname.h>

int gethostid()
{
  struct utsname info;
  
  uname(&info);
  return atoi(info.idnumber);
}

#elif defined(__svr4__)

#include <stdlib.h>
#include <sys/systeminfo.h>

int gethostid()
{
  char buffer[32];
  sysinfo(SI_HW_SERIAL, buffer, 32);
  return atoi(buffer);
}

int gethostname(char *name, int namelen)
{
  sysinfo(SI_HOSTNAME, name, namelen);
  return 0;
}

#endif
