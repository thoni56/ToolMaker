/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 *
 * BASED ON:
 *     time.c/time.h by Reibert Olsson
 *
 *
 * $Header: /Repository/ToolMaker/src/smk/time.h,v 1.1 2002/06/25 20:05:01 Thomas Nilsson Exp $
 *
 * $Log: time.h,v $
 * Revision 1.1  2002/06/25 20:05:01  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1997/01/22 16:29:56  gunilla
 * Adapted for WIN32
 *
 * Revision 1.2  1993/04/30 12:33:50  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:25:17  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:39  tools
 * Initial revision
 *
 *
 */

#ifndef timeIncluded
#define timeIncluded

typedef struct {
  long proc_user_time;    /* ticks */
  long proc_system_time;  /* ticks */
  long child_user_time;   /* ticks */
  long child_system_time; /* ticks */
  long pu_start;          /* ticks */
  long pu_elapsed;        /* ms */
  long cu_start;          /* ticks */
  long cu_elapsed;        /* ms */
} *Time, TimeItem;


#ifdef vms
#define TI_HZ 100
#else
#ifdef WIN32
#define TI_HZ CLOCKS_PER_SEC
#else
#define TI_HZ 60
#endif
#endif

extern void tistart(Time tb);
extern void tirestart(Time tb);
extern int tistop(Time tb);
extern char *tistr(int time);

#endif
