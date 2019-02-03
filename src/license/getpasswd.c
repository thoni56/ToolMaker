/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include "common.h"
#include "passwd.h"

int main(int argc, char **argv)
{
  struct tm* tm;
  time_t t;
  int year;
  int month;
  int day;
  int users;
  char *host;
  long hostid;
  

  if(argc!=7) fprintf(stderr,"usage: %s year month day users host hostid\n",*argv),exit(1);
  year=atoi(argv[1]);
  month=atoi(argv[2]);
  day=atoi(argv[3]);
  users=atoi(argv[4]);
  host=argv[5];
#ifdef __svr4__
  hostid=strtoul(argv[6],NULL,16);
#elif defined(__hpux)
  hostid=atoi(argv[6]);
  fprintf(stderr,"HP-UX WARNING! reading the specified hostid as a decimal number, not as a hexadecimal number\n");
#else
  hostid=strtol(argv[6],NULL,16);
#endif

  if(month<1 || month>12) fprintf(stderr,"%s: illegal month number given, %d\n",*argv,month),exit(1);
  if(day<1 || day>31) fprintf(stderr,"%s: illegal day number given, %d\n",*argv,day),exit(1);

  t=time(0);
  tm=localtime(&t);
  tm->tm_year+=1900;
  tm->tm_mon++;
  if(tm->tm_year > year ||
     (tm->tm_year == year &&
      (tm->tm_mon > month ||
       (tm->tm_mon == month && tm->tm_mday > day))))
    fprintf(stderr,"%s: the given date, %d-%02d-%02d, is out of date\n",*argv,year,month,day);

  printf("DATE = %d-%d-%d\n",year,month,day);
  printf("USERS = %d\n",users);
  printf("HOST = %s\n",host);
  printf("HOSTID = %08X\n",hostid);
  printf("PASSWORD = %08X\n", (unsigned int)passwd(year,month,day,users,hostid));

  return 0;
}

  
