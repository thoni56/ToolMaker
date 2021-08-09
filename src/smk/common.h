/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-04-16
 *
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/common.h,v 1.1 2002/06/25 20:04:41 Thomas Nilsson Exp $
 *
 * $Log: common.h,v $
 * Revision 1.1  2002/06/25 20:04:41  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.5  1997/01/22 16:27:29  gunilla
 * Adapted for WIN32
 *
 * Revision 1.4  1993/08/20 11:33:49  tony
 * Conforms more to ANSI C standard.
 *
 * Revision 1.3  1993/04/30  12:32:37  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/27  14:21:47  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.1  1993/04/23  10:24:29  tools
 * Initial revision
 *
 */

#ifndef _common_h_
#define _common_h_

#include <stdlib.h>
#ifdef WIN32
#define F_OK        0   /* does file exist */
#define W_OK        2   /* is it writable by caller */
#define R_OK        4   /* is it readable by caller */
#else
#include <unistd.h>
#endif

enum {codeSKIP=-1};
typedef int Code;
typedef enum {YES=(0==0), NO=(0==1)} Bool;

#ifndef WIN32
#ifdef __svr4__
/*
 * These are not defined under SunOS 4.x
 */
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>

extern int fprintf(FILE *stream, char *format, ...);
extern int fwrite(char *ptr,int size, int nitems, FILE *stream);
extern int printf(char *format, ...);
extern int strftime(char *buf, int bufsize, char *fmt, struct tm *tm);
extern long strtol(char *str, char **ptr, int base);
extern time_t time(time_t *tlocy);
extern void fclose(FILE *stream);
extern char *vsprintf(char *s, char *format, ...);
#else
/*
 * Not strict ansi but ...
 */
extern char* strdup(const char *str);
#endif
#endif

#endif
