/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1991-01-10
 * 
 * SoftLab ab (c) 1991
 *
 * $Header: /Repository/ToolMaker/src/smk/pack.h,v 1.1 2002/06/25 20:04:48 Thomas Nilsson Exp $
 *
 * $Log: pack.h,v $
 * Revision 1.1  2002/06/25 20:04:48  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.2  1993/04/30 12:33:11  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.1  1993/03/24  09:24:36  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:12  tools
 * Initial revision
 * 
 *
 */

#ifndef _PACK_H_
#define _PACK_H_

#define packNoErr	0
#define packErrNoMem	1
#define packErrType	2

typedef struct Pack {

/* These five variables MUST be set before calling packMatrix */ 

  unsigned type;		/* Packing type */
  int insign;			/* The "insignificant"-value */
  int rows;			/* Number of rows in the matrix */
  int cols;			/* Number of columns in the matrix */
  int **matrix;			/* The matrix to be packed */

/* Row Index Scheme (ROW) */

  int ROWrows;			/* The size of the row vector */
  int *ROWrow;			/* The row vector */

/* Column Index Scheme (COL) */

  int COLcols;			/* The size of the column vector */
  int *COLcol;			/* The column vector */

/* Line Elimination Scheme (LES) and/or Graph Coloring Scheme (GCS) */

  int LESscan;			/* Number of scans in LES */
  int LESorGCSrows;		/* The size of the determination row and row vektor for LES */
  int LESorGCScols;		/* The size of the determination column and column vektor for LES */
  int *LESdetRow;		/* Row determination vektor for LES */
  int *LESdetCol;		/* Column determination vektor for LES */
  int *LESorGCSrow;		/* The row vektor for LES andor GCS */
  int *LESorGCScol;		/* The column vektor for LES and/or GCS */
  int ERRrows;			/* The number of rows in ERRvect */
  int ERRcols;			/* The number of columns in ERRvect */
  unsigned char *ERRvect;	/* Insignificant-value bitmap */

/* Packed Insignificant Entries Bitmap */

  int *ERRrow;			/* The mapping of row to packed ERRvect */
  int *ERRcol;			/* The mapping of col to packed ERRvect */

/* Row Displacement Scheme (RDS) */

  int *RDSbase;			/* The mapping from row to index in vector */
  int RDSvectorLen;		/* The length of the value vector */
  int *RDSvector;		/* The values */
  int RDScheckLen;		/* The length of the check vector */
  int *RDScheck;		/* The check vector */

} *Pack,PackItem;

extern int packMatrix(Pack matrix);

/*****************************************************************************

  This comment tells you how to use the packed matrix to get the values of
  the original matrix. The language used to describe this is C with cpp 
  directives.

DEFINITIONS:

    #ifdef ROW
      int ROWrow[ROWrows];
    #endif

    #ifdef COL
      int COLcol[COLcols];
    #endif

    #ifdef LES
      int LESdetRow[LESorGCSrows];
      int LESdetCol[LESorGCScols];
    #endif

    #ifdef LES|GCS
      int LESorGCSrow[LESorGCSrows];
      int LESorGCScol[LESorGCScols];
      unsigned char ERRvect[(ERRows*ERRcols+7)/8];
      #ifdef ERR
       int ERRrow[LESorGCSrows];
       int ERRcol[LESorGCScols];
      #endif
    #endif
  
    #ifdef RDS
      int RDSvector[RDSvectorLen];
      #ifndef LES|GCS
        int RDSbase[rows];
        int RDScheck[RDScheckLen];
      #endif
    #else
      int matrix[rows][cols];
    #endif
    int insign;

ACCESS METHODS:

    #ifdef ROW
      row=ROWrow[row];
    #endif

    #ifdef COL
      col=COLcol[col];
    #endif

    #ifdef LES|GCS
      #ifdef ERR
        ERRindex=ERRrow[row]*ERRcols+ERRcol[col];
      #else
        ERRindex=row*ERRcols+col;
      #endif
      if(ERRvect[ERRindex>>3)] & (0x80>>(ERRindex&0x7)))
	  value=insign;
      #ifdef LES
        else if(LESdetRow[row]<LESdetCol[col])
	  value=LESorGCSrow[row];
        else if(LESdetRow[row]>LESdetCol[col])
	  value=LESorGCScol[col];
      #endif
        else
      #ifdef RDS
	  value=RDSvector[LESorGCSrow[row]+LESorGCScol[col]];
      #else
          value=matrix[LESorGCSrow[row]][LESorGCScol[col]];
      #endif
    #elif RDS
      if(RDScheck[RDSbase[row]+col]==row)
	value=RDSvector[RDSbase[row]+col];
      else
	value=insign;
    #else
      value=matrix[row][col];
    #endif

******************************************************************************/

#endif



