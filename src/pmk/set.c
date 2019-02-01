#include <string.h>
#include "set.h"

void SetUnion(setIn1,setIn2,setOut,length)
     register SET setIn1;
     register SET setIn2;
     register SET setOut;
     register int length;
{
  register int n;

  for(n=((length+7)>>3);--n>-1;)
    setOut[n]=setIn1[n]|setIn2[n];
}

void SetInter(setIn1,setIn2,setOut,length)
     register SET setIn1;
     register SET setIn2;
     register SET setOut;
     register int length;
{
  register int n;

  for(n=((length+7)>>3);--n>-1;)
    setOut[n]=setIn1[n]&setIn2[n];
}

void SetDiff(setIn1,setIn2,setOut,length)
     register SET setIn1;
     register SET setIn2;
     register SET setOut;
     register int length;
{
  register int n;

  for(n=((length+7)>>3);--n>-1;)
    setOut[n]=setIn1[n]&(~setIn2[n]);
}

void SetCompl(setIn,setOut,length)
     register SET setIn;
     register SET setOut;
     register int length;
{
  register int n;

  for(n=((length+7)>>3);--n>-1;)
    setOut[n]=(~setIn[n]);
}

void SetClear(set,length)
     register SET set;
     register int length;
{
  memset(set, 0, (length+7)>>3);
}

int SetMem(set,n)
     register SET set;
     register int n;
{
  return (set[n>>3] & (0x80>>(n&0x7)))!=0;
}

void SetIns(set,n)
     register SET set;
     register int n;
{
  set[n>>3] |= (0x80>>(n&0x7));
}

void SetDel(set,n)
     register SET set;
     register int n;
{
  set[n>>3] &= (0xFF7F>>(n&0x7));
}
    
  
  
void SetClr(set,n,m)
     register SET set;
     register int n;
     register int m;
{
  while(n<=m) {
    set[m>>3] &= (0xFF7F>>(m&0x7));
    m--;
  }
}

int SetEmpty(set,l)
     register SET set;
     register int l;
{
  l=(l+7)/8;
  while(l-->0) if(set[l]!=0) return 0;
  return 1;
}

