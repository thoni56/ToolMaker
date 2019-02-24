/*------------------------------------------------------------------- */
/* TITLE                                                              */
/* ------                                                             */
/* lmk.c                                                              */
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
/* ListerMaker main module                                            */
/*                                                                    */
/* ------------------------------------------------------------------ */
/* IMPORT */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include <unistd.h>
#include "lmk_i.h"
#include "lmkParse.h"
#include "lmkList.h"
#include "version.h"
#ifdef HAVE_LICENSEHANDLING
#include "license.h"
#endif

#include "impMacro.h"


/* UNIT CONSTANTS */
#ifdef WIN32
#define OFLAG _O_BINARY
#else
#define OFLAG 0
#endif

#define MAX 0x7FFFFFFF
OptTabRec tmkOptTab[] = {
  {VERBOSE_OPT,    BOOL_TMO,    "verbose", "verbose"},
  {TMKTARGET_OPT,  STR_TMO,     "target",  "target"},
  {TMKOS_OPT,      STR_TMO,     "os",      "os"},
  {TMKPREFIX_OPT,  STR_TMO,     "prefix",  "prefix"},
  {TMKLIBRARY_OPT, STR_TMO,     "library", "library"},
  {TMKESCAPE_OPT,  BOOLSTR_TMO, "escape",  "escape"},
  {WIDTH_OPT,      BOOLNUM_TMO, "width",   "width",  0, "", {0, MAX}},
  {HEIGHT_OPT,     BOOLNUM_TMO, "height",  "height", 0, "", {0, MAX}},
  {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
     "select [no] generated output {tables | source}", {0},
     {"Tables", "Source", NULL}},
  {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
     "do [not] force generating of source code"},

  {LAST_OPT}
};

OptTabRec lmkOptTab[] = {
  {VERBOSE_OPT,    BOOL_TMO,    "verbose", "verbose", FALSE, "enable[disable] verbose mode"},
  {LMKTARGET_OPT, STR_TMO, "target", "target",
   (intptr_t) "ansi-c", "set target language"},
  {TMKTARGET_OPT, STR_TMO, "target", "",
     (intptr_t) "ansi-c"},
  {LMKOS_OPT, STR_TMO, "os", "os",
#ifdef WIN32
     (intptr_t) "WIN32", "set target operating system"},
#else
     (intptr_t) "SunOS", "set target operating system"},
#endif
  {TMKOS_OPT, STR_TMO, "os", "",
#ifdef WIN32
     (intptr_t) "WIN32"},
#else
     (intptr_t) "SunOS"},
#endif
  {LMKPREFIX_OPT, STR_TMO, "prefix", "",
     (intptr_t) "lm", "set [no] prefix"},
  {TMKPREFIX_OPT, STR_TMO, "prefix", "prefix",
     (intptr_t) "tm", "set [no] prefix"},
  {LMKLIBRARY_OPT, STR_TMO, "library", "library",
     (intptr_t) "%%(TMHOME)/lib/%%(lmkTarget)/", "set library"},
  {TMKLIBRARY_OPT, STR_TMO, "library", "",
     (intptr_t) "%%(TMHOME)/lib/%%(tmkTarget)/"},
  {LMKESCAPE_OPT, BOOLSTR_TMO, "escape", "escape",
     (intptr_t) "`", "set [no] escape character"},
  {TMKESCAPE_OPT, BOOLSTR_TMO, "escape", "",
     (intptr_t) "`"},
  {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
     "select [no] generated output {tables | source}", {0},
     {"Tables", "Source", NULL}},
  {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
     "do [not] force generation of source files"},
  {LISTINGS_OPT, SET_TMO, "listings", "listings", 0x1,
     "select [no] listing functions", {0},
     {"Single", "Multiple", "Separate", NULL}},
  {INCLUDE_OPT, BOOL_TMO, "include", "include", TRUE,
     "do [not] allow nested source files"},
  {LIMIT_OPT, BOOLNUM_TMO, "limit", "limit", BOOLNUM_FALSE,
     "set [no] limit on number of messages in listings", {0, MAX}},
  {MESSAGE_OPT, ENUM_TMO, "message", "message", 1,
     "storage of messages {file | embedded}", {0}, {"file", "embedded", NULL}},
  {LMT_OPT, STR_TMO, "", "lmt <file>", (intptr_t) "",
     "use <file> for tables"},
  {TMK_OPT, STR_TMO, "", "tmk <file>", (intptr_t) "", "read common options from <file>"},
  {HELP_OPT, HELP_TMO, "", "help", 0,
     "this help information"},

  {LAST_OPT}
};

/* UNIT TYPES */

/* UNIT DATA */
char *listerName = NULL;
char *listFileName = NULL;
char *inFiles[3] = {NULL, NULL, NULL};

/* GLOBAL DATA */
lmkScContext lmkCtxt;
char lmkEscape = '`';
MessSectNodeP messSectRoot;

/* UNIT FUNCTIONS */
/*----------------------------------------------------------------------
  tmkLog()

  Interface against tmk lister messages
*/
void tmkLog(pos, ecode, sev, istrs)
     TmkSrcp *pos;		/* IN - Source position */
     int ecode;			/* IN - The error code */
     lmkSev sev;	/* IN - Severity code */
     char istrs[];		/* IN - Insert strings */
{
  lmkLog(pos, ecode, sev, istrs);
}

/*----------------------------------------------------------------------
    parse()

    parse lmk sections

*/
static Boolean parse(inFileName)
  char *inFileName;
{
  lmkCtxt = lmkScNew(lmk_MAIN_MAIN_Scanner);
  if ((lmkCtxt->fd = open(inFileName, OFLAG)) < 0)
    return FALSE;
  else {
    lmkCtxt->fileName = inFileName;
    lmkParse();
    close(lmkCtxt->fd);
  }
  return TRUE;
}

/*----------------------------------------------------------------------
    lmkGenTab

    generate lmk tables

*/
static void lmkGenTab()
{
  MessSectNodeP q;
  MessNodeP p;
  MessNodeP *mTab;
  int i;

  for (q = messSectRoot; q; q = q->next) {
    mTab = (MessNodeP *) malloc(q->messCnt * sizeof(MessNodeP));
    for (i = 0, p = q->messages; p; i++, p = p->next)
      mTab[i] = p;

    /* SORTING... */

    q->messTab = mTab;
  }
}

/*----------------------------------------------------------------------
    main



*/
int main(argc, argv)
    int argc;
    char *argv[];
{
  FILE *lmtFile;
  char *ext1, *ext2;
  char *fileName;
  TokenNodeP tokenNode = NULL, tmpToken = NULL;
  SrcpNodeP srcpNode = NULL, tmpSrcp = NULL;
  CodeNodeP importSection = NULL;
  CodeNodeP lmkImportSection = NULL;
  Boolean tmkExists;
  int ecode = 0;

#ifdef WIN32
#ifdef TMTEST
    freopen("stderr.txt", "w", stderr);
#else
    /* 4f - redirect to stderr to stdout */
#endif
#endif

#ifdef _AMOSDEV
  /* Print welcome greetings */
  printf("%s\n", product.longHeader);
  printf("Licensed to ASTRA for AMOS CLD/CLR Development\n");
  /* Temporarily initialize lister */
  lmkLiInit(product.version.string, "", lmk_AMOS_Messages);
#else
  /* Temporarily initialize lister */
  lmkLiInit(product.version.string, "", lmk_ENGLISH_Messages);
#endif

  /* License handling */
#ifdef HAVE_LICENSEHANDLING
  switch(license()) {
  case LICENSE_OK:
    break;
  case LICENSE_EXPIRED:
    lmkLog((TmkSrcp *)NULL,500,sevFAT,"");
    break;
  case LICENSE_DENIED:
    lmkLog((TmkSrcp *)NULL,501,sevFAT,"");
    break;
  case LICENSE_FORMAT_ERROR:
    lmkLog((TmkSrcp *)NULL,502,sevFAT,"");
    break;
  case LICENSE_NO_SERVER:
    lmkLog((TmkSrcp *)NULL,503,sevFAT,"");
    break;
  case LICENSE_NO_FILE:
    lmkLog((TmkSrcp *)NULL,504,sevFAT,"");
    break;
  case LICENSE_ILLEGAL_PASSWORD:
    lmkLog((TmkSrcp *)NULL,505,sevFAT,"");
    break;
  default:
    lmkLog((TmkSrcp *)NULL,506,sevFAT,"");
    break;
  }
#endif

  if (lmkSeverity() & (sevERR+sevFAT+sevSYS)) {
    lmkListm("", 0, 0x7FFFFFFF, liTINY, sevOK+sevWAR+sevERR+sevFAT+sevSYS, inFiles);
    exit(lmkSeverity());
  }

  /* CLI OPTIONS */
  initOpts(LAST_OPT, lmkOptTab);
  setCliOpts(lmkOptTab, argc, argv, &listerName);

  inFiles[1] = (char *) malloc(strlen(listerName) + 5);
  strcpy(inFiles[1], listerName);

  ext1 = (char *)strrchr(inFiles[1], '.');
#ifdef WIN32
  ext2 = ext1 ? strpbrk(ext1, "/\\") : NULL;
#else
  ext2 = (char *)strrchr(inFiles[1], '/');
#endif
  /* Check for .lmk suffix and add one if missing */
  if ((ext1 == NULL) || (ext2 > ext1)) {
    strcat(inFiles[1], ".lmk");
    ext1 = (char *)strrchr(inFiles[1], '.');
  }/*if*/
  listerName[ext1 - inFiles[1]] = '\0';

  if (optAssigned(TMK_OPT)) {
    char *tmp;
    tmp = getStrOpt(TMK_OPT);
    inFiles[0] = (char*)malloc(strlen(tmp)+1);
    strcpy(inFiles[0], tmp);
  } else {
    inFiles[0] = (char *)malloc(strlen(listerName) + 5);
    strcpy(inFiles[0], listerName);
    strcat(inFiles[0], ".tmk");
  }

  /* Remove the path if any */
#ifdef WIN32
  ext1 = NULL;
  ext2 = strpbrk(listerName, "/\\:");
  while (ext2)
  {
    ext1 = ext2;
    ext2 = strpbrk(ext1+1, "/\\:");
  }
  if (ext1) {
#else
  if ((ext1 = (char *)strrchr(listerName, '/')) != NULL) {
#endif
    listerName = &ext1[1];
  }/*if*/

#ifdef _AMOSDEV
  /* initialize lister */
  lmkLiInit(product.version.string, inFiles[1], lmk_AMOS_Messages);
#else
  /* initialize lister */
  lmkLiInit(product.version.string, inFiles[1], lmk_ENGLISH_Messages);
#endif

  tmkExists = tmkCParse(inFiles[0], tmkOptTab, lmkOptTab, argc, argv,
               &tokenNode, &srcpNode, &importSection, 0,
               TMK_FILE, TMKESCAPE_OPT);

  /* options in input file */
  if (tmkExists) {
    if (tmkCParse(inFiles[1], lmkOptTab, lmkOptTab, argc, argv,
         &tmpToken, &tmpSrcp, &lmkImportSection, 1,
         LMK_FILE, LMKESCAPE_OPT)) {
      if (tmpToken)
        lmkLog(NULL, 52, sevERR, "TOKEN");
      if (tmpSrcp)
        lmkLog(NULL, 52, sevERR, "SRCP");
    } else
      lmkLog(NULL, 70, sevFAT, inFiles[1]);
  } else {
    if (!tmkCParse(inFiles[1], lmkOptTab, lmkOptTab, argc, argv,
          &tokenNode, &srcpNode, &lmkImportSection, 1,
          LMK_FILE, LMKESCAPE_OPT))
      lmkLog(NULL, 70, sevFAT, inFiles[1]);
  }

  if (!SeriousErr) {
    lmkEscape = *getStrOpt(LMKESCAPE_OPT);

    /* Prefix assignment */
    mergeOptions(LMKPREFIX_OPT, TMKPREFIX_OPT, tmkExists);
    /* Library assignment */
    mergeOptions(LMKLIBRARY_OPT, TMKLIBRARY_OPT, tmkExists);
    /* Os assignment */
    mergeOptions(LMKOS_OPT, TMKOS_OPT, tmkExists);
    /* Target assignment */
    mergeOptions(LMKTARGET_OPT, TMKTARGET_OPT, tmkExists);

    if ((strcmp(getStrOpt(TMKTARGET_OPT), "c") != 0) &&
    (strcmp(getStrOpt(TMKTARGET_OPT), "ansi-c") != 0) &&
    (strcmp(getStrOpt(TMKTARGET_OPT), "c++") != 0)) {
      lmkLog(NULL, 405, sevWAR, getStrOpt(TMKTARGET_OPT));
    }

    if ((strcmp(getStrOpt(LMKTARGET_OPT), getStrOpt(TMKTARGET_OPT)) != 0) &&
    (strcmp(getStrOpt(LMKTARGET_OPT), "c") != 0) &&
    (strcmp(getStrOpt(LMKTARGET_OPT), "ansi-c") != 0) &&
    (strcmp(getStrOpt(LMKTARGET_OPT), "c++") != 0)) {
      lmkLog(NULL, 405, sevWAR, getStrOpt(LMKTARGET_OPT));
    }

    if (getBoolOpt(VERBOSE_OPT)) {
      printf("%s\n", product.longHeader);
    }

    if (!srcpNode)
      lmkLog(NULL, 64, sevERR, "SRCP");

    /* parse lister description */
    if (!SeriousErr)
      parse(inFiles[1]);

    if (messSectRoot == NULL)
      lmkLog(NULL, 300, sevERR, "");

    /* generate tables */
    if (!SeriousErr)
      lmkGenTab();

    /* output tables */
    if (!SeriousErr) {
     fileName = (char *) malloc(strlen(listerName) + 5);
      if (strcmp(getStrOpt(LMT_OPT), "") == 0) {
    strcpy(fileName, listerName);
    strcat(fileName, ".lmt");
      } else {
    strcpy(fileName, getStrOpt(LMT_OPT));
      }
      if ((lmtFile = fopen(fileName, "wb")) == NULL)
    lmkLog(NULL, 71, sevFAT, fileName);
      else {
    lmkTab(lmtFile, messSectRoot, tokenNode, srcpNode,
           importSection, lmkImportSection);
    fclose(lmtFile);
      }
    }

    /* Print a TINY list on the terminal */
    if (lmkSeverity() != sevOK)
#ifdef SEPL
      lmkListsi("", 0, 78, liTINY);
      lmkLists(sevALL, 0, inFiles[0]);
      lmkLists(sevALL, 1, inFiles[1]);
      lmkListse(sevALL);
#else
      lmkListm("", 0, 78, liTINY, sevALL, inFiles);
#endif

    /* And a list file if asked to. */
    if (listFileName != NULL) {
      lmkListm(listFileName, 60, 132, liFULL, sevALL, inFiles);
    }

#ifdef SHOWJUNK
    /* JUNK DISPLAY SECTION */
    printDb(lmkOptTab, stderr);
    if (messSectRoot)
      { MessNodeP p;
    printf("\nName: %s\n", messSectRoot->name);
    printf("Messages:\n");
    for (p=messSectRoot->messages; p; p=p->next)
      printf("%4i %s\n", p->number, p->text);
      }
    /* EOJ (END OF JUNK) */
#endif

  } else {
#ifdef SEPL
    lmkListsi("", 0, 78, liTINY);
    lmkLists(sevALL, 0, inFiles[0]);
    lmkLists(sevALL, 1, inFiles[1]);
    lmkListse(sevALL);
#else
    lmkListm("", 0, 78, liTINY, sevALL, inFiles);
#endif
  }
  lmkLiTerminate();
  if (!SeriousErr && (getSetOpt(GENERATE_OPT)&0x2)) {
    ecode = impMacro(fileName, NULL, "", envBit, 0, lmkEscape, &ecode) & (sevERR | sevFAT | sevSYS);
    if (ecode == 0 && !(getSetOpt(GENERATE_OPT)&0x1))
      unlink(fileName);
    return(ecode);
  } else
    return SeriousErr;
}
