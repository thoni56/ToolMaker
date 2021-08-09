/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 *
 * SoftLab ab (c) 1993
 */

#include <stdlib.h>
#include "passwd.h"

#define MOD 67099547
#define RND(x)  ((((((x)<<4)%MOD)<<4)%MOD)<<5)%MOD

int rnd(int rand, unsigned long int n)
{
  long random;
  random=RND(rand^n)*65629;
  random^=RND(random^n);
  return random;
}

unsigned long passwd(int year, int mon, int day, int user, unsigned long int hostid)
{
  unsigned long random;

#if 0
  srand(RND(year));random=rand();
  srand(RND(mon)^random);random^=rand();
  srand(RND(day)^random);random^=rand();
  srand(RND(user)^random);random^=rand();
  srand(RND(hostid)^random);random^=rand();
#else
  random=rnd(35753465,mon);
  random=rnd(random,hostid);
  random=rnd(random,day);
  random=rnd(random,user);
  random=rnd(random,year);
#endif
  return random;
}
