/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1990-06-27
 *
 * SoftLab ab (c) 1990
 */

#include <stdio.h>
#ifndef WIN32
#include <sys/file.h>
#endif
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef WIN32
#include <io.h>
#endif
#include "impMacro.h"
#include "common.h"
#include "char.h"
#include "dfa.h"
#ifdef HAVE_LICENSEHANDLING
#include "license.h"
#endif
#include "map.h"
#include "nfa.h"
#include "pack.h"
#include "screen.h"
#include "set.h"
#include "smalloc.h"
#include "smkList.h"
#include "smkParse.h"
#include "smkScan.h"
#include "smk_i.h"
#include "time.h"
#include "tmk.h"
#include "version.h"
#include "write.h"

smkScContext lexContext;

#define MAX 0x7FFFFFFF

OptTabRec tmkOptTab[] = {
  {VERBOSE_OPT, BOOL_TMO,    "verbose", "verbose"},
  {TMKTARGET_OPT,  STR_TMO,     "target",  "target"},
  {TMKOS_OPT,      STR_TMO,     "os",      "os"},
  {TMKPREFIX_OPT,  BOOLSTR_TMO, "prefix",  "prefix"},
  {TMKLIBRARY_OPT, STR_TMO,     "library", "library"},
  {TMKESCAPE_OPT,  BOOLSTR_TMO, "escape",  "escape"},
  {WIDTH_OPT,   BOOLNUM_TMO, "width",   "width",  0, "", {0, MAX}},
  {HEIGHT_OPT,  BOOLNUM_TMO, "height",  "height", 0, "", {0, MAX}},
  {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
     "select [no] generated output {tables | source}", {0},
      {"Tables", "Source", NULL}},
  {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
     "do [not] force generating of source code"},
  {LAST_OPT}
};

OptTabRec smkOptTab[] =
    {
      {VERBOSE_OPT, BOOL_TMO, "verbose", "verbose", FALSE,
        "do [not] enable verbose mode"},
      {SMKTARGET_OPT, STR_TMO, "target", "target <lang>", (intptr_t) "ansi-c",
        "generate for target language <lang>"},
      {TMKTARGET_OPT, STR_TMO, "", "", (intptr_t) "ansi-c",
        "set target language"},
      {SMKOS_OPT, STR_TMO, "os", "os <os>", (intptr_t) TARGETOS,
        "generate for target os <os>"},
      {TMKOS_OPT, STR_TMO, "", "", (intptr_t) TARGETOS,
        "set target os"},
      {SMKPREFIX_OPT, BOOLSTR_TMO, "prefix", "prefix [<prefix>]", (intptr_t) "sm",
        "set [no] scanner prefix"},
      {TMKPREFIX_OPT, BOOLSTR_TMO, "", "", (intptr_t) "tm",
        "set [no] system prefix"},
      {SMKLIBRARY_OPT, STR_TMO, "library", "library <lib>",
        (intptr_t) "%%(TMHOME)/lib/%%(smkTarget)/", "use directory <lib> as library"},
      {TMKLIBRARY_OPT, STR_TMO, "", "",
        (intptr_t) "%%(TMHOME)/lib/%%(tmkTarget)/", "set library"},
      {SMKESCAPE_OPT, BOOLSTR_TMO, "escape", "escape [<c>]", (intptr_t) "`",
        "set [no] escape character"},
      {TMKESCAPE_OPT, BOOLSTR_TMO, "", "", (intptr_t) "`",
        "set [no] escape character"},
      {WIDTH_OPT, BOOLNUM_TMO, "width", "width <n>", 78,
        "set [no] listing width to <n>", {0, MAX}},
      {HEIGHT_OPT, BOOLNUM_TMO, "height", "height <n>", 60,
        "set [no] listing height to <n>", {0, MAX}},
      {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
        "select [no] generated output { tables | source }", {0},
      {"Tables", "Source", NULL}},
      {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
        "do [not] force generation of source code"},
      {SCREENING_OPT, BOOLNUM_TMO, "screening", "screening", FALSE, "set [no] screened token match length", {0, MAX}},
      {SET_OPT, BOOLSTR_TMO, "set", "set <set>", (intptr_t)"ISO8859_1", "select character set [use default]"},
      {TRACE_OPT, BOOL_TMO, "trace", "trace", FALSE,
        "do [not] generate tracing"},
      {OPTIMIZE_OPT, BOOL_TMO, "optimize", "optimize", TRUE,
        "do [not] optimize tables"},
      {TOKENSIZE_OPT, NUM_TMO, "tokensize", "tokensize <n>", 1024,
        "set normal size of token buffer to <n>", {0, MAX}},
      {TOKENLIMIT_OPT, NUM_TMO, "tokenlimit", "tokenlimit <n>", 512*1024,
        "set maximal token length <n>", {0,MAX}},
      {EXCLUDE_OPT, BOOLSTR_TMO, "exclude", "exclude [<c>]", FALSE,
        "set [no] excluded character"},
      {PACK_OPT, SET_TMO, "pack", "pack", 3,
        "select [no] table packing { row | column | rds | les | gcs | error }", {0},
      {"Row", "Column", "RDS", "LES", "GCS", "Error", NULL}},
      {LIST_OPT, SET_TMO, "list", "list", 0,
        "select [no] listed information { set | map | token | input | nfa | dfa | rule }", {0},
      {"Set", "Map", "Token", "Input", "Nfa", "Dfa", "Rule", NULL}},
      {VOC_OPT, STR_TMO, "", "voc <file>", (intptr_t)NULL, "read vocabulary from <file>"},
      {SML_OPT, STR_TMO, "", "sml <file>", (intptr_t)NULL, "write lists to <file> (if any)"},
      {SMT_OPT, STR_TMO, "", "smt <file>", (intptr_t)NULL, "write tables to <file> (if any)"},
      {TMK_OPT, STR_TMO, "", "tmk <file>", (intptr_t)NULL, "read common options from <file>"},
      {HELP_OPT, HELP_TMO, "help", "help", 0,
        "this help information"},
      {LAST_OPT}
    };

static char *mainListFiles[4]={"",NULL,NULL};
short optExclude;
unsigned char smkEscape;
Name optScanner;
Name optVocabulary;
Name optSmtfile;
Name optSmlfile;
Name optTmkfile;
int optScreen;

TokenNodeP tokenNode = NULL, tmpToken = NULL;
SrcpNodeP srcpNode = NULL, tmpSrcp = NULL;
CodeNodeP importSection, tmkImportSection, smkImportSection;

void tmkLog(pos, ecode, sev, istrs)
    TmkSrcp *pos;   /* IN - Source position */
    int ecode;      /* IN - The error code */
    smkSev sev;     /* IN - Severity code */
    char istrs[];   /* IN - Insert strings */
{
  smkLog(pos, ecode, sev, istrs);
}

static Name optFile(Name from, Name extension)
{
  char *suffix;
  char *basename;
  char *buffer;
  char *to;
  char dot;

#ifdef WIN32
  char *s;

  basename = NULL;
  s = strpbrk(from, "/\\:");
  while (s)
  {
    basename = s;
    s = strpbrk(basename+1, "/\\:");
  }
#else
  basename=strrchr(from,'/');
#endif
  if(basename==0) basename=from;
  suffix=strrchr(from,'.');
  if(suffix==0 || suffix<basename) suffix=basename+strlen(basename);
  dot=*suffix;
  *suffix=0;
  buffer=(char *)smalloc(strlen(from)+strlen(extension)+2);
  strcpy(buffer,from);
  strcat(buffer,".");
  strcat(buffer,extension);
  to=nameSearch(buffer);
  *suffix=dot;
  free(buffer);
  return to;
}

static Name optFileExtension(Name from)
{
  char *suffix;
  char *basename;

#ifdef WIN32
  char *s;

  basename = NULL;
  s = strpbrk(from, "/\\:");
  while (s)
  {
    basename = s;
    s = strpbrk(basename+1, "/\\:");
  }
#else
  basename=strrchr(from,'/');
#endif
  if(basename==0) basename=from;
  suffix=strrchr(from,'.');
  return (suffix==0 || suffix<basename) ? 0 : nameSearch(suffix+1);
}

void mainLicense()
{
#ifdef HAVE_LICENSEHANDLING
  switch(license()) {
  case LICENSE_OK:
    break;
  case LICENSE_EXPIRED:
    smkLog((TmkSrcp *)NULL,500,sevFAT,"");
    break;
  case LICENSE_DENIED:
    smkLog((TmkSrcp *)NULL,501,sevFAT,"");
    break;
  case LICENSE_FORMAT_ERROR:
    smkLog((TmkSrcp *)NULL,502,sevFAT,"");
    break;
  case LICENSE_NO_SERVER:
    smkLog((TmkSrcp *)NULL,503,sevFAT,"");
    break;
  case LICENSE_NO_FILE:
    smkLog((TmkSrcp *)NULL,504,sevFAT,"");
    break;
  case LICENSE_ILLEGAL_PASSWORD:
    smkLog((TmkSrcp *)NULL,505,sevFAT,"");
    break;
  default:
    smkLog((TmkSrcp *)NULL,506,sevFAT,"");
    break;
  }
#endif
}

void mainCreate( int argc, char **argv)
{
  Pack pack;
  TimeItem tb;
  TimeItem tbTotal;
  int time;
  int size;
  unsigned optList;
  Boolean tmkExists;

  tistart(&tbTotal);
  tistart(&tb);

  if(access(optScanner,R_OK))
    smkLog(NULL,240,sevFAT,optScanner);
  if(getStrOpt(VOC_OPT))
    if(access(optVocabulary, F_OK)<0 || access(optVocabulary, R_OK)<0)
      smkLog(NULL,223,sevFAT,optVocabulary);
  if(getStrOpt(TMK_OPT))
    if(access(optTmkfile, F_OK)<0 || access(optTmkfile, R_OK)<0)
      smkLog(NULL,403,sevFAT,optTmkfile);
  if(getSetOpt(GENERATE_OPT)) {
    if(access(optSmtfile,F_OK)==0)
      if(access(optSmtfile,W_OK))
    smkLog(NULL,207,sevFAT,optSmtfile);
  }
  if (getSetOpt(LIST_OPT)) {
    if(access(optSmlfile,F_OK)==0)
      if(access(optSmlfile,W_OK))
    smkLog(NULL,208,sevFAT,optSmlfile);
  }
  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) {
    if (getBoolOpt(VERBOSE_OPT))
      printf("%s\n\n",product.longHeader);
    return;
  }

  /* options in .tmk file */
  if ((tmkExists = tmkCParse(mainListFiles[2], tmkOptTab, smkOptTab, argc, argv,
               &tokenNode, &srcpNode, &importSection, 2, TMK_FILE, TMKESCAPE_OPT))) {
  }
  /* options in input file */
  if (tmkExists) {
    if (tmkCParse(mainListFiles[1], smkOptTab, smkOptTab, argc, argv,
         &tmpToken, &tmpSrcp, &smkImportSection, 1, SMK_FILE, SMKESCAPE_OPT)) {
      if (tmpToken)
    smkLog(NULL, 52, sevERR, "TOKEN");
      if (tmpSrcp)
    smkLog(NULL, 52, sevERR, "SRCP");
    } else
      smkLog(NULL, 401, sevFAT, mainListFiles[1]);
  } else {
    if (!tmkCParse(mainListFiles[1], smkOptTab, smkOptTab, argc, argv,
          &tokenNode, &srcpNode, &smkImportSection, 1, SMK_FILE, SMKESCAPE_OPT))
      smkLog(NULL, 401, sevFAT, mainListFiles[1]);
  }

  if (getBoolOpt(VERBOSE_OPT))
    printf("%s\n\n",product.longHeader);

  if (smkSeverity() & (sevERR+sevFAT+sevSYS)) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  if(getStrOpt(EXCLUDE_OPT) != FALSE)
    optExclude = *getStrOpt(EXCLUDE_OPT);
  else
    optExclude = -1;
  smkEscape = *getStrOpt(SMKESCAPE_OPT);

  /* Prefix assignment */
  mergeOptions(SMKPREFIX_OPT, TMKPREFIX_OPT, tmkExists);
  /* Library assignment */
  mergeOptions(SMKLIBRARY_OPT, TMKLIBRARY_OPT, tmkExists);
  /* Os assignment */
  mergeOptions(SMKOS_OPT, TMKOS_OPT, tmkExists);
  /* Target assignment */
  mergeOptions(SMKTARGET_OPT, TMKTARGET_OPT, tmkExists);

  if ((strcmp(getStrOpt(TMKTARGET_OPT), "c") != 0) &&
      (strcmp(getStrOpt(TMKTARGET_OPT), "ansi-c") != 0) &&
      (strcmp(getStrOpt(TMKTARGET_OPT), "c++") != 0)) {
    smkLog(NULL, 405, sevWAR, getStrOpt(TMKTARGET_OPT));
  }

  if ((strcmp(getStrOpt(SMKTARGET_OPT), getStrOpt(TMKTARGET_OPT)) != 0) &&
      (strcmp(getStrOpt(SMKTARGET_OPT), "c") != 0) &&
      (strcmp(getStrOpt(SMKTARGET_OPT), "ansi-c") != 0) &&
      (strcmp(getStrOpt(TMKTARGET_OPT), "c++") != 0)) {
    smkLog(NULL, 405, sevWAR, getStrOpt(SMKTARGET_OPT));
  }

  optScreen = getNumOpt(SCREENING_OPT);
  if(optScreen<=0) optScreen=0x7FFFFFFF;

  lexContext=smkScNew(smk_MAIN_MAIN_Scanner);
  lexContext->fd=open(optScanner,OFLAG);
  smkParse();
  close(lexContext->fd);
  smkScDelete(lexContext);
  time=tistop(&tb);
  if (getBoolOpt(VERBOSE_OPT)) {
    printf("      PASS          TIME     STATES   CHARACTERS    NOTES\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("create AST      %s\n",tistr(time));
  }
  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  tistart(&tb);
  nfaCreate();
  time=tistop(&tb);
  if(getBoolOpt(VERBOSE_OPT)) printf("create NFA      %s    %7d      %7d\n",tistr(time),nfaSize,charSize);
  if(nfaSize<1 || (smkSeverity() & (sevERR+sevFAT+sevSYS))) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  tistart(&tb);
  nfaOptimize();
  time=tistop(&tb);
  if(getBoolOpt(VERBOSE_OPT)) printf("optimize NFA    %s    %7d      %7d\n",tistr(time),nfaSize,charSize);
  if(charSize<1 || (smkSeverity() & (sevERR+sevFAT+sevSYS))) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }

  tistart(&tb);
  dfaCreate();
  dfaAccept();
  time=tistop(&tb);
  if(getBoolOpt(VERBOSE_OPT)) printf("create DFA      %s    %7d      %7d\n",tistr(time),dfaSize,charSize);
  if(dfaSize<1 || (smkSeverity() & (sevERR+sevFAT+sevSYS))) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  size=dfaSize;

  if (getBoolOpt(OPTIMIZE_OPT)) {
    tistart(&tb);
    dfaOptimize();
    time=tistop(&tb);
    if(getBoolOpt(VERBOSE_OPT)) printf("optimize DFA    %s    %7d      %7d                    %5.2f%%\n",
              tistr(time),dfaSize,charSize,(dfaSize*100.0)/size);
    if(dfaSize<1 || (smkSeverity() & (sevERR+sevFAT+sevSYS))) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  }

  tistart(&tb);
  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }
  pack=dfaPack();
  screenCreate();
  time=tistop(&tb);
  if(getBoolOpt(VERBOSE_OPT)) printf("pack DFA table  %s    %7d      %7d                    %5.2f%%\n",
            tistr(time),pack->rows,pack->cols,(pack->rows*pack->cols*100.0)/(size*256));
  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) {
    optList = getSetOpt(LIST_OPT);
    goto Exit;
  }

  if((optList = getSetOpt(LIST_OPT))) {
    tistart(&tb);
    smkListm(optSmlfile,
        getNumOpt(HEIGHT_OPT),
        getNumOpt(WIDTH_OPT),
        (optList & optLIST_INPUT) ? liFULL : liTINY,
        sevOK+sevINF+sevWAR+sevERR+sevFAT,
        mainListFiles);
    optList=getSetOpt(LIST_OPT);
    if(optList & optLIST_NONE) ;
    if(optList & optLIST_SET) setPrint();
    if(optList & optLIST_MAP) mapPrint();
    if(optList & optLIST_TOKEN) vocabularyPrint();
    if(optList & optLIST_NFA) nfaPrint();
    if(optList & optLIST_DFA) dfaPrint();
    if(optList & optLIST_RULE) rulePrint();
    time=tistop(&tb);
    if(getBoolOpt(VERBOSE_OPT)) printf("write lists     %s\n",tistr(time));
  }

  if(getSetOpt(GENERATE_OPT)) {
    int minsize;
    int maxsize;

    tistart(&tb);
    writeAll(pack,&minsize,&maxsize,size);

    if(getSetOpt(GENERATE_OPT) & optGENERATE_SOURCE) {
      int ecode=0;
      ecode = impMacro(optSmtfile, NULL, "", envBit, 0, smkEscape, &ecode) & (sevERR | sevFAT | sevSYS);
      if (ecode == 0) {
    if((getSetOpt(GENERATE_OPT) & optGENERATE_TABLES)==0)
      unlink(optSmtfile);
    }
      else
    smkLog(0,402,sevFAT,"");
      time=tistop(&tb);
      if(getBoolOpt(VERBOSE_OPT)) printf("generate source %s                            %7d bytes   %5.2f%%\n",
                     tistr(time),minsize,(minsize*100.0)/maxsize);
    }
    else {
      time=tistop(&tb);
      if(getBoolOpt(VERBOSE_OPT)) printf("generate tables %s                            %7d bytes   %5.2f%%\n",
                     tistr(time),minsize,(minsize*100.0)/maxsize);
    }

  }

 Exit:

  if(optList && (smkSeverity() & (sevERR+sevFAT+sevSYS)))
    smkListm(optSmlfile,
        getNumOpt(HEIGHT_OPT),
        getNumOpt(WIDTH_OPT),
        (optList & optLIST_INPUT) ? liFULL : liTINY,
        sevOK+sevINF+sevWAR+sevERR+sevFAT,
        mainListFiles);
  time=tistop(&tbTotal);
  if(getBoolOpt(VERBOSE_OPT)) {
    printf("===============================================================================\n");
    printf("Total           %s\n",tistr(time));
  }
}

int main( int argc, char **argv )
{
  char *fileName;
#ifdef DEBUG
  malloc_debug(2);
#endif

#ifdef WIN32
#ifdef TMTEST
    freopen("stderr.txt", "w", stderr);
#else
    /* 4f - redirect to stderr to stdout */
#endif
#endif

  smkLiInit(product.longHeader, "", smk_ENGLISH_Messages);

  mainLicense();
  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) goto Exit;

  /* Initiate option database */
  initOpts(LAST_OPT, smkOptTab);

  /* Set command line options */
  setCliOpts(smkOptTab, argc, argv, &fileName);

  nameSearch(fileName);
  optScanner = optFileExtension(fileName) ? fileName : optFile(fileName, "smk");

  if (!(optVocabulary = getStrOpt(VOC_OPT))) optVocabulary = optFile(fileName, "voc");
  if (!(optSmtfile = getStrOpt(SMT_OPT))) optSmtfile = optFile(fileName, "smt");
  if (!(optSmlfile = getStrOpt(SML_OPT))) optSmlfile = optFile(fileName, "sml");
  if (!(optTmkfile = getStrOpt(TMK_OPT))) optTmkfile = optFile(fileName, "tmk");

  mainListFiles[0] = optVocabulary;
  mainListFiles[1] = optScanner;
  mainListFiles[2] = optTmkfile;

  setInit();
  smkLiInit(product.longHeader, optScanner, smk_ENGLISH_Messages);

  mainCreate(argc, argv);

 Exit:

  if(smkSeverity() & (sevWAR+sevERR+sevFAT+sevSYS))
    smkListm("",0,0x7FFFFFFF,liTINY,sevOK+sevWAR+sevERR+sevFAT+sevSYS,mainListFiles);

  if(smkSeverity() & (sevERR+sevFAT+sevSYS)) exit(smkSeverity()); else exit(0);
}
