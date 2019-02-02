#ifndef _pmParse_h_
#define _pmParse_h_
/*----------------------------------------------------------------------*\

  pmParse.h

  Parser interface

\*----------------------------------------------------------------------*/


/* Token and Srcp definition */
#include "tmCommon.h"

/* External functions */
extern void pmParse(void); /* Parser */

/* Export */

/* Semantic attribute interface */
 
/* Internal node type */
typedef struct Node {
    char *string;
    int value;
    struct Node *next;
} Node;
 

#endif
