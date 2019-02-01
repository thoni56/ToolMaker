/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#ifdef __svr4__

#include <malloc.h>
#include <string.h>
#include "common.h"

/*
 * strdup is not defined in strict ANSI C
 */

char *strdup(const char *str)
{
  char *buf;
  buf=(char *)malloc(strlen(str)+1);
  strcpy(buf,str);
  return buf;
}

#endif
