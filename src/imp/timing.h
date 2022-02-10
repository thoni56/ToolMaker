/* @(#)timing.h 1.1 (90/11/27 16:54:41) */
#ifndef _timing
#define _timing

#if defined(unix) || defined(__APPLE_CC__)
#include <sys/types.h>
#include <sys/times.h>
typedef struct tms TimesBuffer;
#define uNow timeBuf.tms_utime
#define sNow timeBuf.tms_stime
#define divFactor 60
#endif

#ifdef WIN32
#include <time.h>
typedef struct { clock_t ctime; clock_t dummy; } TimesBuffer;
#define uNow timeBuf.ctime
#define sNow timeBuf.dummy
#define divFactor CLOCKS_PER_SEC
#define times(T) ((T)->ctime = clock(), (T)->dummy = 0)
#endif


/* Data types for timing */
typedef struct {
    TimesBuffer timeBuf;
    int uStart;
    int sStart;
    int elapsed;
} TiBuf;

typedef enum {TiSC, TiMS, TiMSC} TiMode;

extern void tiStart();
extern void tiStop();
extern void tiPrint();
extern int tiC();

#endif
