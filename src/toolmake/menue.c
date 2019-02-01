/*======================================================================
=	FILE: MENUE.C				DATE: 89-11-28/reibert@roo
=
=	menue -- a package for matching strings with a command table
=
=	Written by Reibert Olsson
=	Source language: MS-C v3.00
======================================================================*/
#include <stdio.h>
#include <string.h>

#include "ask.h"

/*----------------------------------------------------------------------
- NAME
-	Menue -- check if keyword is in table
- SYNOPSIS
-	found= Menue(p,ma,hit);
-	char *p, *ma[], **hit;
-	int found;
- DESCRIPTION
-	Counts how many times string p is a prefix to items in
-	string pointer array ma.
- RETURNS
-	Number of hits in table:
-	0  == No hit in ma
-	1  == One hit, and hit points at it
-	>1 == Many hits i.e. ambigouos command
- CAUTIONS
-	Last item in ma *MUST* point at empty string!
----------------------------------------------------------------------*/
PUBLIC boolean prefix(p,s)
char *p,*s;
{
  while (*p) {
    if (!*s || *s++!=*p++) return(FALSE);
  }
  return(TRUE);
}

PUBLIC int getMenue(p, ma, no)
    char *p, *ma[];
    int *no;
{
    int c=0, plen, rno= 0;

    plen= strlen(p);
    if (plen==0) c= 2;
    else while (ma[rno]) {
	if (prefix(p,ma[rno])) {
	    c++; *no= rno;
	    if (strlen(ma[rno])==plen) { c= 1; break; }
	}
	rno++;
    }
    return c;
}


/*----------------------------------------------------------------------
- NAME
-	PutMenue -- Write keywords from table
- SYNOPSIS
-	PutMenue(p,ma,w,n);
-	char *p, *ma[];
-	int w, n;
- DESCRIPTION
-	Writes on fp words in ma matched by p, in n columns and 
-	total width w.
- RETURNS
-	Nothing.
- CAUTIONS
-	Last item in ma *MUST* point at empty string!
----------------------------------------------------------------------*/
PUBLIC void putMenue(p,ma,w,n)
char *p, *ma[];
int w, n;
{
  int c=0, f, i;
  char *cp;

  f= w/n-1;
  while(*ma) {
    if(prefix(p,*ma)) {
      for(i=0, cp= *ma; i<f; i++) putchar( (*cp? *cp++: ' ') );
      if(++c>=n) { putchar('\n'); c=0; } else putchar(' ');
    }
    ma++;
  }
} /* PutMenue */
