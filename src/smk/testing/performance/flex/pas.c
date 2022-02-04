/*
 * AUTHOR : Tony Olsson
 * DATE   : 1991-07-11/tools@heffa
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
  register int unknown;
  register int res;
  extern FILE *yyin;

  if(argc!=2) fprintf(stderr,"usage: %s file\n",*argv),exit(1);
  if((yyin=fopen(argv[1],"r"))==NULL) perror(argv[1]),exit(1);
  tistart(&tb);
  item=0;
  unknown=0;
  do{
    res=yylex();
    if(res>1) unknown++;
    item++;
  } while(res);
  time=tistop(&tb);
  printf("Tokens: %d in %s (unknown tokens %d and last token %d)\n",item,tistr(time),unknown,res);
  exit(0);
}
