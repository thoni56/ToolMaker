/*-----------------------------------------------------------------------------
 * pmTab - ParserMaker table generator
 *		@(#)pmTab.c	1.5 (91/04/03 14:16:24)
 *-----------------------------------------------------------------------------
 * Created:	89-09-08 by Tom
 * Modified:	90-04-18 by Tom. targetHook and all calls removed.
 *		90-05-02 by Tom. Escape characters in %%CODE & %%DATA removed.
 *		90-06-20 by Yngve. pmTarget options logged on pmTab
 *		90-06-28 by Yngve. setLangVars extended to handle Ansi-C, C++
 *		91-04-01 by Yngve. writeSemantics modified to always define
 *				pmSemantics.
 *		91-04-03 by Yngve. writeOptions extended to define pmVersion.
 *-----------------------------------------------------------------------------
 * Entries:
 *	pmTab
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Imports
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32) || defined(MINGW)
#include <io.h>
#endif
#include <unistd.h>
#include "pmk_i.h"
#include "pws.h"
#include "pwGe.h"
#include "pwPack.h"
#include "pwsLexCode.h"
#include "pwsGrm.h"
#include "pwLog.h"
#include "pmkParse.h"
#include "version.h"


static char *caseHead;
static char *caseBeg;
static char *caseSep;
static char *caseEnd;
static char *actEnd;
static char *vecBeg;
static char *vecSep;
static char *vecEnd;
static char *semBeg;
static char *semEnd;
static char *symBeg;
static char *symEnd;
static char *attrSep;
static char *commBeg;
static char *commEnd;
static int curLen;
static Boolean firstEntry;


/*======================================================================
  pmkCopyCode()

  Copy a code segment with length "length" from position "pos"
  in "inFile" to "outFile". In "inFile" use the escape character
  "inEscape" and in "outFile" use "outEscape"
*/
void pmkCopyCode(inFile, pos, length, inEscape, outFile, outEscape)
     int inFile;		/* File to read code from             */
     int pos;			/* Position to start read from        */
     int length;		/* Length of code to read             */
     char inEscape;		/* Escape character to use in infile  */
     FILE *outFile;		/* File to write code to              */
     char outEscape;		/* Escape character to use in outfile */
{
    int i;			/* Loop variable              */
    char ch;			/* Temporary character holder */

    lseek(inFile, pos, 0);
    for (i = 0; i < length; i++) {
        if ((read(inFile, &ch, 1) == 1) && (ch == '%'))
            putc(outEscape, outFile);
        else if (ch == inEscape) {
            if ((read(inFile, &ch, 1) == 1) && (ch == '%'))
                putc(outEscape, outFile);
            i++;
        }
        putc(ch, outFile);
    }
}

/*-----------------------------------------------------------------------------
 * setLangVars - Set a number of variables according to language. Works only
 *		 for C, Ansi-C and C++ at the moment.
 *-----------------------------------------------------------------------------
 */
static void setLangVars()
{
    char *pmkTarget = getStrOpt(PMKTARGET_OPT);
    if ((strcmp(pmkTarget, "c") == 0) ||
        (strcmp(pmkTarget, "c++") == 0) ||
        (strcmp(pmkTarget, "ansi-c") == 0)) {
        caseHead = "    switch (rule) {";
        caseBeg = "    case ";
        caseSep = ":\n    case ";
        caseEnd = ": {";
        actEnd = "\tbreak;}\n";
        vecBeg = "{";
        vecSep = ",";
        vecEnd = "}";
        semBeg = "%%(parserPrefix)SeSt[%%(parserPrefix)StkP+";
        semEnd = "]";
        symBeg = "%%(parserPrefix)SySt[%%(parserPrefix)StkP+";
        symEnd = "]";
        attrSep = ".";
        commBeg = " /* ";
        commEnd = " */\n";
    } else {
        /* Not very nice but we have to have an else-part */
        caseHead = "    switch (rule) {";
        caseBeg = "    case ";
        caseSep = ":\n    case ";
        caseEnd = ": {";
        actEnd = "\tbreak;}\n";
        vecBeg = "{";
        vecSep = ",";
        vecEnd = "}";
        semBeg = "%%(parserPrefix)SeSt[%%(parserPrefix)StkP+";
        semEnd = "]";
        symBeg = "%%(parserPrefix)SySt[%%(parserPrefix)StkP+";
        symEnd = "]";
        attrSep = ".";
        commBeg = " /* ";
        commEnd = " */\n";
    }
}/*setLangVars()*/


/*-----------------------------------------------------------------------------
 * writeMisc - Set a number of macro variables, Most of them previously set
 *             in the .pm or .tm files
 */
static void writeMisc()
{
    int fd;
    char *buff;
    tmkPCommon(pmTbl, tokenNode, srcpNode, importSection, getStrOpt(TMKESCAPE_OPT)[0]);
    fprintf(pmTbl, "%%%%SET tmkForce(%d)\n", getBoolOpt(FORCE_OPT) ? 1 : 0);
    fprintf(pmTbl, "%%%%SET tmkOs(\"%s\")\n", getStrOpt(TMKOS_OPT));
    fprintf(pmTbl, "%%%%SET pmkOs(\"%s\")\n", getStrOpt(PMKOS_OPT));
    fprintf(pmTbl, "%%%%SET currentOs(\"%s\")\n", TARGETOS);
    fprintf(pmTbl, "%%%%SET tmkTarget(\"%s\")\n", getStrOpt(TMKTARGET_OPT));
    fprintf(pmTbl, "%%%%SET pmkTarget(\"%s\")\n", getStrOpt(PMKTARGET_OPT));
    fprintf(pmTbl, "%%%%SET tmkLibrary(\"%s\")\n", getStrOpt(TMKLIBRARY_OPT));
    fprintf(pmTbl, "%%%%SET pmkLibrary(\"%s\")\n", getStrOpt(PMKLIBRARY_OPT));
    fprintf(pmTbl, "%%%%SET tmkPrefix(\"%s\")\n", getStrOpt(TMKPREFIX_OPT));
    fprintf(pmTbl, "%%%%SET parserPrefix(\"%s\")\n", getStrOpt(PMKPREFIX_OPT));
    if (optAssigned(LISTERPREFIX_OPT))
        fprintf(pmTbl, "%%%%SET listerPrefix(\"%s\")\n", getStrOpt(LISTERPREFIX_OPT));
    else
        fprintf(pmTbl, "%%%%SET listerPrefix(\"%s\")\n", getStrOpt(TMKPREFIX_OPT));
    if (tokenNode->codeDecl) {
        buff = (char*) malloc(strlen(tokenNode->codeDecl)+
                              MAXNOPH * (tokenNode->code ? strlen(tokenNode->code) : 0)+1);
        fprintf(pmTbl, "%%%%SET tmkCodeDecl(\"%s\")\n",
                tmkReplPH(tokenNode->codeDecl, tokenNode->code, buff));
        free(buff);
    }
    /* Write the grammar attributes */
    if (grmAttrNames) {
        if (grmAttrDecls) {
            fprintf(pmTbl, "%%%%SET tmkGrmAttrDecl(");
            printStrList(pmTbl, grmAttrDecls, grmAttrNames);
            fprintf(pmTbl, ")\n");
        }
        fprintf(pmTbl, "%%%%SET tmkGrmAttrNames(");
        printStrList(pmTbl, grmAttrNames, NULL);
        fprintf(pmTbl, ")\n");
    }
    if ((pmkImportSection) &&
        (fd = open(pmkImportSection->fname, OFLAG)) >= 0) {
        fprintf(pmTbl, "%%%%BEGIN(pmkImport)\n");
        pmkCopyCode(fd, pmkImportSection->fpos, pmkImportSection->length,
                    pmkEscape, pmTbl, '`');
        close(fd);
        fprintf(pmTbl, "%%%%END(pmkImport)\n");
    }
    if ((exportSection) &&
        (fd = open(exportSection->fname, OFLAG)) >= 0) {
        fprintf(pmTbl, "%%%%BEGIN(pmkExport)\n");
        if (getBoolOpt(LINE_OPT))
            fprintf(pmTbl, "#line %d \"%s\"\n", exportSrcp.line,
                    inFiles[0]);
        pmkCopyCode(fd, exportSection->fpos, exportSection->length,
                    pmkEscape, pmTbl, '`');
        close(fd);
        fprintf(pmTbl, "%%%%END(pmkExport)\n");
    }
    fprintf(pmTbl, "%%%%PROCESS(\"%%%%(tmkLibrary)/Common.imp\")\n%%%%SET pmStackMax(");
    fprintf(pmTbl, "%i", getNumOpt(STACKLIMIT_OPT));
    fprintf(pmTbl, ")\n");
    fprintf(pmTbl, "%%%%SET pmLookAheadMax(%i)\n", getNumOpt(LOOKAHEADMAX_OPT));
    fprintf(pmTbl, "%%%%SET pmCost(%i)\n", getNumOpt(SHIFTCOST_OPT));
    if ((scannerSection) &&
        (fd = open(scannerSection->fname, OFLAG)) >= 0) {
        fprintf(pmTbl, "%%%%BEGIN(pmIScan)\n");
        pmkCopyCode(fd, scannerSection->fpos, scannerSection->length,
                    pmkEscape, pmTbl, '`');
        close(fd);
        fprintf(pmTbl, "%%%%END(pmIScan)\n");
    }
    if ((insertSymbSection) &&
        (fd = open(insertSymbSection->fname, OFLAG)) >= 0) {
        fprintf(pmTbl, "%%%%BEGIN(pmISym)\n");
        if (getBoolOpt(LINE_OPT))
            fprintf(pmTbl, "#line %d \"%s\"\n", insertsymbolSrcp.line,
                    inFiles[0]);
        pmkCopyCode(fd, insertSymbSection->fpos, insertSymbSection->length,
                    pmkEscape, pmTbl, '`');
        close(fd);
        fprintf(pmTbl, "%%%%END(pmISym)\n");
    }
    if ((deleteSymbSection) &&
        (fd = open(deleteSymbSection->fname, OFLAG)) >= 0) {
        fprintf(pmTbl, "%%%%BEGIN(pmDSym)\n");
        if (getBoolOpt(LINE_OPT))
            fprintf(pmTbl, "#line %d \"%s\"\n", deletesymbolSrcp.line,
                    inFiles[0]);
        pmkCopyCode(fd, deleteSymbSection->fpos, deleteSymbSection->length,
                    pmkEscape, pmTbl, '`');
        close(fd);
        fprintf(pmTbl, "%%%%END(pmDSym)\n");
    }
    if (getBoolOpt(TRACE_OPT))
        fprintf(pmTbl, "%%%%SET pmTrace(TRACE)\n");
}
/*-----------------------------------------------------------------------------
 * writeOptions - Set a number of macro variables defining the ParserMaker
 *		  options
 *-----------------------------------------------------------------------------
 */
static void writeOptions()
{
    fprintf(pmTbl, "%%%%SET pmOptimize(");
    if (logOptList(pmTbl, OPTIMIZE_OPT))
        fprintf(pmTbl, ")\n");
    else fprintf(pmTbl, "\"\")\n");

    fprintf(pmTbl, "%%%%SET pmActPack(");
    if (logOptList(pmTbl, ACTIONPACK_OPT))
        fprintf(pmTbl, ")\n");
    else fprintf(pmTbl, "\"\")\n");

    fprintf(pmTbl, "%%%%SET pmGtoPack(");
    if (logOptList(pmTbl, GOTOPACK_OPT))
        fprintf(pmTbl, ")\n");
    else fprintf(pmTbl, "\"\")\n");

    fprintf(pmTbl, "%%%%SET pmRec(");
    if (logOptList(pmTbl, RECOVERY_OPT))
        fprintf(pmTbl, ")\n");
    else fprintf(pmTbl, "\"\")\n");

    fprintf(pmTbl, "%%%%SET pmHeader(\"%s\")\n", product.longHeader);
    fprintf(pmTbl,
            "%%%%SET pmVersion(\"%d.%d\")\n",
            product.version.version,
            product.version.revision);
    fprintf(pmTbl,
            "%%%%SET pmCorrection(\"%d\")\n",
            product.version.correction);

}/*writeOptions()*/


/*-----------------------------------------------------------------------------
 * writeCodeAndData - Copies the code and data parts from the grammar file
 *            to the table file.
 *-----------------------------------------------------------------------------
 */
static void writeCodeAndData()
{
    fprintf(pmTbl, "%%%%BEGIN(pmDecl)");
    if (declSection) {
        if (getBoolOpt(LINE_OPT))
            fprintf(pmTbl, "#line %d \"%s\"\n", declarationsSrcp.line,
                    inFiles[0]);
        pmkCopyCode(pwsGrm, declSection->fpos, declSection->length,
                    pmkEscape, pmTbl, '`');
    } else {
        putc('\n', pmTbl);
    }/*if*/
    fprintf(pmTbl, "%%%%END(pmDecl)\n");
}/*writeCodeAndData()*/


/*-----------------------------------------------------------------------------
 * outBeg - Outputs a vector start to the table file.
 *-----------------------------------------------------------------------------
 */
static void outBeg()
{
    firstEntry = TRUE;
    fprintf(pmTbl, "%s", vecBeg);
    curLen = strlen(vecBeg);
}/*outBeg()*/


/*-----------------------------------------------------------------------------
 * outSubBeg - Outputs a vector start to the table file.
 *-----------------------------------------------------------------------------
 */
static void outSubBeg()
{
    if (firstEntry) {
        fprintf(pmTbl, "%s", vecBeg);
        curLen += strlen(vecBeg);
    } else {
        fprintf(pmTbl, "%s%s", vecSep, vecBeg);
        curLen += strlen(vecSep) + strlen(vecBeg);
        firstEntry = TRUE;
    }/*if*/
}/*outSubBeg()*/


/*-----------------------------------------------------------------------------
 * outEnd - Outputs a vector end to the table file.
 *-----------------------------------------------------------------------------
 */
static void outEnd()
{
    fprintf(pmTbl, "%s\n", vecEnd);
    curLen = 0;
}/*outEnd()*/


/*-----------------------------------------------------------------------------
 * outSubEnd - Outputs a vector end to the table file.
 *-----------------------------------------------------------------------------
 */
static void outSubEnd()
{
    fprintf(pmTbl, "%s\n", vecEnd);
    curLen = 0;
    firstEntry = FALSE;
}/*outSubEnd()*/


/*-----------------------------------------------------------------------------
 * outEntry - Outputs a vector entry with commas and newlines.
 *-----------------------------------------------------------------------------
 */
static void outEntry(ent)
     int ent;			/* IN the entry to write */
{
    if (firstEntry) {
        fprintf(pmTbl, "%u", ent);
        curLen += nofi(ent);
        firstEntry = FALSE;
    } else {
        fprintf(pmTbl, "%s%u", vecSep, ent);
        curLen += strlen(vecSep) + nofi(ent);
        if (curLen > 70) {
            putc('\n', pmTbl);
            curLen = 0;
        }/*if*/
    }/*if*/
}/*outEntry()*/


/*-----------------------------------------------------------------------------
 * outString - Outputs a string with commas and newlines.
 *-----------------------------------------------------------------------------
 */
static void outString(string)
     char *string;			/* IN the string to write */
{
    static char dummy[] = "";
    int i;

    if (!string) string = dummy;
    if (firstEntry) {
        putc('"', pmTbl);
        curLen += strlen(string);
        firstEntry = FALSE;
    } else {
        fprintf(pmTbl, "%s\"", vecSep);
        curLen += strlen(vecSep) + strlen(string);
    }/*if*/
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == '%') {
            putc('`', pmTbl);
            curLen++;
        }/*if*/
        putc(string[i], pmTbl);
    }/*for*/
    putc('"', pmTbl);
    if (curLen > 70) {
        putc('\n', pmTbl);
        curLen = 0;
    }/*if*/
}/*outString()*/


/*-----------------------------------------------------------------------------
 * writeActTab - Writes the parser action table to the table file.
 *-----------------------------------------------------------------------------
 */
static void writeActTab()
{
    int i, j;

    fprintf(pmTbl, "%%%%SET pmStates(%u)\n", stateCnt);
    fprintf(pmTbl, "%%%%SET pmStateTyp(%u)\n", nrBytes(stateCnt));
    fprintf(pmTbl, "%%%%SET pmTerms(%u)\n", termCnt);
    fprintf(pmTbl, "%%%%SET pmTermTyp(%u)\n", nrBytes(termCnt));
    fprintf(pmTbl, "%%%%SET pmActTyp(%u)\n", nrBytes(actMax));
    /*    fprintf(pmTbl, "%%%%SET pmDivFactor(%u)\n", tableFactor);*/
    fprintf(pmTbl, "%%%%SET pmArgTyp(%u)\n", nrBytes(tableFactor));

    if (actRDS) {
        fprintf(pmTbl, "%%%%SET pmActRDSvectorLen(%u)\n", act.RDSvectorLen);

        if (act.RDSvectorLen > 0) {
            fprintf(pmTbl, "%%%%BEGIN(pmActTab)\n");
            outBeg();
            for (i = 0; i < act.RDSvectorLen; i++) outEntry(act.RDSvector[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmActTab)\n");
        }/*if*/
    } else {
        fprintf(pmTbl, "%%%%SET pmActRows(%u)\n", act.rows);
        fprintf(pmTbl, "%%%%SET pmActCols(%u)\n", act.cols);

        if (act.rows > 0 && act.cols > 0) {
            fprintf(pmTbl, "%%%%BEGIN(pmActTab)\n");
            outBeg();
            for (i = 0; i < act.rows; i++) {
                outSubBeg();
                for (j = 0; j < act.cols; j++) outEntry(act.matrix[i][j]);
                outSubEnd();
            }/*for*/
            outEnd();
            fprintf(pmTbl, "%%%%END(pmActTab)\n");
        }/*if*/
    }/*if*/

    if (actRDS && !(actLES || actGCS)) {
        fprintf(pmTbl, "%%%%SET pmActRDScheckLen(%u)\n", act.RDScheckLen);
        fprintf(pmTbl, "%%%%SET pmRDScheckTyp(%u)\n", nrBytes(stateCnt));
        fprintf(pmTbl, "%%%%SET pmActRowMapTyp(%u)\n",
                nrBytes(act.RDSvectorLen));

        fprintf(pmTbl, "%%%%BEGIN(pmRDScheck)\n");
        outBeg();
        for (i = 0; i < act.RDScheckLen; i++) outEntry(act.RDScheck[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmRDScheck)\n");

        fprintf(pmTbl, "%%%%BEGIN(pmActRowMap)\n");
        outBeg();
        for (i = 0; i < stateCnt; i++) outEntry(act.RDSbase[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmActRowMap)\n");
    }/*if*/

    if (actLES || actGCS) {
        if (actLES) {
            fprintf(pmTbl, "%%%%SET pmActCondTyp(%u)\n",
                    nrBytes(act.LESscan));
            if (actRDS) {
                fprintf(pmTbl, "%%%%SET pmActRowMapTyp(%u)\n",
                        nrBytes(max(actMax, act.RDSvectorLen)));
            } else {
                fprintf(pmTbl, "%%%%SET pmActRowMapTyp(%u)\n",
                        nrBytes(max(actMax, act.rows)));
            }/*if*/
            fprintf(pmTbl, "%%%%SET pmActColMapTyp(%u)\n",
                    nrBytes(max(actMax, act.cols)));

            fprintf(pmTbl, "%%%%BEGIN(pmActRowCond)\n");
            outBeg();
            for (i = 0; i < stateCnt; i++) outEntry(act.LESdetRow[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmActRowCond)\n");

            fprintf(pmTbl, "%%%%BEGIN(pmActColCond)\n");
            outBeg();
            for (i = 0; i < termCnt; i++) outEntry(act.LESdetCol[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmActColCond)\n");
        } else {
            if (actRDS) {
                fprintf(pmTbl, "%%%%SET pmActRowMapTyp(%u)\n",
                        nrBytes(act.RDSvectorLen));
            } else {
                fprintf(pmTbl, "%%%%SET pmActRowMapTyp(%u)\n",
                        nrBytes(act.rows));
            }/*if*/
            fprintf(pmTbl, "%%%%SET pmActColMapTyp(%u)\n",
                    nrBytes(act.cols));
        }/*if*/

        fprintf(pmTbl, "%%%%BEGIN(pmActRowMap)\n");
        outBeg();
        for (i = 0; i < stateCnt; i++) outEntry(act.LESorGCSrow[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmActRowMap)\n");

        fprintf(pmTbl, "%%%%BEGIN(pmActColMap)\n");
        outBeg();
        for (i = 0; i < termCnt; i++) outEntry(act.LESorGCScol[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmActColMap)\n");

        fprintf(pmTbl, "%%%%SET pmErrRows(%u)\n", act.ERRrows);
        fprintf(pmTbl, "%%%%SET pmErrCols(%u)\n", act.ERRcols);

        if (getSetOpt(ACTIONPACK_OPT)>>5 & 1) {
            fprintf(pmTbl, "%%%%SET pmErrRowMapTyp(%u)\n",
                    nrBytes(act.ERRrows));
            fprintf(pmTbl, "%%%%SET pmErrColMapTyp(%u)\n",
                    nrBytes(act.ERRcols));

            fprintf(pmTbl, "%%%%BEGIN(pmErrRowMap)\n");
            outBeg();
            for (i = 0; i < stateCnt; i++) outEntry(act.ERRrow[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmErrRowMap)\n");

            fprintf(pmTbl, "%%%%BEGIN(pmErrColMap)\n");
            outBeg();
            for (i = 0; i < termCnt; i++) outEntry(act.ERRcol[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmErrColMap)\n");
        }/*if*/

        fprintf(pmTbl, "%%%%BEGIN(pmErrVect)\n");
        outBeg();
        for (i = 0; i < SETLEN(act.ERRrows * act.ERRcols); i++) {
            outEntry(act.ERRvect[i]);
        }/*for*/
        outEnd();
        fprintf(pmTbl, "%%%%END(pmErrVect)\n");
    }/*if*/

    if (getSetOpt(RECOVERY_OPT)>>1 & 1) {
        fprintf(pmTbl, "%%%%BEGIN(pmContTab)\n");
        outBeg();
        for (i = 1; i <= stateCnt; i++) {
            outSubBeg();
            outEntry(contTbl[i].tsym);
            outEntry(contTbl[i].ssym);
            outSubEnd();
        }/*for*/
        outEnd();
        fprintf(pmTbl, "%%%%END(pmContTab)\n");
    }/*if*/

    fprintf(pmTbl, "%%%%BEGIN(pmSeparators)\n");
    outBeg();
    for (i = 0; i < SETLEN(termCnt); i++) {
        if (recovery_spec.separators) {
            outEntry(recovery_spec.separators->ss[i]);
        } else {
            outEntry(0);
        }/*if*/
    }/*for*/
    outEnd();
    fprintf(pmTbl, "%%%%END(pmSeparators)\n");

    fprintf(pmTbl, "%%%%BEGIN(pmFiducials)\n");
    outBeg();
    for (i = 0; i < SETLEN(termCnt); i++) {
        if (recovery_spec.fiducials) {
            outEntry(recovery_spec.fiducials->ss[i]);
        } else {
            outEntry(0);
        }/*if*/
    }/*for*/
    outEnd();
    fprintf(pmTbl, "%%%%END(pmFiducials)\n");

    fprintf(pmTbl, "%%%%BEGIN(pmSkips)\n");
    outBeg();
    for (i = 0; i < SETLEN(termCnt); i++) {
        if (recovery_spec.skips) {
            outEntry(recovery_spec.skips->ss[i]);
        } else {
            outEntry(0);
        }/*if*/
    }/*for*/
    outEnd();
    fprintf(pmTbl, "%%%%END(pmSkips)\n");
}/*writeActTab()*/


/*-----------------------------------------------------------------------------
 * writeGtoTab - Writes the parser goto table to the table file.
 *-----------------------------------------------------------------------------
 */
static void writeGtoTab()
{
    int i, j;

    fprintf(pmTbl, "%%%%SET pmNonTerms(%u)\n", nonTermCnt);
    fprintf(pmTbl, "%%%%SET pmNonTermTyp(%u)\n",
            nrBytes(nonTermCnt + termCnt));
    fprintf(pmTbl, "%%%%SET pmGtoTyp(%u)\n", nrBytes(gtoMax));

    if (gtoRDS) {
        fprintf(pmTbl, "%%%%SET pmGtoRDSvectorLen(%u)\n", gto.RDSvectorLen);

        if (gto.RDSvectorLen > 0) {
            fprintf(pmTbl, "%%%%BEGIN(pmGtoTab)\n");
            outBeg();
            for (i = 0; i < gto.RDSvectorLen; i++) outEntry(gto.RDSvector[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmGtoTab)\n");
        }/*if*/
    } else {
        fprintf(pmTbl, "%%%%SET pmGtoRows(%u)\n", gto.rows);
        fprintf(pmTbl, "%%%%SET pmGtoCols(%u)\n", gto.cols);

        if (gto.rows > 0 && gto.cols > 0) {
            fprintf(pmTbl, "%%%%BEGIN(pmGtoTab)\n");
            outBeg();
            for (i = 0; i < gto.rows; i++) {
                outSubBeg();
                for (j = 0; j < gto.cols; j++) outEntry(gto.matrix[i][j]);
                outSubEnd();
            }/*for*/
            outEnd();
            fprintf(pmTbl, "%%%%END(pmGtoTab)\n");
        }/*if*/
    }/*if*/

    if (gtoRDS && !(gtoLES || gtoGCS)) {
        fprintf(pmTbl, "%%%%SET pmGtoRowMapTyp(%u)\n",
                nrBytes(gto.RDSvectorLen));

        fprintf(pmTbl, "%%%%BEGIN(pmGtoRowMap)\n");
        outBeg();
        for (i = 0; i < stateCnt; i++) outEntry(gto.RDSbase[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmGtoRowMap)\n");
    }/*if*/

    if (gtoLES || gtoGCS) {
        if (gtoLES) {
            fprintf(pmTbl, "%%%%SET pmGtoCondTyp(%u)\n",
                    nrBytes(gto.LESscan));
            if (gtoRDS) {
                fprintf(pmTbl, "%%%%SET pmGtoRowMapTyp(%u)\n",
                        nrBytes(max(gtoMax, gto.RDSvectorLen)));
            } else {
                fprintf(pmTbl, "%%%%SET pmGtoRowMapTyp(%u)\n",
                        nrBytes(max(gtoMax, gto.rows)));
            }/*if*/
            fprintf(pmTbl, "%%%%SET pmGtoColMapTyp(%u)\n",
                    nrBytes(max(gtoMax, gto.cols)));

            fprintf(pmTbl, "%%%%BEGIN(pmGtoRowCond)\n");
            outBeg();
            for (i = 0; i < stateCnt; i++) outEntry(gto.LESdetRow[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmGtoRowCond)\n");

            fprintf(pmTbl, "%%%%BEGIN(pmGtoColCond)\n");
            outBeg();
            for (i = 0; i < nonTermCnt; i++) outEntry(gto.LESdetCol[i]);
            outEnd();
            fprintf(pmTbl, "%%%%END(pmGtoColCond)\n");
        } else {
            if (gtoRDS) {
                fprintf(pmTbl, "%%%%SET pmGtoRowMapTyp(%u)\n",
                        nrBytes(gto.RDSvectorLen));
            } else {
                fprintf(pmTbl, "%%%%SET pmGtoRowMapTyp(%u)\n",
                        nrBytes(gto.rows));
            }/*if*/
            fprintf(pmTbl, "%%%%SET pmGtoColMapTyp(%u)\n",
                    nrBytes(gto.cols));
        }/*if*/

        fprintf(pmTbl, "%%%%BEGIN(pmGtoRowMap)\n");
        outBeg();
        for (i = 0; i < stateCnt; i++) outEntry(gto.LESorGCSrow[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmGtoRowMap)\n");

        fprintf(pmTbl, "%%%%BEGIN(pmGtoColMap)\n");
        outBeg();
        for (i = 0; i < nonTermCnt; i++) outEntry(gto.LESorGCScol[i]);
        outEnd();
        fprintf(pmTbl, "%%%%END(pmGtoColMap)\n");
    }/*if*/

    fprintf(pmTbl, "%%%%SET pmProds(%u)\n", global_prod_cnt);
    fprintf(pmTbl, "%%%%SET pmLhsTyp(%u)\n", nrBytes(termCnt + nonTermCnt));
    fprintf(pmTbl, "%%%%SET pmRhszTyp(%u)\n", nrBytes(rsszMax));

    fprintf(pmTbl, "%%%%BEGIN(pmLhs)\n");
    outBeg();
    for (i = 1; i <= global_prod_cnt; i++) {
        outEntry(global_pvec_tbl[global_prod_tbl[i]->start]);
    }/*for*/
    outEnd();
    fprintf(pmTbl, "%%%%END(pmLhs)\n");

    fprintf(pmTbl, "%%%%BEGIN(pmRhsz)\n");
    outBeg();
    for (i = 1; i <= global_prod_cnt; i++) outEntry(global_prod_tbl[i]->rssz);
    outEnd();
    fprintf(pmTbl, "%%%%END(pmRhsz)\n");
}/*writeGtoTab()*/


/*-----------------------------------------------------------------------------
 * writeVocTab - Writes the parser vocabulary to the table file.
 *-----------------------------------------------------------------------------
 */
static void writeVocTab()
{
    int i;

    fprintf(pmTbl, "%%%%SET pmSccMax(%u)\n", tc_val);
    fprintf(pmTbl, "%%%%SET pmSccTyp(%u)\n", nrBytes(tc_val));
    fprintf(pmTbl, "%%%%SET pmICostTyp(%u)\n", nrBytes(icostMax));
    fprintf(pmTbl, "%%%%SET pmDCostTyp(%u)\n", nrBytes(dcostMax));

    fprintf(pmTbl, "%%%%BEGIN(pmVocTab)\n");
    outBeg();
    for (i = 1; i <= termCnt; i++) {
        outSubBeg();
        outEntry(vocabulary[i]->code);
        outEntry(vocabulary[i]->syminfo.ter_info.icost);
        outEntry(vocabulary[i]->syminfo.ter_info.dcost);
        outString(vocabulary[i]->name);
        outString(vocabulary[i]->syminfo.ter_info.psymb);
        outSubEnd();
    }/*for*/
    outEnd();
    fprintf(pmTbl, "%%%%END(pmVocTab)\n");
}/*writeVocTab()*/


/*-----------------------------------------------------------------------------
 * writeSemantics - Write the semantic actions to the table file.
 *-----------------------------------------------------------------------------
 */
static void writeSemantics()
{
    int i, j, att;
    register char ch;

    if (semActCnt < 0) {
        fprintf(pmTbl, "%%%%SET pmSem(On)\n");
        fprintf(pmTbl, "%%%%BEGIN(pmSemantics)\n");
        fprintf(pmTbl, "%s", caseHead);
        fprintf(pmTbl, "%%%%END(pmSemantics)\n");
    } else {
        att = 0;
        fprintf(pmTbl, "%%%%SET pmSem(On)\n");
        fprintf(pmTbl, "%%%%BEGIN(pmSemantics)\n");
        if (getBoolOpt(LINE_OPT))
            fprintf(pmTbl, "#line %d \"%s\"\n%s\n",
                    rulesSrcp.line, inFiles[0], caseHead);
        else
            fprintf(pmTbl, "%s\n      ", caseHead);
        for (i = 0; i <= semActCnt; i++) {
            fprintf(pmTbl, "%s%u%s", caseBeg, semAct[i].prod, caseEnd);
            fprintf(pmTbl, "%s", commBeg);
            logRule(pmTbl, semAct[i].prod, '`');
            fprintf(pmTbl, "%s", commEnd);
            if (getBoolOpt(LINE_OPT))
                fprintf(pmTbl, "#line %d \"%s\"\n", semAct[i].line, inFiles[0]);
            j = 0;
            while (att < global_attref_cnt &&
                   global_attref_sto[att].ruleno == semAct[i].prod)
                {
                    while (j < global_attref_sto[att].actPos) {
                        if ((ch = semAct[i].act[j++]) == '%') putc('`', pmTbl);
                        putc(ch, pmTbl);
                    } /*while*/
                    if (vocabulary[global_attref_sto[att].sym]->symbol_typ ==
                        nts_symb)
                        {
                            fprintf(pmTbl, "%s", semBeg);
                        } else {
                        fprintf(pmTbl, "%s", symBeg);
                    } /*if*/
                    if (global_attref_sto[att].pos > 0) {
                        fprintf(pmTbl, "%u", global_attref_sto[att].pos);
                    } else {
                        fprintf(pmTbl, "1");
                    } /*if*/
                    if (vocabulary[global_attref_sto[att].sym]->symbol_typ ==
                        nts_symb)
                        {
                            fprintf(pmTbl, "%s", semEnd);
                        } else {
                        fprintf(pmTbl, "%s", symEnd);
                    } /*if*/
                    if (global_attref_sto[att].att != -1) {
                        fprintf(pmTbl, "%s%s", attrSep,
                                vocabulary[global_attref_sto[att].att]->name);
                    } /*if*/

                    att++;
                } /*while*/
            while (j < strlen(semAct[i].act)) {
                if ((ch = semAct[i].act[j++]) == '%') putc('`', pmTbl);
                putc(ch, pmTbl);
            }	/*while*/
            fprintf(pmTbl, "%s", actEnd);
        } /*for*/
        fprintf(pmTbl, "%%%%END(pmSemantics)\n");
    } /*if*/
} /*writeSemantics()*/


/*-----------------------------------------------------------------------------
 * writeVocabulary - Writes the vocabulary file (xxx.voc)
 *-----------------------------------------------------------------------------
 */
static void writeVocabulary()
{
    int i, j;

    fprintf(pmTbl, "%%%%SET vocFileName (\"%s\")\n", vocFileName);
    fprintf(pmTbl, "%%%%BEGIN (pmVoc)\n");
    for (i = 0; i <= termCnt; i++) {

        fprintf(pmTbl, "%4u %4u ", i, vocabulary[i]->code);
        j = 0;
        while (vocabulary[i]->name[j]) {
            if (vocabulary[i]->name[j] == '%')
                putc(pmkEscape, pmTbl);
            putc(vocabulary[i]->name[j++], pmTbl);
        }
        while (j++ < vocMaxLn) putc(' ', pmTbl);
        fprintf(pmTbl, " main\n");
    }/*for*/
    fprintf(pmTbl, "%%%%END (pmVoc)\n");
}/*writeVocabulary()*/


/*-----------------------------------------------------------------------------
 * pmTab - Entry point to the table generator
 *-----------------------------------------------------------------------------
 */
void pmTab()
{
    setLangVars();
    writeMisc();
    writeOptions();
    writeCodeAndData();
    writeActTab();
    writeGtoTab();
    writeVocTab();
    writeSemantics();
    writeVocabulary();
    fprintf(pmTbl, "%%%%PROCESS(\"%%%%(pmkLibrary)/Parse.imp\")\n");
    if (getBoolOpt(ERRORHANDLER_OPT))
        fprintf(pmTbl, "%%%%PROCESS(\"%%%%(pmkLibrary)/Err.imp\")\n");
}/*pmTab()*/
