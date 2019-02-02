/*------------------------------------------------------------------- */ 
/* TITLE                                                              */ 
/* ------                                                             */ 
/* lmkTab.c                                                           */
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
/* ListerMaker table generator                                        */
/*                                                                    */ 
/* ------------------------------------------------------------------ */
/* IMPORT */
#include <ctype.h>
#include "lmk_i.h"

/* DATA */
int messCntTot = 0;
static char *listType[] = {"Single", "Multiple", "Separate"};

#define boolT(O) (getBoolOpt(O) ? "On" : "Off")

/*----------------------------------------------------------------------
    impify

    adapt string to imp syntax

*/
static void impify(outstr, instr)
  char *outstr;
  char *instr;
{
  for (; *instr; *outstr++ = *instr++)
    if (*instr == '"')
      *outstr++ = '"';
  *outstr = '\0';
}

/*----------------------------------------------------------------------

    prOpts

    print lister options on table file

*/
static void prOpt(outfile)
  FILE *outfile;		/* IN output file */
{
  Boolean optPrinted = FALSE;
  int i;

  fprintf(outfile, "%%%%SET lmkInclude(%s)\n", boolT(INCLUDE_OPT));
  fprintf(outfile, "%%%%SET lmkMessage(%s)\n",
	  (getNumOpt(MESSAGE_OPT) ? "Embedded" : "File"));

  for (i = 0; i < 3; i++)
    if (getSetOpt(LISTINGS_OPT) & (1 << i)) {
      fprintf(outfile, "%%%%SET lmkListings(%s%s)\n", 
	    (optPrinted ? ", " : ""), listType[i]);
      optPrinted = TRUE;
    }

  if (getBoolOpt(LIMIT_OPT))
    fprintf(outfile, "%%%%SET lmkMessagelimit(%i)\n",
	    getNumOpt(LIMIT_OPT));

  fprintf(outfile, "%%%%SET tmkForce(%d)\n", getBoolOpt(FORCE_OPT) ? 1 : 0);
  fprintf(outfile, "%%%%SET tmkTarget(\"%s\")\n", getStrOpt(TMKTARGET_OPT));
  fprintf(outfile, "%%%%SET lmkTarget(\"%s\")\n", getStrOpt(LMKTARGET_OPT));
  fprintf(outfile, "%%%%SET tmkOs(\"%s\")\n", getStrOpt(TMKOS_OPT));
  fprintf(outfile, "%%%%SET lmkOs(\"%s\")\n", getStrOpt(LMKOS_OPT));
  fprintf(outfile, "%%%%SET tmkLibrary(\"%s\")\n", getStrOpt(TMKLIBRARY_OPT));
  fprintf(outfile, "%%%%SET lmkLibrary(\"%s\")\n", getStrOpt(LMKLIBRARY_OPT));
  fprintf(outfile, "%%%%SET tmkPrefix(\"%s\")\n", getStrOpt(TMKPREFIX_OPT));
  fprintf(outfile, "%%%%SET lmkPrefix(\"%s\")\n", getStrOpt(LMKPREFIX_OPT));


  fprintf(outfile, "%%%%SET lmkEscape(\"%c\")\n", *getStrOpt(LMKESCAPE_OPT));
}

/*----------------------------------------------------------------------

    prMess

    print one message table

*/
static void prMess(outfile, msNode)
  FILE *outfile;		/* IN output file */
  MessSectNodeP msNode;		/* IN message sector node */
{
  int i;
  char buff[255];

  /* Convert section name to upper case */
  for (i = 0; msNode->name[i] != '\0'; i++)
    msNode->name[i] = toupper(msNode->name[i]);

  fprintf(outfile, "%%%%SET lmkMSectName(%s%%%%(lmkPrefix)_%s_Messages)\n",
	  (messCntTot==0 ? "" : ", "), msNode->name);
  fprintf(outfile, "%%%%SET lmkMSectOffs(%s%i)\n",
	  (messCntTot==0 ? "" : ", "), messCntTot);
  fprintf(outfile, "%%%%SET lmkMSectLen(%s%i)\n",
	  (messCntTot==0 ? "" : ", "), msNode->messCnt);
  for (i = 0; i < msNode->messCnt; i++) {
    fprintf(outfile, "%%%%SET lmkMsgId(%s\"%-6i\")\n", 
	    (messCntTot==0 ? "" : ", "), msNode->messTab[i]->number);
    impify(buff, msNode->messTab[i]->text);
    fprintf(outfile, "%%%%SET lmkMsg(%s\"%s\")\n", 
	    (messCntTot==0 ? "" : ", "), buff);
    messCntTot++;
  }
}

/*----------------------------------------------------------------------

    prImport

    print lmk import section

*/
static void prImport(outfile, lmkImportSection)
  FILE *outfile;		/* IN output file */
  CodeNodeP lmkImportSection;	/* IN import section */
{
  FILE *infile;

  if (lmkImportSection && 
      (infile = fopen(lmkImportSection->fname, "rb")) != NULL) {
    fprintf(outfile, "%%%%BEGIN(lmkImport)\n");
    tmkCopyCode(infile, lmkImportSection->fpos, lmkImportSection->length, 
		lmkEscape, outfile, '`');
    fprintf(outfile, "%%%%END(lmkImport)\n");
  }
}

/*----------------------------------------------------------------------

    prTail

    print some tail imp code

*/
static void prTail(outfile)
  FILE *outfile;		/* IN output file */
{
  fprintf(outfile, "%%%%PROCESS(\"%%%%(tmkLibrary)/Common.imp\")\n");
  fprintf(outfile, "%%%%PROCESS(\"%%%%(lmkLibrary)/List.imp\")\n");
}

/*======================================================================

    lmkTab()

    print lmk tables and options on output file

*/
void lmkTab(outfile, msNode, tokenNode, srcpNode, 
	    importSection, lmkImportSection)
  FILE *outfile;		/* IN output file */
  MessSectNodeP msNode;		/* IN message sector node */
  TokenNodeP tokenNode;
  SrcpNodeP srcpNode;
  CodeNodeP importSection;
  CodeNodeP lmkImportSection;
{
  /* print options, common stuff and import section */
  prOpt(outfile);
  tmkPCommon(outfile, tokenNode, srcpNode, importSection, getStrOpt(TMKESCAPE_OPT)[0]);
  prImport(outfile, lmkImportSection);

  /* print lmk tables */
  for (; msNode; msNode = msNode->next)
    prMess(outfile, msNode);

  /* print tail imp code */
  prTail(outfile);
}
