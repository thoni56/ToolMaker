/*-----------------------------------------------------------------------------
 * pm - ParserMaker main program.
 *      @(#)pmk.c	1.3 (90/10/18 13:36:42)
 *-----------------------------------------------------------------------------
 * Created:	92-08-26 by H}kan. Copied from older pm.c and modified
 * Modified:
 *-----------------------------------------------------------------------------
 * Entries:
 *	main
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef WIN32
#include <io.h>
#endif
#ifdef HAVE_LICENSEHANDLING
#include "license.h"
#endif
#include "timing.h"
#include "tmk.h"
#include "pmk_i.h"
#include "version.h"
#include "pmkList.h"
#include "pmkScan.h"
#include "pmkParse.h"
#include "pmkTab.h"
#include "pwsGrm.h"
#include "pwGe.h"
#include "pwPack.h"
#include "pwLog.h"
#include "pws.h"

#include "impMacro.h"

static SETDEF(sym_kind_set, unknown_symb + 1); /* For lookup calls */

#define MAX 0x7FFFFFFF

OptTabRec tmkOptTab[] = {
    {VERBOSE_OPT, BOOL_TMO,    "verbose", "verbose"},
    {TMKTARGET_OPT,  STR_TMO,     "target",  "target"},
    {TMKOS_OPT,      STR_TMO,     "os",      "os"},
    {TMKPREFIX_OPT,  BOOLSTR_TMO, "prefix",  "prefix"},
    {TMKLIBRARY_OPT, STR_TMO,     "library", "library"},
    {TMKESCAPE_OPT,  BOOLSTR_TMO, "escape",  "escape"},
    {HEIGHT_OPT,  BOOLNUM_TMO, "height",  "height", 0, "", {0, MAX}},
    {WIDTH_OPT,   BOOLNUM_TMO, "width",   "width",  0, "", {0, MAX}},
    {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
        "select [no] generated output {tables | source}", {0},
        {"Tables", "Source", NULL}},
    {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
        "do [not] force generation of source code"},
    {LAST_OPT}
};

OptTabRec pmkOptTab[] = {
    {VERBOSE_OPT, BOOL_TMO, "verbose", "verbose", FALSE,
        "enable[disable] verbose mode"},
    {PMKTARGET_OPT, STR_TMO, "target", "target <lang>", (unsigned) "ansi-c",
        "generate file for target language <lang>"},
    {TMKTARGET_OPT, STR_TMO, "", "", (unsigned) "ansi-c",
        ""},
#ifdef WIN32
    {PMKOS_OPT, STR_TMO, "os", "os <os>", (unsigned) "WIN32",
        "generate source files for target operating system <os>"},
#else
    {PMKOS_OPT, STR_TMO, "os", "os <os>", (unsigned) "SunOS",
        "generate source files for target operating system <os>"},
#endif
#ifdef WIN32
    {TMKOS_OPT, STR_TMO, "", "", (unsigned) "WIN32", ""},
#else
    {TMKOS_OPT, STR_TMO, "", "", (unsigned) "SunOS", ""},
#endif
    {PMKPREFIX_OPT, BOOLSTR_TMO, "prefix", "prefix [<prefix>]", (unsigned) "pm",
     "set [no] parser prefix"},
    {TMKPREFIX_OPT, BOOLSTR_TMO, "", "", (unsigned) "tm",
     "set [no] system prefix"},
    {PMKLIBRARY_OPT, STR_TMO, "library", "library <lib>",
     (unsigned) "%%(TMHOME)/lib/%%(pmkTarget)/", "use directory <lib> for library files"},
    {TMKLIBRARY_OPT, STR_TMO, "", "",
     (unsigned) "%%(TMHOME)/lib/%%(tmkTarget)/", ""},
    {PMKESCAPE_OPT, BOOLSTR_TMO, "escape", "escape [<c>]", (unsigned) "`",
     "set [no] escape character"},
    {TMKESCAPE_OPT, BOOLSTR_TMO, "", "", (unsigned) "`",
     "set [no] escape character"},
    {WIDTH_OPT, BOOLNUM_TMO, "width", "width [<n>]", 78,
     "set [no] listing width", {0, MAX}},
    {HEIGHT_OPT, BOOLNUM_TMO, "height", "height [<n>]", 62,
     "set [no] listing height", {0, MAX}},
    {GENERATE_OPT, SET_TMO, "generate", "generate", 0x2,
     "select [no] generated output {tables | source}", {0},
     {"Tables", "Source", NULL}},
    {FORCE_OPT, BOOL_TMO, "force", "force", FALSE,
     "do [not] force generating of source code"},
    {LISTERPREFIX_OPT, BOOLSTR_TMO, "listerprefix", "listerprefix [<prefix>]", (unsigned) "lm",
     "set [no] lister prefix"},
    {ERRORHANDLER_OPT, BOOL_TMO, "errorhandler", "errorhandler", TRUE,
     "enable [disable] generation of error handler"},
    {TRACE_OPT, BOOL_TMO, "trace", "trace", FALSE,
     "enable [disable] trace mode"},
    {LINE_OPT, BOOL_TMO, "line", "line", FALSE,
     "do [not] generate line information in the semantic actions"},
    {LOOKAHEADMAX_OPT, NUM_TMO, "lookaheadmax", "lookaheadmax <n>", 5,
     "set max lookahead to <n>", {4, MAX}},
    {SHIFTCOST_OPT, NUM_TMO, "shiftcost", "shiftcost <n>", 5,
     "set shift cost for terminals to <n>", {0, MAX}},
    {STACKLIMIT_OPT, NUM_TMO, "stacklimit", "stacklimit <n>", 32,
     "set parse stack limit to <n> entries", {0, MAX}},
    {PACK_OPT, SET_TMO, "pack", "pack", 4,
     "set [no] table packing { row | column | rds | gcs | les }", {0},
     {"Row", "Column", "RDS", "GCS", "LES", "Error", NULL}},
    {ACTIONPACK_OPT, SET_TMO, "actionpack", "actionpack", 0x4,
     "set [no] packing of action tables", {0},
     {"Row", "Column", "RDS", "GCS", "LES", "Error", NULL}},
    {GOTOPACK_OPT, SET_TMO, "gotopack", "gotopack", 0x4,
     "set [no] packing of goto tables", {0},
     {"Row", "Column", "RDS", "GCS", "LES", NULL}},
    {LIST_OPT, SET_TMO, "list", "list", 0x20,
     "set [no] listings { input | grammar | items | tables | statistics | info }", {0},
     {"Input", "Grammar", "Items", "Tables", "Statistics", "Info", NULL}},
    {OPTIMIZE_OPT, SET_TMO, "optimize", "optimize", 0x1,
     "set [no] optimize mode", {0}, {"Lr0", NULL}},
    {RECOVERY_OPT, SET_TMO, "recovery", "recovery", 0x7,
     "set [no] recovery mode { single | multiple | panic }", {0},
     {"Single", "Multiple", "Panic", NULL}},
    {RESOLVE_OPT, SET_TMO, "resolve", "resolve", 0x1,
     "set [no] resolve mode { sr | rr }", {0},
     {"SR", "RR", NULL}},
    {VOC_OPT, STR_TMO, "", "voc <file>", (unsigned) "",
     "write vocabulary to <file>"},
    {PML_OPT, STR_TMO, "", "pml <file>", (unsigned) "",
     "write lists to <file> (if any)"},
    {PMT_OPT, STR_TMO, "", "pmt <file>", (unsigned) "",
     "write tables to <file> (if any)"},
    {TMK_OPT, STR_TMO, "", "tmk <file>", (unsigned) "",
     "read common options from <file>"},
    {HELP_OPT, HELP_TMO, "", "help", 0,
     "this help information"},
    {LAST_OPT}
};

pmkScContext pmkCtxt;

char *fileBaseName = NULL;

char *inFiles[3] = {NULL, NULL, NULL};
char *pmtFileName = NULL;
char *pmlFileName = NULL;
char *pmiFileName = NULL;
char *vocFileName = NULL;

int pwsGrm;
FILE *pwsLog = NULL;
FILE *pmTbl = NULL;

char pmkEscape = '`';

TokenNodeP tokenNode = NULL, tmpToken = NULL;
SrcpNodeP srcpNode = NULL, tmpSrcp = NULL;
CodeNodeP importSection;
extern int symRef;

/*-----------------------------------------------------------------------------
  tmkLog()

  Interface against pmkLog used by tmk
*/
void tmkLog(pos, ecode, sev, istrs)
     TmkSrcp *pos;		/* IN - Source position */
     int ecode;			/* IN - The error code */
     pmkSev sev;	/* IN - Severity code */
     char istrs[];		/* IN - Insert strings */
{
    pmkLog(pos, ecode, sev, istrs);
}

/*-----------------------------------------------------------------------------
 * pmkAppend() - append .pmi-file to .pml-file and delete .pmi-file
 */
static void pmkAppend(pml, pmi)
     char *pml;
     char *pmi;
{
  FILE *pmlFile;
  FILE *pmiFile;
  char ch;

  if (!pmi) return;

  if (!(pmlFile = fopen(pml, "a"))) {
    pmkLog(NULL, 402, sevFAT, pml);
  }
  putc('\f', pmlFile);

  pmiFile = fopen(pmi, "r");
  while ((ch = getc(pmiFile)) != EOF) {
    putc(ch, pmlFile);
  }
  fclose(pmlFile);
  unlink(pmi);
}

/*-----------------------------------------------------------------------------
 * appendStrList - put a string last in a list of strings
 */
StrListP appendStrList(str, list)
     char *str;
     StrListP list;
{
  StrListP new = (StrListP)malloc(sizeof(StrList));
  new->str = str;
  new->next = list;
  return new;
}

void printStrList(fil, list, names)
     FILE *fil;
     StrListP list;
     StrListP names;
{
  char *buff;
  while (list) {
    if (list->next)
      if (names) {
    buff = (char*) malloc(strlen(list->str)+
                  MAXNOPH * (names->str ? strlen(names->str) : 0)+1);
    fprintf(fil, "\"%s\", ", tmkReplPH(list->str, names->str, buff));
    free(buff);
      } else
    fprintf(fil, "\"%s\", ", list->str);
    else
      if (names) {
    buff = (char*) malloc(strlen(list->str)+
                  MAXNOPH * (names->str ? strlen(names->str) : 0)+1);
    fprintf(fil, "\"%s\"", tmkReplPH(list->str, names->str, buff));
    free(buff);
      } else
    fprintf(fil, "\"%s\"", list->str);
    list = list->next;
    if (names)
      names = names->next;
  }
}

/*-----------------------------------------------------------------------------
 * main
 *-----------------------------------------------------------------------------
 */
int main(argc, argv)
     int argc;	/* IN argument count. */
     char *argv[];	/* IN program arguments. */
{
    Boolean tmkExists;
    char *ext1, *ext2;
    TiBuf tb;

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
    pmkLiInit(product.version.string, "", pmk_AMOS_Messages);
#else
    pmkLiInit(product.version.string, "", pmk_ENGLISH_Messages);
#endif

#ifdef HAVE_LICENSEHANDLING
    /* License handling */
    switch(license()) {
    case LICENSE_OK:
        break;
    case LICENSE_EXPIRED:
        pmkLog((TmkSrcp *)NULL,500,sevFAT,"");
        break;
    case LICENSE_DENIED:
        pmkLog((TmkSrcp *)NULL,501,sevFAT,"");
        break;
    case LICENSE_FORMAT_ERROR:
        pmkLog((TmkSrcp *)NULL,502,sevFAT,"");
        break;
    case LICENSE_NO_SERVER:
        pmkLog((TmkSrcp *)NULL,503,sevFAT,"");
        break;
    case LICENSE_NO_FILE:
        pmkLog((TmkSrcp *)NULL,504,sevFAT,"");
        break;
    case LICENSE_ILLEGAL_PASSWORD:
        pmkLog((TmkSrcp *)NULL,505,sevFAT,"");
        break;
    default:
        pmkLog((TmkSrcp *)NULL,506,sevFAT,"");
        break;
    }
#endif

    if (pmkSeverity() & (sevERR+sevFAT+sevSYS)) {
        pmkListm("", 0, 0x7FFFFFFF, liTINY, sevALL, inFiles);
        exit(pmkSeverity());
    }

    /* Initiate option database */
    initOpts(LAST_OPT, pmkOptTab);

    /* Set command line options */
    setCliOpts(pmkOptTab, argc, argv, &fileBaseName);

    inFiles[0] = (char *)malloc(strlen(fileBaseName) + 5);
    strcpy(inFiles[0], fileBaseName);

    ext1 = (char *)strrchr(inFiles[0], '.');
#ifdef WIN32
    ext2 = ext1 ? strpbrk(ext1, "/\\") : NULL;
#else
    ext2 = (char *)strrchr(inFiles[0], '/');
#endif
    /* Check for .pmk suffix and add one if missing */
    if ((ext1  == NULL) || (ext2 > ext1)) {
        strcat(inFiles[0], ".pmk");
        ext1 = (char *)strrchr(inFiles[0], '.');
    }/*if*/

    fileBaseName[ext1 - inFiles[0]] = '\0';

    if (optAssigned(TMK_OPT)) {
        char *tmp;
        tmp = getStrOpt(TMK_OPT);
        inFiles[1] = (char*)malloc(strlen(tmp)+1);
        strcpy(inFiles[1], tmp);
    } else {
        inFiles[1] = (char *)malloc(strlen(fileBaseName) + 5);
        strcpy(inFiles[1], fileBaseName);
        strcat(inFiles[1], ".tmk");
    }

    /* Remove the path if any */
#ifdef WIN32
    ext1 = NULL;
    ext2 = strpbrk(fileBaseName, "/\\:");
    while (ext2)
        {
            ext1 = ext2;
            ext2 = strpbrk(ext1+1, "/\\:");
        }
    if (ext1) {
#else
        if ((ext1 = (char *)strrchr(fileBaseName, '/')) != NULL) {
#endif
            fileBaseName = &ext1[1];
        }/*if*/

        /* initialize lister */
#ifdef _AMOSDEV
        pmkLiInit(product.version.string, inFiles[1], pmk_ENGLISH_Messages);
#else
        pmkLiInit(product.version.string, inFiles[1], pmk_ENGLISH_Messages);
#endif

        init_grm();   /* This should be done before init_hash_sym_tbl */
        initSymTab();

        /* options in .tmk file */
        if ((tmkExists = tmkCParse(inFiles[1], tmkOptTab, pmkOptTab, argc, argv,
                                   &tokenNode, &srcpNode, &importSection, 1, TMK_FILE, TMKESCAPE_OPT))) {
        }

        /* options in input file */
        if (tmkExists) {
            if (tmkCParse(inFiles[0], pmkOptTab, pmkOptTab, argc, argv,
                          &tmpToken, &tmpSrcp, &pmkImportSection, 0, PMK_FILE, PMKESCAPE_OPT)) {
                if (tmpToken)
                    pmkLog(NULL, 52, sevERR, "TOKEN");
                if (tmpSrcp)
                    pmkLog(NULL, 52, sevERR, "SRCP");
            } else
                pmkLog(NULL, 401, sevFAT, inFiles[0]);
        } else {
            if (!tmkCParse(inFiles[0], pmkOptTab, pmkOptTab, argc, argv,
                           &tokenNode, &srcpNode, &pmkImportSection, 0, PMK_FILE, PMKESCAPE_OPT))
                pmkLog(NULL, 401, sevFAT, inFiles[0]);
        }

        if (getBoolOpt(VERBOSE_OPT)) {
            printf("%s\n", product.longHeader);
        }

        if (optAssigned(PACK_OPT)) {
            if (optAssigned(ACTIONPACK_OPT)){
                pmkLog(NULL, 166, sevFAT, "ACTIONPACK");
            } else {
                mergeOptions(ACTIONPACK_OPT, PACK_OPT, TRUE);
            }
            if (optAssigned(GOTOPACK_OPT)){
                pmkLog(NULL, 166, sevFAT, "GOTOPACK");
            } else {
                mergeOptions(GOTOPACK_OPT, PACK_OPT, TRUE);
            }
        }

        if (!SeriousErr) {
            pmkEscape = *getStrOpt(PMKESCAPE_OPT);

            if (!tokenNode)
                pmkLog(NULL, 64, sevERR, "TOKEN");
            else {
                char *str;
                int i = 0;
                TokenAttrListP attrs;
                search_kind searchResult; /* Variable used for lookup calls */

                /* Insert token attributes into vocabulary */
                attrs = tokenNode->attrs;
                str = NULL;
                while (i < 2 || attrs) {
                    switch (i) {
                    case 0:
                        if (tokenNode->srcp) {
                            str = tokenNode->srcp;
                            i = 1;
                            break;
                        }
                    case 1:
                        i = 2;
                        if (tokenNode->code) {
                            str = tokenNode->code;
                            break;
                        } else if (!attrs)
                            break;
                    default:
                        str = attrs->name;
                        attrs = attrs->next;
                        break;
                    }
                    if (!str) break;

                    SetClear(sym_kind_set, unknown_symb + 1);
                    SetIns(sym_kind_set, attr_symb);
                    lookup(str, sym_kind_set, &symRef, &searchResult);
                    if (new_search == searchResult) {
                        vocabulary[symRef]->symbol_typ = attr_symb;
                        vocabulary[symRef]->syminfo.attr_class = t_attr;
                    } else if (found_search == searchResult) {
                        if (vocabulary[symRef]->syminfo.attr_class != t_attr &&
                            vocabulary[symRef]->syminfo.attr_class != unk_attr)	{
                            vocabulary[symRef]->syminfo.attr_class = voc_attr;
                        } else if (vocabulary[symRef]->syminfo.attr_class == t_attr) {
                            /* ERROR Attribute defined twice */
                            pmkLog(NULL, 119, sevWAR, str);
                        }/*if*/
                    } else {
                        /* ERROR Ambiguous symbol. Attribute expected. */
                        pmkLog(NULL, 118, sevERR, str);
                    }/*if*/
                }
            }

            /* Prefix assignment */
            mergeOptions(PMKPREFIX_OPT, TMKPREFIX_OPT, tmkExists);
            /* Library assignment */
            mergeOptions(PMKLIBRARY_OPT, TMKLIBRARY_OPT, tmkExists);
            /* Os assignment */
            mergeOptions(PMKOS_OPT, TMKOS_OPT, tmkExists);
            /* Target assignment */
            mergeOptions(PMKTARGET_OPT, TMKTARGET_OPT, tmkExists);

            if ((strcmp(getStrOpt(TMKTARGET_OPT), "c") != 0) &&
                (strcmp(getStrOpt(TMKTARGET_OPT), "ansi-c") != 0) &&
                (strcmp(getStrOpt(TMKTARGET_OPT), "c++") != 0)) {
                pmkLog(NULL, 405, sevWAR, getStrOpt(TMKTARGET_OPT));
            }

            if ((strcmp(getStrOpt(PMKTARGET_OPT), getStrOpt(TMKTARGET_OPT)) != 0) &&
                (strcmp(getStrOpt(PMKTARGET_OPT), "c") != 0) &&
                (strcmp(getStrOpt(PMKTARGET_OPT), "ansi-c") != 0) &&
                (strcmp(getStrOpt(PMKTARGET_OPT), "c++") != 0)) {
                pmkLog(NULL, 405, sevWAR, getStrOpt(PMKTARGET_OPT));
            }

            if (strcmp(getStrOpt(PML_OPT), "") == 0) {
                pmlFileName = (char*)malloc(strlen(fileBaseName)+5);
                strcpy(pmlFileName, fileBaseName);
                strcat(pmlFileName, ".pml");
            } else {
                char *tmp;
                tmp = getStrOpt(PML_OPT);
                pmlFileName = (char*)malloc(strlen(tmp)+1);
                strcpy(pmlFileName, tmp);
            }
            if ((getSetOpt(LIST_OPT) & 1) != 0) {
                pmiFileName = (char *)malloc(strlen(fileBaseName) + 5);
                strcpy(pmiFileName, fileBaseName);
                strcat(pmiFileName, ".pmi");
                if (!(pwsLog = fopen(pmiFileName, "w")))
                    pmkLog(NULL, 402, sevFAT, pmiFileName);
            } else
                if (!(pwsLog = fopen(pmlFileName, "w")))
                    pmkLog(NULL, 402, sevFAT, pmlFileName);

            /* parse parser description */
            pmkCtxt = pmkScNew(pmk_MAIN_MAIN_Scanner);
            if (!((pmkCtxt->fd = open(inFiles[0], OFLAG)) >= 0 &&
                  (pwsGrm = open(inFiles[0], OFLAG))))
                pmkLog(NULL, 401, sevFAT, inFiles[0]);

            pmkCtxt->fileName = inFiles[0];
            if (getBoolOpt(VERBOSE_OPT)) {
                printf("\nGrammar Reading          ");
                tiStart(&tb);
            }
            pmkParse();
            if (scannerSection)
                scannerSection->fname = inFiles[0];
            if (exportSection)
                exportSection->fname = inFiles[0];
            if (insertSymbSection)
                insertSymbSection->fname = inFiles[0];
            if (deleteSymbSection)
                deleteSymbSection->fname = inFiles[0];
            if (!getBoolOpt(ERRORHANDLER_OPT) && (insertSymbSection || deleteSymbSection))
                pmkLog(NULL, 237, sevWAR, "");

            if (getBoolOpt(VERBOSE_OPT)) {
                tiStop(&tb);
                tiPrint(&tb, TiMSC);
            }

    if (!SeriousErr) {
        if (getBoolOpt(VERBOSE_OPT)) {
            printf("\nGrammar Writing          ");
            tiStart(&tb);
        }
        logInputStats();
        logGrammar();
        if (getBoolOpt(VERBOSE_OPT)) {
            tiStop(&tb);
            tiPrint(&tb, TiMSC);
        }
    }

    if (!SeriousErr) {
        if (getBoolOpt(VERBOSE_OPT)) {
            printf("\nTable Generation         ");
            tiStart(&tb);
        }/*if*/
        pwGenTab();
        if (getBoolOpt(VERBOSE_OPT)) {
            tiStop(&tb);
            tiPrint(&tb, TiMSC);
        }
    }

    if (!SeriousErr) {
        if (getBoolOpt(VERBOSE_OPT)) {
            printf("\nTable Packing            ");
            tiStart(&tb);
        }
        pwPack();
        if (getBoolOpt(VERBOSE_OPT)) {
            tiStop(&tb);
            tiPrint(&tb, TiMSC);
        }
    }

    if (!SeriousErr) {
        if (strcmp(getStrOpt(PMT_OPT), "") == 0) {
            pmtFileName = (char*)malloc(strlen(fileBaseName)+5);
            strcpy(pmtFileName, fileBaseName);
            strcat(pmtFileName, ".pmt");
        } else {
            char *tmp;
            tmp = getStrOpt(PMT_OPT);
            pmtFileName = (char*)malloc(strlen(tmp)+1);
            strcpy(pmtFileName, tmp);
        }
        if (!(pmTbl = fopen(pmtFileName, "w"))) {
            pmkLog(NULL, 403, sevFAT, pmtFileName);
        }
    }

    if (!SeriousErr) {
        if (strcmp(getStrOpt(VOC_OPT), "") == 0) {
            vocFileName = (char*)malloc(strlen(fileBaseName)+5);
            strcpy(vocFileName, fileBaseName);
            strcat(vocFileName, ".voc");
        } else {
            char *tmp;
            tmp = getStrOpt(VOC_OPT);
            vocFileName = (char*)malloc(strlen(tmp)+1);
            strcpy(vocFileName, tmp);
        }
    }

    if (!SeriousErr) {
        if (getBoolOpt(VERBOSE_OPT)) {
            printf("\nTable Writing            ");
            tiStart(&tb);
        }/*if*/
        pmTab();
        if (getBoolOpt(VERBOSE_OPT)) {
            tiStop(&tb);
            tiPrint(&tb, TiMSC);
        }
    }
    if (getBoolOpt(VERBOSE_OPT))
        printf("\n\n");

    if (pwsLog) fclose(pwsLog);
    if (pmTbl) fclose(pmTbl);
    close(pwsGrm);

    /* Print a TINY list on the terminal */
    if (pmkSeverity() != sevOK || getBoolOpt(VERBOSE_OPT)) {
        if ((getSetOpt(LIST_OPT) >> 5) & 1)
            pmkListm("", 0, 78, liTINY, sevALL, inFiles);
        else
            pmkListm("", 0, 78, liTINY, (sevWAR|sevERR|sevFAT|sevSYS), inFiles);
    }
    /* And a list file if asked to. */
    if ((getSetOpt(LIST_OPT) & 1) != 0) {
        if ((getSetOpt(LIST_OPT) >> 5) & 1)
            pmkListm(pmlFileName, 60, 132, liFULL, sevALL, inFiles);
        else
            pmkListm(pmlFileName, 60, 132, liFULL, (sevWAR|sevERR|sevFAT|sevSYS), inFiles);
    }
    /* JUNK DISPLAY SECTION */
    /*    printDb(pmkOptTab, stderr);*/

  } else  {
      if ((getSetOpt(LIST_OPT) >> 5) & 1)
          pmkListm("", 0, 78, liTINY, sevALL, inFiles);
      else
          pmkListm("", 0, 78, liTINY, (sevWAR|sevERR|sevFAT|sevSYS), inFiles);
  }/*if*/

  pmkLiTerminate();
  pmkAppend(pmlFileName, pmiFileName);

  if (!SeriousErr && getSetOpt(GENERATE_OPT)&0x2) {
      int ecode;

      ecode = impMacro(pmtFileName, NULL, "", envBit, 0, pmkEscape, &ecode) & (sevERR | sevFAT | sevSYS);
      if (ecode == 0 && !(getSetOpt(GENERATE_OPT)&0x01))
          unlink(pmtFileName);
      return(ecode);
  } else
      return SeriousErr;
}/*main()*/
