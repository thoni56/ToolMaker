/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#ifndef _common_h_
#define _common_h_

#include <time.h>
#include <stdio.h>

extern int gethostid();

#ifndef __hpux
extern int gethostname(char *name, int namelen);
#endif

#if !defined(__svr4__) && !defined(__hpux) && !defined(_WIN32)
extern int sscanf(char *s, char *format, ... );
extern long strtol(char *str, char **ptr, int base);
extern time_t time(time_t *tloc);
extern int fscanf(FILE *stream, char *format, ...);
extern int printf(char *format, ...);
extern int fprintf(FILE *stream, char* format, ...);
extern int fclose(FILE* stream);
#endif

#endif
