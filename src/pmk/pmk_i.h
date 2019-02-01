#ifndef _pmk_i_h
#define _pmk_i_h
/*------------------------------------------------------------------- */ 
/* TITLE                                                              */ 
/* ------                                                             */ 
/* pmk_i.h                                                            */
/*                                                                    */ 
/* VERSION:   1.0                                                     */
/* ------------------------------------------------------------------ */ 
/*                                                                    */ 
/* REVISION DATA                                                      */ 
/* -------------                                                      */
/* CREATED:   92-08-26 H}kan Petersson                                */
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
#include "pmkCommon.h"
#include <fcntl.h>

#ifdef CYGWIN
#define OFLAG _O_RAW
#define TARGETOS "cygwin"
#else
#ifdef MINGW
#define OFLAG _O_RAW
#define TARGETOS "mingw"
#else
#ifdef WIN32
#define OFLAG _O_TEXT
#define TARGETOS "WIN32"
#else
#define OFLAG 0
#endif
#endif
#endif

#define MAXNOPH 3		/* max mumber of placeholders */

typedef struct StrList {
  char *str;
  struct StrList *next;
} StrList;
typedef struct StrList *StrListP;

typedef enum OptTabKind {
  GENERATE_OPT, FORCE_OPT,
  VERBOSE_OPT, TRACE_OPT, WIDTH_OPT, HEIGHT_OPT, LINE_OPT, STACKSIZE_OPT, 
  STACKLIMIT_OPT, LOOKAHEADMAX_OPT, SHIFTCOST_OPT, PMKTARGET_OPT,
  TMKTARGET_OPT, PMKOS_OPT, TMKOS_OPT, TMKESCAPE_OPT, PMKESCAPE_OPT,
  PMKPREFIX_OPT, LISTERPREFIX_OPT, TMKPREFIX_OPT, OPTIMIZE_OPT, PACK_OPT,
  ACTIONPACK_OPT, GOTOPACK_OPT, RECOVERY_OPT, RESOLVE_OPT, LIST_OPT, TMK_OPT, VOC_OPT,
  PML_OPT, PMT_OPT, HELP_OPT, PMKLIBRARY_OPT, TMKLIBRARY_OPT, ERRORHANDLER_OPT,
  LAST_OPT
} OptTabKind;

extern OptTabRec tmkOptTab[];
extern OptTabRec pmkOptTab[];

extern char pmkEscape;
extern TokenNodeP tokenNode;
extern SrcpNodeP srcpNode;
extern CodeNodeP importSection;

extern StrListP grmAttrNames, grmAttrDecls;

extern CodeNodeP 
  pmkImportSection,
  exportSection,
  declSection,
  scannerSection,
  insertSymbSection,
  deleteSymbSection;

StrListP appendStrList();
void printStrList();
#endif
