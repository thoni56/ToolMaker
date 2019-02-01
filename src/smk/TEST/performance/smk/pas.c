/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-06-09/tony@eeyore
 * CREATED: 1990-07-02
 * 
 * SoftLab ab (c) 1990
 */

#include <stdio.h>
#include "pasScan.h"
#include "time.h"

pasScContext aContext;

main(argc,argv)
     register int argc;
     register char **argv;
{
  TimeItem tb;
  register int time;
  register int item;
  register int res;
  register int unknown;
  PasToken token;

  if(argc!=2) fprintf(stderr,"usage: %s file\n",*argv),exit(1);
  aContext=pasScNew(pas_PASCAL_MAIN_Scanner);
  if((aContext->fd=open(argv[1],0))<0) perror(argv[1]),exit(1);
  
  tistart(&tb);
  res=0;
  item=0;
  unknown=0;
  do {
    res=pasScan(aContext,&token);
    if(res==pas_PASCAL_UNKNOWN_Token) unknown++;
    item++;
  } while(res!=pas_PASCAL_EOT_Token);
  time=tistop(&tb);
  printf("Tokens: %d in %s (unknown tokens %d and last token %d)\n",item,tistr(time),unknown,res);
  exit(0);
}
