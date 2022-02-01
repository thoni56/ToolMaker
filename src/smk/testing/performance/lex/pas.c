/*
 * AUTHOR : Tony Olsson
 * DATE   : 1990-07-12/tony@whoozle
 * CREATED: 1990-07-02
 *
 * SoftLab ab (c) 1990
 */

#include <stdio.h>
#include "time.h"

int fd;

main(argc,argv)
    register int argc;
    register char **argv;
{
  TimeItem tb;
  register int time;
  register int item;
  register int res;
  extern FILE *yyin;

  if(argc!=2) fprintf(stderr,"usage: %s file\n",*argv),exit(1);
  if((yyin=fopen(argv[1],"r"))==NULL) perror(argv[1]),exit(1);
  tistart(&tb);
  item=0;
  do{
    res=yylex();
    item++;
  } while(res);
  time=tistop(&tb);
  printf("Tokens: %d in %s (last %d)\n",item,tistr(time),0);
}
