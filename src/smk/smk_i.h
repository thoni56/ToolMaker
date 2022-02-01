#ifndef _smk_i_h
#define _smk_i_h
/*------------------------------------------------------------------- */
/* TITLE                                                              */
/* ------                                                             */
/* smk_i.h                                                            */
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
#include <fcntl.h>
#include "tmk.h"
#include "name.h"

#ifdef CYGWIN
#define OFLAG O_TEXT
#else
#ifdef WIN32
#define OFLAG _O_BINARY
#else
#define OFLAG 0
#endif
#endif

/* Values for Pack option */
#define ePackROW (0x01)
#define ePackCOL (0x02)
#define ePackRDS (0x04)
#define ePackLES (0x08)
#define ePackGCS (0x10)
#define ePackERR (0x20)

#define optLIST_NONE    (0x00)
#define optLIST_SET     (0x01)
#define optLIST_MAP     (0x02)
#define optLIST_TOKEN   (0x04)
#define optLIST_INPUT   (0x08)
#define optLIST_NFA     (0x10)
#define optLIST_DFA     (0x20)
#define optLIST_RULE    (0x40)

#define optGENERATE_TABLES (0x01)
#define optGENERATE_SOURCE (0x02)


typedef enum OptTabKind {
  VERBOSE_OPT, TRACE_OPT, WIDTH_OPT, HEIGHT_OPT, SMKTARGET_OPT, TMKTARGET_OPT,
  SMKOS_OPT, TMKOS_OPT, TMKESCAPE_OPT, SMKESCAPE_OPT, SMKPREFIX_OPT,
  TMKPREFIX_OPT, PACK_OPT, SMKLIBRARY_OPT, TMKLIBRARY_OPT, ERRORHANDLER_OPT,
  OPTIMIZE_OPT, LIST_OPT, GENERATE_OPT, FORCE_OPT, HELP_OPT, VOC_OPT, SMT_OPT, SML_OPT, TMK_OPT,
  SCREENING_OPT, SET_OPT, TOKENSIZE_OPT, TOKENLIMIT_OPT, EXCLUDE_OPT,
  LAST_OPT
} OptTabKind;

extern short optExclude;
extern unsigned char smkEscape;
extern Name optScanner;
extern Name optVocabulary;
extern Name optSmtfile;
extern Name optSmlfile;
extern Name optTmkfile;
extern TokenNodeP tokenNode;
extern SrcpNodeP srcpNode;
extern CodeNodeP importSection, tmkImportSection, smkImportSection;
extern int optScreen;

#endif
