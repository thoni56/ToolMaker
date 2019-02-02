/*-----------------------------------------------------------------------------
 * pwLog - Pretty printing routines for log file
 *		@(#)pwLog.c	1.4 (91/04/03 14:18:58)
 *-----------------------------------------------------------------------------
 * Created:	89-09-15 by Tom
 * Modified:	90-07-03 by Yngve. Better formatting in LogInputStats.
 *				Added 'Escape' output, fixed bug in "number of
 *				Semantic Actions" output.
 *		90-11-06 by Yngve. Removed all references to divFactor.
 *		91-04-02 by Yngve. Removed logging of action numbers
 *				 on pwsLog.
 *-----------------------------------------------------------------------------
 * Entries:								     
 *	?????
 *-----------------------------------------------------------------------------
 */

#include <string.h>
#include "pmk_i.h"
#include "pwsLexCode.h"
#include "pwLog.h"
#include "pwsGrm.h"
#include "pwsOrd.h"
#include "pwGe.h"
#include "pwPack.h"
#include <ctype.h>


static int tTabSize;		/* Size of t-table */
static int ntsTabSize;		/* Size of nts-table */
static int vocTabSize;		/* Size of voc-table */


/*-----------------------------------------------------------------------------
 * logOptList - Write a comma-separated list of options
 *-----------------------------------------------------------------------------
 */
int logOptList(file, opt)
FILE *file;			/* IN the file to write to (log or table) */
OptTabKind opt;			/* IN option to print*/
{
    int i = 0, j = 0, optCnt = 0;

    while (pmkOptTab[i].optTabKind != LAST_OPT) {
      if (pmkOptTab[i].optTabKind == opt) {
	while (pmkOptTab[i].sitems[j]) {
	  if (getSetOpt(opt)>>j & 1)
	    fprintf(file, (optCnt++? ", %s": "%s"), pmkOptTab[i].sitems[j]);
	  j++;
	}
	return optCnt;
      }
      i++;
    }
    return 0;
}/*logOptList()*/


/*-----------------------------------------------------------------------------
 * logInputStats - Write input summary
 *-----------------------------------------------------------------------------
 */
void logInputStats()
{
    int pos, tpos;

    if ((getSetOpt(LIST_OPT))>>4 & 1 != 0) {
	fprintf(pwsLog, "\n\n%50s\n", "Summary of the input process");
	fprintf(pwsLog, "%50s\n\n", "----------------------------");
	fprintf(pwsLog, "Grammar file name = %s\n", inFiles[0]); 
	fprintf(pwsLog, "Activated options = ");

	fprintf(pwsLog, "Recovery ");
	logOptList(pwsLog, RECOVERY_OPT);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "Optimize ");
	logOptList(pwsLog, OPTIMIZE_OPT);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "Actionpack ");
	logOptList(pwsLog, ACTIONPACK_OPT);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "Gotopack ");
	logOptList(pwsLog, GOTOPACK_OPT);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "List ");
	logOptList(pwsLog, LIST_OPT);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "Resolve ");
	logOptList(pwsLog, RESOLVE_OPT);
	fprintf(pwsLog, ";\n");

	if (!getBoolOpt(VERBOSE_OPT)) fprintf(pwsLog, "No ");
	fprintf(pwsLog, "Verbose");
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "Target '");
	fprintf(pwsLog, getStrOpt(PMKTARGET_OPT));
	fprintf(pwsLog, "';\n");

	fprintf(pwsLog, "Escape ");
	if (isprint(pmkEscape)) fprintf(pwsLog, "'%c'", pmkEscape);
	else fprintf(pwsLog, "%u", pmkEscape);
	fprintf(pwsLog, ";\n");

	fprintf(pwsLog, "\nProductions       = %u\n", global_prod_cnt);
	fprintf(pwsLog, "Terminals         = %u\n", termCnt);
	fprintf(pwsLog, "Non terminals     = %u\n", nonTermCnt);
	fprintf(pwsLog, "Attributes        = %u\n", attrCnt);
	fprintf(pwsLog, "Semantic actions  = %u\n\n", semActCnt + 1);
    }/*if*/
}/*logInputStats()*/


/*-----------------------------------------------------------------------------
 * logRule - Write a single rule or all rules with the same LHS
 *-----------------------------------------------------------------------------
 */
void logRule(file, rule, escChar)
FILE *file;			/* IN the file to write to (log or table) */
int rule;			/* IN the rule number to write */
char escChar;			/* IN the escape character for '%' if any */
{
    int lhs, rsize, len, i, j;
    char *name;
    char ch;

    lhs = global_prod_tbl[rule]->start;
    rsize = global_prod_tbl[rule]->rssz;

    /* Write left hand side symbol
     */
    if (escChar) {
	name = vocabulary[global_pvec_tbl[lhs]]->name;
	len = strlen(name);
	for (j = 0; j < len; j++) {
	    if ((ch = name[j]) == '%') putc(escChar, file);
	    putc(ch, file);
	}/*for*/
	fprintf(file, " =");
    } else {
	fprintf(file, "%s =", vocabulary[global_pvec_tbl[lhs]]->name);
    }/*if*/

    /* Write the right hand side symbols
     */
    for (i = lhs + 1; i <= lhs + rsize; i++) {
	if (escChar) {
	    name = vocabulary[global_pvec_tbl[i]]->name;
	    len = strlen(name);
	    putc(' ', file);
	    for (j = 0; j < len; j++) {
		if ((ch = name[j]) == '%') putc(escChar, file);
		putc(ch, file);
	    }/*for*/
	} else {
	    fprintf(file, " %s", vocabulary[global_pvec_tbl[i]]->name);
	}/*if*/
    }/*for*/

    fprintf(file, ";");
}/*logRule()*/


/*-----------------------------------------------------------------------------
 * logGrammar - Write formatted grammar
 *-----------------------------------------------------------------------------
 */
void logGrammar()
{
    int i, j;
    int name_len, lhs_len, line_pos;
    int lhs, rsize;
    char *name;

    if ((getSetOpt(LIST_OPT))>>1 & 1 != 0) {
	fprintf(pwsLog, "%60s\n\n", "T H E   V O C A B U L A R Y");
	fprintf(pwsLog, "T E R M I N A L S\n\n");

	for (i = 1; i <= termCnt; i++) {
	    fprintf(pwsLog, "%3u.  %*s = %3u  (icost = %u, dcost = %u",
		    i, -max_sym_len, vocabulary[i]->name,
		    vocabulary[i]->code,
		    vocabulary[i]->syminfo.ter_info.icost,
		    vocabulary[i]->syminfo.ter_info.dcost);
	    if (vocabulary[i]->syminfo.ter_info.psymb) {
		fprintf(pwsLog, ", => %s",
			vocabulary[i]->syminfo.ter_info.psymb);
	    }/*if*/
	    fprintf(pwsLog, ")\n");
	}/*for*/

	fprintf(pwsLog, "\n\nN O N   T E R M I N A L S\n\n");
	for (i = termCnt + 1; i <= gramSymCnt; i++) {
	    fprintf(pwsLog, "%3u.  %s\n", i, vocabulary[i]->name);
	}/*for*/

	if (attrCnt > 0) {
	    fprintf(pwsLog, "\n\nA T T R I B U T E S\n\n");
	    for (i = gramSymCnt + 1; i <= gramSymCnt + attrCnt; i++)
	    {
		fprintf(pwsLog, "%3u.  %s\n", i, vocabulary[i]->name);
	    }/*for*/
	}/*if*/

	fprintf(pwsLog, "\f%60s\n\n", "T H E   P R O D U C T I O N S");

	for (i = 1; i <= global_prod_cnt;) {
	    /* Get left hand side symbol
	     */
	    lhs = global_prod_tbl[i]->start;
	    rsize = global_prod_tbl[i]->rssz;

	    name = vocabulary[global_pvec_tbl[lhs]]->name;
	    lhs_len = strlen(name);

	    /* Write left hand side symbol
	     */
	    fprintf(pwsLog, "%3u. %s = ", i, name);

	    /* Write all right hand sides with same left symbol
	     */
	    for (;;) {
		line_pos = lhs_len + 9;
		for (j = lhs + 1; j <= lhs + rsize; j++) {
		    name = vocabulary[global_pvec_tbl[j]]->name;
		    name_len = strlen(name);
		    if (line_pos + name_len >= pws_width_max) { 
			line_pos = lhs_len + 8;
			fprintf(pwsLog, "\n%*s", line_pos, " ");
		    }/*if*/

		    fprintf(pwsLog, "%s ", name);
		    line_pos += name_len + 1;
		}/*for*/

		fprintf(pwsLog, "\n");
		if (global_prod_tbl[i++]->nxtls == -1) break;
		else {
		    /* More rules to write
		     */
		    fprintf(pwsLog, "%3u.%*s", i, lhs_len + 4, "! ");
		    lhs = global_prod_tbl[i]->start;
		    rsize = global_prod_tbl[i]->rssz;
		}/*if*/
	    }/*for*/

	    fprintf(pwsLog, "%*s\n\n", lhs_len + 7, ";");
	 }/*for*/
    }/*if*/
}/*logGrammar()*/


/*-----------------------------------------------------------------------------
 * logItemSet - Write the LALR(1) item set for a particular state
 *-----------------------------------------------------------------------------
 */
void logItemSet(state, firstCall)
int state;			/* IN state number */
Boolean firstCall;		/* IN first call? */
{
    int lnPos;			/* Current line position */
    int tLnPos;			/* Temporary line position */
    int firstItem;		/* First item number */
    int lastItem;		/* Last item number */
    int symLen;			/* Length of symbol */
    int i, j, k;		/* for loop variables */
    prod_rec *prodRef;		/* Temporary production reference */
    sym_ref symRef;		/* Temporary symbol reference */

    if (firstCall) {
	fprintf(pwsLog, "\f%60s\n\n\n",
		"L A L R ( 1 )  S E T S  O F  I T E M S");
    }/*if*/

    /* Write the continuation function
     */
    fprintf(pwsLog, "\nState: %4u   !  Continuation: ", state);
    if (contTbl[state].tsym != -1) {
	/* Note! The "%s"-format string in the following statement must not
	 * be removed since the name string may contain two %-signs which
	 * will be printed as one if the format string is omitted!
	 */
	fprintf(pwsLog, "%s", vocabulary[contTbl[state].tsym]->name);
	if (contTbl[state].tsym != contTbl[state].ssym) {
	    fprintf(pwsLog, "(%s)", vocabulary[contTbl[state].ssym]->name);
	}/*if*/
    }/*if*/

    fprintf(pwsLog, "\n- - - - - - - !");
    for (i = 0; i < ((pws_width_max - 16) / 2); i++) fprintf(pwsLog, " -");
    fprintf(pwsLog, "\n");

    firstItem = stateList[state].istart;
    lastItem = firstItem + stateList[state].setsz - 1;

    for (j = firstItem; j <= lastItem; j++) {
	/* Write all items in the set
	 */
	if ((accItem[j].typ == complete) || accItem[j].sr) { 
	    fprintf(pwsLog, "%*s%u", 13 - nofi(accItem[j].item.prod),
		    (accItem[j].sr? "SR": "R"), accItem[j].item.prod);
	} else {
	    fprintf(pwsLog, "%13u", accItem[j].succState);
	}/*if*/

	prodRef = global_prod_tbl[accItem[j].item.prod];
	symRef = vocabulary[global_pvec_tbl[prodRef->start]];
	symLen = strlen(symRef->name); 
	fprintf(pwsLog, " ! %*s --> ", symLen, symRef->name);
	lnPos = 21 + symLen;
	tLnPos = lnPos;

	for (k = 0; k < prodRef->rssz; k++) {
	    /* Write rightside of rule
	     */
	    if (k == accItem[j].item.dot) {  
		putc('.', pwsLog);
		lnPos++;
	    }/*if*/

	    /* Write one rightside element
	     */
	    symRef = vocabulary[global_pvec_tbl[k + prodRef->start + 1]];
	    symLen = strlen(symRef->name);
	    if ((symLen + lnPos) >= pws_width_max) {
		fprintf(pwsLog, "\n%15s%*s", "!", tLnPos - 15, " ");
		lnPos = tLnPos;
	    }/*if*/

	    fprintf(pwsLog, "%*s ", symLen, symRef->name);
	    lnPos += symLen + 1;
	}/*for*/

	if (accItem[j].item.dot == prodRef->rssz) { 
	    putc('.', pwsLog); 
	    lnPos++;
	}/*if*/

	/* Write the look-ahead set
	 * ------------------------
	 */
	if (accItem[j].typ == complete) {
	    fprintf(pwsLog, "\n%15s%*s{", "!", tLnPos - 15, " ");
	    tLnPos++;
	    lnPos = tLnPos;

	    for (k = 1; k <= termCnt; k++) {
		if (SetMem(accItem[j].laPtr, k)) {
		    symRef = vocabulary[k];
		    symLen = strlen(symRef->name);
		    if ((symLen + lnPos) >= pws_width_max) {
			fprintf(pwsLog, "\n%15s%*s", "!", tLnPos - 15, " ");
			lnPos = tLnPos;
		    }/*if*/

		    fprintf(pwsLog, "%*s ", symLen, symRef->name);
		    lnPos += symLen + 1;
		}/*if*/
	    }/*for*/
	    putc('}', pwsLog);
	}/*if*/
	putc('\n', pwsLog);
    }/*for*/
    putc('\n', pwsLog);
}/*logItemSet()*/
 

/*-----------------------------------------------------------------------------
 * logParseTables - Print the ACTION and the GOTO tables
 *-----------------------------------------------------------------------------
 */
void logParseTables()
{
    int ent;
    int act;
    int arg;
    int i, j;			/* Loop index */

    if ((getSetOpt(LIST_OPT))>>3 & 1 != 0) {
	/* Start with the Action Table */
	fprintf(pwsLog, "\n\n\n%60s\n\n\n",
		  "T H E  P A R S E R  A C T I O N  T A B L E");
	fprintf(pwsLog, "  TOP OF STACK%*s%s\n",
		7 + ((termCnt * 3) / 2), " ", "INPUT SYMBOL");
	fprintf(pwsLog, "STATE NAME%17s", "!");
	for (i = 1; i <= termCnt; i++) fprintf(pwsLog, "%3u", i);
	fprintf(pwsLog, "\n--------------------------!");
	for (i = 1; i <= termCnt; i++) fprintf(pwsLog, "---");
	fprintf(pwsLog, "\n");

	for (i = 1; i <= stateCnt; i++) {
	    /* For all states
	     */
	    fprintf(pwsLog, "%3u   %-20.20s! ", i,
		    vocabulary[stateList[i].top]->name);

	    for (j = 1; j <= termCnt; j++) {
		/* Write one row
		 */
		ent = actTbl[i - 1][j - 1];
		act = ent & 07;
		arg = ent >> 3;

		switch (act) {

		case error: 
		    if (SetMem(dontCare[i], j)) fprintf(pwsLog, " * ");
		    else fprintf(pwsLog, " X ");
		    break;

		case shift:
		    fprintf(pwsLog, "S");
		    break;

		case shiftReduce:
		    fprintf(pwsLog, "-");
		    break;

		case reduce:
		    fprintf(pwsLog, "R");
		    break;

		case accept:
		    fprintf(pwsLog, " A ");
		    break;
		}/*switch*/

		if (act != error && act != accept) {
		    fprintf(pwsLog, "%-2u", arg);
		}/*if*/
	    }/*for*/

	    fprintf(pwsLog, "\n");
	}/*for*/

	/* Parser Goto Table
	 * -----------------
	 */
	fprintf(pwsLog, "\n\n\n%50s\n\n\n", "T H E  G O T O  T A B L E");
	fprintf(pwsLog, "  TOP OF STACK%*sSYMBOL\n",
		10 + ((nonTermCnt * 3) / 2), " ");
	fprintf(pwsLog, "STATE NAME%17s", "!");
	for (i = termCnt + 1; i <= termCnt + nonTermCnt; i++) {
	    fprintf(pwsLog, "%3u", i);
	}/*for*/
	fprintf(pwsLog, "\n--------------------------!");
	for (i = termCnt + 1; i <= termCnt + nonTermCnt; i++) {
	    fprintf(pwsLog, "---");
	}/*for*/
	fprintf(pwsLog, "\n");

	for (i = 1; i <= stateCnt; i++) {
	    /* For all states
	     */
	    fprintf(pwsLog, "%3u   %-20.20s! ", i,
		    vocabulary[stateList[i].top]->name);
	    for (j = termCnt + 1; j <= termCnt + nonTermCnt;
		 j++)
	    {
		act = gtoTbl[i - 1][j - termCnt - 1] & 07;
		arg = gtoTbl[i - 1][j - termCnt - 1] >> 3;
		if (act == error) fprintf(pwsLog, " * ");
		else {
		    if (act == shiftReduce) fprintf(pwsLog, "-");
		    else fprintf(pwsLog, "S");
		    fprintf(pwsLog, "%-2u", arg);
		}/*if*/
	    }/*for*/

	    fprintf(pwsLog, "\n");
	}/*for*/
    }/*if*/
}/*logParseTables()*/


/*-----------------------------------------------------------------------------
 * logGeStats - Output generated summary
 *-----------------------------------------------------------------------------
 */
void logGeStats()
{
    int i, tot_space;

    if ((getSetOpt(LIST_OPT))>>4 & 1 != 0) {
	/* Action table
	 * ------------
	 */
	tTabSize = stateCnt * termCnt * nrBytes(actMax);
	if ((getSetOpt(RESOLVE_OPT))>>1 & 1 != 0) {
	    /* Continuation function (tsym and ssym)
	     */
	    tTabSize += stateCnt * 2 * nrBytes(termCnt);
	}/*if*/
	/* Recovery data
	 */
	tTabSize += 3 * SETLEN(termCnt + 1);

	/* Goto table
	 * ----------
	 */
	ntsTabSize = stateCnt * nonTermCnt * nrBytes(gtoMax);
	/* Production data
	 */
	ntsTabSize += global_prod_cnt *
	    (nrBytes(termCnt + nonTermCnt) + nrBytes(rsszMax));

	/* Vocabulary
	 * ----------
	 */
	vocTabSize = termCnt *
	    (nrBytes(tc_val) +	/* Scanner code value */
	     nrBytes(icostMax) + /* Insertion cost */
	     nrBytes(dcostMax) + /* Deletion cost */
	     2 * pointerSize);	/* Name and print name pointers */
	for (i = 1; i <= termCnt; i++) {
	    vocTabSize += strlen(vocabulary[i]->name) + 1;
	    if (vocabulary[i]->syminfo.ter_info.psymb) {
		vocTabSize +=
		    strlen(vocabulary[i]->syminfo.ter_info.psymb) + 1;
	    }/*if*/
	}/*for*/

	tot_space = tTabSize + ntsTabSize + vocTabSize;
	fprintf(pwsLog, "\n\n%50s\n",
		"Summary of the table generation process");
	fprintf(pwsLog, "%50s\n\n",
		"---------------------------------------");
	fprintf(pwsLog, "Number of states = %4u\n", stateCnt);
	fprintf(pwsLog, "Total table space = %6u bytes\n", tot_space);
	fprintf(pwsLog, "     T-table =   %5u bytes\n", tTabSize);
	fprintf(pwsLog, "     NTS-table = %5u bytes\n", ntsTabSize);
	fprintf(pwsLog, "     VOC-table = %5u bytes\n\n", vocTabSize);
    }/*if*/
}/*logGeStats()*/


/*-----------------------------------------------------------------------------
 * outputEntry - Output one parser entry
 *-----------------------------------------------------------------------------
 */
static void outputEntry(entry)
int entry;			/* IN parser action */
{
    int act, arg;

    act = entry & 07;

    switch (act) {

    case error: 
	fprintf(pwsLog, " X ");
	return;

    case shift: 	 
	fprintf(pwsLog, "S");
	break;

    case shiftReduce:
	fprintf(pwsLog, "-");
	break;

    case reduce:
	fprintf(pwsLog, "R");
	break;

    case accept:
	fprintf(pwsLog, " A ");
	return;
    }/*switch*/

    arg = entry >> 3;
    fprintf(pwsLog, "%-2u", arg);
}/*outputEntry()*/
     

/*-----------------------------------------------------------------------------
 * logPackedTables - Output the packed tables
 *-----------------------------------------------------------------------------
 */
void logPackedTables()
{
    int i, j, k;


    if ((getSetOpt(LIST_OPT))>>3 & 1 != 0) {
      /* ACTION table
	 * ------------
	 */
	if (actGCS || actLES || actRDS) {
	    fprintf(pwsLog, "\n\n\n%60s\n\n\n",
		    "T H E   P A C K E D   A C T I O N   T A B L E");

	    /* Non ERROR table
	     * ---------------
	     */
	    if (actGCS || actLES) {
	      if (getSetOpt(ACTIONPACK_OPT)>>5 & 1) {
		    fprintf(pwsLog, "%15s%s\n\n", " ",
			    "ERROR column mapping vector");
		    fprintf(pwsLog, " Column !");
		    for (i = 1; i <= termCnt; i++) {
			fprintf(pwsLog, "%3u", i);
		    }/*for*/
		    fprintf(pwsLog, "\n -------!");
		    for (i = 0; i < termCnt; i++) fprintf(pwsLog, "---");
		    fprintf(pwsLog, "\n Index  !");
		    for (i = 0; i < termCnt; i++) {
			fprintf(pwsLog, "%3u", act.ERRcol[i] + 1);
		    }/*for*/
		    fprintf(pwsLog, "\n\n%15s%s\n\n", " ",
			    "ERROR row mapping vector");
		    fprintf(pwsLog, " Row    !");
		    for (i = 1; i <= stateCnt; i++) {
			fprintf(pwsLog, "%3u", i);
		    }/*for*/
		    fprintf(pwsLog, "\n -------!");
		    for (i = 0; i < stateCnt; i++) fprintf(pwsLog, "---");
		    fprintf(pwsLog, "\n Index  !");
		    for (i = 0; i < stateCnt; i++) {
			fprintf(pwsLog, "%3u", act.ERRrow[i] + 1);
		    }/*for*/
		    fprintf(pwsLog, "\n\n");
		}/*if*/

		fprintf(pwsLog, "%15s%s\n\n", " ", "ERROR table");
		fprintf(pwsLog, "%6s", "!");
		for (i = 1; i <= act.ERRcols; i++) fprintf(pwsLog, "%3u", i);
		fprintf(pwsLog, "\n ----!");
		for (i = 0; i < act.ERRcols; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\n");

		for (i = 0; i < act.ERRrows; i++) { 
		    fprintf(pwsLog, "%4u ! ", i + 1);
		    for (j = 0; j < act.ERRcols; j++) {
			k = i * act.ERRcols + j;
			if (act.ERRvect[k >> 3] & (0x80 >> (k & 0x7))) {
			    fprintf(pwsLog, " 1 ");
			} else {
			    fprintf(pwsLog, " 0 ");
			}/*if*/
		    }/*for j*/
		    fprintf(pwsLog, "\n");
		}/*for*/
		fprintf(pwsLog, "\n\n");
	    }/*if*/

	    /* Row Displacement Check Vector
	     * -----------------------------
	     */
	    if (actRDS && !(actLES || actGCS)) {
		fprintf(pwsLog, "%15sRow Displacement Check Vector\n\n",
			  " ");
		for (i = 0; i <= (act.RDScheckLen - 1) / 20; i++) {
		    k = 20 * i;
		    fprintf(pwsLog, "Column       !");
		    for (j = k + 1; j <= min(act.RDScheckLen, k + 20); j++) {
			fprintf(pwsLog, "%3u", j);
		    }/*for*/
		    fprintf(pwsLog, "\n-------------!");
		    for (j = k; j < min(act.RDScheckLen, k + 20); j++) {
			fprintf(pwsLog, "---");
		    }/*for*/
		    fprintf(pwsLog, "\nRow Index    ! ");
		    for (j = k; j < min(act.RDScheckLen, k + 20); j++) {
			if (act.RDScheck[j] != stateCnt) {
			    fprintf(pwsLog, "%2u ", act.RDScheck[j] + 1);
			} else {
			    fprintf(pwsLog, " X ");
			}/*if*/
		    }/*for j*/
		    fprintf(pwsLog, "\n\n");
		}/*for i*/
	    }/*if*/

	    /* Row/column conditionals from Line Elimination Scheme
	     * ----------------------------------------------------
	     */
	    if (actLES) {
		fprintf(pwsLog, "%15sColumn conditional vector\n\n", " ");
		fprintf(pwsLog, "Column       !");
		for (i = 1; i <= termCnt; i++) fprintf(pwsLog, "%3u", i);
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < termCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nConditionals !");
		for (i = 0; i < termCnt; i++) {
		    if (act.LESdetCol[i] == act.LESscan) {
			fprintf(pwsLog, "   ");
		    } else {
			fprintf(pwsLog, "%3u", act.LESdetCol[i]);
		    }/*if*/
		}/*for*/

		fprintf(pwsLog, "\n\n%15sRow conditional vector\n\n", " ");
		fprintf(pwsLog, "Row          !");
		for (i = 1; i <= stateCnt; i++) fprintf(pwsLog, "%3u", i);
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < stateCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nConditionals !");
		for (i = 0; i < stateCnt; i++) {
		    if (act.LESdetRow[i] == act.LESscan) {
			fprintf(pwsLog, "   ");
		    } else {
			fprintf(pwsLog, "%3u", act.LESdetRow[i]);
		    }/*if*/
		}/*for*/
		fprintf(pwsLog, "\n\n");
	    }/*if*/

	    /* Row/column mapping vectors
	     * --------------------------
	     */
	    if (actGCS || actLES) {
		fprintf(pwsLog, "%15sColumn mapping vector\n\n", " ");
		fprintf(pwsLog, "Column       !");
		for (i = 1; i <= termCnt; i++) fprintf(pwsLog, "%3u", i);
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < termCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nIndex/Action !");
		for (i = 0; i < termCnt; i++) {
		    if (actLES && act.LESdetCol[i] != act.LESscan) {
			outputEntry(act.LESorGCScol[i]);
		    } else {
			fprintf(pwsLog, "%3u", act.LESorGCScol[i] + 1);
		    }/*if*/
		}/*for*/
		fprintf(pwsLog, "\n\n");
	    }/*if*/

	    fprintf(pwsLog, "%15sRow mapping vector\n\n", " ");
	    fprintf(pwsLog, "Row          !");
	    for (i = 1; i <= stateCnt; i++) fprintf(pwsLog, "%3u", i);
	    fprintf(pwsLog, "\n-------------!");
	    for (i = 0; i < stateCnt; i++) fprintf(pwsLog, "---");
	    if (actGCS || actLES) {
		fprintf(pwsLog, "\nIndex/Action !");
		for (i = 0; i < stateCnt; i++) {
		    if (actLES && act.LESdetRow[i] != act.LESscan) {
			outputEntry(act.LESorGCSrow[i]);
		    } else {
			fprintf(pwsLog, "%3u", act.LESorGCSrow[i] + 1);
		    }/*if*/
		}/*for*/
	    } else {
		fprintf(pwsLog, "\nIndex        !");
		for (i = 0; i < stateCnt; i++) {
		    fprintf(pwsLog, "%3u", act.RDSbase[i] + 1);
		}/*for*/
	    }/*if*/
	    fprintf(pwsLog, "\n\n");

	    /* Compressed ACTION table
	     * -----------------------
	     */
	    if (actRDS && act.RDSvectorLen > 0) {
		fprintf(pwsLog, "%15sCompressed ACTION table\n\n", " ");
		for (i = 0; i <= (act.RDSvectorLen - 1) / 20; i++) {
		    k = 20 * i;
		    fprintf(pwsLog, "Index        !");
		    for (j = k + 1; j <= min(act.RDSvectorLen, k + 20); j++) {
			fprintf(pwsLog, "%3u", j);
		    }/*for*/
		    fprintf(pwsLog, "\n-------------!");
		    for (j = k; j < min(act.RDSvectorLen, k + 20); j++) {
			fprintf(pwsLog, "---");
		    }/*for*/
		    fprintf(pwsLog, "\nEntry        ! ");
		    for (j = k; j < min(act.RDSvectorLen, k + 20); j++) {
			outputEntry(act.RDSvector[j]);
		    }/*for*/
		    fprintf(pwsLog, "\n\n");
		}/*for i*/
	    } else if ((act.rows > 0) && (act.cols > 0)) {
		/* Table has not been removed completely
		 */
		fprintf(pwsLog, "%15sCompressed ACTION table\n\n", " ");
		fprintf(pwsLog, "%5s", "!");
		for (i = 1; i <= act.cols; i++) {
		    fprintf(pwsLog, "%3u", i);
		}/*for*/
		fprintf(pwsLog, "\n----!");
		for (i = 0; i < act.cols; i++) {
		    fprintf(pwsLog, "---");
		}/*for*/
		fprintf(pwsLog, "\n");

		for (i = 0; i < act.rows; i++) {
		    /* For all remaining rows
		     */
		    fprintf(pwsLog, "%3u ! ", i + 1);
		    for (j = 0; j < act.cols; j++) {
			outputEntry(act.matrix[i][j]);
		    }/*for j*/
		    fprintf(pwsLog, "\n");
		}/*for i*/
	    }/*if*/
	}/*if*/

	/* GOTO table
	 * ----------
	 */
	if (gtoGCS || gtoLES || gtoRDS) {
	    fprintf(pwsLog, "\n\n\n%60s\n\n\n",
		    "T H E   P A C K E D   G O T O   T A B L E");

	    /* Row/column conditionals from Line Elimination Scheme
	     */
	    if (gtoLES) {
		fprintf(pwsLog, "%15sColumn conditional vector\n\n", " ");
		fprintf(pwsLog, "Column       !");
		for (i = 1; i <= nonTermCnt; i++) {
		    fprintf(pwsLog, "%3u", i + termCnt);
		}/*for*/
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < nonTermCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nConditionals !");
		for (i = 0; i < nonTermCnt; i++) {
		    if (gto.LESdetCol[i] == gto.LESscan) {
			fprintf(pwsLog, "   ");
		    } else {
			fprintf(pwsLog, "%3u", gto.LESdetCol[i]);
		    }/*if*/
		}/*for*/
		fprintf(pwsLog, "\n\n%15sRow conditional vector\n\n", " ");
		fprintf(pwsLog, "Row          !");
		for (i = 1; i <= stateCnt; i++) fprintf(pwsLog, "%3u", i);
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < stateCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nConditionals !");
		for (i = 0; i < stateCnt; i++) {
		    if (gto.LESdetRow[i] == gto.LESscan) {
			fprintf(pwsLog, "   ");
		    } else {
			fprintf(pwsLog, "%3u", gto.LESdetRow[i]);
		    }/*if*/
		}/*for*/
		fprintf(pwsLog, "\n\n");
	    }/*if*/

	    /* Row/column mapping vectors
	     * --------------------------
	     */
	    if (gtoGCS || gtoLES) {
		fprintf(pwsLog, "%15sColumn mapping vector\n\n", " ");
		fprintf(pwsLog, "Column       !");
		for (i = 1; i <= nonTermCnt; i++) {
		    fprintf(pwsLog, "%3u", i + termCnt);
		}/*for*/
		fprintf(pwsLog, "\n-------------!");
		for (i = 0; i < nonTermCnt; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\nIndex/Action !");
		for (i = 0; i < nonTermCnt; i++) {
		    if (gtoLES && gto.LESdetCol[i] != gto.LESscan) {
			outputEntry(gto.LESorGCScol[i]);
		    } else if (gtoRDS) {
			fprintf(pwsLog, "%3u", gto.LESorGCScol[i] + 1);
		    } else {
			fprintf(pwsLog, "%3u",
				gto.LESorGCScol[i] + termCnt + 1);
		    }/*if*/
		}/*for*/
		fprintf(pwsLog, "\n\n");
	    }/*if*/

	    fprintf(pwsLog, "%15sRow mapping vector\n\n", " ");
	    fprintf(pwsLog, "Row          !");
	    for (i = 1; i <= stateCnt; i++) fprintf(pwsLog, "%3u", i);
	    fprintf(pwsLog, "\n-------------!");
	    for (i = 0; i < stateCnt; i++) fprintf(pwsLog, "---");
	    if (gtoGCS || gtoLES) {
		fprintf(pwsLog, "\nIndex/Action !");
		for (i = 0; i < stateCnt; i++) {
		    if (gtoLES && gto.LESdetRow[i] != gto.LESscan) {
			outputEntry(gto.LESorGCSrow[i]);
		    } else if (gtoRDS) {
			fprintf(pwsLog,
				"%3u", gto.LESorGCSrow[i] + termCnt + 1);
		    } else {
			fprintf(pwsLog, "%3u", gto.LESorGCSrow[i] + 1);
		    }/*if*/
		}/*for*/
	    } else {
		fprintf(pwsLog, "\nIndex        !");
		for (i = 0; i < stateCnt; i++) {
		    fprintf(pwsLog, "%3u", gto.RDSbase[i] + termCnt + 1);
		}/*for*/
	    }/*if*/
	    fprintf(pwsLog, "\n\n");

	    /* Compressed GOTO table
	     * ---------------------
	     */
	    if (gtoRDS && gto.RDSvectorLen > 0) {
		fprintf(pwsLog, "%15sCompressed GOTO table\n\n", " ");
		for (i = 0; i <= (gto.RDSvectorLen - 1) / 20;
		     i++)
		{
		    k = 20 * i;
		    fprintf(pwsLog, "Index        !");
		    for (j = k + 1; j <= min(gto.RDSvectorLen, k + 20); j++) {
			fprintf(pwsLog, "%3u", j + termCnt);
		    }/*for*/
		    fprintf(pwsLog, "\n-------------!");
		    for (j = k; j < min(gto.RDSvectorLen, k + 20); j++) {
			fprintf(pwsLog, "---");
		    }/*for*/
		    fprintf(pwsLog, "\nEntry        ! ");
		    for (j = k; j < min(gto.RDSvectorLen, k + 20); j++) {
			outputEntry(gto.RDSvector[j]);
		    }/*for*/
		    fprintf(pwsLog, "\n\n");
		}/*for*/
	    } else if ((gto.rows > 0) && (gto.cols > 0)) {
		/* Table has not been removed completely
		 */
		fprintf(pwsLog, "%15sCompressed GOTO table\n\n", " ");
		fprintf(pwsLog, "%5s", "!");
		for (i = 1; i <= gto.cols; i++) {
		    fprintf(pwsLog, "%3u", i + termCnt);
		}/*for*/
		fprintf(pwsLog, "\n----!");
		for (i = 0; i < gto.cols; i++) fprintf(pwsLog, "---");
		fprintf(pwsLog, "\n");

		for (i = 0; i < gto.rows; i++) {
		    /* For all remaining rows
		     */
		    fprintf(pwsLog, "%3u ! ", i + 1);
		    for (j = 0; j < gto.cols; j++) {
			outputEntry(gto.matrix[i][j]);
		    }/*for*/
		    fprintf(pwsLog, "\n");
		}/*for*/
	    }/*if*/
	}/*if*/
    }/*if*/
}/*logPackedTables()*/

   
/*-----------------------------------------------------------------------------
 * logPackStats - Summary the packing process
 *-----------------------------------------------------------------------------
 */
void logPackStats()
{
    int goto_cols;
    int tot_space;

    if ((getSetOpt(LIST_OPT))>>4 & 1 != 0) {
	tTabSize -= stateCnt * termCnt * nrBytes(actMax);
	ntsTabSize -= stateCnt * nonTermCnt * nrBytes(gtoMax);

	if (actRDS) {
	    tTabSize += act.RDSvectorLen * nrBytes(actMax); /* Action vector */
	} else {
	    tTabSize += act.rows * act.cols * nrBytes(actMax); /* Action tab */
	}/*if*/

	if (actRDS && !(actLES || actGCS)) {
	    /* RDS check vector
	     */
	    tTabSize += act.RDScheckLen * nrBytes(stateCnt);
	    /* RDS mapping vector
	     */
	    tTabSize += stateCnt * nrBytes(act.RDSvectorLen);
	}/*if*/

	if (actGCS || actLES) {
	    /* Error table
	     */
	    tTabSize += SETLEN(act.ERRrows * act.ERRcols);
	    if (getSetOpt(ACTIONPACK_OPT)>>5 & 1) {
		/* Error row and column mappings
		 */
		tTabSize += stateCnt * nrBytes(act.ERRrows);
		tTabSize += termCnt * nrBytes(act.ERRcols);
	    }/*if*/
	}/*if*/

	if (actLES) {
	    /* Row and column conditionals
	     */
	    tTabSize += stateCnt * nrBytes(act.LESscan);
	    tTabSize += termCnt * nrBytes(act.LESscan);
	    /* Row and column mapping vectors
	     */
	    if (actRDS) {
		tTabSize += stateCnt * nrBytes(max(actMax, act.RDSvectorLen));
	    } else {
		tTabSize += stateCnt * nrBytes(max(actMax, act.rows));
	    }/*if*/
	    tTabSize += termCnt * nrBytes(max(actMax, act.cols));
	} else if (actGCS) {
	    /* Row and column mapping vectors
	     */
	    if (actRDS) tTabSize += stateCnt * nrBytes(act.RDSvectorLen);
	    else tTabSize += stateCnt * nrBytes(act.rows);
	    tTabSize += termCnt * nrBytes(act.cols);
	}/*if*/

	if (gtoRDS) {
	    ntsTabSize += gto.RDSvectorLen * nrBytes(gtoMax); /* Goto vector */
	} else {
	    ntsTabSize += gto.rows * gto.cols * nrBytes(gtoMax); /* Goto tab */
	}/*if*/

	if (gtoRDS && !(gtoLES || gtoGCS)) {
	    /* RDS mapping vector
	     */
	    ntsTabSize += stateCnt * nrBytes(gto.RDSvectorLen);
	}/*if*/

	if (gtoLES) {
	    /* Row and column conditionals
	     */
	    ntsTabSize += stateCnt * nrBytes(gto.LESscan);
	    ntsTabSize += nonTermCnt * nrBytes(gto.LESscan);
	    /* Row and column mapping vectors
	     */
	    if (gtoRDS) {
		ntsTabSize +=
		    stateCnt * nrBytes(max(gtoMax, gto.RDSvectorLen));
	    } else {
		ntsTabSize += stateCnt * nrBytes(max(gtoMax, gto.rows));
	    }/*if*/
	    ntsTabSize += nonTermCnt * nrBytes(max(gtoMax, gto.cols));
	} else if (gtoGCS) {
	    /* Row and column mapping vectors
	     */
	    if (gtoRDS) ntsTabSize += stateCnt * nrBytes(gto.RDSvectorLen);
	    else ntsTabSize += stateCnt * nrBytes(gto.rows);
	    ntsTabSize += nonTermCnt * nrBytes(gto.cols);
	}/*if*/

	tot_space = tTabSize + ntsTabSize + vocTabSize;

	fprintf(pwsLog, "\n\n%50s\n", "Summary of the packing process");
	fprintf(pwsLog, "%50s\n\n", "------------------------------");
	fprintf(pwsLog, "Total table space = %6u bytes\n", tot_space);
	fprintf(pwsLog, "     T-table   = %5u bytes\n", tTabSize);
	fprintf(pwsLog, "     NTS-table = %5u bytes\n", ntsTabSize);
	fprintf(pwsLog, "     VOC-table = %5u bytes\n", vocTabSize);
	fprintf(pwsLog, "\n");
    }/*if*/
}/*logPackStats()*/
