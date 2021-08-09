/*--------------------------------------------------------------------*\
    toolmake.c                        Date: 1993-10-28/reibert@roo

    toolmake - main program

    Author: Reibert Arbring.

    History:
    2.0     1993-04-17/reibert@roo - ToolMaker 2.0, spa 4.0, no update
    1.2(0)  1991-02-21/reibert@roo - SAR: 90-020, new spa
    1.1(0)  1990-08-09/tony@kix - make TMHOME available as _TMHOME
    1.1(0)  1990-06-08/reibert@roo - C++, ANSI-C
    1.0(1)  1990-01-09/tools@roo - License checking
    1.0(0)  1990-01-08/tools@roo - Apollo
    1.0(1)a 89-12-13/reibert@roo - Simplified, update mode
    1.0(0)a 89-12-01/reibert@roo - First shot

    Copyright (c) 1991, 1993 SoftLab ab
\*--------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "toolmake.h"
#include "version.h"
#include "system.h"
#include "spa.h"
#include "ask.h"

#include "license.h"


PRIVATE char
    *tmDir = NULL,              /* $TMHOME for the session */
    *libDir = NULL,             /* $TMHOME/lib */
    *languageDir = NULL,        /* $TMHOME/lib/"language" */
    sysName[256] = { 0 };       /* Subsystem name */


#ifdef DBG
PRIVATE boolean
    debug;                      /* -debug option */
#else
#define debug FALSE;
#endif
PRIVATE boolean
    go,                         /* -go option */
    verbose,                    /* -verbose option */
    pmk = TRUE,                 /* Parser wanted */
    smk = TRUE,                 /* Scanner wanted */
    lmk = TRUE,                 /* Lister wanted */
    tm = TRUE,                  /* A toolmaker part is wanted */
    mm = TRUE,                  /* Main program wanted */
    mk = TRUE,                  /* Make file wanted */
    voc = FALSE,                /* A vocabulary file wanted */
    gen = TRUE,                 /* Something shall be generated */
    alwaysOverWrite = FALSE;    /* Overwrite existing files */


/*======================================================================
    perr() - writer of error messages

    The message is written as "name: severity![ desc[: add]]".
    The flag verbose (and possibly debug) controls writing.
    Exits on serious errors [FS].
*/
PUBLIC void perr(sev, desc, add)
    char sev;           /* IN - [(D)IWEFS] */
    char *desc;         /* IN - NULL-optional description */
    char *add;          /* IN - NULL-optional addendendum */
{
    if (add) spaAlert(sev, "%s: %s", desc, add);
    else spaAlert(sev, "%s", desc);
}

/*======================================================================

*/
PRIVATE void getSystemName()
{
    if (!go) {
        askString("Subsystem name", sysName, 16,
                  "A ToolMaker subsystem name", *sysName? 0: A_NDV+A_NSD);
    }
    dperr("System name", sysName);
}


/***********************************************************************
    Language info menue
*/

typedef enum { lC, lCansi, lCxx, lADA, lPAS } LangIx;

PRIVATE char
    *languages[] = { "C", "ANSI-C", "C++", /*"ADA", "PASCAL", "MODULA-2"*/ NULL },
    *langDir[] = { "c", "ansi-c", "c++"/*, "ada" , "p" */},
    *langExt[] = { "c", "c", "cc"/*, "ada" , "p" */};

PRIVATE LangIx lIx = lCansi;    /* Default language */


PRIVATE void establishLanguage()
{
    languageDir = makePathName(libDir, langDir[lIx]);
    if (! isDir(languageDir))
        perr('F', "Language library not found", languageDir);

    dperr("Language", languages[lIx]);
}

PRIVATE void getLanguage()
{
    if (!go) {
        askSet(askCommandPrompt, (long)"? ");
        askCom("Target language", (int *)&lIx, languages, NULL, 0);
        askSet(askCommandPrompt, (long)"> ");
    }
    establishLanguage();
}



/***********************************************************************
    Level menue
*/

PRIVATE char
    *levels[] = { "MINIMAL", "NORMAL", "EXAMPLE", NULL };

typedef enum {
    aSmal, aNorm, aExam,
} Level;

PRIVATE Level gType = aNorm;


PRIVATE void getLevel()
{
    if (!go) {
        askSet(askCommandPrompt, (long)"? ");
        askCom("Level", (int *)&gType, levels, NULL, 0);
        askSet(askCommandPrompt, (long)"> ");
    }

    dperr("Level", levels[gType]);
}


/***********************************************************************
   Action (main) menue
*/

PRIVATE char *acts[] = {
    "GENERATE", "QUIT",
    "ALL", "NONE",
    "PARSER", "SCANNER", "LISTER", "MAIN", "MAKEFILE",
    "LEVEL", "LANGUAGE",
    "VERBOSE", "HELP", "INFORMATION",
    NULL
};

typedef enum {
    aGen, aQuit,
    aAll, aNone,
    aPars, aScan, aList, aMain, aMake,
    aLevel, aLanguage,
    aVerbose, aHelp, aInf,
} Act;


PRIVATE void actionHelp()
{
    printf("\
\nExecution commands:\n\
  %-14s -- Generate selected components\n\
  %-14s -- Quit from %s\n\
\nSelection commands:\n\
  %-14s -- Select all\n\
  %-14s -- Select none\n\
  %-14s -- Toggle selection for parser files\n\
  %-14s -- Toggle selection for scanner files\n\
  %-14s -- Toggle selection for lister files\n\
  %-14s -- Toggle selection for main module files\n\
  %-14s -- Toggle selection for makefile\n\
\nSpecification commands:\n\
  %-14s -- Set level for files generation\n\
  %-14s -- Set target language\n\
\nand ...\n\
  %-14s -- Toggle verbose information\n\
  %-14s -- This help\n\
  %-14s -- Information about selection\n\
\n",
           acts[aGen], acts[aQuit], product.abbreviation,
           acts[aAll], acts[aNone],
           acts[aPars], acts[aScan], acts[aList], acts[aMain], acts[aMake],
           acts[aLevel], acts[aLanguage],
           acts[aVerbose], acts[aHelp], acts[aInf]
);
}

PRIVATE void printSelection()
{
    printf("\nSpecified: \n");
    printf("  Subsystem: %s\n", sysName);
    printf("  Target language: %s (%s)\n\n", languages[lIx], languageDir);
    if (gen) {
        printf("Selected: ");
        if (pmk) printf("%s ", acts[aPars]);
        if (smk) printf("%s ", acts[aScan]);
        if (lmk) printf("%s ", acts[aList]);
        if (mm) printf("%s ", acts[aMain]);
        if (mk) printf("%s ", acts[aMake]);
        printf("\n\nLevel: %s", levels[gType]);
    } else printf("Nothing to generate!");
    printf("\n\n");
}

PRIVATE void getActions()
{
    Act actO, actN;

    actO = actN = (gen? aGen: aQuit);

    for (;;) {
        if (!go) askCom(product.abbreviation, (int *)&actN, acts, NULL, 0);
        tm = pmk | smk | lmk;
        gen = tm | mm | mk;
        switch (actN) {
        case aGen : goto EXIT;
        case aQuit: exit(GOOD);
        case aVerbose:
            verbose = !verbose;
#ifdef DBG
            SpaAlertLevel = debug? 'D': (verbose? 'I': 'W');
#else
            SpaAlertLevel = verbose? 'I': 'W';
#endif
            printf("Verbose mode is now %s!\n", (verbose? "ON": "OFF"));
            actN = actO;
            break;
        case aHelp: actionHelp(); actN = actO; break;
        case aInf : printSelection(); actN = actO; break;
        case aAll : pmk = smk = lmk = mm = mk = TRUE; actN = aGen; break;
        case aNone: pmk = smk = lmk = mm = mk = FALSE; actN = aQuit; break;
        case aPars: pmk = !pmk; actN = aGen; break;
        case aScan: smk = !smk; actN = aGen; break;
        case aList: lmk = !lmk; actN = aGen; break;
        case aLevel: getLevel(); actN = aGen; break;
        case aLanguage: getLanguage(); actN = aGen; break;
        case aMain: mm = !mm; actN = aGen; break;
        case aMake: mk = !mk; actN = aGen; break;
        default: spaAlert('S', "getActions(): switch error (%d)", actN);
        }
        actO = actN;
    }
 EXIT:
    if ( !pmk ) {
        /* Ask if voc wanted */
        voc = TRUE;
        askBool(
            "Do you want a vocabulary file generated",
            &voc,
            "Although you have selected a scanner without parser, you\n\
can use a vocbulary file with your scanner description",
            NULL, 0);
    }
}


/***********************************************************************
    File creation handling.
*/

PRIVATE char *fa[] = {
    "GENERATE",
    "RENAME",
    "SKIP",
    "QUIT",
    "CONTINUE",
    "HELP",
    "!",
    NULL,
};

typedef enum {
    F_OW, F_REN, F_SKIP,
    F_QUIT, F_CONT,
    F_HELP, F_SH
} FAnswer;

char *okToWrite(n)
    char *n;
{
    FAnswer answer;
    char nn[256], *tmp;

    if (isFile(n)) {
        perr('W', "File exists", n);
        if (!alwaysOverWrite) {
        AGAIN:
            answer = (FAnswer) 0;
            askCom("File action", (int *)&answer, fa, NULL, 0);
            switch(answer) {
            case F_CONT: alwaysOverWrite = TRUE; /* Fall thru... */
            case F_OW: break;
            case F_REN:
                askString("Rename target to", nn, 256,
                     "Please give a file name (relative to current directory)",
                      A_NDV+A_NSD);
                tmp = okToWrite(nn);
                return (tmp? newString(tmp): NULL);
            case F_SKIP: return NULL;
            case F_SH: system("$SHELL"); goto AGAIN; break;
            case F_QUIT: exit(GOOD);
            case F_HELP: printf("\
The file to be generated (%s) exists, please decide action:\n\n\
  %-14s -- generate this file again (will destroy old content)\n\
  %-14s -- rename this file\n\
  %-14s -- do not generate this file (but continue %s)\n\
  %-14s -- generate this and all remaiding files\n\
  %-14s -- exit %s immediatly\n\
  %-14s -- visit subshell\n\
  %-14s -- this help\n\
\n",
                    n, fa[F_OW], fa[F_REN],
                    fa[F_SKIP], product.abbreviation,
                    fa[F_CONT],
                    fa[F_QUIT], product.abbreviation,
                    fa[F_SH], fa[F_HELP]);
                goto AGAIN;
                break;
            default: spaAlert('S', "okToWrite(): switch error (%d)", answer);
            }
        }
        backup(n);
    }
    return n;
}

#ifndef IMPSYS
#include "impMacro.h"

PRIVATE assertVar(int i, char* n) {
    if (i!=0) spaAlert('S', "IMP failed to set %s (error code %d)", n, i);
}

PRIVATE setStrVar(char *var, char *val) {
    char buf[1024];

    sprintf(buf, "%s(\"%s\")", var, val);
    dperr("impSetVar", buf);
    assertVar(impSetVar(buf), var);
}

#define sevNONE 0
#define sevOK   (1<<0)
#define sevINF  (1<<1)
#define sevWAR  (1<<2)
#define sevERR  (1<<3)
#define sevFAT  (1<<4)
#define sevSYS  (1<<5)

PRIVATE void impFile(dir, from, to)
    char *dir, *from, *to;
{
    char buf[1024], *ff, *tf;
    int exitcode = 0, ie;

    ff = makePathName(dir, from);
    dperr("Impify", ff);
    tf = to;
    dperr("to", tf);

    if (!isFile(ff)) {
        perr('E', "File not found", ff);
        goto EXIT;
    }
    if ( (tf = okToWrite(tf))==NULL ) goto EXIT;

    setStrVar("_D", getDate(0));
    setStrVar("_T", getTime(0));

    setStrVar("_P", product.abbreviation);
    setStrVar("_sN", sysName);
    setStrVar("_lN", languageDir);
    setStrVar("_Lvl", levels[gType]);
    setStrVar("_tOS", targetOS);
    setStrVar("_tL", languages[lIx]);
    setStrVar("_mm", (mm ? "YES" : "NO"));
    setStrVar("_tX", langExt[lIx]);
    setStrVar("_tD", langDir[lIx]);

    sprintf(buf, "_V(v%d, r%d, c%d)",
            product.version.version, product.version.revision,
            product.version.correction/*, product.version.state, */);
    dperr("impSetVar", buf);
    assertVar(impSetVar(buf), "_V");

    sprintf(buf, "_i(%s%s%s%s%s)",
            (pmk? "pm, ": ""),
            (smk? "sm, ": ""),
            (lmk? "lm, ": ""),
            (voc? "voc, ": ""),
            (tm ? "tm"  : "\"\""));
    dperr("impSetVar", buf);
    assertVar(impSetVar(buf), "_i");

    perr('I', "Generating", tf);
    ie = impMacro(ff, tf, "", envBit, 0, '`', &exitcode);

    if (exitcode)
        spaAlert('F', "skeleton file halted with error code %d", exitcode);
    if (ie>sevOK)
        spaAlert('S',  "IMP failed (error level %d)", ie);
 EXIT:
    free(ff); /* free(tf); -- not malloc'd */
}

#else

PRIVATE void impFile(dir, from, to)
    char *dir, *from, *to;
{
    char buf[1024], *ff, *tf;

    ff = makePathName(dir, from);
    dperr("Impify", ff);
    tf = to;
    dperr("to", tf);

    if (!isFile(ff)) {
        perr('E', "File not found", ff);
        goto EXIT;
    }
    if ( (tf = okToWrite(tf))==NULL ) goto EXIT;

    sprintf(buf,
"'-s_P(%s)' '-s_V(v%d,r%d,c%d)' '-s_sN(%s)'\
 '-s_lN(\"%s/\")' '-s_Lvl(%s)'\
 '-s_tOS(%s)' '-s_tL(\"%s\")' '-s_i(%s%s%s%s%s)' '-s_mm(%s)'\
 '-s_tX(\"%s\")' '-s_tD(\"%s\")'",
            product.abbreviation,
            product.version.version, product.version.revision,
            product.version.correction, /* product.version.state, */
            sysName, languageDir, levels[gType],
            targetOS, languages[lIx],
            (pmk? "pm, ": ""),
            (smk? "sm, ": ""),
            (lmk? "lm, ": ""),
            (voc? "voc, ": ""),
            (tm ? "tm"  : "\"\""),
            (mm ? "YES" : "NO"),
            langExt[lIx], langDir[lIx]);

    perr('I', "Generating", tf);
    imp(buf, ff, tf, NULL);
 EXIT:
    free(ff); /* free(tf); -- not malloc'd */
}
#endif

PRIVATE void doGenerate()
{
    char tmp[32];

    if (verbose && !go) printSelection();

    if (tm) {
        sprintf(tmp, "%s.tmk", sysName);
            impFile(languageDir, "tmk.imp", tmp);
    }

    if (pmk) {
        sprintf(tmp, "%s.pmk", sysName);
        impFile(languageDir, "pmk.imp", tmp);
    }

    if (smk) {
        sprintf(tmp, "%s.smk", sysName);
        impFile(languageDir, "smk.imp", tmp);

        if (voc) {
            sprintf(tmp, "%s.voc", sysName);
            impFile(languageDir, "voc.imp", tmp);
        }
    }

    if (lmk) {
        sprintf(tmp, "%s.lmk", sysName);
        impFile(languageDir, "lmk.imp", tmp);
    }

    if (mm) {
        sprintf(tmp, "%s.%s", sysName, langExt[lIx]);
        impFile(languageDir, "main.imp", tmp);
    }

    if (mk) {
        impFile(languageDir, "makefile.imp", "Makefile");
    }

    if (pmk && !lmk) {
        sprintf(tmp, "%sErr.%s", sysName, langExt[lIx]);
        impFile(languageDir, "Err.imp", tmp);
    }
}


/***********************************************************************
    SPA part

    Defines processing of the user supplied argument line.
*/

PRIVATE SPA_FUN(xit) { exit(BAD); }
PRIVATE SPA_FUN(args) { perr('W', "Argument not used", rawName); }
PRIVATE SPA_FUN(setName) { strcpy(sysName, rawName); }

PRIVATE SPA_ERRFUN(spaPerr) { perr( (char)sev, msg, add ); }

PRIVATE SPA_DECLARE(arguments)
  SPA_FUNCTION("name", "for the subsystem", setName)
  SPA_FUNCTION("", NULL, args)
SPA_END

PRIVATE SPA_DECLARE(options)
#ifdef DBG
  SPA_FLAG("debug", "debug mode", debug, FALSE, NULL)
  SPA_KEYWORD("language", "target code language\nStandard K&R C\nThe standard\nOo what a C...",
              lIx, languages, lCansi, NULL)
  SPA_KEYWORD("level", "contents in generated files\nVery terse\nA runnable example\nA complete parser for PL/0",
              gType, levels, aNorm, NULL)
#endif
  SPA_FLAG("go", "quick toolmake with all defaults accepted", go, FALSE, NULL)
  SPA_FLAG("verbose", "verbose mode", verbose, FALSE, NULL)
SPA_END


/***********************************************************************
    MAIN
*/

main(argc, argv)
    int argc;
    char *argv[];
{
    int lic;

    SpaAlertName = product.abbreviation;
#ifdef DBG
    SpaAlertLevel = 'D';
#endif
    printf("%s\n\n", product.longHeader);

    switch (lic = license()) {
    case LICENSE_OK:
        break;
    case LICENSE_EXPIRED:
        perr('W', "license server", "date expired");
        break;
    case LICENSE_DENIED:
        perr('W', "license server", "no license available");
        break;
    case LICENSE_FORMAT_ERROR:
        perr('W', "license server", "format error");
        break;
    case LICENSE_NO_SERVER:
        perr('W', "license server", "no contact");
        break;
    case LICENSE_NO_FILE:
        perr('W', "license server", "license file missing");
        break;
    case LICENSE_ILLEGAL_PASSWORD:
        perr('W', "license server", "illegal license key");
        break;
    default:
        spaAlert('E', "license server: unknown error (%d)", lic);
        break;
    }

    spaProcess(argc, argv, arguments, options, spaPerr);
#ifdef DBG
    SpaAlertLevel = debug? 'D': (verbose? 'I': 'W');
#else
    SpaAlertLevel = verbose? 'I': 'W';
#endif

    tmDir = (char *)getenv("TMHOME");
    if (!tmDir) tmDir = TMHOME;
#ifdef DBG
    libDir = (char *)getenv("TMLIB");
    if (!libDir)
#endif
    libDir = makePathName(tmDir, "lib");
    establishLanguage();

    askSet(askNumericPrompt, (long)"? "); /* Also strings */
    askSet(askHelpWidth, 72);
    askSet(askEolnCharSet, (long)"");
/*    askSet(askBuffering, FALSE); */

    getSystemName();

    printSelection();
    getActions();

    if (gen) doGenerate();

    exit(GOOD);
}

/* EoF */
