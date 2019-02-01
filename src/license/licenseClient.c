/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#include <pwd.h>
#else
#include <io.h>
#endif
#include <time.h>
#ifndef WIN32
#include <sys/file.h>
#endif
#include <sys/types.h>
#ifndef WIN32
#include <sys/time.h>
#endif
#include "common.h"
#include "license.h"
#include "readParam.h"
#include "passwd.h"

#ifndef apollo
#ifndef WIN32
#include <rpc/rpc.h>
#include "license_rpc.h"
#endif
#endif

int timeCheck(int year,int month,int day)
{
#ifdef apollo
  long at;
#else
  time_t at;
#endif
  struct tm *tmp;
  
  at=time(0);
  tmp=localtime(&at);
  tmp->tm_year+=1900;
  tmp->tm_mon++;
  if(tmp->tm_year<year) return -1;
  if(tmp->tm_year>year) return  1;
  if(tmp->tm_mon <month) return -1;
  if(tmp->tm_mon >month) return  1;
  if(tmp->tm_mday<day) return -1;
  if(tmp->tm_mday>day) return  1;
  return 0;
}

License license()
{
#ifdef WIN32
#ifdef _AMOSDEV
	char *file = "C:\\ToolMaker.lic";

	if(access(file,4)==0) {
    char *value;
    int year, month, day;
    unsigned long hostid;
    int users;
    
    /*
     * Check DATE (must be greater or equal to today)
     */

    if ((value=getParameter(file,"DATE"))==NULL) 
		return LICENSE_FORMAT_ERROR;
    sscanf(value,"%d-%d-%d",&year,&month,&day);
    if(timeCheck(year,month,day)>0) 
		return LICENSE_EXPIRED;

    /*
     * Check USER (must be equal to 0)
     */
    if ((value=getParameter(file,"USERS"))==NULL) 
		return LICENSE_FORMAT_ERROR;
    users=atoi(value);
    if(users!=0) 
		return LICENSE_FORMAT_ERROR;

    /*
     * Check hostid (must be equal to this host)
     */
    if ((value=getParameter(file,"HOSTID"))==NULL) 
		return LICENSE_FORMAT_ERROR;
    hostid = strtoul(value,NULL,16);
    /*
     * Check host (must be equal to AMOS_Development_License)
     */
    if((value=getParameter(file,"HOST"))==NULL) 
		return LICENSE_FORMAT_ERROR;
    if(strcmp(value, "AMOS_Development_License") != 0)
		return LICENSE_DENIED;

    /*
     * Check password
     */

    if((value=getParameter(file,"PASSWORD"))==NULL) return LICENSE_FORMAT_ERROR;
    if(passwd(year,month,day,users,hostid)!=strtoul(value,NULL,16)) 
		return LICENSE_ILLEGAL_PASSWORD;

    /*
     * License is OK
     */

    return LICENSE_OK;
  }
    /*
   * No license file found 
   */

  return LICENSE_NO_FILE;  
#else
  return LICENSE_OK;
#endif
#else
  char file[1024];

  if(getenv("TMHOME")==NULL) return LICENSE_NO_FILE;

  /*
   * Check if standalone system
   */
    
  sprintf(file,"%s/.license.%x",getenv("TMHOME"),gethostid());
  if(access(file,R_OK)==0) {
    char *value;
    int year, month, day;
    long hostid;
    int users;
    
    /*
     * Check DATE (must be greater or equal to today)
     */

    if((value=getParameter(file,"DATE"))==NULL) return LICENSE_FORMAT_ERROR;
    sscanf(value,"%d-%d-%d",&year,&month,&day);
    if(timeCheck(year,month,day)>0) return LICENSE_EXPIRED;

    /*
     * Check USER (must be equal to 0)
     */

    if((value=getParameter(file,"USERS"))==NULL) return LICENSE_FORMAT_ERROR;
    users=atoi(value);
    if(users!=0) return LICENSE_FORMAT_ERROR;

    /*
     * Check hostid (must be equal to this host)
     */

    if((value=getParameter(file,"HOSTID"))==NULL) return LICENSE_FORMAT_ERROR;
#ifdef __svr4__
    if(strtoul(value,NULL,16)!=(hostid=gethostid())) return LICENSE_DENIED;
#else
    if(strtol(value,NULL,16)!=(hostid=gethostid())) return LICENSE_DENIED;
#endif

    /*
     * Check password
     */

    if((value=getParameter(file,"PASSWORD"))==NULL) return LICENSE_FORMAT_ERROR;
#ifdef __svr4__
    if(passwd(year,month,day,users,hostid)!=strtoul(value,NULL,16)) return LICENSE_ILLEGAL_PASSWORD;
#else
    if(passwd(year,month,day,users,hostid)!=strtol(value,NULL,16)) return LICENSE_ILLEGAL_PASSWORD;
#endif

    /*
     * License is OK
     */

    return LICENSE_OK;
  }

#ifndef apollo
  /*
   * Check if network based system
   */

  sprintf(file,"%s/.license",getenv("TMHOME"));
  if(access(file,R_OK)==0) {
    CLIENT *cl;
    int *result;
    char *server;
    static char who[18];
    static char *message;

    /*
     * Check host name of server
     */

    if((server=getParameter(file,"HOST"))==NULL) return LICENSE_FORMAT_ERROR;

    /*
     * Try to connect to server
     */

    if((cl=clnt_create(server,LICENSEPROG,LICENSEVERS,"tcp"))==NULL) return LICENSE_NO_SERVER;

    /*
     * Send request for license
     */

    sprintf(who,"%08X.%08X",getuid(),gethostid());
    message=who;
    result=license_1(&message,cl);
    if(result==NULL) return LICENSE_NO_SERVER;
    return *result;
  }
#endif

  /*
   * No license file found 
   */

  return LICENSE_NO_FILE;
#endif
}
    
