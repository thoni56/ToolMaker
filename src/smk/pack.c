/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1991-01-10
 * 
 * SoftLab ab (c) 1991
 *
 * $Header: /Repository/ToolMaker/src/smk/pack.c,v 1.1 2002/06/25 20:04:48 Thomas Nilsson Exp $
 *
 * $Log: pack.c,v $
 * Revision 1.1  2002/06/25 20:04:48  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:09  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:24:33  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  13:38:36  tools
 * Initial revision
 * 
 *
 */

#include <stdio.h>
#include <malloc.h>
#include "smk_i.h"
#include "pack.h"

static int packCOL(void);
static int packROW(void);
static int packLES(void);
static int packGCS(void);
static int packRDS(void);
static int packERR(int);

static Pack pack;

int packMatrix(Pack matrix)
{
  int result;

  pack=matrix;

  if(pack->rows>pack->cols) {
    if(pack->type & ePackCOL) {
      result=packCOL();
      if(result!=0) return result;
    }
    if(pack->type & ePackROW) {
      result=packROW();
      if(result!=0) return result;
    }
  }
  else {
    if(pack->type & ePackROW) {
      result=packROW();
      if(result!=0) return result;
    }
    if(pack->type & ePackCOL) {
      result=packCOL();
      if(result!=0) return result;
    }
  }

  if(pack->type & (ePackLES | ePackGCS)) {
    result=packERR(pack->type & ePackERR);
    if(result!=0) return result;
  }

  if(pack->type & ePackLES) {
    int row1;
    int col1;

    result=packLES();
    if(result!=0) return result;
    if(pack->type & ePackGCS) {
      int LESrows;
      int LEScols;
      int *LESrow;
      int *LEScol;
      int row2;
      int col2;

      LESrows=pack->LESorGCSrows;
      LEScols=pack->LESorGCScols;
      LESrow=pack->LESorGCSrow;
      LEScol=pack->LESorGCScol;
      result=packGCS();
      if(result!=0) return result;
      for(row1=0,row2=0;row1<LESrows;row1++)
	if(pack->LESdetRow[row1]<0)
	  LESrow[row1]=pack->LESorGCSrow[row2++];
      for(col1=0,col2=0;col1<LEScols;col1++)
	if(pack->LESdetCol[col1]<0)
	  LEScol[col1]=pack->LESorGCScol[col2++];
      free((char *)(pack->LESorGCSrow));
      free((char *)(pack->LESorGCScol));
      pack->LESorGCSrows=LESrows;
      pack->LESorGCScols=LEScols;
      pack->LESorGCSrow=LESrow;
      pack->LESorGCScol=LEScol;
    }
    if(pack->type & ePackRDS) {
      result=packRDS();
      if(result!=0) return result;
      for(row1=0;row1<pack->LESorGCSrows;row1++)
	if(pack->LESdetRow[row1]<0)
	  pack->LESorGCSrow[row1]=pack->RDSbase[pack->LESorGCSrow[row1]];
      free((char *)(pack->RDSbase));
      free((char *)(pack->RDScheck));
      pack->RDSbase=NULL;
      pack->RDScheck=NULL;
    }
      

/* fill unused entries in determination vectors */

      for(row1=0;row1<pack->LESorGCSrows;row1++) if(pack->LESdetRow[row1]<0) pack->LESdetRow[row1]=pack->LESscan;
      for(col1=0;col1<pack->LESorGCScols;col1++) if(pack->LESdetCol[col1]<0) pack->LESdetCol[col1]=pack->LESscan;
  }
  else if(pack->type & ePackGCS) {
    result=packGCS();
    if(result!=0) return result;
    if(pack->type & ePackRDS) {
      int row1;

      result=packRDS();
      if(result!=0) return result;
      for(row1=0;row1<pack->LESorGCSrows;row1++)
	pack->LESorGCSrow[row1]=pack->RDSbase[pack->LESorGCSrow[row1]];
      free((char *)(pack->RDSbase));
      free((char *)(pack->RDScheck));
      pack->RDSbase=NULL;
      pack->RDScheck=NULL;
    }
  }
  else if(pack->type & ePackRDS) {
    result=packRDS();
    if(result!=0) return result;
  }
  return packNoErr;
}

/*
  This function compress the matrix by finding equivallent rows.
*/

static int packROW()
{
  int row1;
  int row2;
  int col1;
  int *m1;
  int *m2;

/* Find equivallent rows */

  pack->ROWrow=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  if(pack->ROWrow==NULL) return packErrNoMem;
  pack->ROWrows=pack->rows;
  pack->rows=0;
  for(row1=0;row1<pack->ROWrows;row1++) pack->ROWrow[row1]= -1;
  for(row1=0;row1<pack->ROWrows;row1++)
    if(pack->ROWrow[row1]<0) {
      m1=pack->matrix[row1];
      pack->ROWrow[row1]=pack->rows;
      for(row2=row1+1;row2<pack->ROWrows;row2++)
	if(pack->ROWrow[row2]<0) {
	  m2=pack->matrix[row2];
	  for(col1=0;col1<pack->cols;col1++)
	    if(m1[col1]!=m2[col1]) break;
	  if(col1<pack->cols) continue;
	  pack->ROWrow[row2]=pack->rows;
	}
      pack->rows++;
    }

/* Rearrange the matrix */

  for(row1=0;row1<pack->ROWrows;row1++)
    if(pack->ROWrow[row1]!=row1) {
      if(pack->matrix[pack->ROWrow[row1]]!=NULL)
	free((char *)(pack->matrix[row1]));
      else
	pack->matrix[pack->ROWrow[row1]]=pack->matrix[row1];
      pack->matrix[row1]=NULL;
    }

  return packNoErr;
}

/*
  This function compress the matrix by finding equivallent columns.
*/

static int packCOL()
{
  int row1;
  int col1;
  int col2;

/* find equivallent columns */

  pack->COLcol=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  if(pack->COLcol==NULL) return packErrNoMem;
  pack->COLcols=pack->cols;
  pack->cols=0;
  for(col1=0;col1<pack->COLcols;col1++) pack->COLcol[col1]= -1;
  for(col1=0;col1<pack->COLcols;col1++)
    if(pack->COLcol[col1]<0) {
      pack->COLcol[col1]=pack->cols;
      for(col2=col1+1;col2<pack->COLcols;col2++)
	if(pack->COLcol[col2]<0) {
	  for(row1=0;row1<pack->rows;row1++)
	    if(pack->matrix[row1][col1]!=pack->matrix[row1][col2]) break;
	  if(row1<pack->rows) continue;
	  pack->COLcol[col2]=pack->cols;
	}
      pack->cols++;
    }

/* Rearrange matrix */

  for(row1=0;row1<pack->rows;row1++) {
    for(col1=0;col1<pack->COLcols;col1++)
      if(pack->COLcol[col1]!=col1)
	pack->matrix[row1][pack->COLcol[col1]]=pack->matrix[row1][col1];
    pack->matrix[row1]=(int *)realloc((char *)(pack->matrix[row1]),(unsigned int)(sizeof(int)*pack->cols));
  }
  return packNoErr;
}

/*
  This function creates a bit map of insignificant entries. Used for LES and GCS.
*/

static int packERR(int packed)
{
  int row1;
  int row2;
  int col1;
  int col2;
  unsigned char mask;
  unsigned char *ERRptr;

  if(packed) {
    pack->ERRrow=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
    pack->ERRcol=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
    if(pack->ERRrow==NULL || pack->ERRcol==NULL)
      return packErrNoMem;
    
    for(row1=0;row1<pack->rows;row1++) pack->ERRrow[row1]= -1;
    for(col1=0;col1<pack->cols;col1++) pack->ERRcol[col1]= -1;
    pack->ERRrows=0;
    pack->ERRcols=0;
    
    for(col1=0;col1<pack->cols;col1++)
      if(pack->ERRcol[col1]<0) {
	pack->ERRcol[col1]=pack->ERRcols;
	for(col2=col1+1;col2<pack->cols;col2++)
	  if(pack->ERRcol[col2]<0) {
	    for(row1=0;row1<pack->rows;row1++)
	      if((pack->matrix[row1][col1]==pack->insign) ==
		 (pack->matrix[row1][col2]!=pack->insign)) break;
	    if(row1<pack->rows) continue;
	    pack->ERRcol[col2]=pack->ERRcols;
	  }
	pack->ERRcols++;
      }
		
    for(row1=0;row1<pack->rows;row1++) 
      if(pack->ERRrow[row1]<0) {
	pack->ERRrow[row1]=pack->ERRrows;
	for(row2=row1+1;row2<pack->rows;row2++)
	  if(pack->ERRrow[row2]<0) {
	    for(col1=0;col1<pack->cols;col1++)
	      if((pack->matrix[row1][col1]==pack->insign) ==
		 (pack->matrix[row2][col1]!=pack->insign)) break;
	    if(col1<pack->cols) continue;
	    pack->ERRrow[row2]=pack->ERRrows;
	  }
	pack->ERRrows++;
      }

    pack->ERRvect=(unsigned char *)malloc((unsigned int)(pack->ERRrows*((pack->ERRcols+7)/8)));
    if(pack->ERRvect==NULL) return packErrNoMem;
    ERRptr=pack->ERRvect;
    mask=0x80;
    *ERRptr=0;
    for(row1=0,row2=0;row1<pack->rows;row1++)
      if(pack->ERRrow[row1]==row2) {
	for(col1=0,col2=0;col1<pack->cols;col1++) 
	  if(pack->ERRcol[col1]==col2) {
	    if(pack->matrix[row1][col1]==pack->insign)
	      *ERRptr|=mask;
	    mask>>=1;
	    if(mask==0) {
	      ERRptr++;
	      mask=0x80;
	      *ERRptr=0;
	    }
	    col2++;
	  }
	row2++;
      }
  }
  else {
    pack->ERRrow=NULL;
    pack->ERRcol=NULL;
    pack->ERRrows=pack->rows;
    pack->ERRcols=pack->cols;

    pack->ERRvect=(unsigned char *)malloc((unsigned int)(pack->ERRrows*((pack->ERRcols+7)/8)));
    if(pack->ERRvect==NULL) return packErrNoMem;
    ERRptr=pack->ERRvect;
    mask=0x80;
    *ERRptr=0;
    for(row1=0;row1<pack->rows;row1++) {
      for(col1=0;col1<pack->cols;col1++) {
	if(pack->matrix[row1][col1]==pack->insign)
	  *ERRptr|=mask;
	mask>>=1;
	if(mask==0) {
	  ERRptr++;
	  mask=0x80;
	  *ERRptr=0;
	}
      }
    }
  }  
  return packNoErr;
}

/*
  This function compress the matrix by using a Line Elimination Scheme as
  described in ACM, Transactions on Programming Languages and Systems, Oct 1984,
  Vol. 6 No.4, page. 550-551.
*/

static int packLES()
{
  int row1;
  int col1;
  int nomod;
  int value;

  pack->LESdetRow=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  pack->LESdetCol=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  pack->LESorGCSrow=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  pack->LESorGCScol=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  if(pack->LESdetRow==NULL || pack->LESdetCol==NULL || pack->LESorGCSrow==NULL || pack->LESorGCScol==NULL)
    return packErrNoMem;
  pack->LESorGCSrows=pack->rows;
  pack->LESorGCScols=pack->cols;
  pack->rows=0;
  pack->cols=0;
  pack->LESscan=0;
  
  for(row1=0;row1<pack->LESorGCSrows;row1++) pack->LESdetRow[row1]= -1;
  for(col1=0;col1<pack->LESorGCScols;col1++) pack->LESdetCol[col1]= -1;
  while(1) {

/* check for lonely entries in pack->rows */

    nomod=1;
    for(row1=0;row1<pack->LESorGCSrows;row1++)
      if(pack->LESdetRow[row1]<0) {
	value=pack->insign;
	for(col1=0;col1<pack->LESorGCScols;col1++)
	  if(pack->matrix[row1][col1]!=pack->insign &&
	     pack->LESdetCol[col1]<0) break;
	if(col1<pack->LESorGCScols) {
	  for(value=pack->matrix[row1][col1];col1<pack->LESorGCScols;col1++)
	    if(pack->matrix[row1][col1]!=pack->insign &&
	       pack->matrix[row1][col1]!=value &&
	       pack->LESdetCol[col1]<0) break;
	  if(col1<pack->LESorGCScols) continue;
	}
	pack->LESdetRow[row1]=pack->LESscan;
	pack->LESorGCSrow[row1]=value;
	nomod=0;
      }
    if(nomod) break;
    pack->LESscan++;

/* check for lonely entries in columns */
    
    nomod=1;
    for(col1=0;col1<pack->LESorGCScols;col1++)
      if(pack->LESdetCol[col1]<0) {
	value=pack->insign;
	for(row1=0;row1<pack->LESorGCSrows;row1++)
	  if(pack->matrix[row1][col1]!=pack->insign &&
	     pack->LESdetRow[row1]<0) break;
	if(row1<pack->LESorGCSrows) {
	  for(value=pack->matrix[row1][col1];row1<pack->LESorGCSrows;row1++)
	    if(pack->matrix[row1][col1]!=pack->insign &&
	       pack->matrix[row1][col1]!=value &&
	       pack->LESdetRow[row1]<0) break;
	  if(row1<pack->LESorGCSrows) continue;
	}
	pack->LESdetCol[col1]=pack->LESscan;
	pack->LESorGCScol[col1]=value;
	nomod=0;
      }
    if(nomod) break;
    pack->LESscan++;
  }
  
/* fill unused entris in row/column vectors */

  for(row1=0;row1<pack->LESorGCSrows;row1++) if(pack->LESdetRow[row1]<0) pack->LESorGCSrow[row1]=pack->rows++;
  for(col1=0;col1<pack->LESorGCScols;col1++) if(pack->LESdetCol[col1]<0) pack->LESorGCScol[col1]=pack->cols++;

/* Rearrange matrix */

  for(row1=0;row1<pack->LESorGCSrows;row1++) {
    if(pack->LESdetRow[row1]<0) {
      if(pack->LESorGCSrow[row1]!=row1) {
	pack->matrix[pack->LESorGCSrow[row1]]=pack->matrix[row1];
	pack->matrix[row1]=NULL;
      }
    }
    else {
      free((char *)(pack->matrix[row1]));
      pack->matrix[row1]=NULL;
    }
  }
  for(row1=0;row1<pack->rows;row1++) {
    for(col1=0;col1<pack->LESorGCScols;col1++)
      if(pack->LESdetCol[col1]<0)
	if(pack->LESorGCScol[col1]!=col1){
	  pack->matrix[row1][pack->LESorGCScol[col1]]=pack->matrix[row1][col1];
	}
    pack->matrix[row1]=(int *)realloc((char *)(pack->matrix[row1]),(unsigned int)(sizeof(int)*pack->cols));
  }
  return packNoErr;
}

static int packGCS()
{
  int row1;
  int row2;
  int col1;
  int col2;
  int tmp;
  int *m1;
  int *m2;
  int *size;
  int *map;

  pack->LESorGCSrow=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  size=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  map=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  if(pack->LESorGCSrow==NULL || size==NULL || map==NULL)
    return packErrNoMem;

/* Find size of all rows */

  for(row1=0;row1<pack->rows;row1++) {
    pack->LESorGCSrow[row1]=row1;
    size[row1]=0;
    for(col1=0;col1<pack->cols;col1++)
      if(pack->matrix[row1][col1]!=pack->insign) size[row1]++;
  }

/* Sort all rows in ascending order */

  for(row1=0;row1<pack->rows;row1++) {
    map[row1]= -1;
    for(row2=row1+1;row2<pack->rows;row2++)
      if(size[row1]<size[row2]) {
	tmp=size[row1];
	size[row1]=size[row2];
	size[row2]=tmp;
	tmp=pack->LESorGCSrow[row1];
	pack->LESorGCSrow[row1]=pack->LESorGCSrow[row2];
	pack->LESorGCSrow[row2]=tmp;
	m1=pack->matrix[row1];
	pack->matrix[row1]=pack->matrix[row2];
	pack->matrix[row2]=m1;
      }
  }

/* Pack the table */
	
  pack->LESorGCSrows=pack->rows;
  pack->rows=0;

  for(row1=0;row1<pack->LESorGCSrows;row1++)
    if(map[row1]<0) {
      map[row1]=pack->rows;
      m1=pack->matrix[row1];
      for(row2=row1+1;row2<pack->LESorGCSrows;row2++)
	if(map[row2]<0) {
	  m2=pack->matrix[row2];
	  for(col1=0;col1<pack->cols;col1++)
	    if(m1[col1]!=pack->insign &&
	       m2[col1]!=pack->insign &&
	       m1[col1]!=m2[col1]) break;
	  if(col1<pack->cols) continue;
	  map[row2]=pack->rows;
	  for(col1=0;col1<pack->cols;col1++)
	    if(m1[col1]==pack->insign) m1[col1]=m2[col1];
	  free((char *)(m2));
	  pack->matrix[row2]=NULL;
	}
      if(pack->rows!=row1)
	pack->matrix[pack->rows]=pack->matrix[row1];
      pack->rows++;
    }

/* Reindex the LESorGCSrow */

  for(row1=0;row1<pack->LESorGCSrows;row1++)
    size[pack->LESorGCSrow[row1]]=map[row1];
  for(row1=0;row1<pack->LESorGCSrows;row1++)
    pack->LESorGCSrow[row1]=size[row1];

  free((char *)(size));
  free((char *)(map));

/* PACK COLUMNS */

  pack->LESorGCScol=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  size=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  map=(int *)malloc((unsigned int)(sizeof(int)*pack->cols));
  if(pack->LESorGCScol==NULL || size==NULL || map==NULL)
    return packErrNoMem;

/* Find size of all cols */

  for(col1=0;col1<pack->cols;col1++) {
    pack->LESorGCScol[col1]=col1;
    size[col1]=0;
    for(row1=0;row1<pack->rows;row1++)
      if(pack->matrix[row1][col1]!=pack->insign) size[col1]++;
  }

/* Sort all cols in ascending order */

  for(col1=0;col1<pack->cols;col1++) {
    map[col1]= -1;
    for(col2=col1+1;col2<pack->cols;col2++)
      if(size[col1]<size[col2]) {
	tmp=size[col1];
	size[col1]=size[col2];
	size[col2]=tmp;
	tmp=pack->LESorGCScol[col1];
	pack->LESorGCScol[col1]=pack->LESorGCScol[col2];
	pack->LESorGCScol[col2]=tmp;
	for(row1=0;row1<pack->rows;row1++) {
	  tmp=pack->matrix[row1][col1];
	  pack->matrix[row1][col1]=pack->matrix[row1][col2];
	  pack->matrix[row1][col2]=tmp;
	}
      }
  }

/* Pack the table */
	
  pack->LESorGCScols=pack->cols;
  pack->cols=0;

  for(col1=0;col1<pack->LESorGCScols;col1++)
    if(map[col1]<0) {
      map[col1]=pack->cols;
      for(col2=col1+1;col2<pack->LESorGCScols;col2++)
	if(map[col2]<0) {
	  for(row1=0;row1<pack->rows;row1++) {
	    m1=pack->matrix[row1];
	    if(m1[col1]!=pack->insign &&
	       m1[col2]!=pack->insign &&
	       m1[col1]!=m1[col2]) break;
	  }
	  if(row1<pack->rows) continue;
	  map[col2]=pack->cols;
	  for(row1=0;row1<pack->rows;row1++) {
	    m1=pack->matrix[row1];
	    if(m1[col1]==pack->insign) m1[col1]=m1[col2];
	  }
	}
      if(pack->cols!=col1)
	for(row1=0;row1<pack->rows;row1++) {
	  m1=pack->matrix[row1];
	  m1[pack->cols]=m1[col1];
	}
      pack->cols++;
    }

/* Reindex the LESorGCScol */

  for(col1=0;col1<pack->LESorGCScols;col1++)
    size[pack->LESorGCScol[col1]]=map[col1];
  for(col1=0;col1<pack->LESorGCScols;col1++)
    pack->LESorGCScol[col1]=size[col1];

  free((char *)(size));
  free((char *)(map));

/* REALLOC THE SIZE OF THE MATRIX */

  for(row1=0;row1<pack->rows;row1++)
    pack->matrix[row1]=(int *)realloc((char *)(pack->matrix[row1]),(unsigned int)(sizeof(int)*pack->cols));

  return packNoErr;
}

static int packRDS()
{
  char *vect;
  int *index;
  int *size;
  int col1;
  int row1;
  int row2;

  vect=(char *)malloc((unsigned int)(sizeof(char)*(pack->rows*pack->cols)+1));
  pack->RDSbase=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  index=(int *)malloc((unsigned int)(sizeof(int)*pack->rows));
  size=pack->RDSbase;
  if(vect==NULL || pack->RDSbase==NULL || index==NULL)
    return packErrNoMem;

  /* Sort matrix by using index so that rows with most significant entries */
  /* are processed first */

  for(row1=0;row1<pack->rows;row1++) {
    size[row1]=0;		/* Temporary use of pack->RDSbase as size */
    for(col1=0;col1<pack->cols;col1++)
      if(pack->matrix[row1][col1]!=pack->insign) size[row1]++;
    index[row1]=row1;
  }
  for(row1=0;row1<pack->rows;row1++)
    for(row2=row1+1;row2<pack->rows;row2++)
      if(size[row1]<size[row2]) {
	/* swap size and index entries using col1 (!) */
	col1=size[row1];
	size[row1]=size[row2];
	size[row2]=col1;
	col1=index[row1];
	index[row1]=index[row2];
	index[row2]=col1;
      }

/* Create the RDS value vector and base vector */

  pack->RDScheckLen=0;
  for(row1=pack->rows*pack->cols;row1-->0;) vect[row1]=0;
  for(row1=0;row1<pack->rows;row1++) { 
/* use index[row1] instead of row1 to use sorted rows */
    int *m;
    int col2;
    int col3;
    int col4;
    int cols;

    col1=0;
    m=pack->matrix[index[row1]];
    for(col2=0;col2<pack->cols;col1++,col2++) if(m[col2]!=pack->insign) break;
    if(col2==pack->cols) continue;
    for(cols=pack->cols;cols-->0;) if(m[cols]!=pack->insign) break;
    for(;;col1++) {
      for(;vect[col1];col1++);
      for(col3=col2,col4=col1;col3<=cols;col3++,col4++)
	if(vect[col4] && m[col3]!=pack->insign) break;
      if(col3<=cols) continue;
      for(col3=col2,col4=col1;col3<=cols;col3++,col4++)
	if(m[col3]!=pack->insign) vect[col4]=1;
      pack->RDSbase[index[row1]]=col1-col2;
      if(pack->RDScheckLen<col1-col2) pack->RDScheckLen=col1-col2;
      break;
    }
  }
  free((char *)(index));
  pack->RDScheckLen+=pack->cols;
  pack->RDSvector=(int *)malloc((unsigned int)(sizeof(int)*pack->RDScheckLen));
  pack->RDScheck=(int *)malloc((unsigned int)(sizeof(int)*pack->RDScheckLen));
  if(pack->RDSvector==NULL || pack->RDScheck==NULL)
    return packErrNoMem;
  for(row1=0;row1<pack->RDScheckLen;row1++) {
    pack->RDScheck[row1]=pack->rows;
    pack->RDSvector[row1]=pack->insign;
  }
  for(row1=0;row1<pack->rows;row1++) {
    for(col1=0;col1<pack->cols;col1++)
      if(vect[pack->RDSbase[row1]+col1] && pack->matrix[row1][col1]!=pack->insign) {
	pack->RDSvector[pack->RDSbase[row1]+col1]=pack->matrix[row1][col1];
	pack->RDScheck[pack->RDSbase[row1]+col1]=row1;
      }
    free((char *)(pack->matrix[row1]));
  }
  for(pack->RDSvectorLen=pack->RDScheckLen;pack->RDSvector[--(pack->RDSvectorLen)]==pack->insign;);
  pack->RDSvectorLen++;
  free((char *)(vect));
  free((char *)(pack->matrix));
  pack->matrix=NULL;  
  pack->cols=0;
  return packNoErr;
}

