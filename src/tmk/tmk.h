#ifndef _tmk_h
#define _tmk_h

/* IMPORT */
#include <stdint.h>
#include "tmkCommon.h"

/* UNIT CONSTANTS */
#define BOOLNUM_FALSE 0x80000000
#define BOOLSTR_FALSE "__BOOLSTR_FALSE"

/* UNIT TYPES */
#ifndef Boolean
typedef int Boolean;
#ifndef TRUE
#define TRUE       (0==0)
#endif
#ifndef FALSE
#define FALSE      (!TRUE)
#endif
#endif

typedef enum TmoKind {
  BOOL_TMO,                     /* Boolean option */
  NUM_TMO,                      /* Number option */
  STR_TMO,                      /* String option */
  SET_TMO,                      /* Set option */
  ENUM_TMO,                     /* Enum option */
  BOOLNUM_TMO,                  /* Boolean/number option */
  BOOLSTR_TMO,                  /* Boolean/string option */
  HELP_TMO,                     /* Help option (used only in clin) */
  NOTUSED_TMO                   /* Not used option */
} TmoKind;

typedef enum FileType {
  TMK_FILE,
  PMK_FILE,
  SMK_FILE,
  LMK_FILE
} FileType;

typedef struct OptNode *OptNodeP;
typedef struct OptNode {
  TmkSrcp srcp;                    /* Source position */
  char *name;                      /* Name of option */
  OptNodeP next;                   /* Next option in list */
} OptNode;

typedef struct TmoNode *TmoNodeP;
typedef struct TmoNode {
  TmkSrcp srcp;                    /* Source position */
  TmoKind dirKind;                 /* Kind of option */
  char *name;                      /* Name of option */
  TmoNodeP next;                   /* Next option in list */
  union {
    int ival;                      /* Value of number parameter */
    int bval;                      /* Value of boolean parameter */
    char *sval;                    /* Value of string parameter */
    OptNodeP opts;                 /* List of set parameters */
  } oval;
} TmoNode;

/* option table record type */
typedef struct OptTabRec {
  /* Common values */
  int optTabKind;                  /* Option */
  TmoKind dirKind;                 /* Option type */
  char *optName;                   /* Option name */
  char *cliName;                   /* Cli option name */
  intptr_t defval;                 /* Default value */
  char *optHelp;                   /* Option help string */

  /* Values used for semantic checks */
  struct {
    int mini;                      /* Min number value */
    int maxi;                      /* Max number value */
  } irange;
  char* sitems[10];                /* Set item list */
} OptTabRec;

typedef struct CodeNode *CodeNodeP;
typedef struct CodeNode {
  long fpos;                    /* File pos of target language code */
  long length;                  /* Length of target language code */
  char *fname;                  /* File name */
} CodeNode;

typedef struct TokenAttrList *TokenAttrListP;
typedef struct TokenAttrList {
  char *name;                      /* Attribute name */
  char *nameDecl;                  /* Attribute name declaration */
  TokenAttrListP next;             /* Next attribute in list */
} TokenAttrList;

typedef struct TokenNode *TokenNodeP;
typedef struct TokenNode {
  char *name;                      /* Token name */
  char *code;                      /* Token code */
  char *codeDecl;                  /* Token code declaration */
  char *srcp;                      /* Token srcp */
  char *srcpDecl;                  /* Token srcp declaration */
  TokenAttrListP attrs;            /* Token attribute list */
} TokenNode;

typedef struct SrcpNode *SrcpNodeP;
typedef struct SrcpNode {
  char *name;                      /* Srcp name */
  char *row;                       /* Srcp row */
  char *rowDecl;                   /* Srcp row declaration */
  char *col;                       /* Srcp col */
  char *colDecl;                   /* Srcp col declaration */
  char *file;                      /* Srcp file */
  char *fileDecl;                  /* Srcp file declaration */
  char *pos;                       /* Srcp pos */
  char *posDecl;                   /* Srcp pos declaration */
} SrcpNode;

typedef enum SkipType {
  NOSTRS_SKIP,
  STRSKP_SKIP,
  RULES_SKIP,
  SEM_SKIP,
  SUB_SKIP
} SkipType;

/* UNIT DATA */

/* UNIT FUNCTIONS */

extern void initOpts();
extern void mergeOptions();
extern void setOpts();
extern void setCliOpts();
extern Boolean getBoolOpt();
extern Boolean optAssigned();
extern int getNumOpt();
extern char *getStrOpt();
extern unsigned getSetOpt();

extern char* tmkReplPH();
extern void tmkCopyCode();
extern void tmkSkipCode();
extern void tmkPCommon();
extern Boolean tmkCParse();
extern CodeNodeP tmkNewCode();

#endif
