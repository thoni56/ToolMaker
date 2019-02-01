/*

   Dummy license handler for systems with no network.

 */
#include <io.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "license.h"
#include "readParam.h"
#include "passwd.h"

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
#ifdef _AMOSDEV
	char *file = "C:\\ToolMaker.lic";

	if(access(file,R_OK)==0) {
    char *value;
    int year, month, day;
	int tmp1,tmp2;
    long hostid;
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

    if((value=getParameter(file,"HOST"))==NULL) 
		return LICENSE_FORMAT_ERROR;
    if(strcmp(value, "AMOS_Development_License") != 0)
		return LICENSE_DENIED;

    /*
     * Check password
     */

    if((value=getParameter(file,"PASSWORD"))==NULL) return LICENSE_FORMAT_ERROR;
    if((tmp1 = passwd(year,month,day,users,hostid))!=(tmp2 = strtoul(value,NULL,16))) 
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
}
