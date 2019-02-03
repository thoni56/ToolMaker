/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#include <stdio.h>
#include <malloc.h>
#ifdef WIN32
#include <string.h>
#endif
#include "common.h"
#include "readParam.h"

static Parameter parameter=NULL;

char *getParameter(char *file, char *name)
{
  Parameter p;

  if(parameter==0) {
    FILE *fd;
    char name[128];
    char value[128];

    if((fd=fopen(file,"r"))==NULL) return NULL;
    while(fscanf(fd," %s = %s \n",name,value)==2) {
      p=(Parameter)malloc(sizeof(ParameterItem));
      strcpy(p->name=(char *)malloc(strlen(name)+1),name);
      strcpy(p->value=(char *)malloc(strlen(value)+1),value);
      p->next=parameter;
      parameter=p;
    }
  }
  
  for(p=parameter;p!=NULL;p=p->next)
    if(strcmp(p->name,name)==0) return p->value;
  return NULL;
}
