/*----------------------------------------------------------------------*\

	lmkScan.c

	ScannerMaker generated scanner

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include "lmk_i.h"

/* END %%IMPORT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmkScan.h"

/* Local imports */
extern int lmkScReader( lmkScContext smThis, unsigned char *smBuffer, unsigned int smLength );
extern int lmkScPreHook( lmkScContext smThis, LmkToken *smToken );
extern int lmkScAction( lmkScContext smThis, int smInternalCode, LmkToken *smToken );

/* System dependencies */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;


/* START of scanning tables */


/*
 * MAP
 *
 * [character] -> character
 *
 */

static UByte1 smMap[256]={
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79
,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95
,96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79
,80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127
,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143
,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159
,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175
,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191
,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207
,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223
,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207
,208,209,210,211,212,213,214,247,216,217,218,219,220,221,222,255
}
;


/*
 * SCANNER
 *
 * [scanner] -> state
 */

static UByte1 smScanner[1]={
0
}
;

/*
 * ACCEPT (internal token code)
 *
 * [state] -> icode
 */

static UByte1 smAccept[51]={
0,13,5,1,4,6,12,2,7,11,8,3,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0
}
;

/*
 * EXTERNAL TOKEN CODE
 *
 * [icode] -> ecode
 */

static UByte1 smTokenCode[13]={
3,6,9,8,4,5,7,7,1,2,0,0,0
}
;

/*
 * EOT and Unknown
 *
 * [scanner] -> icode
 *
 */

static UByte1 smEOTCode[1]={
9
}
;
static UByte1 smUnknownCode[1]={
8
}
;

/*
 * DFA
 */

static UByte2 smDFArow[51]={
0,25,50,75,100,75,125,75,75,75,75,75,150,175,200,225
,250,275,300,325,350,375,400,425,450,475,500,525,550,575,600,625
,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1025
,1050,1075,1100
}
;
static UByte1 smDFAcol[256]={
0,0,0,0,0,0,0,0,0,1,2,0,0,1,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,1,0,0,0,0,3,0,4,0,0,0,0,0,5,0,0
,6,6,6,6,6,6,6,6,6,6,0,7,0,0,0,0
,0,8,9,10,11,12,9,13,9,14,9,15,9,16,17,18
,19,9,20,21,22,9,9,9,9,9,9,0,23,0,0,24
,0,8,9,10,11,12,9,13,9,14,9,15,9,16,17,18
,19,9,20,21,22,9,9,9,9,9,9,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,0,9,9,9,9,9,9,9,0
,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9
,9,9,9,9,9,9,9,0,9,9,9,9,9,9,9,0
}
;
  
static UByte1 smDFAval[1125]={
51,1,1,12,13,14,2,3,4,4,4,4,4,4,4,4
,4,4,4,4,4,4,4,51,51,
51,1,1,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,2,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,4,51,4,4,4,4,4,4,4,4
,4,4,4,4,4,4,4,51,17,
6,6,51,6,6,6,6,6,6,6,6,6,6,6,6,6
,6,6,6,6,6,6,6,6,6,
51,51,51,15,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
13,13,51,13,5,13,13,13,13,13,13,13,13,13,13,13
,13,13,13,13,13,13,13,16,13,
51,51,51,51,51,6,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,18,51,19,51,20,51
,21,51,22,51,51,23,40,51,51,
13,13,51,13,13,13,13,13,13,13,13,13,13,13,13,13
,13,13,13,13,13,13,13,13,13,
51,51,51,51,51,51,4,51,4,4,4,4,4,4,4,4
,4,4,4,4,4,4,4,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,42,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,24,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,25,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,26,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,27,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,28,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,7,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,46,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,45,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,30,51,51,
51,51,51,51,51,51,51,51,51,51,31,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,43
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,50,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,8,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,41,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,36,51,51,51,51,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,8,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,8,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,49,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,51,9,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,10,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,11,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,29,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,37,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,48,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,34,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,35,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,51,51,51,33,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,44,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,38,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,32,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,39,51,51,51
,51,51,51,51,51,51,51,51,51,
51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51
,51,51,47,51,51,51,51,51,51
}
;
  


/* END of scanning tables */






/*
 * Source position calculation 
 */

static void smSourcePosition(
     lmkScContext smThis,
     unsigned char *smAt,
     unsigned char *smEnd)
{
  if(smThis->smPosContinue<smEnd) {
    if(smThis->smPosContinue>smAt) smAt=smThis->smPosContinue;
    smThis->smNextPosition+=smEnd-smAt;
    for(;smAt<smEnd;smAt++) 
      if(*smAt==10) {
	smThis->smPosLine=smAt;
	smThis->smNextLine++;
      }

    smThis->smNextColumn=smEnd-smThis->smPosLine;
    smThis->smPosContinue=smEnd;
  }
}

static void smRewindSourcePosition(
     lmkScContext smThis,
     unsigned char *smAt,
     unsigned char *smEnd)
{
  if(smThis->smPosContinue>smEnd) return;
  smThis->smNextPosition-=smEnd-smAt;
  while(smAt<smEnd--) if(*smEnd==10) smThis->smNextLine--;
  while(smThis->smBegining<smEnd) 
    if(*smEnd==10) {
      smThis->smPosLine=smEnd;
      break; 
    }
    else smEnd--;
  if(smAt<smThis->smPosLine) smThis->smPosLine=smThis->smPosPrevLine;
  smThis->smNextColumn=smAt-smThis->smPosLine;
  smThis->smPosContinue=smAt;
}


/*
 * int smReadBuffer(SMContext smThis)
 *
 * SmThis function reads charcters using the reader into the buffer in a
 * context. The buffer is enlarged if the current buffer is full
 * (smEnd-smText==smSize) or reduced if current buffer is larger than
 * the standard buffer size and the token may fit the standard buffer
 * (smEnd-smText<smTokenSize AND smSize>smTokenSize). The function
 * returns the number of characters read into the buffer.
 *
 */

static int smReadBuffer(lmkScContext smThis)
{
  long length;
  int size;
  long mod;

  if(smThis->smBegining!=smThis->smText) {
    /* Move data to beginning of buffer */
    length=smThis->smEnd-smThis->smText;
    memcpy((void *)smThis->smBegining,(void *)smThis->smText,(size_t)length);
    if(length<1024 && smThis->smSize>1024) {
      /* Reduce buffer size */
      smThis->smSize=1024;
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,(size_t)1024+1);
    }
  }
  else if(smThis->smBegining+smThis->smSize==smThis->smEnd) {
    /* Try to enlarge buffer */
    if(smThis->smSize==524288) {
      /* Cut Buffer */
      smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
      memcpy((void *)smThis->smBegining,(void *)(smThis->smEnd-1024),(size_t)1024);
      mod=smThis->smEnd-smThis->smBegining-1024;
      smThis->smContinue-=mod;
      smThis->smEnd-=mod;
      smThis->smPosPrevLine-=mod;
      smThis->smPosLine-=mod;
      smThis->smPosContinue-=mod;
      smThis->smBufferOverflow+=mod;
    }
    else {
      unsigned char *begining = smThis->smBegining;
      size=smThis->smSize*1.5;
      if(size>524288) size=524288;
      /* Enlarge buffer */
      smThis->smBegining=(unsigned char *)realloc(smThis->smBegining,(size_t)size+1);
      if(smThis->smBegining==NULL) {
	/* Cut Buffer */
	smThis->smBegining = begining;	/* Restore to original buffer */
	smSourcePosition(smThis,smThis->smText,smThis->smEnd-1024);
	memcpy((void *)smThis->smBegining, (void *)(smThis->smEnd-1024), (size_t)1024);
	mod=smThis->smEnd-smThis->smBegining-1024;
	smThis->smContinue-=mod;
	smThis->smEnd-=mod;
	smThis->smPosPrevLine-=mod;
	smThis->smPosLine-=mod;
	smThis->smPosContinue-=mod;
        smThis->smBufferOverflow+=mod;
      }
      else
	smThis->smSize=size;
    }
  }
  if(smThis->smBegining!=smThis->smText) {
    mod=smThis->smText-smThis->smBegining;
    smThis->smContinue-=mod;
    smThis->smEnd-=mod;
    smThis->smPosPrevLine-=mod;
    smThis->smPosLine-=mod;
    smThis->smPosContinue-=mod;
    smThis->smText-=mod;
  }
  length=smThis->smSize-(smThis->smEnd-smThis->smBegining);
  length=lmkScReader(smThis,smThis->smEnd,(unsigned int)length);
  if(length<0) return length;
  smThis->smEnd+=length;
  return length;
}

/*
 * SMContext SMNew( lmkScScanner scanner )
 *
 * Create a new context.
 *
 */

lmkScContext lmkScNew(lmkScScanner smScanner)
{
  lmkScContext smThis;

  smThis=(lmkScContext)malloc((size_t)sizeof(lmkScContextItem));
  if(smThis==NULL) {
    return NULL;
  }
  smThis->smBegining=(unsigned char *)malloc((size_t)1024+1);
  if(smThis->smBegining==NULL) {
    free((char *)smThis);
    return NULL;
  }
  smThis->smSize=1024;
  smThis->smContinue=smThis->smBegining;
  smThis->smEnd=smThis->smBegining;
  smThis->smPosPrevLine=smThis->smBegining-1;
  smThis->smPosLine=smThis->smBegining-1;
  smThis->smPosContinue=smThis->smBegining;
  smThis->smText=smThis->smBegining;
  
  smThis->smLength=0;
  smThis->smNextLine=1;
  smThis->smNextColumn=1;
  smThis->smNextPosition=0;
  smThis->smLine=1;
  smThis->smColumn=1;
  smThis->smPosition=0;
  smThis->smScanner=smScanner;
  smThis->smBegining[0]=0;
  return smThis;
}

/*
 * void SMDelete( SMContext smThis )
 *
 * Destroy a context and associated buffer.
 *
 */

void lmkScDelete(lmkScContext smThis)
{
  free((char *)smThis->smBegining);
  free((char *)smThis);
}

/*
 * int SMSkip( SMContext smThis, int smLength )
 *
 * Enlarge/reduce the current token in a context with length characters.
 * If length is less than zero reduce the token, if length is greater
 * than zero enlarge the token.
 *
 */

int lmkScSkip(
     lmkScContext smThis,
     int smLength)
{
  int empty;

  if(smLength>0) {
    empty=smThis->smEnd-smThis->smContinue;
    if(empty<smLength) {
      empty=smReadBuffer(smThis);
      if(empty<0) return empty;
      empty=smThis->smEnd-smThis->smContinue;
      if(empty<smLength) smLength=empty;
    }
    smSourcePosition(smThis,smThis->smContinue,smThis->smContinue+smLength);
    smThis->smContinue+=smLength;
    smThis->smLength+=smLength;
  }
  else if(smLength<0) {
    smLength= -smLength;
    if(smLength>smThis->smLength) smLength=smThis->smLength;
    smRewindSourcePosition(smThis,smThis->smContinue-smLength,smThis->smContinue);
    smThis->smContinue-=smLength;
    smThis->smLength-=smLength;
    }
  return smLength;
}

int lmkScModify(
     lmkScContext smThis,
     unsigned char *smBuffer,
     int smLength)
{
  if(smLength<0) {
/* This code is identical to smSkip but no source position is rewinded */
    smLength= -smLength;
    if(smLength>smThis->smLength) smLength=smThis->smLength;
    smThis->smContinue-=smLength;
    smThis->smLength-=smLength;
/***********************************************************************/
    memcpy((void *)smThis->smContinue,(void *)smBuffer,(size_t)smLength);
    return smLength;
  }
  else if(smLength>0) {
    int length1;
    int length2;
    
    for(length2=smLength;(length1=lmkScSkip(smThis,length2));length2-=length1) {
      if(length1<0) return length1;
      memcpy((void *)(smThis->smContinue-length1),(void *)smBuffer,(size_t)length1);
      smBuffer+=length1;
    }
    return smLength-length2;
  }
  return smLength;
}

int lmkScCopy(
     lmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smFrom,
     unsigned int smTo)
{
  if(smFrom>smThis->smLength) smFrom=smThis->smLength;
  if(smTo>smThis->smLength) smTo=smThis->smLength;
  memcpy((void *)smBuffer,(void *)(smThis->smText+smFrom),(size_t)smTo-smFrom);
  return smTo-smFrom;
}

int lmkScMapCopy(
     lmkScContext smThis,
     unsigned char *smBuffer,
     unsigned int smFrom,
     unsigned int smTo)
{
  int n;
  int len;
  unsigned char *at;

  if(smFrom>smThis->smLength) smFrom=smThis->smLength;
  if(smTo>smThis->smLength) smTo=smThis->smLength;
  len=0;
  for(n=smFrom,at=smThis->smText+smFrom;n<smTo;n++) {
*smBuffer++=smMap[*at++];
    len++;
  }
  return len;
}

void lmkScScrScanner(
     lmkScScanner smScanner,
     int smOnOff)
{
}

void lmkScScrToken(
     lmkScScanner smScanner,
     int smCode,
     int smOnOff)
{
}

void lmkScScrRule(
     lmkScScanner smScanner,
     int smCode,
     int smOnOff)
{
}

int lmkScan(
     lmkScContext smThis,
     LmkToken *smToken)
{
  unsigned char *at;
  unsigned char *end;
  unsigned char *rew_at;
  unsigned char ch;
  int state;
  int rew_state;
  int code;

  do {				/* Skip loop */
    smThis->smLine=smThis->smNextLine;
    smThis->smColumn=smThis->smNextColumn;
    smThis->smPosition=smThis->smNextPosition;
    lmkScPreHook(smThis,smToken);
    end=(smThis->smEnd);
    smThis->smText=smThis->smContinue;
    smThis->smBufferOverflow=0;
    smToken->srcp.line=smThis->smNextLine;
    smToken->srcp.col=smThis->smNextColumn;
    smThis->smPosPrevLine=smThis->smPosLine;
    rew_at=smThis->smText;
    do {			/* Continue loop */
      rew_state=51;
      rew_at++;
      at=(smThis->smContinue);
      state=smScanner[smThis->smScanner];
      for (;;) {
	if(at==end) {
	  int mod;
	  
	  if(state>=51) state-=51+1;
	  smThis->smContinue=end;
	  mod=smReadBuffer(smThis);
	  if(mod<0) return mod;
	  rew_at-=end-smThis->smContinue;
	  at=smThis->smContinue;
	  end=smThis->smEnd;
          if(at==end) 
	    break;
        }
	  ch = *at++;
{

  
    
      
  state=smDFAval[smDFArow[state]+smDFAcol[ch]];
      
    
  
}
	  if(state>=51) break;
	  if(smAccept[state]>0) {
	    rew_state=state;
	    rew_at=at;
	  }
      }
      if(rew_state==51) {
        if(rew_at>end) {
  	  code=smEOTCode[smThis->smScanner];
	  rew_at=end;
        }
        else
	  code=smUnknownCode[smThis->smScanner];
      }	
      else
	code=smAccept[rew_state]-1;	
      smThis->smContinue=rew_at;
      smThis->smLength=smThis->smContinue-smThis->smText;
      smSourcePosition(smThis,smThis->smText,smThis->smContinue);
      smToken->code=smTokenCode[code]-1;
      code=lmkScAction(smThis,code,smToken);
    } while(code<-1);
  } while(code<0);
  return smToken->code=code;
}
