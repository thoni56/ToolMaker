/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-19/tony@wolf
 * CREATED: 1990-06-26
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/write.c,v 1.1 2002/06/25 20:05:04 Thomas Nilsson Exp $
 *
 * $Log: write.c,v $
 * Revision 1.1  2002/06/25 20:05:04  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.16  1997/07/28 15:18:32  thoni
 * Added generation of currentOS so that Scan.imp can use the correct commands
 *
 * Revision 1.15  1997/06/26 11:53:49  hakan
 * <CR><LF> problematiken åtgärdad
 *
 * Revision 1.14  1997/01/22 16:28:32  gunilla
 * Adapted for WIN32
 *
 * Revision 1.13  1997/01/13 10:20:52  thoni
 * Fixed Memory Access errors
 *
 * Revision 1.12  1995/12/19 15:23:27  tony
 * If token is a string and token code less than zero then write its name
 * in a coded form (non-numbers and non-alpha characters are written as
 * numbers).
 *
 * Revision 1.11  1995/10/26  12:32:18  thoni
 * Removed empty line generation in the table file
 *
 * Revision 1.10  1995/01/23  19:18:39  thole
 * - Using SEEK_SET instead of L_SET in call to lseek() since L_SET is
 *   not availible on hp. (SEEK_SET is a newer form of L_SET. Both have
 *   the same value.)
 *
 * Revision 1.9  1993/08/20  11:33:57  tony
 * Conforms more to ANSI C standard.
 *
 * Revision 1.8  1993/07/12  12:58:42  tony
 * Fixed warnings from gcc 2.4.5
 *
 * Revision 1.7  1993/06/29  06:08:13  thoni
 * Changed formatting and typecasting to comply better with older 'c' compilers
 *
 * Revision 1.6  1993/05/27  08:41:43  tools
 * Sorry, previous change (%%CODE) was WRONG!
 * This section is removed again.
 *
 * Revision 1.5  1993/05/23  16:33:17  tools
 * Committed Tony's changes
 *
 * Revision 1.4  1993/04/30  12:34:07  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.3  1993/04/27  14:22:24  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.2  1993/04/23  11:24:05  tools
 * Removed use of explicit allocated variables.
 * Updated to use new concept of vocabularies, tokens, rules and
 * scanners.
 * Updated to use new concept of screening.
 * Some minor bug fixes.
 *
 * Revision 1.1  1993/03/24  09:25:36  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.11  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.10  91/09/20  05:20:06  tools
 * Fixed SKIP test in writeToken
 * 
 * Revision 1.9  1991/08/22  07:24:46  tools
 * Changed handling of EOT and UNKNOWN tokens.
 * Fix size bug in smDebugScanner
 *
 * Revision 1.8  1991/08/12  16:25:47  tools
 * Comment row number in DFA
 *
 * Revision 1.7  1991/07/12  05:12:12  tools
 * Change %%SCREEN to be automatically generated as a packing scheme.
 * This includes a new rule NO SCREENING which is given in the %%VOCABULARY
 * section.
 * Fixed size notes in verbose mode (I hope).
 *
 * Revision 1.6  1991/07/10  14:20:01  tools
 * New SET handling
 *
 * Revision 1.5  1991/04/05  14:13:19  tools
 * New imp uses [] instead of () as index
 *
 * Revision 1.4  91/02/18  10:45:39  tools
 * Allocated to little memory when writing debug info.
 * 
 * Revision 1.3  91/02/15  16:35:16  tools
 * Added TRACE option
 * 
 * Revision 1.2  91/02/15  15:11:19  tools
 * Debug text for token was not correctly sorted.
 * 
 * Revision 1.1  91/01/10  12:22:51  tools
 * Initial revision
 * 
 *
 */

#include <memory.h>
#include <sys/types.h>
#ifndef WIN32
#include <sys/file.h>
#endif
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef WIN32
#include <io.h>
#endif
#include "smk_i.h"
#include "pack.h"
#include "action.h"
#include "dfa.h"
#include "rule.h"
#include "scanner.h"
#include "set.h"
#include "map.h"
#include "version.h"
#include "screen.h"
#include "smalloc.h"
#include "lmprintf.h"

static void writeVoc(FILE *fd);
static void writeDebug(FILE *fd);
static void writeActions(FILE *fd);
static int writeMap(FILE *fd);
static int writeScanner(FILE *fd);
static int writeAccept(FILE *fd);
static int writeRuleCode(FILE *fd);
static int writeLookahead(FILE *fd);
static int writeScreening(FILE *fd);
static int writeDFA(FILE *fd, Pack pack);

static char *gLineCommentBegin="/*";
static char *gLineCommentEnd="*/";
static char *gArrayBegin="{";
static char *gArrayEnd="}";
static char *gArrayDelimiter=",";

/*======================================================================
    smkCopyCode()

    Copy a code segment with length "length" from position "pos" 
    in "inFile" to "outFile". In "inFile" use the escape character
    "inEscape" and in "outFile" use "outEscape"
 */
static void smkCopyCode(inFile, pos, length, inEscape, outFile, outEscape)
     int inFile;		/* File to read code from             */
     int pos;			/* Position to start read from        */
     int length;		/* Length of code to read             */
     char inEscape;		/* Escape character to use in infile  */
     FILE *outFile;		/* File to write code to              */
     char outEscape;		/* Escape character to use in outfile */
{
  int i;			/* Loop variable              */
  char ch;			/* Temporary character holder */
  
  lseek(inFile, pos, 0);
  for (i = 0; i < length; i++) {
    if ((read(inFile, &ch, 1) == 1) && (ch == '%'))
      putc(outEscape, outFile);
    else if (ch == inEscape) {
      if ((read(inFile, &ch, 1) == 1) && (ch == '%'))
	putc(outEscape, outFile);
      i++;
    }
    putc(ch, outFile);
  }
}

void writeAll(pack,size,maxsize,unoptsize) 
     Pack pack;
     int *size;
     int *maxsize;
     int unoptsize;
{
  FILE *fd;
  int aSize, inFile;
  long clock;
  char *date, *target;
  
  *size=0;
  *maxsize=0;
  if((fd=fopen(optSmtfile,"wb"))==NULL) return;
  tmkPCommon(fd, tokenNode, srcpNode, importSection, getStrOpt(TMKESCAPE_OPT)[0]);
  clock=time(0);
  date=(char *)ctime(&clock);
  date[strlen(date)-1]=0;
     fprintf(fd,"%%%%SET smVersion(\"%s\")\n",product.longHeader);
  target = getStrOpt(SMKTARGET_OPT);
  fprintf(fd, "%%%%SET tmkForce(%d)\n",getBoolOpt(FORCE_OPT) ? 1 : 0);
  fprintf(fd, "%%%%SET tmkOs(\"%s\")\n", getStrOpt(TMKOS_OPT));
  fprintf(fd, "%%%%SET smkOs(\"%s\")\n", getStrOpt(SMKOS_OPT));
#ifdef WIN32
  fprintf(fd, "%%%%SET currentOs(\"WIN32\")\n");
#else
  fprintf(fd, "%%%%SET currentOs(\"SunOS\")\n");
#endif
  fprintf(fd, "%%%%SET tmkTarget(\"%s\")\n", getStrOpt(TMKTARGET_OPT));
  fprintf(fd, "%%%%SET smkTarget(\"%s\")\n", target);
  fprintf(fd, "%%%%SET tmkLibrary(\"%s\")\n", getStrOpt(TMKLIBRARY_OPT));
  fprintf(fd, "%%%%SET smkLibrary(\"%s\")\n", getStrOpt(SMKLIBRARY_OPT));
  fprintf(fd, "%%%%SET tmkPrefix(\"%s\")\n", getStrOpt(TMKPREFIX_OPT));
  fprintf(fd, "%%%%SET smkPrefix(\"%s\")\n", getStrOpt(SMKPREFIX_OPT));
  if ((smkImportSection) &&
      (inFile = open(smkImportSection->fname, OFLAG)) >= 0) {
    fprintf(fd, "%%%%BEGIN(smIMPORT)\n");
    smkCopyCode(inFile, smkImportSection->fpos, smkImportSection->length, 
		smkEscape, fd, '`');
    close(inFile);
    fprintf(fd, "%%%%END(smIMPORT)\n");
  }
  if ((strcmp(target, "c") == 0) ||
      (strcmp(target, "ansi-c") == 0) ||
      (strcmp(target, "c++") == 0)) {
    gArrayBegin="{";
    gArrayEnd="}";
    gArrayDelimiter=",";
  }
  else {
    gArrayBegin="{";
    gArrayEnd="}";
    gArrayDelimiter=",";
  }    
  if(optExclude>=0) fprintf(fd,"%%%%SET smExclude(\"%d\")\n",optExclude);
  fprintf(fd,"%%%%SET smTokenSize(\"%d\")\n",getNumOpt(TOKENSIZE_OPT));
  fprintf(fd,"%%%%SET smTokenMaxSize(\"%d\")\n",getNumOpt(TOKENLIMIT_OPT));
  fprintf(fd,"%%%%SET smTrace(%d)\n",getBoolOpt(TRACE_OPT) ? 1 : 0);
  fprintf(fd,"%%%%SET smVerbose(%d)\n",getBoolOpt(VERBOSE_OPT) ? 1 : 0);
  fprintf(fd,"%%%%SET smNewLine(%d)\n",setTable['\n']);
  fprintf(fd,"%%%%SET smCarriageReturn(%d)\n",setTable['\r']);

  writeVoc(fd);
  writeDebug(fd);
  writeActions(fd);
  
  if(mapUsed) {
    aSize=writeMap(fd);
    *size+=aSize;
    *maxsize+=aSize;
  }
  
  aSize=writeScanner(fd);
  *size+=aSize;
  *maxsize+=aSize;
  
  aSize=writeAccept(fd);
  *size+=aSize;
  *maxsize+=aSize;
  
  aSize=writeRuleCode(fd);
  *size+=aSize;
  *maxsize+=aSize;
  
  if(lookaheadRoot) {
    aSize=writeLookahead(fd);
    *size+=aSize;
    *maxsize+=aSize;
  }
  
  if(screenHasScreening) {
    aSize=writeScreening(fd);
    *size+=aSize;
    *maxsize+=aSize;
  }
  
  aSize=writeDFA(fd,pack);
  *size+=aSize;
  if(unoptsize<256)
    *maxsize+=unoptsize*256;
  else if(unoptsize<256*256)
    *maxsize+=unoptsize*256*2;
  else
    *maxsize+=unoptsize*256*4;
  fprintf(fd, "%%%%PROCESS(\"%%%%(tmkLibrary)/Common.imp\")\n");
  fprintf(fd, "%%%%PROCESS(\"%%%%(smkLibrary)/Scan.imp\")\n");
  fclose(fd);
}

/*
 * Write a comment
 */

static void writeComment(fd,buffer,length)
     FILE *fd;
     char *buffer;
     int length;
{
  char *ch;
  char *target;

  target = getStrOpt(SMKTARGET_OPT);
  if ((strcmp(target, "c") == 0) ||
      (strcmp(target, "ansi-c") == 0)) {
    fprintf(fd,"/* ");
    while((ch=strpbrk(buffer,"%*"))) {
      fwrite(buffer,1,ch-buffer,fd);
      fwrite(*ch=='%' ? "`%" : "* ",1,2,fd);
      length-=ch-buffer+1;
      buffer=ch+1;
    }
    fwrite(buffer,1,length,fd);
    fprintf(fd,"*/ ");
  }
  else if (strcmp(target, "c++") == 0) {
    fprintf(fd,"// ");
    while((ch=strpbrk(buffer,"%"))) {
      fwrite(buffer,1,ch-buffer,fd);
      fwrite("`%",1,2,fd);
      length-=ch-buffer+1;
      buffer=ch+1;
    }
    fwrite(buffer,1,length,fd);
  }
  else {
    fprintf(fd,"/* ");
    while((ch=strpbrk(buffer,"%*"))) {
      fwrite(buffer,1,ch-buffer,fd);
      fwrite(*ch=='%' ? "`%" : "* ",1,2,fd);
      length-=ch-buffer+1;
      buffer=ch+1;
    }
    fwrite(buffer,1,length,fd);
    fprintf(fd,"*/ ");
  }
}

/*
 * Write code removing escape charaters and quoting %
 */

static void writeCode(fd,buffer,length)
     FILE *fd;
     char *buffer;
     int length;
{
  char *ch;
  char brk[3];

  brk[0]='%';
  brk[1]=smkEscape;
  brk[2]=0;
  while((ch=strpbrk(buffer,brk))) {
    fwrite(buffer,1,ch-buffer,fd);
    if(*ch=='%') {
      fwrite("`%",1,2,fd); 
      length-=ch-buffer+1;
      buffer=ch+1;
    }
    else {
      if(ch[1]=='%') 
	fwrite("`%",1,2,fd); 
      else
	fwrite(ch+1,1,1,fd);
      length-=ch-buffer+2;
      buffer=ch+2;
    }      
  }
  fwrite(buffer,1,length,fd);
}
	
/*
 * Write Vector data
 */

static int writeVector(fd,vector,cols)
     FILE *fd;
     int *vector;
     int cols;
{
  int col;
  int max;

  if(cols==0) {
    fprintf(fd,"%s0%s\n",gArrayBegin,gArrayEnd);
    return 1;
  }
  max=0;
  fprintf(fd,"%s",gArrayBegin);
  for(col=0;col<cols;col++) {
    if((col&15)==0) fprintf(fd,"\n");
    if(col>0) fprintf(fd,"%s",gArrayDelimiter);
    fprintf(fd,"%d",vector[col]);
    if(max<vector[col]) max=vector[col];
  }
  fprintf(fd,"\n%s\n",gArrayEnd);
  if(max<=0xFF) return 1;
  if(max<=0xFFFF) return 2;
  return 4;
}

static int writeMatrix(fd,matrix,rows,cols)
     FILE *fd;
     int **matrix;
     int rows;
     int cols;
{
  int row;
  int col;
  int max;

  if(rows==0 || cols==0) {
    fprintf(fd,"%s%s0%s%s\n",gArrayBegin,gArrayBegin,gArrayEnd,gArrayEnd);
    return 1;
  }
  max=0;
  fprintf(fd,"%s",gArrayBegin);
  for(row=0;row<rows;row++) {
    if(row>0) fprintf(fd,"%s",gArrayDelimiter);
    fprintf(fd,"%s %s %d %s",gArrayBegin,gLineCommentBegin,row,gLineCommentEnd);
    for(col=0;col<cols;col++) {
      if((col&15)==0) fprintf(fd,"\n");
      if(col>0) fprintf(fd,"%s",gArrayDelimiter);
      fprintf(fd,"%d",matrix[row][col]);
      if(max<matrix[row][col]) max=matrix[row][col];
    }
    fprintf(fd,"\n%s",gArrayEnd);
  }
  fprintf(fd,"\n%s\n",gArrayEnd);
  if(max<=0xFF) return 1;
  if(max<=0xFFFF) return 2;
  return 4;
}

static int writeMatrixAsVector(fd,matrix,rows,cols)
     FILE *fd;
     int **matrix;
     int rows;
     int cols;
{
  int row;
  int col;
  int max;

  if(rows==0 || cols==0) {
    fprintf(fd,"%s0%s\n",gArrayBegin,gArrayEnd);
    return 1;
  }
  max=0;
  fprintf(fd,"%s",gArrayBegin);
  for(row=0;row<rows;row++) {
    if(row>0) fprintf(fd,"%s",gArrayDelimiter);
    for(col=0;col<cols;col++) {
      if((col&15)==0) fprintf(fd,"\n");
      if(col>0) fprintf(fd,"%s",gArrayDelimiter);
      fprintf(fd,"%d",matrix[row][col]);
      if(max<matrix[row][col]) max=matrix[row][col];
    }
  }
  fprintf(fd,"\n%s\n",gArrayEnd);
  if(max<=0xFF) return 1;
  if(max<=0xFFFF) return 2;
  return 4;
}

/*
 * Write Error matrix for LES or GCS
 *
 */

static int writeErrorMatrix(fd,pack)
     FILE *fd;
     Pack pack;
{
  int size;
  int rows;
  int row;
  char *target;
  
  size=0;

  /* Write the error table, NOTE that this is target specific */

  target = getStrOpt(SMKTARGET_OPT);
  if ((strcmp(target, "c") == 0) ||
      (strcmp(target, "ansi-c") == 0) ||
      (strcmp(target, "c++") == 0)) {
    fprintf(fd,"%%%%BEGIN(smERRvec)\n");
    rows=(pack->ERRrows*pack->ERRcols+7)/8;
    fprintf(fd,"%s",gArrayBegin);
    for(row=0;row<rows;row++) {
      if(row>0) fprintf(fd,"%s",gArrayDelimiter);
      if((row&15)==0) fprintf(fd,"\n");
      fprintf(fd,"0x%02X",pack->ERRvect[row]);
    }
    fprintf(fd,"\n%s",gArrayEnd);
    fprintf(fd,"%%%%END(smERRvec)\n");
    fprintf(fd,"%%%%SET smERRrowLen(%d)\n",pack->ERRrows);
    fprintf(fd,"%%%%SET smERRcolLen(%d)\n",pack->ERRcols);
    fprintf(fd,"%%%%SET smERRtyp(%d)\n",1);
    size+=rows;
  }
  else {
    fprintf(fd,"%%%%BEGIN(smERRvec)\n");
    rows=(pack->ERRrows*pack->ERRcols+7)/8;
    fprintf(fd,"%s",gArrayBegin);
    for(row=0;row<rows;row++) {
      if(row>0) fprintf(fd,"%s",gArrayDelimiter);
      if((row&15)==0) fprintf(fd,"\n");
      fprintf(fd,"0x%02X",pack->ERRvect[row]);
    }
    fprintf(fd,"\n%s",gArrayEnd);
    fprintf(fd,"%%%%END(smERRvec)\n");
    fprintf(fd,"%%%%SET smERRrowLen(%d)\n",pack->ERRrows);
    fprintf(fd,"%%%%SET smERRcolLen(%d)\n",pack->ERRcols);
    fprintf(fd,"%%%%SET smERRtyp(%d)\n",1);
    size+=rows;
  }
  return size;
}

/*
 * Write DFA
 *
 */

static int writeDFA(fd, pack)
     FILE *fd;
     Pack pack;
{
  int size;
  int type;
  int row;

  size=0;

/* packing type */

  fprintf(fd,"%%%%SET smFAST(%d)\n",pack->type==0 && scannerCodes==1 ? 1 : 0);
  fprintf(fd,"%%%%SET smROW(%d)\n",(pack->type & ePackROW)!=0);
  fprintf(fd,"%%%%SET smCOL(%d)\n",(pack->type & ePackCOL)!=0);
  fprintf(fd,"%%%%SET smRDS(%d)\n",(pack->type & ePackRDS)!=0);
  fprintf(fd,"%%%%SET smLES(%d)\n",(pack->type & ePackLES)!=0);
  fprintf(fd,"%%%%SET smGCS(%d)\n",(pack->type & ePackGCS)!=0);
  fprintf(fd,"%%%%SET smERR(%d)\n",(pack->type & ePackERR)!=0);

/* error state */

  fprintf(fd,"%%%%SET smError(%d)\n",pack->insign);

/* Write ROW */

  if(pack->type & ePackROW) {
    fprintf(fd,"%%%%BEGIN(smROWvec)\n");
    if((pack->type & (ePackRDS|ePackLES|ePackGCS))==0) 
      for(row=0;row<pack->ROWrows;row++) pack->ROWrow[row]*=pack->cols;
    type=writeVector(fd,pack->ROWrow,pack->ROWrows);
    fprintf(fd,"%%%%END(smROWvec)\n");
    fprintf(fd,"%%%%SET smROWlen(%d)\n",pack->ROWrows?pack->ROWrows:1);
    fprintf(fd,"%%%%SET smROWtyp(%d)\n",type);
    size+=type*pack->ROWrows;
  }

/* Write COL */

  if(pack->type & ePackCOL) {
    fprintf(fd,"%%%%BEGIN(smCOLvec)\n");
    type=writeVector(fd,pack->COLcol,pack->COLcols);
    fprintf(fd,"%%%%END(smCOLvec)\n");
    fprintf(fd,"%%%%SET smCOLlen(%d)\n",pack->COLcols?pack->COLcols:1);
    fprintf(fd,"%%%%SET smCOLtyp(%d)\n",type);
    size+=type*pack->COLcols;
  }

/* Write LES and GCS */
  
  if(pack->type & (ePackLES|ePackGCS)) {

    /* if LES, write determination row and column */

    if(pack->type & ePackLES) {
      fprintf(fd,"%%%%BEGIN(smLESdetRow)\n");
      type=writeVector(fd,pack->LESdetRow,pack->LESorGCSrows);
      fprintf(fd,"%%%%END(smLESdetRow)\n");
      fprintf(fd,"%%%%SET smLESdetRowTyp(%d)\n",type);
      size+=type*pack->LESorGCSrows;
      fprintf(fd,"%%%%BEGIN(smLESdetCol)\n");
      type=writeVector(fd,pack->LESdetCol,pack->LESorGCScols);
      fprintf(fd,"%%%%END(smLESdetCol)\n");
      fprintf(fd,"%%%%SET smLESdetColTyp(%d)\n",type);
      size+=type*pack->LESorGCScols;
    }

    /* write LES or GCS row and column index vectors */
    
    fprintf(fd,"%%%%BEGIN(smLESorGCSrow)\n");
    type=writeVector(fd,pack->LESorGCSrow,pack->LESorGCSrows);
    fprintf(fd,"%%%%END(smLESorGCSrow)\n");
    fprintf(fd,"%%%%SET smLESorGCSrowLen(%d)\n",pack->LESorGCSrows?pack->LESorGCSrows:1);
    fprintf(fd,"%%%%SET smLESorGCSrowTyp(%d)\n",type);
    size+=type*pack->LESorGCSrows;
    fprintf(fd,"%%%%BEGIN(smLESorGCScol)\n");
    type=writeVector(fd,pack->LESorGCScol,pack->LESorGCScols);
    fprintf(fd,"%%%%END(smLESorGCScol)\n");
    fprintf(fd,"%%%%SET smLESorGCScolLen(%d)\n",pack->LESorGCScols?pack->LESorGCScols:1);
    fprintf(fd,"%%%%SET smLESorGCScolTyp(%d)\n",type);
    size+=type*pack->LESorGCScols;

    size+=writeErrorMatrix(fd,pack);

    if(pack->type & ePackERR) {
      fprintf(fd,"%%%%BEGIN(smERRrow)\n");
      type=writeVector(fd,pack->ERRrow,pack->LESorGCSrows);
      fprintf(fd,"%%%%END(smERRrow)\n");
      fprintf(fd,"%%%%SET smERRrowTyp(%d)\n",type);
      size+=type*pack->LESorGCSrows;
      fprintf(fd,"%%%%BEGIN(smERRcol)\n");
      type=writeVector(fd,pack->ERRcol,pack->LESorGCScols);
      fprintf(fd,"%%%%END(smERRcol)\n");
      fprintf(fd,"%%%%SET smERRcolTyp(%d)\n",type);
      size+=type*pack->LESorGCScols;
    }
  }
  
/* Write RDS or normal matrix */

  if(pack->type & ePackRDS) {
    
    /* write RDS vector */

    fprintf(fd,"%%%%BEGIN(smRDSvec)\n");
    type=writeVector(fd,pack->RDSvector,pack->RDSvectorLen);
    fprintf(fd,"%%%%END(smRDSvec)\n");
    fprintf(fd,"%%%%SET smRDSvecLen(%d)\n",pack->RDSvectorLen?pack->RDSvectorLen:1);
    fprintf(fd,"%%%%SET smRDSvecTyp(%d)\n",type);
    size+=type*pack->RDSvectorLen;
    
    /* if not LES or GCS, write base and check vectors */

    if(!(pack->type & (ePackLES|ePackGCS))) {
      fprintf(fd,"%%%%BEGIN(smRDSbas)\n");
      type=writeVector(fd,pack->RDSbase,pack->rows);
      fprintf(fd,"%%%%END(smRDSbas)\n");
      fprintf(fd,"%%%%SET smRows(%d)\n",pack->rows);
      fprintf(fd,"%%%%SET smRDSbasTyp(%d)\n",type);
      size+=type*pack->rows;
      fprintf(fd,"%%%%BEGIN(smRDSchk)\n");
      type=writeVector(fd,pack->RDScheck,pack->RDScheckLen);
      fprintf(fd,"%%%%END(smRDSchk)\n");
      fprintf(fd,"%%%%SET smRDSchkLen(%d)\n",pack->RDScheckLen?pack->RDScheckLen:1);
      fprintf(fd,"%%%%SET smRDSchkTyp(%d)\n",type);
      size+=type*pack->RDScheckLen;
    }
  }
  else {
    
    /* write normal matrix */
      
    if((pack->type & ePackROW) && !(pack->type & (ePackLES|ePackGCS|ePackRDS))) {
      fprintf(fd,"%%%%BEGIN(smDFAmat)\n");
      type=writeMatrixAsVector(fd,pack->matrix,pack->rows,pack->cols);
      fprintf(fd,"%%%%END(smDFAmat)\n");
      fprintf(fd,"%%%%SET smDFArowLen(%d)\n",0);
      fprintf(fd,"%%%%SET smDFAcolLen(%d)\n",pack->rows*(pack->cols?pack->cols:1));
      fprintf(fd,"%%%%SET smDFAtyp(%d)\n",type);
      size+=type*pack->rows*pack->cols;
    }
    else {
      fprintf(fd,"%%%%BEGIN(smDFAmat)\n");
      type=writeMatrix(fd,pack->matrix,pack->rows,pack->cols);
      fprintf(fd,"%%%%END(smDFAmat)\n");
      fprintf(fd,"%%%%SET smDFArowLen(%d)\n",pack->rows?pack->rows:1);
      fprintf(fd,"%%%%SET smDFAcolLen(%d)\n",pack->cols?pack->cols:1);
      fprintf(fd,"%%%%SET smDFAtyp(%d)\n",type);
      size+=type*pack->rows*pack->cols;
    }
  }

  return size;
}



static void writeActions(FILE *fd)
{
  Action action;
  int length;
  char *buffer;
  int ifd;
  int hasSemanticActions;
  char *target;

  hasSemanticActions=0;
  ifd=open(optScanner,OFLAG);
  for(action=actionRoot;action;action=action->next) {
    length=action->stop-action->start+1;
    buffer=(char *)smalloc((unsigned int)(length+1));
    lseek(ifd,action->start,SEEK_SET);
    length=read(ifd,buffer,length);
    buffer[length]=0;
    switch(action->type) {
    case actionSEMANTIC:
      hasSemanticActions=1;
      fprintf(fd,"%%%%BEGIN(smACTION%d)\n",action->code);
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smACTION%d)\n",action->code);
      break;
    case actionDECLARATION:
      fprintf(fd,"%%%%BEGIN(smDECLARATION)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smDECLARATION)\n");
      break;
/*
    case actionCODE:
      fprintf(fd,"%%%%BEGIN(smCODE)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smCODE)\n");
      break;
*/
    case actionREADER:
      fprintf(fd,"%%%%BEGIN(smREADER)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smREADER)\n");
      break;
    case actionCONTEXT:
      fprintf(fd,"%%%%BEGIN(smCONTEXT)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smCONTEXT)\n");
      break;
    case actionEXPORT:
      fprintf(fd,"%%%%BEGIN(smEXPORT)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smEXPORT)\n");
      break;
    case actionACTION:
      fprintf(fd,"%%%%BEGIN(smACTION)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smACTION)\n");
      break;
    case actionPREHOOK:
      fprintf(fd,"%%%%BEGIN(smPREHOOK)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smPREHOOK)\n");
      break;
    case actionPOSTHOOK:
      fprintf(fd,"%%%%BEGIN(smPOSTHOOK)\n");
      writeCode(fd,buffer,length);
      fprintf(fd,"\n%%%%END(smPOSTHOOK)\n");
      break;
    default:
      break;
    }
    free(buffer);
  }
  close(ifd);
  
  if(hasSemanticActions) {
    fprintf(fd,"%%%%SET smACTIONS(1)\n");
    fprintf(fd,"%%%%BEGIN(smACTIONS)\n");
    target = getStrOpt(SMKTARGET_OPT);
    if ((strcmp(target, "c") == 0) ||
	(strcmp(target, "ansi-c") == 0) ||
	(strcmp(target, "c++") == 0)) {
      fprintf(fd,"  switch(%%%%(smACTIONS[1])) {");
      for(action=actionRoot;action;action=action->next)
	if(action->type==actionSEMANTIC) {
	  Vocabulary vocabulary;
	  Scanner scanner;
	  Rule rule;
	  
	  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
	    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
	      for(rule=scanner->rules;rule;rule=rule->next)
		if(rule->action==action) {
		  fprintf(fd,"\n  case %3d:\t\t",rule->code);
		  writeComment(fd,rule->token->name,strlen(rule->token->name));
/* fprintf(fd," in %s::%s", vocabulary->name, scanner->name); */
		}
	  fprintf(fd,"\n    {%%%%INCLUDE(smACTION%d)}\n    break;\n",action->code);
	}
      fprintf(fd,"  }\n");
    }
    else {
      fprintf(fd,"  switch(%%%%(smACTIONS[1])) {");
      for(action=actionRoot;action;action=action->next)
	if(action->type==actionSEMANTIC) {
	  Vocabulary vocabulary;
	  Scanner scanner;
	  Rule rule;
	  
	  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
	    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
	      for(rule=scanner->rules;rule;rule=rule->next)
		if(rule->action==action) {
		  fprintf(fd,"\n  case %3d:\t\t",rule->code);
		  writeComment(fd,rule->token->name,strlen(rule->token->name));
/* fprintf(fd," in %s::%s", vocabulary->name, scanner->name); */
		}
	  fprintf(fd,"\n    {%%%%INCLUDE(smACTION%d)}\n    break;\n",action->code);
	}
      fprintf(fd,"  }\n");
    }
    fprintf(fd,"%%%%END(smACTIONS)\n");
  }
}

static int writeScanner(fd)
     FILE *fd;
{
  Vocabulary vocabulary;
  Scanner scanner;
  int *table;
  int type;
  int size;

  table=(int *)smalloc((unsigned int)(sizeof(int)*scannerCodes));
  size=0;
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      table[scanner->code]=scanner->dfa->node;
  fprintf(fd,"%%%%BEGIN(smSCANNERvec)\n");
  type=writeVector(fd,table,scannerCodes);
  fprintf(fd,"%%%%END(smSCANNERvec)\n");
  fprintf(fd,"%%%%SET smSCANNERvecLen(%d)\n",scannerCodes);
  fprintf(fd,"%%%%SET smSCANNERvecTyp(%d)\n",type);
  size+=type*scannerCodes;
  free((char *)table);
  return size;
}

static int writeAccept(fd)
     FILE *fd;
{
  DFA dfa;
  int *table;
  int type;
  int size;

  table=(int *)smalloc((unsigned int)(sizeof(int)*(dfaSize+1)));
  size=0;
  fprintf(fd,"%%%%-- rule code is 1 to high (0=no accept)!\n");
  for(dfa=dfaRoot;dfa;dfa=dfa->next)
    table[dfa->node]=dfa->accept ? dfa->accept->code+1 : 0;
  table[dfaSize]=0;
  fprintf(fd,"%%%%BEGIN(smACCEPTvec)\n");
  type=writeVector(fd,table,dfaSize);
  fprintf(fd,"%%%%END(smACCEPTvec)\n");
  fprintf(fd,"%%%%SET smACCEPTvecLen(%d)\n",dfaSize);
  fprintf(fd,"%%%%SET smACCEPTvecTyp(%d)\n",type);
  size+=type*dfaSize;
  free((char *)table);
  return size;
}
    
    
static int writeRuleCode(fd)
     FILE *fd;
{
  int *table;
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;
  int type;
  int size;

  table=(int *)smalloc((unsigned int)(sizeof(int)*ruleCodes));
  size=0;
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if(rule->type!=ruleUNDEF)
	  table[rule->code]=(rule->type==ruleSKIP) ? 0 : rule->token->code+1;
  fprintf(fd,"%%%%-- rule code is 1 to high (0=skip)!\n"); 
  fprintf(fd,"%%%%BEGIN(smTOKENCODEvec)\n");
  type=writeVector(fd,table,ruleCodes);
  fprintf(fd,"%%%%END(smTOKENCODEvec)\n");
  fprintf(fd,"%%%%SET smTOKENCODEvecLen(%d)\n",ruleCodes);
  fprintf(fd,"%%%%SET smTOKENCODEvecTyp(%d)\n",type);
  size+=type*ruleCodes;
  free((char *)table);
  /*
   * Write EOT and UNKNOWN internal codes
   */
  table=(int *)smalloc((unsigned int)(sizeof(int)*scannerCodes));
  fprintf(fd,"%%%%BEGIN(smEOTCODEvec)\n");
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if(rule->ast==astEOT) table[scanner->code]=rule->code;
  type=writeVector(fd,table,scannerCodes);
  fprintf(fd,"%%%%END(smEOTCODEvec)\n");
  fprintf(fd,"%%%%SET smEOTCODEvecLen(%d)\n",scannerCodes);
  fprintf(fd,"%%%%SET smEOTCODEvecTyp(%d)\n",type);
  size+=type*scannerCodes;
  fprintf(fd,"%%%%BEGIN(smUNKNOWNCODEvec)\n");
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
      if(rule->ast==astUNKNOWN) table[scanner->code]=rule->code;
  type=writeVector(fd,table,scannerCodes);
  fprintf(fd,"%%%%END(smUNKNOWNCODEvec)\n");
  fprintf(fd,"%%%%SET smUNKNOWNCODEvecLen(%d)\n",scannerCodes);
  fprintf(fd,"%%%%SET smUNKNOWNCODEvecTyp(%d)\n",type);
  size+=type*scannerCodes;
  free((char *)table);
  return size;
}

static int writeMap(fd)
     FILE *fd;
{
  int *table;
  int n;
  int type;
  int size;

  fprintf(fd,"%%%%SET smMAP(1)\n");
  table=(int *)smalloc(sizeof(int)*256);
  size=0;
  memset((char *)table,0,sizeof(int)*256);
  for(n=0;n<256;n++)
    table[setTable[n]]=setTable[mapTable[n]];
  fprintf(fd,"%%%%BEGIN(smMAPvec)\n");
  type=writeVector(fd,table,256);
  fprintf(fd,"%%%%END(smMAPvec)\n");
  fprintf(fd,"%%%%SET smMAPvecLen(%d)\n",256);
  fprintf(fd,"%%%%SET smMAPvecTyp(%d)\n",type);
  size+=type*256;
  free((char *)table);
  if(mapSkip>=0) fprintf(fd,"%%%%SET smMAPskip(%d)\n",mapSkip);

  return size;
}

static int writeLookahead(fd)
     FILE *fd;
{
  int *table;
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;
  int type;
  int size;

  fprintf(fd,"%%%%SET smLOOKAHEAD(1)\n");
  table=(int *)smalloc((unsigned int)(sizeof(int)*ruleCodes));
  size=0;
  /*
   * Lookahead type (0=no lookahead, 1=fix prefix, 2=fix suffix, 3=variable)
   */
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if (rule->type != ruleUNDEF) {
	  if(rule->lookahead)
	    if(rule->lookahead->lengthPrefix>0)
	      table[rule->code]=1;
	    else if(rule->lookahead->lengthSuffix>0)
	      table[rule->code]=2;
	    else 
	      table[rule->code]=3;
	  else
	    table[rule->code]=0;
	}
  fprintf(fd,"%%%%BEGIN(smLOOKAHEADtypeVec)\n");
  type=writeVector(fd,table,ruleCodes);
  fprintf(fd,"%%%%END(smLOOKAHEADtypeVec)\n");
  fprintf(fd,"%%%%SET smLOOKAHEADtypeVecLen(%d)\n",ruleCodes);
  fprintf(fd,"%%%%SET smLOOKAHEADtypeVecTyp(%d)\n",type);
  size+=type*ruleCodes;
  /*
   * Lookahead prefix dfa/length
   */
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if (rule->type != ruleUNDEF) {
	  if(rule->lookahead==NULL)
	    table[rule->code]=0;
	  else if(rule->lookahead->dfaPrefix)
	    table[rule->code]=rule->lookahead->dfaPrefix->node;
	  else if(rule->lookahead->lengthPrefix>0)
	    table[rule->code]=rule->lookahead->lengthPrefix;
	  else
	    table[rule->code]=0;
	}
  fprintf(fd,"%%%%BEGIN(smLOOKAHEADprefixVec)\n");
  type=writeVector(fd,table,ruleCodes);
  fprintf(fd,"%%%%END(smLOOKAHEADprefixVec)\n");
  fprintf(fd,"%%%%SET smLOOKAHEADprefixVecLen(%d)\n",ruleCodes);
  fprintf(fd,"%%%%SET smLOOKAHEADprefixVecTyp(%d)\n",type);
  size+=type*ruleCodes;
  /*
   * Lookahead suffix dfa/length
   */
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if (rule->type != ruleUNDEF) {
	  if(rule->lookahead==NULL)
	    table[rule->code]=0;
	  else if(rule->lookahead->dfaSuffix)
	    table[rule->code]=rule->lookahead->dfaSuffix->node;
	  else if(rule->lookahead->lengthSuffix>0)
	    table[rule->code]=rule->lookahead->lengthSuffix;
	  else
	    table[rule->code]=0;
	}
  fprintf(fd,"%%%%BEGIN(smLOOKAHEADsuffixVec)\n");
  type=writeVector(fd,table,ruleCodes);
  fprintf(fd,"%%%%END(smLOOKAHEADsuffixVec)\n");
  fprintf(fd,"%%%%SET smLOOKAHEADsuffixVecLen(%d)\n",ruleCodes);
  fprintf(fd,"%%%%SET smLOOKAHEADsuffixVecTyp(%d)\n",type);
  size+=type*ruleCodes;
  free((char *)table);
  return size;
}

static int writeScreening(fd)
     FILE *fd;
{
  int type;
  int size;

  fprintf(fd,"%%%%SET smSCREEN(1)\n");

  size=0;
  fprintf(fd,"%%%%BEGIN(smSCREENcheckScan)\n");
  type=writeVector(fd,screenCheckScan,screenCheckScanSize);
  fprintf(fd,"%%%%END(smSCREENcheckScan)\n");
  fprintf(fd,"%%%%SET smSCREENcheckScanLen(%d)\n",screenCheckScanSize);
  fprintf(fd,"%%%%SET smSCREENcheckScanTyp(%d)\n",type);
  size+=type*screenCheckScanSize;

  fprintf(fd,"%%%%BEGIN(smSCREENcheckCode)\n");
  type=writeVector(fd,screenCheckCode,screenCheckCodeSize);
  fprintf(fd,"%%%%END(smSCREENcheckCode)\n");
  fprintf(fd,"%%%%SET smSCREENcheckCodeLen(%d)\n",screenCheckCodeSize);
  fprintf(fd,"%%%%SET smSCREENcheckCodeTyp(%d)\n",type);
  size+=type*screenCheckCodeSize;

  fprintf(fd,"%%%%BEGIN(smSCREENcheckCodeScan)\n");
  type=writeVector(fd,screenCheckCodeScan,screenCheckCodeSize);
  fprintf(fd,"%%%%END(smSCREENcheckCodeScan)\n");
  fprintf(fd,"%%%%SET smSCREENcheckCodeScanLen(%d)\n",screenCheckCodeSize);
  fprintf(fd,"%%%%SET smSCREENcheckCodeScanTyp(%d)\n",type);
  size+=type*screenCheckCodeSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtableBegin)\n");
  type=writeVector(fd,screenTableBegin,screenTableSize);
  fprintf(fd,"%%%%END(smSCREENtableBegin)\n");
  fprintf(fd,"%%%%SET smSCREENtableBeginLen(%d)\n",screenTableSize);
  fprintf(fd,"%%%%SET smSCREENtableBeginTyp(%d)\n",type);
  size+=type*screenTableSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtableEnd)\n");
  type=writeVector(fd,screenTableEnd,screenTableSize);
  fprintf(fd,"%%%%END(smSCREENtableEnd)\n");
  fprintf(fd,"%%%%SET smSCREENtableEndLen(%d)\n",screenTableSize);
  fprintf(fd,"%%%%SET smSCREENtableEndTyp(%d)\n",type);
  size+=type*screenTableSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtokenLength)\n");
  type=writeVector(fd,screenTokenLength,screenTokenSize);
  fprintf(fd,"%%%%END(smSCREENtokenLength)\n");
  fprintf(fd,"%%%%SET smSCREENtokenLengthLen(%d)\n",screenTokenSize);
  fprintf(fd,"%%%%SET smSCREENtokenLengthTyp(%d)\n",type);
  size+=type*screenTokenSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtokenStart)\n");
  type=writeVector(fd,screenTokenStart,screenTokenSize);
  fprintf(fd,"%%%%END(smSCREENtokenStart)\n");
  fprintf(fd,"%%%%SET smSCREENtokenStartLen(%d)\n",screenTokenSize);
  fprintf(fd,"%%%%SET smSCREENtokenStartTyp(%d)\n",type);
  size+=type*screenTokenSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtokenCode)\n");
  type=writeVector(fd,screenTokenCode,screenTokenSize);
  fprintf(fd,"%%%%END(smSCREENtokenCode)\n");
  fprintf(fd,"%%%%SET smSCREENtokenCodeLen(%d)\n",screenTokenSize);
  fprintf(fd,"%%%%SET smSCREENtokenCodeTyp(%d)\n",type);
  size+=type*screenTokenSize;

  fprintf(fd,"%%%%BEGIN(smSCREENcheckToken)\n");
  {
    int i;
    fprintf(fd,"{");
    for(i=0;i<screenTokenSize;i++) fprintf(fd,i>0 ? (i%16==15 ? ",1\n" : ",1") : (i%16==15 ? "1\n" : "1"));
    fprintf(fd,"}\n");
    type=1;
  }
  fprintf(fd,"%%%%END(smSCREENcheckToken)\n");
  fprintf(fd,"%%%%SET smSCREENcheckTokenLen(%d)\n",screenTokenSize);
  fprintf(fd,"%%%%SET smSCREENcheckTokenTyp(%d)\n",type);
  size+=type*screenTokenSize;

  fprintf(fd,"%%%%BEGIN(smSCREENtokens)\n");
  type=writeVector(fd,screenTokens,screenTokensPackedSize);
  fprintf(fd,"%%%%END(smSCREENtokens)\n");
  fprintf(fd,"%%%%SET smSCREENtokensLen(%d)\n",screenTokensPackedSize);
  fprintf(fd,"%%%%SET smSCREENtokensTyp(%d)\n",type);
  size+=type*screenTokensPackedSize;
  
  return size;
}

static void writeVoc(fd)
     FILE *fd;
{
  Vocabulary vocabulary;
  Scanner scanner;
  Token token;
  char *target;
  
  target = getStrOpt(SMKTARGET_OPT);
  if ((strcmp(target, "c") == 0) ||
      (strcmp(target, "ansi-c") == 0) ||
      (strcmp(target, "c++") == 0)) {
    fprintf(fd,"%%%%BEGIN(smVOCABULARY)\n");
    fprintf(fd,"typedef enum %%%%(smkPrefix)ScScanner {\n");    
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
      for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
	fprintf(fd,"\t%%%%(smkPrefix)_%s_%s_Scanner = %d",
		vocabulary->name,scanner->name,scanner->code);
	if(vocabulary->next || scanner->next) fprintf(fd,",\n"); else fprintf(fd,"\n");
      }
    fprintf(fd,"} %%%%(smkPrefix)ScScanner;\n\n");
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next) {
      fprintf(fd,"typedef enum %%%%(smkPrefix)_%s_ScToken {\n",vocabulary->name);
      for(token=vocabulary->tokens;token;token=token->next) {
	if(token->name[0]=='"' || token->name[0]=='\'')
	  if(token->code<0) {
	    char* c;
	    fprintf(fd,"\t%%%%(smkPrefix)_%s_c",vocabulary->name);
	    for(c=token->name;*c;c++)
	      fprintf(fd,(*c>='0' && *c<='9') || (*c>='A' && *c<='Z') || (*c>='a' && *c<='z') ? "%c" : "%X",*c);
	    fprintf(fd,"_Token = %d",token->code);
	  }
	  else
	    fprintf(fd,"\t%%%%(smkPrefix)_%s_%d_Token = %d",
		    vocabulary->name,token->code,token->code);
	else
	  fprintf(fd,"\t%%%%(smkPrefix)_%s_%s_Token = %d",
		  vocabulary->name,token->name,token->code);
	if(token->next) fprintf(fd,",\n"); else fprintf(fd,"\n");
      }
      fprintf(fd,"} %%%%(smkPrefix)_%s_ScToken;\n\n",vocabulary->name);
    }
    fprintf(fd,"%%%%END(smVOCABULARY)\n");
  }
  else {
    fprintf(fd,"%%%%BEGIN(smVOCABULARY)\n");
    fprintf(fd,"typedef enum %%%%(smkPrefix)ScScanner {\n");    
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
      for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
	fprintf(fd,"\t%%%%(smkPrefix)_%s_%s_Scanner = %d",
		vocabulary->name,scanner->name,scanner->code);
	if(vocabulary->next || scanner->next) fprintf(fd,",\n"); else fprintf(fd,"\n");
      }
    fprintf(fd,"} %%%%(smkPrefix)ScScanner;\n\n");
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next) {
      fprintf(fd,"typedef enum %%%%(smkPrefix)_%s_ScToken {\n",vocabulary->name);
      for(token=vocabulary->tokens;token;token=token->next) {
	if(token->name[0]=='"' || token->name[0]=='\'')
	  fprintf(fd,"\t%%%%(smkPrefix)_%s_%d_Token = %d",
		  vocabulary->name,token->code,token->code);
	else
	  fprintf(fd,"\t%%%%(smkPrefix)_%s_%s_Token = %d",
		  vocabulary->name,token->name,token->code);
	if(token->next) fprintf(fd,",\n"); else fprintf(fd,"\n");
      }
      fprintf(fd,"} %%%%(smkPrefix)_%s_ScToken;\n\n",vocabulary->name);
    }
    fprintf(fd,"%%%%END(smVOCABULARY)\n");
  }
}

static void writeDebug(fd)
     FILE *fd;
{
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;
  unsigned char *ch1;
  unsigned char *ch2;
  char **table;
  int index;
  char *target;

  table=(char **)smalloc(sizeof(char *)*ruleCodes);
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next)
	if (rule->type != ruleUNDEF)
	  table[rule->code]=(char *)(rule->token->name);
  target = getStrOpt(SMKTARGET_OPT);
  if ((strcmp(target, "c") == 0) ||
      (strcmp(target, "ansi-c") == 0) ||
      (strcmp(target, "c++") == 0)) {
    fprintf(fd,"%%%%BEGIN(smDEBUG)\n");
    fprintf(fd,"static char *smDebugTokens[%d]={\n",ruleCodes);
    
    ch1=0;
    for(index=0;index<ruleCodes;) {
      if(table[index]==NULL) 
	fprintf(fd,"<UNDEFINED>");
      else {
	fprintf(fd,"\t\"");
	for(ch1=ch2=(unsigned char *)table[index];(ch2=(unsigned char *)strpbrk((char *)ch2,"\"\\`%"));ch1=ch2,ch2++) {
	  fwrite((char *)ch1,1,ch2-ch1,fd);
	  if(*ch2=='"' || *ch2=='\\')
	    fwrite("\\",1,1,fd);
	  else
	    fwrite("`",1,1,fd);
	}
      }
      index++;
      fprintf(fd,index < ruleCodes ? "%s\",\n" : "%s\"};\n",ch1);
    }
    fprintf(fd,"static char *smDebugScanners[%d]={\n",scannerCodes+1);
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
      for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
	fprintf(fd,"\t\"%s::%s\",",vocabulary->name,scanner->name);
    fprintf(fd,"\"\"};\n%%%%END(smDEBUG)\n");
  }
  else {
    fprintf(fd,"%%%%BEGIN(smDEBUG)\n");
    fprintf(fd,"static char *smDebugTokens[%d]={\n",ruleCodes);
    
    ch1=0;
    for(index=0;index<ruleCodes;) {
      if(table[index]==NULL) 
	fprintf(fd,"<UNDEFINED>");
      else {
	fprintf(fd,"\t\"");
	for(ch1=ch2=(unsigned char *)table[index];(ch2=(unsigned char *)strpbrk((char *)ch2,"\"\\`%"));ch1=ch2,ch2++) {
	  fwrite((char *)ch1,1,ch2-ch1,fd);
	  if(*ch2=='"' || *ch2=='\\')
	    fwrite("\\",1,1,fd);
	  else
	    fwrite("`",1,1,fd);
	}
      }
      index++;
      fprintf(fd,index < ruleCodes ? "%s\",\n" : "%s\"};\n",ch1);
    }
    fprintf(fd,"static char *smDebugScanners[%d]={\n",scannerCodes+1);
    for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
      for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
	fprintf(fd,"\t\"%s::%s\",",vocabulary->name,scanner->name);
    fprintf(fd,"\"\"};\n%%%%END(smDEBUG)\n");
  }
  free((char *)table);
}
