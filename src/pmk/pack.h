/*
 * AUTHOR : Tony Olsson
 * DATE   : 89-09-21/tony@whoozle
 *
 * MODIFIED:
 *
 */

#ifndef PackIncluded
#define PackIncluded

#define packNoErr	0
#define packErrNoMem	1
#define packErrType	2

typedef enum ePack {
  ePackROW	= 0x01,
  ePackCOL	= 0x02,
  ePackRDS	= 0x04,
  ePackLES	= 0x08,
  ePackGCS	= 0x10,
  ePackERR	= 0x20
} ePack;

typedef struct Pack {

/* These five variables MUST be set before calling packMatrix */ 

  ePack type;			/* Packing type */
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

extern int packMatrix( /* Pack *pack */ );

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



