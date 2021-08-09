/* toolmake.h                         Date: 1993-04-19/reibert@roo

   Common definitions for toolmake

   1.00 -
*/
#ifndef _toolmake_H_
#define _toolmake_H_ 1

#define PRIVATE static
#define PUBLIC
#define IN
#define OUT
#define IN_OUT

#ifndef FALSE
typedef int boolean;

#define FALSE 0
#define TRUE 1
#endif

#ifdef PROTOTYPES
void perr(IN char severity, IN char *desc, IN char *add);
#else
extern void perr();
#endif

#ifdef DBG
#define dperr(m1, m2) spaAlert('D', "%s: %s", m1, m2)
#else
#define dperr(m1, m2)
#endif

#endif
