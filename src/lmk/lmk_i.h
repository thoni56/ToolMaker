#ifndef _lmk_i_h
#define _lmk_i_h
/*------------------------------------------------------------------- */ 
/* TITLE                                                              */ 
/* ------                                                             */ 
/* lmk_i.h                                                            */
/*                                                                    */ 
/* VERSION:   1.0                                                     */
/* ------------------------------------------------------------------ */ 
/*                                                                    */ 
/* REVISION DATA                                                      */ 
/* -------------                                                      */
/* CREATED:   92-07-20  Micael Dahlgren                               */
/* BASED ON:                                                          */
/* MODIFIED:                                                          */ 
/* ------------------------------------------------------------------ */ 
/*                                                                    */ 
/* DESCRIPTION                                                        */ 
/* -----------                                                        */ 
/* Global definitions                                                 */
/*                                                                    */ 
/* ------------------------------------------------------------------ */

/* IMPORT */
#include <stdio.h>
#include "tmk.h"
#include "lmkCommon.h"
#include "lmkScan.h"

/* CONSTANTS */
#define SeriousErr (lmkSeverity() & (sevERR | sevFAT | sevSYS))

typedef enum OptTabKind {
  VERBOSE_OPT, WIDTH_OPT, HEIGHT_OPT, TMKTARGET_OPT, LMKTARGET_OPT,
  TMKOS_OPT, LMKOS_OPT, TMKESCAPE_OPT, LMKESCAPE_OPT, TMKPREFIX_OPT,
  LMKPREFIX_OPT, LISTINGS_OPT, INCLUDE_OPT, MULTIPLE_OPT, LIMIT_OPT, TMK_OPT,
  MESSAGE_OPT, LMT_OPT, TMKLIBRARY_OPT, LMKLIBRARY_OPT, GENERATE_OPT, FORCE_OPT,
  HELP_OPT,

  LAST_OPT
} OptTabKind;

/* TYPES */
typedef struct MessNode *MessNodeP;
typedef struct MessNode {
  int number;
  char *text;
  MessNodeP next;
} MessNode;

typedef struct MessSectNode *MessSectNodeP;
typedef struct MessSectNode {
  char *name;
  int messCnt;
  MessNodeP messages;
  MessNodeP *messTab;
  MessSectNodeP next;
} MessSectNode;

/* VARIABLES */
extern lmkScContext lmkCtxt;
extern char lmkEscape;
extern MessSectNodeP messSectRoot;

/* FUNCTIONS */
extern void lmkTab();
#endif
