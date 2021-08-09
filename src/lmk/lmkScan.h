#ifndef _lmkScan_h_
#define _lmkScan_h_

#include "lmkCommon.h"

typedef enum lmkScScanner {
    lmk_MAIN_MAIN_Scanner = 0
} lmkScScanner;

typedef enum lmk_MAIN_ScToken {
    lmk_MAIN_UNKNOWN_Token = 0,
    lmk_MAIN_ENDOFTEXT_Token = 1,
    lmk_MAIN_2_Token = 2,
    lmk_MAIN_NUMBER_Token = 3,
    lmk_MAIN_STRING_Token = 4,
    lmk_MAIN_5_Token = 5,
    lmk_MAIN_SKIPHEADER_Token = 6,
    lmk_MAIN_IDENTIFIER_Token = 7,
    lmk_MAIN_8_Token = 8,
    lmk_MAIN_COMMENT_Token = -1,
    lmk_MAIN_BLANK_Token = -1
} lmk_MAIN_ScToken;


typedef struct lmkScContextItem *lmkScContext;

extern lmkScContext lmkScNew( lmkScScanner smScanner );
extern void lmkScDelete( lmkScContext smThis );
extern int lmkScSkip( lmkScContext smThis, int smLength );
extern int lmkScModify( lmkScContext smThis, unsigned char *smBuffer, int smLength );
extern int lmkScCopy( lmkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern int lmkScMapCopy( lmkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern void lmkScScrScanner( lmkScScanner scanner, int smOnOff );
extern void lmkScScrToken( lmkScScanner scanner, int smCode, int smOnOff );
extern void lmkScScrRule( lmkScScanner scanner, int smCode, int smOnOff );
extern int lmkScan( lmkScContext smThis, LmkToken *smToken );


typedef struct lmkScContextItem {

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

  lmkScScanner smScanner;



  char *fileName;
  int fd;



} lmkScContextItem;

#endif
