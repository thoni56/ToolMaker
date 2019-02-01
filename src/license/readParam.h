/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1993-08-20
 * 
 * SoftLab ab (c) 1993
 */

#ifndef _readParam_h_
#define _readParam_h_

typedef struct Parameter {
  char *name;
  char *value;
  struct Parameter *next;
} ParameterItem, *Parameter;

extern char *getParameter(char *file, char *name);

#endif
