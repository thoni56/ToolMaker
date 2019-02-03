/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <rpc/rpc.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/file.h>
#include "common.h"
#include "license.h"
#include "license_rpc.h"
#include "readParam.h"
#include "passwd.h"
#include "version.h"

#define AUTOLOGOUT 600
#define DELAYTIME 60

typedef struct LicenseUser {
  char *who;
  time_t at;
  struct LicenseUser *next;
} LicenseUserItem, *LicenseUser;

static LicenseUser licenseUser=NULL;
static int maxUsers=0;
static struct tm maxTime;

static int timeCheck(time_t time, struct tm *tm)
{
  struct tm *tmp;
  
  tmp=localtime(&time);
  tmp->tm_year+=1900;
  tmp->tm_mon++;
  if(tmp->tm_year<tm->tm_year) return -1;
  if(tmp->tm_year>tm->tm_year) return  1;
  if(tmp->tm_mon <tm->tm_mon ) return -1;
  if(tmp->tm_mon >tm->tm_mon ) return  1;
  if(tmp->tm_mday<tm->tm_mday) return -1;
  if(tmp->tm_mday>tm->tm_mday) return  1;
  return 0;
}

static int insert(char *who)
{
  time_t at;
  int n;
  LicenseUser p;

  if(timeCheck(at=time(0),&maxTime)>0)
    return LICENSE_EXPIRED;
  for(n=0,p=licenseUser;p!=NULL && n<maxUsers;n++,p=p->next)
    if(p->at+AUTOLOGOUT>at && strcmp(p->who,who)==0) {
      p->at=at;
      return LICENSE_OK;
    }
  for(n=0,p=licenseUser;p!=NULL && n<maxUsers;n++,p=p->next)
    if(p->at+AUTOLOGOUT<at) {
      if(p->who!=0) free(p->who);
      p->who=(char *)malloc(strlen(who)+1);
      strcpy(p->who,who);
      p->at=at;
      break;
    }
  if(p==NULL && n<maxUsers) {
    p=(LicenseUser)malloc(sizeof(LicenseUserItem));
    p->who=(char *)malloc(strlen(who)+1);
    strcpy(p->who,who);
    p->at=at;
    p->next=licenseUser;
    licenseUser=p;
  }
  return n<maxUsers ? LICENSE_OK : LICENSE_DENIED;
}

int *license_1(message)
     char **message;
{
  static int result;

  if(maxTime.tm_year==0) {
    FILE *fd;
    if((fd=fopen("/dev/console","w"))==NULL) fd=stdout;
    fprintf(fd,"%s not initialized, severe error!\n",product.name);
    result=LICENSE_INITIALIZATION_FAILURE;
  }
  else
    result=insert(*message);
  return &result;
}


void licenseInit(int argc, char **argv)
{
  char file[1024];
  char *value;
  char hostname[128];
  char *server;

  server=argv[0];
  if(strrchr(server,'/')!=NULL) server=strrchr(server,'/')+1;

  /*
   * Get license file name (argument or TMHOME/.license)
   */

  if(argc==1) {
    if(getenv("TMHOME")!=NULL) sprintf(file,"%s/.license",getenv("TMHOME"));
    else
      fprintf(stderr,"%s: environment variable TMHOME not set\n\r",server),exit(1);
  } else if(argc==2) strcpy(file,argv[1]);
  else
    fprintf(stderr,"usage: %s [license-file]\n\r",server),exit(1);

  /*
   * Check if license file exist
   */

  if(access(file,R_OK))
    fprintf(stderr,"%s: can not find license file \"%s\"\n\r",server,file),exit(1);

  /*
   * Check hostid (must be equal to this hostid)
   */


  if((value=getParameter(file,"HOSTID"))==NULL)
    fprintf(stderr,"%s: can not find HOSTID in license file\n\r",server),exit(1);
#ifdef __svr4__
  else if(strtoul(value,NULL,16)!=gethostid())
#else
  else if(strtol(value,NULL,16)!=gethostid())
#endif
#ifdef DEBUG
    fprintf(stderr,"%s: wrong server machine (%s in license file, hostid is %x)\n\r", server, value, gethostid());
#else
    fprintf(stderr,"%s: wrong server machine (%s in license file, hostid is %x)\n\r", server, value, gethostid()),exit(1);
#endif

  /*
   * Check host name (must be equal to this host)
   */

  if((value=getParameter(file,"HOST"))==NULL)
    fprintf(stderr,"%s: can not find HOST in license file\n\r",server),exit(1);
  else if(gethostname(hostname,128)<0)
    fprintf(stderr,"%s: can not get hostname\n\r",server),exit(1);
  else if(strcmp(value,hostname)!=0)
#ifdef DEBUG
    fprintf(stderr,"%s: wrong name of server machine\n\r",server);
#else
    fprintf(stderr,"%s: wrong name of server machine\n\r",server),exit(1);
#endif

  /*
   * Check date (must be greater or equal to today)
   */

  if((value=getParameter(file,"DATE"))==NULL)
    fprintf(stderr,"%s: can not find DATE in license file\n\r",server),exit(1);
  sscanf(value,"%d-%d-%d",&(maxTime.tm_year),&(maxTime.tm_mon),&(maxTime.tm_mday));
  if(timeCheck(time(0),&maxTime)>0)
    fprintf(stderr,"%s: license has expired\n\r",server),exit(1);

  /*
   * Check number of users (must be greater than zero)
   */

  if((value=getParameter(file,"USERS"))==NULL)
    fprintf(stderr,"%s: can not find USERS in license file\n\r",server),exit(1);
  else maxUsers=atoi(value);
  if(maxUsers==0)
    fprintf(stderr,"%s: number of users must be greater than zero\n\r",server),exit(1);

  /* 
   * Check password 
   */

  if((value=getParameter(file,"PASSWORD"))==NULL)
    fprintf(stderr,"%s: can not find PASSWORD in license file\n\r",server),exit(1);
  else {
    unsigned long pw, key;
#ifdef DEBUG
    pw = passwd(maxTime.tm_year,maxTime.tm_mon,maxTime.tm_mday,maxUsers,(unsigned long)0x77D1D926);
#endif
    pw = passwd(maxTime.tm_year,maxTime.tm_mon,maxTime.tm_mday,maxUsers,gethostid());
#ifdef __svr4__
    key = strtoul(value,NULL,16);
#else
    key = strtol(value,NULL,16);
#endif
#ifdef DEBUG
    fprintf(stderr, "value = %s, pw = %8x, key = %8x\n", value, pw, key);
#endif
    if (key != pw)
      fprintf(stderr,"%s: illegal PASSWORD in license file\n\r",server),exit(1);
  }
}

void licenseDelay()
{
  FILE *fd;
  int n;
  
  if((fd=fopen("/dev/console","w"))==NULL) fd=stdout;
  if(maxTime.tm_year<9999 && maxTime.tm_mon<99 && maxTime.tm_mday<99 && maxUsers<9999)
    for(n=0;n<3;n++)
      fprintf(fd,"Starting %s %s, please wait %d seconds.\n\r",
	      product.name,product.version.string,
	      (DELAYTIME*(3-n))/3),sleep(DELAYTIME/3);
  fprintf(fd,"%s %s started.\n\r",product.name,product.version.string);
  fclose(fd);
}
