/*
 * AUTHOR : Tony Olsson
 * DATE   : 89-09-29/tony@whoozle
 *
 * BASED ON:
 *     time.c/time.h by Reibert Olsson
 *
 * MODIFIED:
 *
 */

#ifndef timeIncluded
#define timeIncluded

typedef struct {
  long proc_user_time;      /* ticks */
  long proc_system_time;    /* ticks */
  long child_user_time;     /* ticks */
  long child_system_time;   /* ticks */
  long pu_start;            /* ticks */
  long pu_elapsed;          /* ms */
  long cu_start;            /* ticks */
  long cu_elapsed;          /* ms */
} *Time, TimeItem;


#ifdef vms
#define TI_HZ 100
#else
#define TI_HZ 60
#endif

extern void tistart( /* Time buffer */ );
extern void tirestart( /* Time buffer */ );
extern int tistop( /* Time buffer */ );
extern char *tistr( /* Time buffer */ );

#endif
