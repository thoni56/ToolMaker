/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1991-01-10
 * 
 * SoftLab ab (c) 1991
 *
 * $Header: /Repository/ToolMaker/src/smk/char.c,v 1.1 2002/06/25 20:04:40 Thomas Nilsson Exp $
 *
 * $Log: char.c,v $
 * Revision 1.1  2002/06/25 20:04:40  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1996/11/18 14:37:29  tony
 * Fixed bug when parsing strings starting with a ".
 *
 * Revision 1.2  1993/04/30 12:32:31  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:23:38  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.4  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.3  91/07/10  14:20:01  tools
 * New SET handling
 * 
 * Revision 1.2  1991/07/09  07:33:35  tools
 * Fix map bug and added mapping in DFA-table
 *
 * Revision 1.1  1991/01/10  13:20:59  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <memory.h>
#include "smk_i.h"
#include "char.h"
#include "map.h"
#include "smalloc.h"
#include "set.h"

short charSize=256;
short charTable[256];
short charMinTable[256];
short charMaxTable[256];

/*
 * Return the value of the quote.
 */

short charDequote(unsigned char *string)
{
  short value;

  value=0;
  if(*string=='\\') {
    string++;
    if(*string=='x' || *string=='X') {
      string++;
      if(*string>='0' && *string<='9')
	value = *string-'0';
      else if(*string>='A' && *string<='F')
	value = *string-'A'+10;
      else if(*string>='a' && *string<='f')
	value = *string-'a'+10;
      string++;
      if(*string>='0' && *string<='9')
	value = value*16+*string-'0';
      else if(*string>='A' && *string<='F')
	value = value*16+*string-'A'+10;
      else if(*string>='a' && *string<='f')
	value = value*16+*string-'a'+10;
    }
    else if(*string>='0' && *string<='7') {
      if(*string>='0' && *string<='7')
	value = *string-'0';
      string++;
      if(*string>='0' && *string<='7')
	value = value*8+*string-'0';
      string++;
	if(*string>='0' && *string<='7')
	  value = value*8+*string-'0';
    }
    else if(*string=='b')
      value =8;
    else if(*string=='t')
      value =9;
    else if(*string=='n')
      value =10;
    else if(*string=='v')
      value =11;
    else if(*string=='f')
      value =12;
    else if(*string=='r')
      value =13;
    else 
      value = *string;
  }
  else
    value = *string;
  if(setUsed && setTable[value]<0)
    return -1;
  else if(mapUsed && mapTable[value]!=value)
    return -1;
  else  if(value==optExclude)
    return -1;
  else
    return value;
}
    
/*
 * Return the length of the quote
 */

short charQuoteLength(char *string)
{
  if(*string=='\\') {
    string++;
    if(*string=='x' || *string=='X') return 4;
    else if(*string>='0' && *string<='7') return 4;
    else return 2;
  }
  else
    return 1;
}

int charIsRevClass(char *class)
{
  int min;
  int max;
  
  class++;
  if(*class=='^') class++;
  min=(*class=='-' ? 0 : charDequote((unsigned char *)class));
  for(max=256;*class!=']';class+=charQuoteLength(class))
    if(*class!='-') max=charDequote((unsigned char *)class);
  return min>max;
}

/*
 * Return a class vector describing the character class.
 */

char *charClass(char *string)
{
  char *class;
  short min;
  short max;
  short set;

  class=(char *)smalloc(256); 
  string++;
  if(*string=='^') {
    set=0;
    string++;
  }
  else
    set=1;
  memset(class,1-set,256);
  for(min=0;*string!=']';string+=charQuoteLength(string)) {
    if(*string=='-') {
      string++;
      max=*string==']'?255:charDequote((unsigned char *)string);
      if(max<0) return NULL;
      if(min>max)
	for(;max<=min;max++) 
	  if(max==optExclude || (mapUsed && mapTable[max]!=max) || (setUsed && setTable[max]<0))
	    continue; 
	  else 
	    class[max]=set;
      else
	for(;min<=max;min++) 
	  if(min==optExclude || (mapUsed && mapTable[min]!=min) || (setUsed && setTable[min]<0)) 
	    continue; 
	  else 
	    class[min]=set;
      if(*string==']') break;
    }
    min=charDequote((unsigned char *)string);
    if(min<0) return NULL;
    class[min]=set;
  }
  return class;
}

/*
 * Dequote the string and return the length of the string. 
 * NOTE: the string argument is modified.
 */

int charString(unsigned char *string1)
{
  unsigned char *string2;
  unsigned char *string3;
  unsigned char endchar;
  short c;

  string3=string2=string1;
  endchar=*string1;
  for(string1++;*string1 && *string1!=endchar;string1+=charQuoteLength((char *)string1)) {
    c=charDequote(string1);
    if(c<0) return -1;
    *string2++ = c;
  }
  return (int)(string2-string3);
}

void charDumpClass(char *class)
{
  int n;
  
  printf("Class\n");
  for(n=0;n<256;n++) {
    printf(n<' '||n>'~'?"x%02X %c   ":"'%c' %c   ",n,class[n]?'*':'.');
    if((n&7)==7) printf("\n");
  }
}
