/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-13
 * 
 * SoftLab ab (c) 1990
 *
 * Max path length is 2 lg2(N) for 2-3-4 trees.
 * Max path length is 1.444 lg2(N) for AVL trees.
 *
 * $Header*
 *
 * $Log: name.c,v $
 * Revision 1.1  2002/06/25 20:04:45  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:32:59  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:06:20  tools
 * Hmm, new date only.
 *
 * Revision 1.1  1993/03/24  09:24:13  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.3  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.2  91/07/11  10:38:37  tools
 * Added Inherited scanners and Undefined tokens
 * 
 * Revision 1.1  1991/01/10  13:18:22  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include "smkList.h"
#include "smk_i.h"
#include "name.h"
#include "smalloc.h"
#include "lmprintf.h"

typedef enum NodeColor {RED,BLACK} NodeColor;

typedef struct Node {
  Name name;
  NodeColor c;
  struct Node *l,*r;
} *Node,NodeItem;

Node root=NULL;
Node nil=NULL;
Node guard=NULL;

static Node nodeNew(name,c,l,r)
     Name name;
     NodeColor c;
     Node l;
     Node r;
{
  Node n;

  n=(Node)smalloc(sizeof(NodeItem));
  n->name=name;
  n->c=c;
  n->l=l;
  n->r=r;
  return n;
}

Name nameSearch(name)
     Name name;
{
  Node x,gg,g,f;

  if(root==NULL) {
    guard=nodeNew("",RED,0,0);
    nil=nodeNew("",BLACK,guard,guard);
    root=nodeNew("",BLACK,nil,nil);
  }

  x=f=g=root;

  while(x!=nil && strcmp(name,x->name)!=0) {
    gg=g;
    g=f;
    f=x;
    if(strcmp(name,x->name)<0) x=x->l; else x=x->r;

    if(x->l->c==RED && x->r->c==RED) {
    /* Split 2-4 NODE to 3-2-2 NODE OR 3-4 NODE to 4-2-2 NODE */
    /* The 4 NODE may be nil */

      if(x==nil) {
	/* if 4 NODE is nil insert NEW NODE and do a color flip */

	x=nodeNew((Name)strdup(name),RED,nil,nil);
	if(strcmp(name,f->name)<0) f->l=x; else f->r=x;
      }
      else {
	/* do a color flip; 2-4 NODE to 3-2-2 NODE OR 3-4 NODE to 4-2-2 NODE */

	x->l->c=BLACK;
	x->r->c=BLACK;
	x->c=RED;
      }

      if(f->c==RED) {
	/* a 3-4 NODE split to 4-2-2 NODE must be balanced!! */

	if(g->l==f) {
	  if(f->r==x) {
	    f->r=x->l;
	    x->l=f;
	    f=x;
	  }
	  g->l=f->r;
	  f->r=g;
	}
	else {
	  if(f->l==x) {
	    f->l=x->r;
	    x->r=f;
	    f=x;
	  }
	  g->r=f->l;
	  f->l=g;
	}
	f->l->c=RED;
	f->r->c=RED;
	f->c=BLACK;
	if(gg->l==g) gg->l=f; else gg->r=f;
	g=f;
	x=g;
      }
    }
  }
  root->r->c=BLACK;
  return x->name;
}

/*
 * Remove name from the tree.
 */

void nameRemove(name)
     Name name;
{
  Node x,f,g,b,bb,t;

  f=root;
  x=root->r;
  t=nil;
  g=f;
  while(x!=nil) {
    if(strcmp(name,x->name)==0) {
      t=x;
    }

    g=f;
    f=x;
    if(strcmp(name,x->name)<0) {x=f->l;b=f->r;} else {x=f->r;b=f->l;}
    
    if(x->c==BLACK && f->c==BLACK && b->c==RED) {
      /* father is a 3-NODE which should be flipped */

      f->c=RED;
      b->c=BLACK;
      if(f->r==b) {
	/* flip father 3R-NODE to 3L-NODE */

	f->r=b->l;
	b->l=f;
      }
      else {
	/* flip father 3L-NODE to 3R-NODE */
	
	f->l=b->r;
	b->r=f;
      }
      if(g->l==f) g->l=b; else g->r=b;
      g=b;
      if(f->l==x) b=f->r; else b=f->l;
    }
    
    if(f->l==x) bb=b->l; else bb=b->r;

    if(x->c==BLACK && x->r->c==BLACK && x->l->c==BLACK) {
      /* Current NODE is a 2-NODE */

      if(b->c==BLACK && b->r->c==BLACK && b->l->c==BLACK) {
	/* Brother is a 2-NODE */

	x->c=RED;
	b->c=RED;
	f->c=BLACK;		/* If father is not 2-NODE */
      }
      else if(bb->c==RED) {
	if(f->l==x) {
	  bb->c=f->c;
	  f->r=bb->l;
	  b->l=bb->r;
	  bb->l=f;
	  bb->r=b;
	  x->c=RED;
	  f->c=BLACK;
	  if(g->l==f) g->l=bb; else g->r=bb;
	  g=bb;
	}
	else {
	  bb->c=f->c;
	  f->l=bb->r;
	  b->r=bb->l;
	  bb->r=f;
	  bb->l=b;
	  x->c=RED;
	  f->c=BLACK;
	  if(g->l==f) g->l=bb; else g->r=bb;
	  g=bb;
	}
      }
      else if(bb->c==BLACK) {
	if(f->l==x) {
	  b->c=f->c;
	  b->r->c=BLACK;
	  f->r=b->l;
	  b->l=f;
	  x->c=RED;
	  f->c=BLACK;
	  if(g->l==f) g->l=b; else g->r=b;
	  g=b;
	}
	else {
	  b->c=f->c;
	  b->l->c=BLACK;
	  f->l=b->r;
	  b->r=f;
	  x->c=RED;
	  f->c=BLACK;
	  if(g->l==f) g->l=b; else g->r=b;
	  g=b;
	}
      }
    }
  }
  if(t!=nil) {
    free(t->name);
    t->name=f->name;
    if(g->l==f) g->l=nil; else g->r=nil;
    free((char *)f);
  }	  
}

static int analyze(p,l,n)
     int p;
     int l;
     Node n;
{
  int m;

  if(n==nil) {
    if(p) printf("%*snil\n",l*8,"");
    return 0;
  }
  if(n->c!=BLACK)
    printf("NODE MUST BE BLACK %s\n",n->name);
  if(n->l->c==BLACK)
    if(n->r->c==BLACK) {
      if(p) printf("%*s2-NODE (%s)\n",l*8,"",n->name);
      if(n->r==nil || n->l==nil)
	if(n->r==nil && n->l==nil)
          return 1;
	else
	  printf("%*sSOME NODES IS NOT NIL!\n",l*8,"");
      m=analyze(p,l+1,n->r);
      m+=analyze(p,l+1,n->l)+1;
      return m;
    }
    else {
      if(p) printf("%*s3-NODE [%s,%s]\n",l*8,"",n->r->name,n->name);
      if(n->r->r==nil || n->r->l==nil || n->l==nil)
	if(n->r->r==nil && n->r->l==nil && n->l==nil)
	  return 2;
	else
	  printf("%*sSOME NODES IS NOT NIL!\n",l*8,"");
      m=analyze(p,l+1,n->r->r);
      m+=analyze(p,l+1,n->r->l);
      m+=analyze(p,l+1,n->l)+2;
      return m;
    }
  else
    if(n->r->c==BLACK) {
      if(p) printf("%*s3-NODE (%s,%s)\n",l*8,"",n->name,n->l->name);
      if(n->l->r==nil || n->l->l==nil || n->r==nil)
	if(n->l->r==nil && n->l->l==nil && n->r==nil)
	  return 2;
	else
	  printf("%*sSOME NODES IS NOT NIL!\n",l*8,"");
      m=analyze(p,l+1,n->r);
      m+=analyze(p,l+1,n->l->r);
      m+=analyze(p,l+1,n->l->l)+2;
      return m;
    }
    else {
      if(p) printf("%*s4-NODE (%s,%s,%s)\n",l*8,"",n->r->name,n->name,n->l->name);
      if(n->l->r==nil || n->l->l==nil || n->l->r==nil || n->l->l==nil)
	if(n->l->r==nil && n->l->l==nil && n->l->r==nil && n->l->l==nil)
	  return 3;
	else
	  printf("%*sSOME NODES IS NOT NIL!\n",l*8,"");
      m=analyze(p,l+1,n->r->r);
      m+=analyze(p,l+1,n->r->l);
      m+=analyze(p,l+1,n->l->r);
      m+=analyze(p,l+1,n->l->l)+3;
      return m;
    }
}

void nameDump()
{
  analyze(1,0,root->r);
}

void print(n)
     Node n;
{
  if(n==nil) return;
  print(n->l);
  lmPrintf("\t%s\n",n->name);
  print(n->r);
}

void namePrint()
{
  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("Defined names\n\n");
  print(root->r);
  lmFlush();
}
