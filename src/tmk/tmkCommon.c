/*------------------------------------------------------------------- */
/* TITLE                                                              */
/* ------                                                             */
/* tmkCommon.c                                                        */
/*                                                                    */
/* VERSION:   1.0                                                     */
/* ------------------------------------------------------------------ */
/*                                                                    */
/* REVISION DATA                                                      */
/* -------------                                                      */
/* CREATED:   92-07-20  Micael Dahlgren                               */
/* BASED ON:                                                          */
/* MODIFIED:                                                          */
/* ------------------------------------------------------------------ */
/*                                                                    */
/* DESCRIPTION                                                        */
/* -----------                                                        */
/* Common functions for the ToolMaker system                          */
/*                                                                    */
/* ------------------------------------------------------------------ */
/* IMPORT */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#ifdef WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include "tmk_i.h"
#include "tmkParse.h"
#include "tmkScan.h"

char tmkEscape = '`';

/* UNIT CONSTANTS */
#define MAXNOPH 3		/* max mumber of placeholders */

#ifdef CYGWIN
#define OFLAG O_TEXT
#else
#ifdef WIN32
#define OFLAG _O_BINARY
#else
#define OFLAG 0
#endif
#endif

/* UNIT TYPES */
/* UNIT DATA */
TmkEnvP tmkEnv = NULL;
extern tmkScContext tmkCext;

/* UNIT FUNCTIONS */
#define fpopt(F,S) if (S) fprintf(F, "%s", S)
#define fpoptv(F,V,S) if (S) fprintf(F, "%%%%SET %s(\"%s\")\n", V, S)

/*======================================================================
  tmkSkipCode()

  Skip code in sematic actions and some sections
 */
void tmkSkipCode(skipType, this, fpos, length, escapeChar)
     SkipType skipType;
     tmkScContext this;
     long *fpos;
     long *length;
     char escapeChar;
{
  unsigned char *ch;
  int at;
  int state = 0;
  char stringSep1, stringSep2, oldSep;
  SkipType oldSkip;

  int skip;

  switch (skipType) {
  case NOSTRS_SKIP:
    skip = 2;
    stringSep1 = stringSep2 = '\0';
    break;
  case SEM_SKIP:
    skip = 0;
    stringSep1 = '\'';
    stringSep2 = '<';
    break;
  case RULES_SKIP:
  case STRSKP_SKIP:
    skip = 2;
    stringSep1 = '\'';
    stringSep2 = '<';
    break;
  default:
    return;
  }

  *fpos = this->smNextPosition;
  while (tmkScSkip(this, 10000)) {
    /* 2BChanged, Tillst}ndsmaskinen ska inte b|rja om */
    /* f|r att bufferten ut|kas */
    state = 0;
    ch = this->smText + 2;
    for (at = 2; at < this->smLength; at++, ch++)
      switch(state) {
      case 0:
    if (*ch == escapeChar) state = 4;
    else if (*ch == '%') state = 1;
    else if ((*ch == stringSep1) && (skipType != SEM_SKIP) && (skipType != SUB_SKIP))
      state = 5;
    else if ((*ch == stringSep2) && (skipType != SEM_SKIP) && (skipType != SUB_SKIP))
      state = 6;
    break;
      case 1:
    if (*ch == escapeChar) state = 4;
    else if (*ch == '%') state = 2;
    else if (*ch == stringSep1) state = 5;
    else if (*ch == stringSep2) state = 6;
    else state = 0;
    break;
      case 2:
    if (skipType == SUB_SKIP) {
      stringSep1 = oldSep;
      skipType = oldSkip;
      state = 0;
    } else if (skipType == SEM_SKIP) {
      goto Exit;
    } else if (skipType == RULES_SKIP) {
      oldSep = stringSep1;
      oldSkip = RULES_SKIP;
      stringSep1 = '\0';
      skipType = SUB_SKIP;
      state = 0;
    } else if (*ch == escapeChar) state = 4;
    else if (*ch == '%') state = 2;
    else if (*ch == stringSep1) state = 5;
    else if (*ch == stringSep2) state = 6;
    else if (isalpha(*ch)) goto Exit;
    else state = 0;
    break;
      case 3:
    state = 5;
      case 4:
    state = 0;
    break;
      case 5:
    if (*ch == '\\') state = 3;
    else if (*ch == stringSep1) state = 0;
    break;
      case 6:
    if (*ch == '>') state = 0;
    break;
      }
  }

  skip = 0;

Exit:
  tmkScSkip(this, at - this->smLength - skip);
  *length = this->smNextPosition - *fpos - 2 + skip;
}

/*======================================================================
  tmkReplPH()

  Replace %1 in an optional declaration with the real name of the attribute

 */
char* tmkReplPH(decl, attrName, new)
     char *decl;
     char *attrName;
     char *new;
{
  int attrLen;			/* Length of attribute name                   */
  int subst = 0;		/* Number of placeholder substitutions so far */
  int state = 0;		/* What state am I in ?                       */
  int oldPtr = 0, newPtr = 0;	/* Pointers into new and old declarations     */

  if (!decl)
    return NULL;

  if (attrName)
    attrLen = strlen(attrName);
  else
    attrLen = 0;

  while (decl[oldPtr] != '\0') {
    switch (state) {
    case 0:
      if (decl[oldPtr] == tmkEscape)
    state = 1;
      else if (decl[oldPtr] == '%')
    state = 2;
      if (state != 2) {
    new[newPtr++] = decl[oldPtr];
      }
      oldPtr++;
      break;
    case 1:
      state = 0;
      new[newPtr++] = decl[oldPtr++];
      break;
    case 2:
      if (decl[oldPtr] == tmkEscape) {
    state = 3;
    oldPtr++;
      } else if (decl[oldPtr] == '1') {
    state = 0;
    strncpy(&new[newPtr], attrName, attrLen);
    newPtr = newPtr + attrLen;
    oldPtr++;
      } else {
    new[newPtr++] = '%';
    new[newPtr++] = decl[oldPtr++];
    state = 0;
      }
      break;
    case 3:
      state = 0;
      if (decl[oldPtr] == '1') {
    strncpy(&new[newPtr], attrName, attrLen);
    newPtr = newPtr + attrLen;
    oldPtr++;
      } else {
    new[newPtr++] = '%';
    new[newPtr++] = tmkEscape;
    new[newPtr++] = decl[oldPtr++];
      }
      break;
    }
  }
  new[newPtr] = '\0';
  return new;
}

/*----------------------------------------------------------------------
  prWithPH()

  print a string with placeholders

*/
static void prWithPH(outfile, decl, attrName)
     FILE *outfile;
     char *decl;
     char *attrName;
{
  char *buff = (char*) malloc(strlen(decl)+
                  MAXNOPH * (attrName ? strlen(attrName) : 0)+1);
  tmkReplPH(decl, attrName, buff);
  fpopt(outfile, buff);
  free(buff);
}


/*======================================================================
    tmkCopyCode()

    Copy a code segment with length "length" from position "pos"
    in "inFile" to "outFile". In "inFile" use the escape character
    "inEscape" and in "outFile" use "outEscape"
 */
void tmkCopyCode(inFile, pos, length, inEscape, outFile, outEscape)
     FILE *inFile;		/* File to read code from             */
     int pos;			/* Position to start read from        */
     int length;		/* Length of code to read             */
     char inEscape;		/* Escape character to use in infile  */
     FILE *outFile;		/* File to write code to              */
     char outEscape;		/* Escape character to use in outfile */
{
  int i;			/* Loop variable              */
  char ch;			/* Temporary character holder */

  fseek(inFile, pos, 0);
  for (i = 0; i < length; i++) {
    if ((ch = (char)getc(inFile)) == '%')
      putc(outEscape, outFile);
    else if (ch == inEscape) {
      if ((ch = (char)getc(inFile)) == '%')
    putc(outEscape, outFile);
      i++;
    }
    putc(ch, outFile);
  }
}

/*======================================================================
    tmkPCommon()

    print common segments to table file

*/
void tmkPCommon(outfile, tokenNode, srcpNode, importSection, escapeChar)
     FILE *outfile;
     TokenNodeP tokenNode;
     SrcpNodeP srcpNode;
     CodeNodeP importSection;
     char escapeChar;
{
  FILE *infile;
  TokenAttrListP  p;
  int i;
  char ch;
  char *buff;

  /* token node declaration */
  if (tokenNode) {
    fprintf(outfile, "%%%%SET tmkTokenName(\"%s\")\n", tokenNode->name);

    if (tokenNode->code)
      fpoptv(outfile, "tmkTokenCode", tokenNode->code);

    if (tokenNode->srcp)
      fpoptv(outfile, "tmkTokenSrcp", tokenNode->srcp);

    if (tokenNode->codeDecl) {
      fprintf(outfile, "%%%%SET tmkTokenDecl (\"");
      /* Declaration of CODE part */
      if (tokenNode->codeDecl) {
    prWithPH(outfile, tokenNode->codeDecl, tokenNode->code);
    if (tokenNode->srcpDecl || tokenNode->srcp || tokenNode->attrs)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
      /* Declaration of source position part */
      if (tokenNode->srcpDecl) {
    prWithPH(outfile, tokenNode->srcpDecl, tokenNode->srcp);
    if (tokenNode->attrs)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      } else if (tokenNode->srcp) {
    fprintf(outfile, " %s %s", srcpNode->name, tokenNode->srcp);
    if (tokenNode->attrs)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
      /* Declaration of attributes */
      for (p = tokenNode->attrs; p; p = p->next) {
    prWithPH(outfile, p->nameDecl, p->name);
    if (p->next)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
    }
  }

  /* srcp node declaration */
  if (srcpNode) {
    fprintf(outfile, "%%%%SET tmkSrcpName(\"%s\")\n", srcpNode->name);
    if (srcpNode->row)
      fpoptv(outfile, "tmkSrcpRow", srcpNode->row);
    if (srcpNode->col)
      fpoptv(outfile, "tmkSrcpCol", srcpNode->col);
    if (srcpNode->file)
      fpoptv(outfile, "tmkSrcpFile", srcpNode->file);
    if (srcpNode->pos)
      fpoptv(outfile, "tmkSrcpPos", srcpNode->pos);
    if (srcpNode->rowDecl || srcpNode->colDecl ||
    srcpNode->fileDecl || srcpNode->posDecl)  {
      fprintf(outfile, "%%%%SET tmkSrcpDecl(\"");
      if (srcpNode->row) {
    prWithPH(outfile, srcpNode->rowDecl, srcpNode->row);
    if (srcpNode->col || srcpNode->file || srcpNode->pos)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
      if (srcpNode->col) {
    prWithPH(outfile, srcpNode->colDecl, srcpNode->col);
    if (srcpNode->file || srcpNode->pos)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
      if (srcpNode->file) {
    prWithPH(outfile, srcpNode->fileDecl, srcpNode->file);
    if (srcpNode->pos)
      fprintf(outfile, "\", \"");
    else
      fprintf(outfile, "\")\n");
      }
      if (srcpNode->pos) {
    prWithPH(outfile, srcpNode->posDecl, srcpNode->pos);
    fprintf(outfile, "\")\n");
      }
    }
  }

  /* tmk import section */
  if (importSection &&
      (infile = fopen(importSection->fname, "rb")) != NULL) {
    fprintf(outfile, "%%%%BEGIN(tmkImport)\n");
    tmkCopyCode(infile, importSection->fpos, importSection->length,
        escapeChar, outfile, '`');
    fprintf(outfile, "%%%%END(tmkImport)\n");
  }

/* This is perhaps optimal but failure to declare the %%import in the
   .tmk file causes problems (and it does'nt work with the current skeletons!!
  if (!importSection &&
      !(tokenNode && tokenNode->codeDecl) &&
      !(srcpNode && (srcpNode->rowDecl || srcpNode->colDecl ||
             srcpNode->fileDecl || srcpNode->posDecl)))
    fprintf(outfile, "%%%%SET doNotGenerateTokenH(TRUE)\n");
*/
}

/*======================================================================
    tmkNewCode
 */
CodeNodeP tmkNewCode(fpos, length)
  long fpos;			/* File pos of target language code */
  long length;			/* Length of target language code */
{
  CodeNodeP p = (CodeNodeP) malloc(sizeof(CodeNode));
  p->fpos = fpos;
  p->length = length;
  p->fname = NULL;
  return p;
}

/*======================================================================
    tmkCParse()

    parse common segments in tmk or other files

*/
Boolean tmkCParse(inFileName, optTab, cliTab, argc, argv,
         tokenNode, srcpNode, importSection, fileNo, fileType, escapeOpt)
     char *inFileName;
     OptTabRec *optTab;
     OptTabRec *cliTab;
     int argc;
     char *argv[];
     TokenNodeP *tokenNode;
     SrcpNodeP *srcpNode;
     CodeNodeP *importSection;
     int fileNo;
     FileType fileType;
     int escapeOpt;
{
  tmkEscape = *getStrOpt(escapeOpt);
  tmkCext = tmkScNew(tmk_MAIN_MAIN_Scanner);
  if (!tmkCext)
    return FALSE;
  else if ((tmkCext->fd = open(inFileName, OFLAG)) < 0) {
    tmkScDelete(tmkCext);
    return FALSE;
  } else {
    tmkCext->fileName = inFileName;

    /* setup env */
    tmkEnv = (TmkEnvP) calloc(1,sizeof(TmkEnv));
    tmkEnv->fileType = fileType;
    tmkEnv->escapeOpt = escapeOpt;
    tmkEnv->optTab = optTab;
    tmkEnv->cliTab = cliTab;
    tmkEnv->argc = argc;
    tmkEnv->argv = argv;
    tmkEnv->fileNo = fileNo;
    tmkEnv->tokenNode = NULL;
    tmkEnv->srcpNode = NULL;
    tmkEnv->importSection = NULL;

    /* parse and cleanup */
    tmkParse();
    close(tmkCext->fd);
    if (tmkEnv->importSection) {
      tmkEnv->importSection->fname = (char *) malloc(strlen(inFileName)+1);
      strcpy(tmkEnv->importSection->fname, inFileName);
    }

    /* copy to output parameters */
    *tokenNode = tmkEnv->tokenNode;
    *srcpNode = tmkEnv->srcpNode;
    *importSection = tmkEnv->importSection;
    free(tmkEnv);
    tmkScDelete(tmkCext);
  }
  return TRUE;
}
