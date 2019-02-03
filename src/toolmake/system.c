/* system.c					Date: 1993-05-24/reibert@roo

	system -- toolmake (System Specific)

	Written by Reibert Arbring, SoftLab ab.

	Copyright (c) 1988, 1989, 1993 SoftLab ab.

*/
#include <stdio.h>
#ifdef WIN32
#define popen _popen
#define pclose _pclose
#endif
#include <time.h>
#include <stdlib.h>
#ifdef vms
#include descrip
#include rmsdef
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#endif

#include "system.h"

PUBLIC char *targetOS = 
#ifdef sun
    "SunOS"
#else
#ifdef apollo
    "Apollo"
#else
#ifdef VMS
    "VMS"
#else
#ifdef WIN32
    "WIN32"
#else
    "UNKNOWN"
#endif
#endif
#endif
#endif
;

/* -- SUBROUINES -- */

PRIVATE long get_time(name)
    char *name;
{
    struct stat buf;

    stat(name, &buf);
    return buf.st_mtime;
}


PRIVATE char *get_line(fp)
    FILE *fp;
{
    char tmp[512];
    int len;

    if (fgets(tmp, 512, fp)==NULL) return newString(NULL);
    len= strlen(tmp);
    if (len>0 && tmp[len-1]<' ') tmp[len-1]= 0;
    return newString(strip(tmp));
}


PRIVATE char* getFileName(name)
    char *name;
{
    char newName[256], *fileName;
    
    strcpy(newName, name);
#ifdef vms
    if ( (fileName= strrchr(newName, ']')) != NULL ) fileName++;
    else if ( (fileName= strrchr(newName, '>')) != NULL ) fileName++;
#else
    if ( (fileName= strrchr(newName, '/')) != NULL ) fileName++;
#endif
    else fileName= newName;
#ifdef vms
    { char *x;
      if ( (x= strrchr(name, ';')) != NULL ) *x= 0; /* Strip VAX-nr */
    }
#endif
    return newString(fileName);
}


PRIVATE char* getPathName(name)
    char *name;
{
    char newName[256], *fileName;
    
    strcpy(newName, name);
#ifdef vms
    if ( (fileName= strrchr(newName, ']')) != NULL ) fileName++;
    else if ( (fileName= strrchr(newName, '>')) != NULL ) fileName++;
#else
    if ( (fileName= strrchr(newName, '/')) != NULL ) {}
#endif
    else fileName= newName;
    *fileName = 0;

    return newString(newName);
}


/* -- Memory allocation -- */

PUBLIC void *new(sz, cp)
    unsigned long sz;		/* bytes */
    void *cp;
{				/* Allocate and check a trunc of memory */
    char *n;

    if ( (n=(char *)malloc(sz)) == NULL)
	perr('S', "malloc", "out of memory");
    if (cp) memcpy(n, cp, sz);
    else memset(n, 0, sz);
    return n;
}


PUBLIC char *newString(s)
    char *s;
{				/* Get a fresh copy of a string */
    char *n;
    int len;

    if (s==NULL) len= 0;
    else len= strlen(s);
    n= new(len+1, s);
    return n;
}


PUBLIC char *strip(s)
    char *s;
/* Remove trailing blank chars [NUL..' '] (will of course waste memory) */
{
    int i;

    if (s!=NULL) {
	i= strlen(s)-1;
	while (i>=0 && s[i]<=' ') --i;
	s[i+1]= '\0';
    }
    return s;
}


PUBLIC char *strupr(s)
    char *s;
{
    char *u;

    for (u=s; *u; u++) *u= TOUPPER(*u);
    return s;
}
 

PUBLIC char *strlwr(s)
    char *s;
{
    char *u;

    for (u=s; *u; u++) *u= TOLOWER(*u);
    return s;
}
 

PUBLIC char *makePathName(dir, file)
    char *dir;
    char *file;
{
    char buf[512];

    if (dir) {
	strcpy(buf, dir);
#ifndef vms
#ifdef WIN32
	if (*dir) strcat(buf, "\\");
#else
	if (*dir) strcat(buf, "/");
#endif
#endif
    } else
	buf[0]= 0;
    strcat(buf, file);
    return newString(buf);
}    


PUBLIC int getFileList(pn, fl)
    char *pn;
    char ***fl;
{
    char buf[256];
    int found=0;
    char *tmp[256];
#ifdef vms
    struct dsc$descriptor ndsc, rdsc;
    char *pos;
    long context= 0, flag= 2;
#else
    FILE *ls;
#endif

#ifdef vms
    ndsc.dsc$a_pointer = pn;
    ndsc.dsc$w_length  = strlen(pn);
    ndsc.dsc$b_dtype   = DSC$K_DTYPE_T;
    ndsc.dsc$b_class   = DSC$K_CLASS_S;

    rdsc.dsc$a_pointer 	= buf;
    rdsc.dsc$w_length  	= 256;
    rdsc.dsc$b_dtype   	= DSC$K_DTYPE_T;
    rdsc.dsc$b_class   	= DSC$K_CLASS_S;
    buf[0]= 0;
#else
    strcpy(buf, "ls -1d ");
    strcat(buf, pn);
    ls= popen(buf, "r");
    if (ls==NULL) perr('S', "popen", buf);
#endif

#ifdef vms
    while (LIB$FIND_FILE(&ndsc, &rdsc, &context, 0,0,0, &flag)==RMS$_NORMAL) {
	pos= strchr(buf, ' ');	/* Remove trailing spaces */
	if (pos!=NULL) *pos=0;
#else
    while (fgets(buf, 256, ls)!=NULL) {
	strip(buf);		/* Remove trailing \n */
#endif
#ifdef DBG
        perr('D', "Found file", buf);
#endif
	tmp[found++]= newString(buf); /* Should check found<256 */
    }
    tmp[found++]= NULL;
#ifdef vms
    LIB$FIND_FILE_END(&context);
#else
    pclose(ls);
#endif

    *fl= new( found*sizeof(char *), tmp );
    return found-1;
}


PUBLIC boolean backup(name)
    char *name;
{
    char *bak;
    boolean ok;

    bak= new(strlen(name)+2, name);
    strcat(bak, "~");
    perr('I', "Backup file", bak);
    unlink(bak);
    ok= rename(name, bak)==0;
    free(bak);
    return ok;
}


PUBLIC boolean isDir(name)
    char *name;
{
    struct stat buf;

    return (stat(name, &buf)==0) && (buf.st_mode & S_IFDIR);
}


PUBLIC boolean isFile(name)
    char *name;
{
    struct stat buf;

    return (stat(name, &buf)==0) && (buf.st_mode & S_IFREG);
}


PUBLIC char *getDate(t)
    long t;
{
    static char tmp[64];
    struct tm *lt;

    if (t==0) time(&t);

    lt= localtime(&t);
    sprintf(tmp, "19%02d-%02d-%02d", lt->tm_year, lt->tm_mon+1, lt->tm_mday);
    return tmp;
}


PUBLIC char *getTime(t)
    long t;
{
    static char tmp[64];
    struct tm *lt;

    if (t==0) time(&t);

    lt= localtime(&t);
    sprintf(tmp, "%02d:%02d:%02d",  lt->tm_hour, lt->tm_min, lt->tm_sec);
    return tmp;
}

#ifndef IMPSYS

#ifdef __STDC__
PUBLIC int imp(char *farg, ...){
#else
PUBLIC int imp(va_alist)
    va_dcl
{
    char *farg;
#endif
    va_list ap;
    char args[1024], *this;

#ifdef __STDC__
    va_start(ap, farg);
#else
    va_start(ap);
    farg = va_arg(ap, char *);
#endif
    sprintf(args, "imp '-s_D(\"%s\")' '-s_T(\"%s\")' %s",
	    getDate(0), getTime(0), farg?farg:"");
    for (;;) {
	this= va_arg(ap, char *);
	if (!this) break;
	strcat(args, " ");
	strcat(args, this);
    }
    va_end (ap);
    dperr("CALLING", args);
    return system(args);
}

#endif

/* -- system.c -- */
