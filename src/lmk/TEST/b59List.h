#ifndef _b59List_H_
#define _b59List_H_
/*----------------------------------------------------------------------*\

	b59List.h

	Header file for ListerMaker generated error message and listing
	handler

\*----------------------------------------------------------------------*/

#include "b59Common.h"


/* Insert string separator */
#define b59SEPARATOR ((char)0xff)

/* Severity type and codes */
typedef int b59Sev;
#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

#define sevALL (sevOK|sevINF|sevWAR|sevERR|sevFAT|sevSYS)


/* Listing types */
typedef int b59Typ;
#define liNONE  0
#define liSUM   (1<<0)		/* Summary */
#define liERR   (1<<1)		/* Erroneous source lines */
#define liOK    (1<<2)		/* Correct source lines */
#define liINCL  (1<<3)		/* Look also in PUSHed files */
#define liHEAD  (1<<4)		/* Heading */

#define liTINY (liSUM|liERR|liHEAD|liINCL)
#define liFULL (liTINY|liOK)

typedef enum b59Messages {
    b59_ENGLISH_Messages
} b59Messages;


/* UNINITIALISED: */
/* Initialise the b59Lister System */
extern void b59LiInit(char header[],
				 char src[],
				 b59Messages msect);

/* COLLECTING: */
/* Log a message at a source position */
extern void b59Log(TmSrcp *pos,
				int ecode,
				b59Sev sev,
				char *istrs);

/* Log a message at a source position using va_arg handling */
extern void b59Logv(TmSrcp *pos,
				int ecode,
				b59Sev sev,
				...);

/* Turn listing completely off after a particular source position */
extern void b59LiOff(TmSrcp *pos);

/* Turn listing on again at a particular source position */
extern void b59LiOn(TmSrcp *pos);

/* Start reading an included file at a particular source position */
extern void b59LiEnter(TmSrcp *pos,
				  TmSrcp *start,
				  char fnm[]);

/* Stop reading from an included file prematurely */
extern void b59LiExit(TmSrcp *pos);

/* (Un)conditionally skip to a new page at a source position */
extern void b59LiPage(TmSrcp *pos,
				 int lins);

/* Read worst severity logged so far */
extern b59Sev b59Severity(void);
extern b59Sev b59LocSeverity(void);
extern void b59ResLocSeverity(void);

/* RETRIEVING: */
/* Create a listing of a selected type in a file or the screen */
extern void b59List(char ofnm[],
				 int lins,
				 int cols,
				 b59Typ typ,
				 b59Sev sevs);

/* Return the i'th formatted message, return 0 if not found */
extern int b59Msg(int i,
			       TmSrcp *pos,
			       char *msg);

/* Print a string on a line in the output file */
extern void b59LiPrint(char str[]);

/* (Un)conditionally skip to a new page in the output file */
extern void b59SkipLines(int lins);

/* Terminate the b59Lister system */
extern void b59LiTerminate(void);


#endif

