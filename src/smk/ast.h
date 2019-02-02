/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-13
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/ast.h,v 1.1 2002/06/25 20:04:40 Thomas Nilsson Exp $
 *
 * $Log: ast.h,v $
 * Revision 1.1  2002/06/25 20:04:40  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:32:29  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  10:59:43  tools
 * Visible astEOT and astUNKNOWN preallocated token rules
 * Visible astSequenceLength
 *
 * Revision 1.1  1993/03/24  09:23:35  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.3  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.2  91/07/12  05:12:12  tools
 * Change %%SCREEN to be automatically generated as a packing scheme.
 * This includes a new rule NO SCREENING which is given in the %%VOCABULARY
 * section.
 * Fixed size notes in verbose mode (I hope).
 * 
 * Revision 1.1  1991/01/10  12:22:54  tools
 * Initial revision
 *
 *
 */

#ifndef _AST_H_
#define _AST_H_

typedef struct AST *AST;

#include "name.h"

/*
 * The type AST is used to repressent a node in the abstract syntax 
 * tree of a regular expression (RE). Each node repressent an operator
 * in the RE.
 */

typedef struct AST {
  char type;
  char circular;
  struct AST *car;
  struct AST *cdr;
} ASTItem;

extern AST astEOT;
extern AST astUNKNOWN;

extern AST astLookahead(AST car, AST cdr);
extern AST astSelect(AST car, AST cdr);
extern AST astConcat(AST car, AST cdr);
extern AST astClosure(AST car, int n, int m);
extern AST astSequence(AST car, AST cdr);
extern int astSequenceLength(AST ast);
extern AST astString(char *string);
extern AST astClass(char *string);
extern AST astDiff(AST ast1, AST ast2);
extern AST astInverse(AST ast);
extern AST astCut(void);
extern Name astToName(AST ast);
extern void astPrint(AST ast);
extern void astDump(AST ast);

#endif
