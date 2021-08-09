/*----------------------------------------------------------------------*\

  pmkErr.c

  Parser error handler

\*----------------------------------------------------------------------*/

/* %%IMPORT */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pws.h"
#include "pmkList.h"
#include "pwsLexCode.h"
#include "pwsOrd.h"
#include "set.h"
#include "pmk_i.h"
#include "tmk.h"
#include "pwSymSet.h"
#include "pwsGrm.h"
#include "pmkScan.h"
extern pmkScContext pmkCtxt;

/* END %%IMPORT */

#include <string.h>
#include <stdlib.h>
#include "pmkList.h"
#include "pmkCommon.h"

#define MaxTokens 5


static char insStr[101] = "";   /* Inserted symbol strings */
static int insToks = 0;

static char delStr[201] = "";   /* Deleted symbol strings */
static int delToks = 0;

/*-----------------------------------------------------------------------------
 * pmkRPoi - Recovery point, output a message indicating the position.
 *-----------------------------------------------------------------------------
 */
void pmkRPoi(
    PmkToken *token     /* IN the restart symbol */
)
{
    if (delToks > MaxTokens) {
       /* Output a recovery point error message
       */
       pmkLog(&(token->srcp), 100, sevINF, "");
    }/*if*/

    /* Clear both token print strings */
    insStr[0] = '\0';
    delStr[0] = '\0';

    insToks = 0;
    delToks = 0;
}/*pmkRPoi()*/


/*-----------------------------------------------------------------------------
 * pmkISym - A symbol is to be inserted, collect it for later output, and
 *      construct the requested token for use by the parser.
 *-----------------------------------------------------------------------------
 */
void pmkISym(
    int code,           /* IN terminal code number */
    char *symString,    /* IN terminal string */
    char *printString,  /* IN the terminals print symbol */
    PmkToken *token     /* OUT the created scanner symbol */
)
{
    char *selectedString;

    if (insToks < MaxTokens) {
    /* Concatenate the token string
     */
    if (insToks > 0) strcat(insStr, " ");
    if (code == 0) strcat(insStr, "<unknown token>");
    else if (code == 1) strcat(insStr, "<end of file>");
        else {
            if (*printString != '\0') selectedString = printString;
            else selectedString = symString;
            if (selectedString[0] == '\'') {
                strcat(insStr, &selectedString[1]);
                insStr[strlen(insStr)-1] = '\0';
            } else
                strcat(insStr, selectedString);
        }
    } else if (insToks == MaxTokens) {
    strcat(insStr, " ...");
    }/*if*/
    insToks++;
#define sym token
#define sstr symString
#define pstr printString
#line 46 "pmk.pmk"


    /* Make the requested token */
    sym->code = code;

    switch (code) {

    case 2:         /* IDENTIFIER */
    case 3:         /* QUOTED_STRING */
    case 4:         /* ANGLE_BRACKETED_STRING */
    if (*pstr != '\0') {
        sym->sval = (char *)malloc(strlen(pstr) + 1);
        strcpy(sym->sval, pstr);
    } else {
        sym->sval = (char *)malloc(strlen(sstr) + 1);
        strcpy(sym->sval, sstr);
    }/*if*/
    sym->ival = 0;
    break;

    case 5:         /* INTEGER */
    sym->ival = 0;
    break;
    }/*switch*/

#undef sym
#undef sstr
#undef pstr
}/*pmkISym()*/


/*-----------------------------------------------------------------------------
 * pmkDSym - The indicated symbol is deleted by the parser, collect its string
 *           for later output.
 *-----------------------------------------------------------------------------
 */
void pmkDSym(
    PmkToken *token,    /* IN terminal */
    char *symString,    /* IN terminal string */
    char *printString   /* IN terminals print string */
)
{
    char *selectedString;

    if (delToks < MaxTokens) {
    /* Concatenate the symbol strings */
    if (delToks > 0) strcat(delStr, " ");
    if (token->code == 0) strcat(delStr, "<unknown token>");
    else if (token->code == 1) strcat(delStr, "<end of file>");
    else {
#ifdef DELETEIDENTIFIERASINPUTTED
            if (token->code == 2) selectedString = token->chars;
            else
#endif
            if (*printString != '\0') selectedString = printString;
            else selectedString = symString;
            if (selectedString[0] == '\'') {
                strcat(delStr, &selectedString[1]);
                delStr[strlen(delStr)-1] = '\0';
            } else
                strcat(delStr, selectedString);
        }
    } else if (delToks == MaxTokens) {
    strcat(delStr, " ...");
    }/*if*/
    delToks++;
}/*pmkDSym()*/


/*-----------------------------------------------------------------------------
 * pmkMess - An error message should be output, symbol indicates point of error.
 *-----------------------------------------------------------------------------
 * Method:  1 = Symbol(s) insertion         Message: % inserted
 *          2 = Symbol(s) deletion                   % deleted
 *          3 = Symbol(s) replacement                % replaced by %
 *          4 = Stack backup                Malformed phrase
 *          5 = Halted                               %. System halted
 *
 * Code:    1 = Unknown token (error token from scanner)
 *          2 = Syntax error
 *          3 = Parse stack overflow
 *          4 = Table error
 *
 * Severity:    1 = Warning
 *              2 = Error (repairable)
 *              3 = Fatal error
 *              4 = System error & Limit error
 *-----------------------------------------------------------------------------
 */
void pmkMess(
    PmkToken *sym,      /* IN error token */
    int method,         /* IN recovery method */
    int code,           /* IN error classification */
    int severity        /* IN error severity code */
)
{
    pmkSev sev;

    switch (severity) {
    case 1: sev = sevWAR; break;
    case 2: sev = sevERR; break;
    case 3: sev = sevFAT; break;
    case 4: sev = sevSYS; break;
    default: sev = sevSYS; break;
    }

    switch (code) {

    case 1:
    /* Unknown symbol, deleted */
    pmkLog(&(sym->srcp), 102, sev, "Unknown Token");
    break;

    case 2:
    /* Syntax Error */
    switch (method) {

    case 1:
        /* Insert */
        pmkLog(&(sym->srcp), 101, sev, insStr);
        break;

    case 2:
        /* Delete */
        pmkLog(&(sym->srcp), 102, sev, delStr);
        break;

    case 3:
        /* Replace */
        delStr[strlen(delStr)+1] = '\0';
        delStr[strlen(delStr)] = pmkSEPARATOR; /* Separator */
        strcat(delStr, insStr);
        pmkLog(&(sym->srcp), 103, sev, delStr);
        break;

    case 4:
        /* Stack backed up */
        pmkLog(&(sym->srcp), 104, sev, "");
        break;

    case 5:
        /* Syntax error, system halted */
        pmkLog(&(sym->srcp), 105, sev, "");
        break;
    }
    break;

    case 3:
    /* Parse stack overflow */
    pmkLog(&(sym->srcp), 106, sev, "");
    break;

    case 4:
    /* Parse table error */
    pmkLog(&(sym->srcp), 107, sev, "");
    break;
    }

    if (method == 5) {
    /* System halted, output informational message */
    pmkLog(&(sym->srcp), 108, sevINF, "");
    }
}/*pmkMess()*/
