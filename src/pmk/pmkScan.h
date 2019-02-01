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
	pmk_MAIN_99_Token = 99,
	pmk_MAIN_100_Token = 100,
	pmk_MAIN_101_Token = 101,
	pmk_MAIN_102_Token = 102,
	pmk_MAIN_103_Token = 103,
	pmk_MAIN_104_Token = 104,
	pmk_MAIN_105_Token = 105,
	pmk_MAIN_106_Token = 106,
	pmk_MAIN_107_Token = 107,
	pmk_MAIN_108_Token = 108,
	pmk_MAIN_109_Token = 109,
	pmk_MAIN_110_Token = 110,
	pmk_MAIN_111_Token = 111,
	pmk_MAIN_112_Token = 112,
	pmk_MAIN_113_Token = 113,
	pmk_MAIN_114_Token = 114,
	pmk_MAIN_115_Token = 115,
	pmk_MAIN_116_Token = 116,
	pmk_MAIN_117_Token = 117,
	pmk_MAIN_118_Token = 118,
	pmk_MAIN_119_Token = 119,
	pmk_MAIN_SKIPHEADER_Token = 120,
	pmk_MAIN_121_Token = 121,
	pmk_MAIN_122_Token = 122,
	pmk_MAIN_123_Token = 123,
	pmk_MAIN_124_Token = 124,
	pmk_MAIN_125_Token = 125,
	pmk_MAIN_126_Token = 126,
	pmk_MAIN_127_Token = 127,
	pmk_MAIN_128_Token = 128,
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
