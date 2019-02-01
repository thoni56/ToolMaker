#ifndef _pmkScan_h_
#define _pmkScan_h_

#include "pmkCommon.h"

typedef enum pmkScScanner {
	pmk_MAIN_MAIN_Scanner = 0
} pmkScScanner;

typedef enum pmk_MAIN_ScToken {
	pmk_MAIN_UNKNOWN_Token = 0,
	pmk_MAIN_ENDOFTEXT_Token = 1,
	pmk_MAIN_IDENTIFIER_Token = 2,
	pmk_MAIN_STRING_Token = 3,
	pmk_MAIN_ANG_BRACK_STRING_Token = 4,
	pmk_MAIN_INTEGER_Token = 5,
	pmk_MAIN_6_Token = 6,
	pmk_MAIN_7_Token = 7,
	pmk_MAIN_8_Token = 8,
	pmk_MAIN_9_Token = 9,
	pmk_MAIN_10_Token = 10,
	pmk_MAIN_11_Token = 11,
	pmk_MAIN_12_Token = 12,
	pmk_MAIN_13_Token = 13,
	pmk_MAIN_14_Token = 14,
	pmk_MAIN_15_Token = 15,
	pmk_MAIN_16_Token = 16,
	pmk_MAIN_17_Token = 17,
	pmk_MAIN_18_Token = 18,
	pmk_MAIN_19_Token = 19,
	pmk_MAIN_20_Token = 20,
	pmk_MAIN_21_Token = 21,
	pmk_MAIN_22_Token = 22,
	pmk_MAIN_23_Token = 23,
	pmk_MAIN_24_Token = 24,
	pmk_MAIN_25_Token = 25,
	pmk_MAIN_SKIPHEADER_Token = 26,
	pmk_MAIN_27_Token = 27,
	pmk_MAIN_28_Token = 28,
	pmk_MAIN_29_Token = 29,
	pmk_MAIN_30_Token = 30,
	pmk_MAIN_31_Token = 31,
	pmk_MAIN_32_Token = 32,
	pmk_MAIN_33_Token = 33,
	pmk_MAIN_COMMENT_Token = -1,
	pmk_MAIN_BLANK_Token = -1
} pmk_MAIN_ScToken;


typedef struct pmkScContextItem *pmkScContext;

extern pmkScContext pmkScNew( /* SMVocScanner smScanner */ );
extern void pmkScDelete( /* SMContext smThis */ );
extern int pmkScSkip( /* SMContext smThis, int smLength */ );
extern int pmkScModify( /* SMContext smThis, unsigned char *smBuffer, int smLength */ );
extern int pmkScCopy( /* SMContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo */ );
extern int pmkScMapCopy( /* SMContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo */ );
extern void pmkScScrScanner( /* pmkScScanner scanner, int smOnOff */ );
extern void pmkScScrToken( /* pmkScScanner scanner, int smCode, int smOnOff */ );
extern void pmkScScrRule( /* pmkScScanner scanner, int smCode, int smOnOff */ );
extern int pmkScan( /* SMContext smThis, TMToken *smToken */ );


typedef struct pmkScContextItem {

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

  pmkScScanner smScanner;



  char *fileName;
  int fd;



} pmkScContextItem;

#endif
