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
	smk_MAIN_2_Token = 2,
	smk_MAIN_3_Token = 3,
	smk_MAIN_4_Token = 4,
	smk_MAIN_5_Token = 5,
	smk_MAIN_6_Token = 6,
	smk_MAIN_7_Token = 7,
	smk_MAIN_8_Token = 8,
	smk_MAIN_9_Token = 9,
	smk_MAIN_10_Token = 10,
	smk_MAIN_11_Token = 11,
	smk_MAIN_12_Token = 12,
	smk_MAIN_13_Token = 13,
	smk_MAIN_14_Token = 14,
	smk_MAIN_15_Token = 15,
	smk_MAIN_16_Token = 16,
	smk_MAIN_17_Token = 17,
	smk_MAIN_18_Token = 18,
	smk_MAIN_19_Token = 19,
	smk_MAIN_20_Token = 20,
	smk_MAIN_21_Token = 21,
	smk_MAIN_22_Token = 22,
	smk_MAIN_23_Token = 23,
	smk_MAIN_24_Token = 24,
	smk_MAIN_25_Token = 25,
	smk_MAIN_26_Token = 26,
	smk_MAIN_27_Token = 27,
	smk_MAIN_28_Token = 28,
	smk_MAIN_29_Token = 29,
	smk_MAIN_30_Token = 30,
	smk_MAIN_31_Token = 31,
	smk_MAIN_32_Token = 32,
	smk_MAIN_33_Token = 33,
	smk_MAIN_34_Token = 34,
	smk_MAIN_35_Token = 35,
	smk_MAIN_CLASS_Token = 36,
	smk_MAIN_37_Token = 37,
	smk_MAIN_38_Token = 38,
	smk_MAIN_39_Token = 39,
	smk_MAIN_40_Token = 40,
	smk_MAIN_STRING_Token = 41,
	smk_MAIN_NUMBER_Token = 42,
	smk_MAIN_43_Token = 43,
	smk_MAIN_44_Token = 44,
	smk_MAIN_45_Token = 45,
	smk_MAIN_46_Token = 46,
	smk_MAIN_47_Token = 47,
	smk_MAIN_48_Token = 48,
	smk_MAIN_49_Token = 49,
	smk_MAIN_50_Token = 50,
	smk_MAIN_51_Token = 51,
	smk_MAIN_52_Token = 52,
	smk_MAIN_53_Token = 53,
	smk_MAIN_54_Token = 54,
	smk_MAIN_SKIPHEADER_Token = 55,
	smk_MAIN_56_Token = 56,
	smk_MAIN_57_Token = 57,
	smk_MAIN_58_Token = 58,
	smk_MAIN_59_Token = 59,
	smk_MAIN_IDENTIFIER_Token = 60,
	smk_MAIN_61_Token = 61,
	smk_MAIN_62_Token = 62,
	smk_MAIN_63_Token = 63,
	smk_MAIN_64_Token = 64,
	smk_MAIN_65_Token = 65,
	smk_MAIN_66_Token = 66,
	smk_MAIN_67_Token = 67,
	smk_MAIN_68_Token = 68,
	smk_MAIN_69_Token = 69,
	smk_MAIN_70_Token = 70,
	smk_MAIN_71_Token = 71,
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
