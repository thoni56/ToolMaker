/*-----------------------------------------------------------------------------
 * impMacro - The macro processor main routine.
 * @(#)impMacro.c       1.2 (91/04/30 16:54:42)
 *-----------------------------------------------------------------------------
 * Created:     87-10-28 by Tom
 * Modified:    89-09-28 by Tom. Moved to Sun and Sws2.
 *              89-10-25 by Tom. mwsSetVar introduced.
 *              89-11-21 by Tom. Renamed to IMP.
 *              90-03-14 by Tom. Interface to impMacro changed, environment
 *                               variable support introduced.
 *              90-06-07 by Tom. impSetVar changed to handle integers also.
 *                               License check removed.
 *              90-06-27 by Tom. Bug fix: string lengths in impSetVar incr.
 *                               Bug fix: wrong file name passed to impInit.
 *              90-12-03 by Tom. impSetVar changed to allow empty values.
 *-----------------------------------------------------------------------------
 * Entries:
 *      impSetVar
 *      impMacro
 *-----------------------------------------------------------------------------
 */

#ifdef vms
#define HOME "dua1:[root.ToolMaker]"
#else
#ifdef WIN32
#define HOME "C:\\Program\\ToolMaker"
#else
#define HOME "/usr/local/ToolMaker"
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifdef WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include "impMacro.h"
#include "impList.h"
#include "impScan.h"
#include "impParse.h"
#include "ast.h"
#include "name.h"
#include "timing.h"
#include "version.h"

#ifdef MINGW
#define OFLAG _O_TEXT
#else
#ifdef WIN32
#define OFLAG _O_BINARY
#else
#define OFLAG 0
#endif
#endif

/* Internal data */
static char *inFileName;
static FILE *outFile;
FILE *impCcFile;

/* Global data */
int impFileNo;
int impExitCode;
char impEsc;            /* Escape character in macro files */
ImpBoolean impLastPass;
ImpBoolean impUseEnv;
ImpBoolean impCodeCov;
jmp_buf jmpEnv;
jmp_buf jmpExit;                /* Where to jump on %%EXIT() */

static TiBuf tb;                /* Timing buffer */

impScContext impcontext;
typedef enum TokenType {
    STRING,
    ID,
    INTEGER,
    COMMA,
    LPAR,
    RPAR,
    UNKNOWN
} TokenType;


/*-----------------------------------------------------------------------------
 * strScan - Scan a token from a string
 *-----------------------------------------------------------------------------
 */
static TokenType strScan(str, ind, chars)
char *str;                      /* IN the string to scan */
int *ind;                       /* INOUT the current index in str */
char *chars;                    /* OUT the scanned characters if pertinent */
{
    while (isspace(str[*ind])) (*ind)++;
    if (isdigit(str[*ind])) {
    while (isdigit(str[*ind])) *(chars++) = str[(*ind)++];
    if (!(isalnum(str[*ind]) || str[*ind] == '_')) {
        *chars = '\0';
        return INTEGER;
    }/*if*/
    }/*if*/
    if (isalnum(str[*ind]) || str[*ind] == '_') {
    while (isalnum(str[*ind]) || str[*ind] == '_') {
        *(chars++) = str[(*ind)++];
    }/*while*/
    *chars = '\0';
    return ID;
    } else {
    switch (str[(*ind)++]) {

    case '"':
/*      *(chars++) = '"'; */
        for (;;) {
        if (str[*ind] == '\0') return UNKNOWN;
        else if (str[*ind] == '"') {
            *(chars++) = str[(*ind)++];
            if (str[*ind] != '"') {
/*                      *chars = '\0'; */
            *(chars-1) = '\0';
            return STRING;
            }/*if*/
        }/*if*/
        *(chars++) = str[(*ind)++];
        }/*for*/

    case ',':
        return COMMA;

    case '(':
        return LPAR;

    case ')':
        return RPAR;

    default:
        return UNKNOWN;

    }/*switch*/
    }/*if*/
}/*strScan()*/


/*-----------------------------------------------------------------------------
 * impSetVar - Sets a variable prior to a macro processor call.
 *-----------------------------------------------------------------------------
 */
int impSetVar(str)
char *str;                      /* IN variable string, format "Var(val, ...)"*/
                /* RET non-zero if syntax error */
{
    int ind = 0;
    char *val, *var, *valdup;
    TokenType tok;

    val = (char*)malloc(strlen(str)+1); /* Just to be sure */
    if (!val) {
      return -1;
    }
    var = (char*)malloc(strlen(str)+1); /* Just to be sure */
    if (!var) {
      return -1;
    }

    tok = strScan(str, &ind, var);
    if (!(tok == ID)) return 1;
    if ((tok = strScan(str, &ind, val)) != LPAR) return 1;
    for (;;) {
      switch (strScan(str, &ind, val)) {

      case INTEGER:
    if (tok == LPAR || tok == COMMA) {
      valdup = strdup(val);
      if (!valdup)
        return -1;
      impNameAppend(var, impAstNode(nulSrcp, nulSrcp, nulSrcp,
                    AST_INTEGER, strlen(val), valdup,
                    NULL, NULL, NULL, NULL));
      tok = INTEGER;
    } else return 1;
    break;

      case ID:
    if (tok == LPAR || tok == COMMA) {
      valdup = strdup(val);
      if (!valdup)
        return -1;
      impNameAppend(var, impAstNode(nulSrcp, nulSrcp, nulSrcp,
                    AST_UNQUOTED_STRING, strlen(val), valdup,
                    NULL, NULL, NULL, NULL));
      tok = ID;
    } else return 1;
    break;

      case STRING:
    if (tok == LPAR || tok == COMMA) {
      valdup = strdup(val);
      if (!valdup)
        return -1;
      impNameAppend(var, impAstNode(nulSrcp, nulSrcp, nulSrcp,
                    AST_STRING, strlen(val), valdup,
                    NULL, NULL, NULL, NULL));
      tok = STRING;
    } else return 1;
    break;

      case COMMA:
    if (tok != COMMA) tok = COMMA;
    else return 1;
    break;

      case RPAR:
    if (tok == COMMA) return 1;
    if (tok == LPAR) impNameAppend(var, NULL);
    return 0;

      default:
    return 1;
      }/*switch*/
    }/*for*/
  }/*impSetVar()*/

/*-----------------------------------------------------------------------------
 * impMacro - The MACRO processor entry.
 *-----------------------------------------------------------------------------
 */
int impMacro(inName, outName, msgName, flags, listType, escChar, exitCode)
     char *inName;              /* IN input file name */
     char *outName;             /* IN output file name or empty */
     char *msgName;             /* IN file name for imp message file */
     long flags;                /* IN the various flag values */
     int listType;              /* IN type of list or zero */
     int escChar;               /* IN escape character */
     int *exitCode;             /* OUT exit code from %%EXIT(), 0 if not */
{

  char *listFileName, *libPath, *tail, *codeCovFile;
  Ast topAst;
  int fd;

  if (!setjmp(jmpEnv)) {
    *exitCode = 0;
    impExitCode = 0;

    inFileName = malloc(strlen(inName) + 5);
    if (!inFileName) {
      if (!(impAstGarb() && (inFileName = malloc(strlen(inName) + 5))))
    longjmp(jmpEnv, 1);
    }
    strcpy(inFileName, inName);

    if ((libPath = (char *)getenv("TMHOME")) == NULL) libPath = HOME;

    /* Check for .imp extension and add one if missing.
     */
    if ((fd=open(inFileName,OFLAG)) < 0) {
#ifdef WIN32
      tail = strrchr(inFileName, '.');
      if (tail && strpbrk(tail, "/\\"))
    tail = NULL;
      if (!tail) {
#else
      if ((((tail = strrchr(inFileName, '/')) != 0) &&
       (strrchr(tail, '.') == 0)) ||
      (strrchr(inFileName, '.') == 0)) {
#endif
    strcat(inFileName, ".imp");
      }/*if*/
      fd = open(inFileName, OFLAG);
    }

    impLiInit(product.version.string, inFileName, imp_ENGLISH_Messages);

    /* Create list file name if listing should be done.
     */
    if (listType) {
      listFileName = malloc(strlen(inName) + 5);
      if (!listFileName) {
    if (!(impAstGarb() && (listFileName = malloc(strlen(inName) + 5))))
      longjmp(jmpEnv, 1);
      }
      strcpy(listFileName, inFileName);
      strcpy(strrchr(listFileName, '.'), ".iml");
    }/*if*/

    /* Create code coverage file if code coverage should be reported */
    if (flags & covBit) {
      codeCovFile = malloc(strlen(inName) + 5);
      if (!codeCovFile) {
    if (!(impAstGarb() && (codeCovFile = malloc(strlen(inName) + 5))))
      longjmp(jmpEnv, 1);
      }
      strcpy(codeCovFile, inFileName);
      strcpy(strrchr(codeCovFile, '.'), ".imc");
      if (!(impCcFile = impWriteOpen(codeCovFile, &nulSrcp))) {
    impMyLog(&nulSrcp, 207, sevERR, codeCovFile);
      }
    } else impCcFile = NULL;

    /* Open output file if it is given.
     */
    if (outName != NULL && outName[0] != 0) {
      if ((outFile = impWriteOpen(outName, &nulSrcp)) != NULL) {
    impInitOutput(outFile);
      } else {
    impInitOutput(NULL);
    impMyLog(&nulSrcp, 207, sevERR, outName);
      }/*if*/
    } else {
      outFile = (FILE*)0;
      impInitOutput(stdout);
    }/*if*/

    impEsc = escChar;
    impFileNo = 0;
    impLastPass = !(flags & intBit);
    impUseEnv = flags & envBit;
    impCodeCov = flags & covBit;

    impcontext = impScNew(imp_MAIN_MAIN_Scanner);
    if((impcontext->fd = fd) < 0)
      perror(inFileName),exit(1);
    impcontext->fileNo = 0;

#ifdef DEBUG
    printf("--------------------------------------------------\n");
#endif
    tiStart(&tb);
    impParse();
    topAst = impAstRoot;
#ifdef DEBUG
    printf("--------------------------------------------------\n");
#endif
  } else {
    impMyLog(&nulSrcp, 304, sevSYS, "");
  }

  /* Print a TINY list on the terminal if errors detected or if verbose
   * mode.
   */
  if (impSeverity() != sevOK) {
    impList("", 0, 78, liTINY, sevALL);
  } else {

    if (!setjmp(jmpEnv)) {
      if (!setjmp(jmpExit))
        impInterpretAst(topAst);
      else
        *exitCode = impExitCode;
      if (impCodeCov) {
        impReportFile = inFileName;
        impReportCnt(topAst);
        impReportFiles();
      }
    } else {
      impMyLog(&nulSrcp, 304, sevSYS, "");
    }
    impFreeAst(topAst);
    impFreeSymtabs();
    impScDelete(impcontext);
    tiStop(&tb);
    if (flags & verbBit) {
      printf("\nImping %s \nExecution time:  ", inFileName);
      tiPrint(&tb, TiMSC);
      printf("\n");
    } /*if*/
    if (impSeverity() != sevOK || flags & verbBit)
      impList("", 0, 78, liTINY, sevALL);
    /*      nameDump(stdout);*/
  }

  /* And a list file if asked to.
   */
  if (listType) {
    impList(listFileName, 60, 78, listType, sevALL);
  }/*if*/

  impLiTerminate();
  if (listType) free(listFileName);
  if (flags & covBit) free(codeCovFile);
  free(inFileName);
  if (outFile)
    impWriteClose(outFile);
  if (impCcFile)
    impWriteClose(impCcFile);
  return impSeverity();
}/*impMacro()*/
