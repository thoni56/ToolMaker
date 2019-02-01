/*
 * AUTHOR : Tony Olsson
 * DATE   : 1991-08-23/tools@heffa
 * CREATED: 1991-08-23
 * 
 * SoftLab ab (c) 1991
 */

#ifndef _name_h_
#define _name_h_

#include "ast.h"
#include <sys/types.h>
#include <sys/stat.h>

typedef struct ParsedFileItem *ParsedFile;
typedef struct ParsedFileItem {
  char *file;
  ParseResult result;
  Ast ast;
  ino_t st_ino;
  dev_t st_dev;
  time_t st_time;
  int actCnt;
  ParsedFile next;
} ParsedFileItem;

typedef struct WrittenFileItem *WrittenFile;
typedef struct WrittenFileItem {
  FILE *file;
  ino_t st_ino;
  dev_t st_dev;
  WrittenFile next;
} WrittenFileItem;

typedef struct NameItem *Name;
typedef struct NameItem {
  char *name;
  ImpBoolean undef;
  int noElems;
  Ast ast;
  Name left;
  Name right;
} NameItem;

typedef struct ParamItem *Param;
typedef struct ParamItem {
  Name param;
  Param next;
} ParamItem;

typedef struct PlistItem *Plist;
typedef struct PlistItem {
  char *name;
  Plist next;
} PlistItem;

typedef struct RegionItem *Region;
typedef struct RegionItem {
  char *name;
  Ast ast;
  Name symtab;
  Plist params;
  Region left;
  Region right;
} RegionItem;

extern void impNamePut();
extern void impNameAppend();
extern ImpBoolean impNameGet();
extern ImpBoolean impNameGetIndexed();
extern Region impGetRegion();
extern void impFreeSymtabs();
extern void impNameUndef();
extern void impAddRegion();
extern void impPopLocalSymtab();
extern void impPushLocalSymtab();
extern void impReportFiles();
extern ParseResult impAstGet();
extern FILE *impWriteOpen();
extern void impWriteClose();
#endif
