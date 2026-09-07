#ifndef _tmkScan_h_
#define _tmkScan_h_

#include "tmkCommon.h"

typedef enum tmkScScanner {
	tmk_MAIN_MAIN_Scanner = 0
} tmkScScanner;

typedef enum tmk_MAIN_ScToken {
	tmk_MAIN_UNKNOWN_Token = 0,
	tmk_MAIN_ENDOFTEXT_Token = 1,
	tmk_MAIN_2_Token = 2,
	tmk_MAIN_3_Token = 3,
	tmk_MAIN_4_Token = 4,
	tmk_MAIN_5_Token = 5,
	tmk_MAIN_6_Token = 6,
	tmk_MAIN_NUMBER_Token = 7,
	tmk_MAIN_STRING_Token = 8,
	tmk_MAIN_9_Token = 9,
	tmk_MAIN_10_Token = 10,
	tmk_MAIN_11_Token = 11,
	tmk_MAIN_12_Token = 12,
	tmk_MAIN_13_Token = 13,
	tmk_MAIN_14_Token = 14,
	tmk_MAIN_15_Token = 15,
	tmk_MAIN_16_Token = 16,
	tmk_MAIN_17_Token = 17,
	tmk_MAIN_18_Token = 18,
	tmk_MAIN_SKIPHEADER_Token = 19,
	tmk_MAIN_IDENTIFIER_Token = 20,
	tmk_MAIN_21_Token = 21,
	tmk_MAIN_22_Token = 22,
	tmk_MAIN_COMMENT_Token = -1,
	tmk_MAIN_BLANK_Token = -1
} tmk_MAIN_ScToken;


typedef struct tmkScContextItem *tmkScContext;

extern tmkScContext tmkScNew( tmkScScanner smScanner );
extern void tmkScDelete( tmkScContext smThis );
extern int tmkScSkip( tmkScContext smThis, int smLength );
extern int tmkScModify( tmkScContext smThis, unsigned char *smBuffer, int smLength );
extern int tmkScCopy( tmkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern int tmkScMapCopy( tmkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern void tmkScScrScanner( tmkScScanner scanner, int smOnOff );
extern void tmkScScrToken( tmkScScanner scanner, int smCode, int smOnOff );
extern void tmkScScrRule( tmkScScanner scanner, int smCode, int smOnOff );
extern int tmkScan( tmkScContext smThis, TmkToken *smToken );


typedef struct tmkScContextItem {

/* Private */

  unsigned char *smBegining;
  unsigned char *smContinue;
  unsigned char *smEnd;
  unsigned char *smPosPrevLine;
  unsigned char *smPosLine;
  unsigned char *smPosContinue;

/* Public */

  int smSize;

  int smBufferOverflow;
  int smLength;
  unsigned char *smText;

  int smLine;
  int smColumn;
  int smPosition;
  int smNextLine;
  int smNextColumn;
  int smNextPosition;

  tmkScScanner smScanner;



  char *fileName;
  int fd;



} tmkScContextItem;

#endif
