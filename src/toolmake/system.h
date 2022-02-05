/* system.h                                     Date: 1993-05-24/reibert@roo

        system -- toolmake (OS Specific)

        Written by Reibert Arbring, SoftLab ab.

        Copyright (c) 1988, 1989, 1993 SoftLab ab.

*/
#ifndef _system_h_
#define _system_h_ 1

#include "toolmake.h"

#define GOOD 0
#define BAD  1
#include <ctype.h>
#define TOUPPER(c)  (islower(c)? toupper(c): c)
#define TOLOWER(c)  (isupper(c)? tolower(c): c)


extern char *targetOS;

/* The following routines must be defined in a OS-dependent module */

char *makePathName(             /* Combine to legal pathname */
    IN char *directoryName,     /* NULL=cwd */
    IN char *fileName
);
int getFileList(                /* Get matching files */
    IN char *fileName,          /* wildcards allowed */
    OUT char ***list
);
boolean backup(
    IN char *name
);
boolean isDir(
    IN char *name
);
boolean isFile(
    IN char *name
);

char *getTime(                  /* Get time as string*/
    IN long time                /* 0 = current time */
);
char *getDate(                  /* Get date (ISO) as string*/
    IN long time                /* 0 = current time */
);

#ifndef IMPSYS
int imp(char *arg, ...);
#endif

void *new    (IN unsigned long byte_size, IN void *copy_from);
char *newString(IN char *string_to_copy);
char *strip  (IN char *string_to_strip);
char *strupr (IN char *string_to_upper_case);
char *strlwr (IN char *string_to_lower_case);

#endif
/* -- system.h -- */
