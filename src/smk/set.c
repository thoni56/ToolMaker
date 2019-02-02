/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1990-06-25
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/set.c,v 1.1 2002/06/25 20:04:51 Thomas Nilsson Exp $
 *
 * $Log: set.c,v $
 * Revision 1.1  2002/06/25 20:04:51  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.8  1997/01/22 16:27:40  gunilla
 * Added string.h
 *
 * Revision 1.7  1994/01/05 16:06:02  thoni
 * Inverted the MAC and PC character sets (that is how they are supposed
 * to work!)
 *
 * Revision 1.6  1993/12/09  13:48:06  thoni
 * Added predefined character sets PC & MAC
 * Fixed bug preventing -set to be used from command line
 *
 * Revision 1.5  1993/06/04  12:52:27  tools
 * Changed back xScScan to xScan
 *
 * Revision 1.4  1993/04/30  12:33:24  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.3  1993/04/27  14:21:54  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.2  1993/04/23  11:13:47  tools
 * Updated to handle new generated scanner
 *
 * Revision 1.1  1993/03/24  09:24:49  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.6  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.5  91/07/30  11:46:51  tools
 * Change the name of ISO8859-1 to ISO8859_1
 * 
 * Revision 1.4  1991/07/11  10:38:37  tools
 * Added Inherited scanners and Undefined tokens
 *
 * Revision 1.3  1991/07/10  14:20:01  tools
 * New SET handling
 *
 * Revision 1.2  1991/07/09  07:33:35  tools
 * Fix map bug and added mapping in DFA-table
 *
 * Revision 1.1  1991/01/10  13:50:59  tools
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "smk_i.h"
#include "set.h"
#include "char.h"
#include "smkList.h"
#include "lmprintf.h"
#include "smkScan.h"

Set setRoot=NULL;
int setSize=0;

short *setTable;
short setSkip=-1;
short setUsed=0;

Set setPut(Name name)
{
  Set set;
  int c;
  
  set=(Set)malloc(sizeof(SetItem));
  set->name=name;
  for(c=0;c<256;c++) set->code[c]= -1;
  set->next=setRoot;
  setRoot=set;
  return set;
}

Set setGet(Name name)
{
  Set set;

  for(set=setRoot;set;set=set->next)
    if(strcmp(set->name,name)==0) return set;
  return NULL;
}

Set setUse(Name name)
{
  Set set;

  set=setGet(name);
  if(set) {
    setTable=set->code;
    setUsed=1;
  }
  return set;
}

void setDump()
{
  int r;
  int c;
  int ch;

  printf("Set Table\n\n");
  if(setSkip>=0) {
    printf(setSkip<' ' || setSkip>'~' ? "    Skip on %03X\n" : "    Skip on '%c'\n",setSkip);
  }
  for(r=0;r<32;r++) {
    printf("\n    ");
    for(c=0;c<8;c++) {
      ch=r*8+c;
      printf(ch<' ' || ch>'~' ? "  %03X" : "  '%c'",ch);
    }
    printf("\n    ");
    for(c=0;c<8;c++) {
      ch=setTable[r*8+c];
      printf(ch<' ' || ch>'~' ? "  %03X" : "  '%c'",ch);
    }
    printf("\n");
  }
}

void setPrint()
{
  int row;
  int col;
  int ch1;
  int ch2;

  smkSkipLines(getNumOpt(HEIGHT_OPT)-6);
  lmPrintf("Set Table\n");
  if(setSkip>=0) {
    lmPrintf(setSkip<' ' || setSkip>'~' ? "    Skip on %03X\n" : "    Skip on '%c'\n",setSkip);
  }
  lmPrintf("\n        0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
  for(row=0;row<16;row++) {
    lmPrintf("     %X ",row);
    for(col=0;col<16;col++) {
      ch1=(row<<4)+col;
      for(ch2=0;ch2<256 && ch1!=setTable[ch2];ch2++);
      if(ch2==256)
	lmPrintf(" ..");
      else
	lmPrintf(ch2<=' ' || ch2>'~' ? " %02X" : "  %c",ch2);
    }
    lmPrintf("\n");
  }
 lmFlush();
}

void setRead(smkScContext context)
{
  SmkToken token;
  Set set;
  int code;
  int c;
  
  context->smScanner=smk_SET_MAIN_Scanner;
  if(smkScan(context,&token)!=smk_SET_IDENTIFIER_Token)
    smkLog(&token.srcp,247,sevERR,"");
  else {
    if(setGet(token.name))
      smkLog(&token.srcp,248,sevERR,"");
    else {
      set=setPut(token.name);
      for(code=0;code<256;code++) {
	smkScan(context,&token);
	switch(token.code) {
	case smk_SET_UNKNOWN_Token:
	case smk_SET_IDENTIFIER_Token:
	  smkLog(&token.srcp,251,sevWAR,"");
	  break;
	case smk_SET_ENDOFTEXT_Token:
	case smk_SET_EOS_Token:
	  smkLog(&token.srcp,249,sevERR,"");
	  goto exit;
	case smk_SET_NUMBER_Token:
	  c=strtol(token.name,NULL,16);
	  if(set->code[c]<0)
	    set->code[c]=code;
	  else
	    smkLog(&token.srcp,250,sevERR,"");
	  break;
	case smk_SET_UNDEFINED_Token:
	  break;
	case smk_SET_CHARACTER_Token:
	  c=token.name[0];
	  if(set->code[c]<0)
	    set->code[c]=code;
	  else
	    smkLog(&token.srcp,250,sevERR,"");
	  break;
	}
      }
      if(smkScan(context,&token)!=smk_SET_EOS_Token)
	  smkLog(&token.srcp,249,sevERR,"");
    }
  }
  while(token.code!=smk_SET_EOS_Token && token.code!=smk_SET_ENDOFTEXT_Token) smkScan(context,&token);
 exit:
  context->smScanner=smk_MAIN_MAIN_Scanner;
}

void setCheck(Name name, short *code)
{
  int c1;
  int c2;
  char buffer[512];
  
  for(c1=0;c1<256;c1++)
    if(code[c1]<0) continue;
    else for(c2=c1+1;c2<256;c2++)
      if(code[c1]==code[c2]) {
	if(code[c2]<' '||code[c2]>'~')
	  sprintf(buffer,"%02X (%d)%c%s",code[c2],code[c2],smkSEPARATOR,name);
	else
	  sprintf(buffer,"'%c'%c%s",code[c2],smkSEPARATOR,name);
	smkLog(NULL,252,sevERR,buffer);
      }
}

/* ======================================== */

short setISO8859_1[256]={
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15, 
  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31, 
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47, 
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63, 
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79, 
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95, 
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

short setASCII[256]={
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15, 
  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31, 
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47, 
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63, 
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79, 
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95, 
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1};

short setEBCDIC[256]={
   0,   1,   2,   3,  55,  45,  46,  47,  22,   5,  37,  11,  12,  13,  14,  15,
  16,  17,  18,  19,  60,  61,  50,  38,  24,  25,  63,  39,  28,  29,  30,  31,
  64,  79, 127, 123,  91, 108,  80, 125,  77,  93,  92,  78, 107,  96,  75,  97,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 122,  94,  76, 126, 110, 111,
 124, 193, 194, 195, 196, 197, 198, 199, 200, 201, 209, 210, 211, 212, 213, 214,
 215, 216, 217, 226, 227, 228, 229, 230, 231, 232, 233,  74, 224,  90,  95, 109,
 121, 129, 130, 131, 132, 133, 134, 135, 136, 137, 145, 146, 147, 148, 149, 150,
 151, 152, 153, 162, 163, 164, 165, 166, 167, 168, 169, 192, 106, 208, 161,   7,
  32,  33,  34,  35,  36,  21,   6,  23,  40,  41,  42,  43,  44,   9,  10,  27,
  48,  49,  26,  51,  52,  53,  54,   8,  56,  57,  58,  59,   4,  20,  62, 225,
  65,  66,  67,  68,  69,  70,  71,  72,  73,  81,  82,  83,  84,  85,  86,  87,
  88,  89,  98,  99, 100, 101, 102, 103, 104, 105, 112, 113, 114, 115, 116, 117,
 118, 119, 120, 128, 138, 139, 140, 141, 142, 143, 144, 154, 155, 156, 157, 158,
 159, 160, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183,
 184, 185, 186, 187, 188, 189, 190, 191, 202, 203, 204, 205, 206, 207, 218, 219,
 220, 221, 222, 223, 234, 235, 236, 237, 238, 239, 250, 251, 252, 253, 254, 255};

short setIBM[256]={
   0,   1,   2,   3,  55,  45,  46,  47,  22,   5,  37,  11,  12,  13,  14,  15,
  16,  17,  18,  19,  60,  61,  50,  38,  24,  25,  63,  39,  28,  29,  30,  31,
  64,  90, 127, 123,  91, 108,  80, 125,  77,  93,  92,  78, 107,  96,  75,  97,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 122,  94,  76, 126, 110, 111,
 124, 193, 194, 195, 196, 197, 198, 199, 200, 201, 209, 210, 211, 212, 213, 214,
 215, 216, 217, 226, 227, 228, 229, 230, 231, 232, 233, 173, 224, 189,  95, 109,
 121, 129, 130, 131, 132, 133, 134, 135, 136, 137, 145, 146, 147, 148, 149, 150,
 151, 152, 153, 162, 163, 164, 165, 166, 167, 168, 169, 192,  79, 208, 161,   7,
  32,  33,  34,  35,  36,  21,   6,  23,  40,  41,  42,  43,  44,   9,  10,  27,
  48,  49,  26,  51,  52,  53,  54,   8,  56,  57,  58,  59,   4,  20,  62, 225,
  65,  66,  67,  68,  69,  70,  71,  72,  73,  81,  82,  83,  84,  85,  86,  87,
  88,  89,  98,  99, 100, 101, 102, 103, 104, 105, 112, 113, 114, 115, 116, 117,
 118, 119, 120, 128, 138, 139, 140, 141, 142, 143, 144, 154, 155, 156, 157, 158,
 159, 160, 170, 171, 172,  -1, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183,   /* character 173 should be defined here */
 184, 185, 186, 187, 188,  -1, 190, 191, 202, 203, 204, 205, 206, 207, 218, 219,   /* character 189 should be defined here */
 220, 221, 222, 223, 234, 235, 236, 237, 238, 239, 250, 251, 252, 253, 254, 255};

short setPC[256]={
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
0xCA,0xC1,0xA2,0xA3,0xB0,0xB4,0xBA,0xA4,0xAC,0xA9,0xBB,0xC7,0xC2,0xD0,0xA8,0xD1,
0xA1,0xB1,0xAA,0xD5,0xAB,0xB5,0xA6,0xA5,0xD4,0xA0,0xBC,0xC8,0xD9,0xDA,0xDB,0xC0,
0xCB,0xDC,0xD7,0xCC,0x80,0x81,0xAE,0x82,0xC5,0x83,0xB7,0xC9,0xB3,0xB2,0xC3,0xC4,
0xC6,0x84,0xDD,0xDE,0xBD,0xCD,0x85,0xAD,0xAF,0xD3,0xD2,0xDF,0x86,0xCE,0xB8,0xA7,
0x88,0x87,0x89,0x8B,0x8A,0x8C,0xBE,0x8D,0x8F,0x8E,0x90,0x91,0x93,0x92,0x94,0x95,
0xB6,0x96,0x98,0x97,0x99,0x9B,0x9A,0xD6,0xBF,0x9D,0x9C,0x9E,0x9F,0xCF,0xB9,0xD8};

short setMAC[256]={
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
0xFF,0xD0,0x9B,0x9C,0xE5,0x9D,0x9F,0xD1,0xF7,0xE0,0xA6,0xAE,0xFB,0xD2,0xE7,0xFA,
0xF8,0xF1,0xFD,0xD3,0xFE,0xE6,0xE3,0xF9,0xD4,0xD5,0xA7,0xAF,0xAC,0xAB,0xF0,0xA8,
0xA9,0xAA,0xEF,0xD6,0x8E,0x8F,0x92,0x80,0xE2,0x90,0xE4,0xEE,0xF5,0xF4,0xD7,0xAD,
0xE9,0xA5,0xD8,0xD9,0xEA,0xE8,0x99,0xEC,0xED,0xF2,0xF3,0xDA,0x9A,0xDB,0x9E,0xE1,
0x85,0xA0,0x83,0xDC,0x84,0x86,0x91,0x87,0x8A,0x82,0x88,0x89,0x8D,0xA1,0x8C,0x8B,
0xEB,0xA4,0x95,0xA2,0x93,0xDD,0x94,0xF6,0xDE,0x97,0xA3,0x96,0x81,0xDF,0xFC,0x98};


void setInit()
{
  Set set;
  
  set=setPut("ISO8859_1");
  memcpy(set->code,setISO8859_1,sizeof(set->code));
#ifdef SETCHECK
  setCheck("ISO8859_1",set->code);
#endif
  setTable=set->code;

  set=setPut("ASCII");
  memcpy(set->code,setASCII,sizeof(set->code));
#ifdef SETCHECK
  setCheck("ASCII",set->code);
#endif

  set=setPut("EBCDIC");
  memcpy(set->code,setEBCDIC,sizeof(set->code));
#ifdef SETCHECK
  setCheck("EBCDIC",set->code);
#endif

  set=setPut("IBM");
  memcpy(set->code,setIBM,sizeof(set->code));
#ifdef SETCHECK
  setCheck("IBM",set->code);
#endif

  set=setPut("PC");
  memcpy(set->code,setPC,sizeof(set->code));
#ifdef SETCHECK
  setCheck("PC",set->code);
#endif

  set=setPut("MAC");
  memcpy(set->code,setMAC,sizeof(set->code));
#ifdef SETCHECK
  setCheck("MAC",set->code);
#endif
}
