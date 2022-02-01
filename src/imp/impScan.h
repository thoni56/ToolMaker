#ifndef _impScan_h_
#define _impScan_h_

#include "impCommon.h"

typedef enum impScScanner {
        imp_MAIN_MAIN_Scanner = 0,
        imp_MAIN_IMP_Scanner = 1,
        imp_MAIN_STRING_Scanner = 2,
        imp_MAIN_KEEP_Scanner = 3,
        imp_MAIN_COMMENT_Scanner = 4
} impScScanner;

typedef enum imp_MAIN_ScToken {
        imp_MAIN_UNKNOWN_Token = 0,
        imp_MAIN_ENDOFTEXT_Token = 1,
        imp_MAIN_2_Token = 2,
        imp_MAIN_3_Token = 3,
        imp_MAIN_4_Token = 4,
        imp_MAIN_5_Token = 5,
        imp_MAIN_6_Token = 6,
        imp_MAIN_7_Token = 7,
        imp_MAIN_8_Token = 8,
        imp_MAIN_9_Token = 9,
        imp_MAIN_10_Token = 10,
        imp_MAIN_11_Token = 11,
        imp_MAIN_12_Token = 12,
        imp_MAIN_13_Token = 13,
        imp_MAIN_14_Token = 14,
        imp_MAIN_15_Token = 15,
        imp_MAIN_16_Token = 16,
        imp_MAIN_17_Token = 17,
        imp_MAIN_TEXT_Token = 18,
        imp_MAIN_19_Token = 19,
        imp_MAIN_20_Token = 20,
        imp_MAIN_21_Token = 21,
        imp_MAIN_22_Token = 22,
        imp_MAIN_23_Token = 23,
        imp_MAIN_24_Token = 24,
        imp_MAIN_25_Token = 25,
        imp_MAIN_26_Token = 26,
        imp_MAIN_27_Token = 27,
        imp_MAIN_28_Token = 28,
        imp_MAIN_29_Token = 29,
        imp_MAIN_30_Token = 30,
        imp_MAIN_31_Token = 31,
        imp_MAIN_INTEGER_Token = 32,
        imp_MAIN_33_Token = 33,
        imp_MAIN_34_Token = 34,
        imp_MAIN_35_Token = 35,
        imp_MAIN_36_Token = 36,
        imp_MAIN_37_Token = 37,
        imp_MAIN_38_Token = 38,
        imp_MAIN_39_Token = 39,
        imp_MAIN_40_Token = 40,
        imp_MAIN_41_Token = 41,
        imp_MAIN_42_Token = 42,
        imp_MAIN_43_Token = 43,
        imp_MAIN_44_Token = 44,
        imp_MAIN_45_Token = 45,
        imp_MAIN_QUOT_STRING_Token = 46,
        imp_MAIN_47_Token = 47,
        imp_MAIN_48_Token = 48,
        imp_MAIN_49_Token = 49,
        imp_MAIN_UNQUOT_STRING_Token = 50,
        imp_MAIN_51_Token = 51,
        imp_MAIN_KEEP_Token = -1,
        imp_MAIN_COMMENT_Token = -1,
        imp_MAIN_SINGLELINECOMMENT_Token = -1,
        imp_MAIN_BLANK_Token = -1
} imp_MAIN_ScToken;


typedef struct impScContextItem *impScContext;

extern impScContext impScNew( impScScanner smScanner );
extern void impScDelete( impScContext smThis );
extern int impScSkip( impScContext smThis, int smLength );
extern int impScModify( impScContext smThis, unsigned char *smBuffer, int smLength );
extern int impScCopy( impScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern int impScMapCopy( impScContext smThis, unsigned char *smBuffer, unsigned int smFrom, unsigned int smTo );
extern void impScScrScanner( impScScanner scanner, int smOnOff );
extern void impScScrToken( impScScanner scanner, int smCode, int smOnOff );
extern void impScScrRule( impScScanner scanner, int smCode, int smOnOff );
extern int impScan( impScContext smThis, TmToken *smToken );


typedef struct impScContextItem {

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

  impScScanner smScanner;



  int fd;
  int fileNo;
  int endPos;



} impScContextItem;

#endif
