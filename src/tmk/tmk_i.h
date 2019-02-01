#ifndef _tmk_i_h
#define _tmk_i_h
/*------------------------------------------------------------------- */ 
/* TITLE                                                              */ 
/* ------                                                             */ 
/* tmk_i.h                                                            */
/*                                                                    */ 
/* VERSION:   1.0                                                     */
/* ------------------------------------------------------------------ */ 
/*                                                                    */ 
/* REVISION DATA                                                      */ 
/* -------------                                                      */
/* CREATED:   92-07-04  Micael Dahlgren                               */
/* BASED ON:                                                          */
/* MODIFIED:                                                          */ 
/* ------------------------------------------------------------------ */ 
/*                                                                    */ 
/* DESCRIPTION                                                        */ 
/* -----------                                                        */ 
/*                                                                    */
/*                                                                    */ 
/* ------------------------------------------------------------------ */
/* IMPORT */
#include "tmk.h"

/* UNIT CONSTANTS */

/* UNIT TYPES */
typedef struct TmkEnv *TmkEnvP;
typedef struct TmkEnv {
  TokenNodeP tokenNode;
  SrcpNodeP srcpNode;
  CodeNodeP importSection;
  OptTabRec *optTab;
  OptTabRec *cliTab;
  int argc;
  char **argv;
  int fileNo;
  FileType fileType;
  int escapeOpt;
} TmkEnv;

/* UNIT DATA */
extern TmkEnvP tmkEnv;
extern char tmkEscape;

/* UNIT FUNCTIONS */
#endif
