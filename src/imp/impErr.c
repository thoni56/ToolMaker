/*-----------------------------------------------------------------------------
 * impErr.c
 *
 * Parser error handler interface
 *-----------------------------------------------------------------------------
 * Created:	89-09-19 by Tom
 * Modified:	90-06-20 by Yngve. Generates (tmkPrefix)Err.h
 *                          Changes #ifdef _PROTOTYPES_ to
 *                          %%IF(tmkTarget("ANSI-C") OR tmkTarget("C++"))
 *-----------------------------------------------------------------------------
 * Entires:
 *	impRPoi - Recovery point
 *	impISym - Symbol inserted
 *	impDSym - Symbol deleted
 *	impMess - Output a message
 *-----------------------------------------------------------------------------
 * Host:
 * Target:
 *-----------------------------------------------------------------------------
 */
/* Import */

/* .pmk-import */
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "impScan.h"
#include "impList.h"
extern impScContext impcontext;

#include "impErr.h"

static char insStr[101] = "";	/* Inserted symbol strings */
static int insToks = 0;

static char delStr[201] = "";	/* Deleted symbol strings */
static int delToks;

static TmSrcp prevSrcp = {0, 0}; /* Previous error position */


/*-----------------------------------------------------------------------------
 * impRPoi - Recovery point, output a message indicating the position.
 *-----------------------------------------------------------------------------
 */
void impRPoi(sym)
    TmToken *sym;		/* IN the restart symbol */
{
    /* If the recovery point is different than the error point
     */
    if (sym->srcp.line != prevSrcp.line ||
	sym->srcp.col != prevSrcp.col
	|| sym->srcp.file != prevSrcp.file
	)
    {
	if (delToks > MaxTokens) {
	    /* Output a recovery point error message
	     */
	    impMyLog(&(sym->srcp), 100, sevINF, "");
	}/*if*/
    }/*if*/

    /* Clear both token print strings
     */
    insStr[0] = '\0';
    delStr[0] = '\0';

    insToks = 0;
    delToks = 0;
}/*impRPoi()*/


/*-----------------------------------------------------------------------------
 * impISym - A symbol is to be inserted, collect it for later output, and
 *	    construct the requested token for use by the parser.
 *-----------------------------------------------------------------------------
 */
void impISym(code, sstr, pstr, sym) 
     int code;		/* IN terminal code number */
    char *sstr;			/* IN terminal string */
    char *pstr;			/* IN the terminals print symbol */
    TmToken *sym;		/* OUT the created scanner symbol */
{
    if (insToks < MaxTokens) {
	/* Concatenate the token string
	 */
	if (insToks > 0) strcat(insStr, " ");
	if (code == 0) strcat(insStr, "Unknown Token");
	else if (code == 1) strcat(insStr, "End Of File");
	else if (*pstr != '\0') strcat(insStr, pstr);
	else strcat(insStr, sstr);
    } else if (insToks == MaxTokens) {
	strcat(insStr, " ...");
    }/*if*/
    insToks++;


    /* Make the requested token
     */
    sym->code = code;


}/*impISym()*/


/*-----------------------------------------------------------------------------
 * impDSym - The indicated symbol is deleted by the parser, collect its string
 *	    for later output.
 *-----------------------------------------------------------------------------
 */
void impDSym(sym, sstr)
    TmToken *sym;		/* IN terminal code number */
    char *sstr;			/* IN terminal string */
{
    if (delToks < MaxTokens) {
	/* Concatenate the symbol string
	 */
	if (delToks > 0) strcat(delStr, " ");
	if (sym->code == 0) strcat(delStr, "Unknown Token");
	else strcat(delStr, sstr);
    } else if (delToks == MaxTokens) {
	strcat(delStr, " ...");
    }/*if*/
    delToks++;
}/*impDSym()*/


/*-----------------------------------------------------------------------------
 * impMess - An error message should be output, symbol indicates point of error.
 *-----------------------------------------------------------------------------
 * Method:	1 = Symbol(s) insertion	       Message:	% inserted
 *		2 = Symbol(s) deletion			% deleted
 *		3 = Symbol(s) replacement		% replaced by %
 *	        4 = Stack backup			Malformed phrase
 *		5 = Halted				%. System halted
 *
 * Code:	1 = Unknown token (error token from scanner)
 *		2 = Syntax error
 *		3 = Parse stack overflow
 *		4 = Table error
 *
 * Severity:	1 = Warning
 *		2 = Error (repairable)
 *		3 = Fatal error
 *		4 = System error & Limit error
 *-----------------------------------------------------------------------------
 */
void impMess(sym, method, code, severity)
    TmToken *sym;	/* IN error token */
    int method;			/* IN recovery method */
    int code;			/* IN error classification */
    int severity;		/* IN error severity code */
{
    impSev sev;

    switch (severity) {
    case 1: sev = sevWAR; break;
    case 2: sev = sevERR; break;
    case 3: sev = sevFAT; break;
    case 4: sev = sevSYS; break;
    }

    switch (code) {

    case 1:
	/* Unknown symbol, deleted
	 */
	impMyLog(&(sym->srcp), 102, sev, "Unknown Token");
	break;

    case 2:
	/* Syntax Error
	 */
	switch (method) {

	case 1:
	    /* Insert
	     */
	    impMyLog(&(sym->srcp), 101, sev, insStr);
	    break;

	case 2:
	    /* Delete
	     */
	    impMyLog(&(sym->srcp), 102, sev, delStr);
	    break;

	case 3:
	    /* Replace
	     */
	    delStr[strlen(delStr)+1] = '\0';
	    delStr[strlen(delStr)] = impSEPARATOR; /* Separator */
	    strcat(delStr, insStr);
	    impMyLog(&(sym->srcp), 103, sev, delStr);
	    break;

	case 4:
	    /* Stack backed up
	     */
	    impMyLog(&(sym->srcp), 104, sev, "");
	    break;

	case 5:
	    /* Syntax error, system halted
	     */
	    impMyLog(&(sym->srcp), 105, sev, "");
	    break;
	}
	break;

    case 3:
	/* Parse stack overflow
	 */
	impMyLog(&(sym->srcp), 106, sev, "");
	break;

    case 4:
	/* Parse table error
	 */
	impMyLog(&(sym->srcp), 107, sev, "");
	break;
    }

    if (method == 5) {
	/* System halted, output informational message
	 */
	impMyLog(&(sym->srcp), 108, sevINF, "");
    }
}/*impMess()*/
