#ifndef _smkScan_h_
#define _smkScan_h_

#include "smkCommon.h"

typedef enum smkScScanner {
	smk_MAIN_MAIN_Scanner = 0,
	smk_VOCABULARY_MAIN_Scanner = 1,
	smk_SET_MAIN_Scanner = 2
} smkScScanner;

typedef enum smk_MAIN_ScToken {
	smk_MAIN_UNKNOWN_Token = 0,
	smk_MAIN_ENDOFTEXT_Token = 1,
	smk_MAIN_99_Token = 99,
	smk_MAIN_100_Token = 100,
	smk_MAIN_101_Token = 101,
	smk_MAIN_102_Token = 102,
	smk_MAIN_103_Token = 103,
	smk_MAIN_104_Token = 104,
	smk_MAIN_105_Token = 105,
	smk_MAIN_106_Token = 106,
	smk_MAIN_107_Token = 107,
	smk_MAIN_108_Token = 108,
	smk_MAIN_109_Token = 109,
	smk_MAIN_110_Token = 110,
	smk_MAIN_111_Token = 111,
	smk_MAIN_112_Token = 112,
	smk_MAIN_113_Token = 113,
	smk_MAIN_CLASS_Token = 114,
	smk_MAIN_115_Token = 115,
	smk_MAIN_STRING_Token = 116,
	smk_MAIN_NUMBER_Token = 117,
	smk_MAIN_118_Token = 118,
	smk_MAIN_119_Token = 119,
	smk_MAIN_120_Token = 120,
	smk_MAIN_121_Token = 121,
	smk_MAIN_122_Token = 122,
	smk_MAIN_SKIPHEADER_Token = 123,
	smk_MAIN_124_Token = 124,
	smk_MAIN_125_Token = 125,
	smk_MAIN_126_Token = 126,
	smk_MAIN_127_Token = 127,
	smk_MAIN_IDENTIFIER_Token = 128,
	smk_MAIN_129_Token = 129,
	smk_MAIN_130_Token = 130,
	smk_MAIN_131_Token = 131,
	smk_MAIN_132_Token = 132,
	smk_MAIN_133_Token = 133,
	smk_MAIN_134_Token = 134,
	smk_MAIN_135_Token = 135,
	smk_MAIN_136_Token = 136,
	smk_MAIN_137_Token = 137,
	smk_MAIN_138_Token = 138,
	smk_MAIN_COMMENT_Token = -1,
	smk_MAIN_BLANK_Token = -1
} smk_MAIN_ScToken;

typedef enum smk_VOCABULARY_ScToken {
	smk_VOCABULARY_ENDOFTEXT_Token = 0,
	smk_VOCABULARY_NUMBER_Token = 2,
	smk_VOCABULARY_IDENTIFIER_Token = 3,
	smk_VOCABULARY_STRING_Token = 4,
	smk_VOCABULARY_NEWLINE_Token = 5,
	smk_VOCABULARY_EOT_Token = 6,
	smk_VOCABULARY_UNKNOWN_Token = -1,
	smk_VOCABULARY_BLANK_Token = -1
} smk_VOCABULARY_ScToken;

typedef enum smk_SET_ScToken {
	smk_SET_ENDOFTEXT_Token = 0,
	smk_SET_UNKNOWN_Token = 1,
	smk_SET_IDENTIFIER_Token = 2,
	smk_SET_NUMBER_Token = 3,
	smk_SET_UNDEFINED_Token = 4,
	smk_SET_CHARACTER_Token = 5,
	smk_SET_EOS_Token = 6,
	smk_SET_BLANK_Token = -1,
	smk_SET_COMMENT_Token = -1
} smk_SET_ScToken;


typedef struct smkScContextItem *smkScContext;

extern smkScContext smkScNew( smkScScanner smScanner );
extern void smkScDelete( smkScContext smThis );
extern int smkScSkip( smkScContext smThis, int smLength );
extern int smkScModify( smkScContext smThis, unsigned char *smBuffer, int smLength );
extern int smkScCopy( smkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern int smkScMapCopy( smkScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern void smkScScrScanner( smkScScanner scanner, int smOnOff );
extern void smkScScrToken( smkScScanner scanner, int smCode, int smOnOff );
extern void smkScScrRule( smkScScanner scanner, int smCode, int smOnOff );
extern int smkScan( smkScContext smThis, SmkToken *smToken );


typedef struct smkScContextItem {

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

  smkScScanner smScanner;



  char *fileName;
  int fd;



} smkScContextItem;

#endif
