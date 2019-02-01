/*----------------------------------------------------------------------*\

	tmkPaSema.c

	ParserMaker generated semantic actions

\*----------------------------------------------------------------------*/

/* %%IMPORT */

#include "tmkScan.h"
#include "tmk.h"
extern tmkScContext tmkCext;
/* END %%IMPORT */

/* System dependencies
 * -------------------
 */

/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;

/* Token and Srcp definition */
#include "tmkCommon.h"

/* Attribute stacks *\
\* ---------------- */
/* %%ATTRIBUTES */
/* The semantic attributes for grammar symbols */
typedef struct tmkGrammar {
    OptNodeP opt;
    TmoNodeP dir;
    TokenAttrListP attr;
    int ival;
    char *sval;
    TmkSrcp srcp;
} tmkGrammar;

/* END %%ATTRIBUTES */

extern short tmkStkP;
extern TmkToken tmkSySt[];
extern tmkGrammar tmkSeSt[];

/* %%DECLARATIONS - User data and routines */


#include <stdio.h>
#include <stdlib.h>
#include "tmkCommon.h"
#include "tmk_i.h"
#include "tmkList.h"

static Boolean srcpOptional = TRUE;
static char *dummy;

static TokenAttrListP newAttr(name, nameDecl)
  char *name;			/* Attribute name */
  char *nameDecl;		/* Attribute name declaration */
{
  TokenAttrListP p = (TokenAttrListP) malloc(sizeof(TokenAttrList));
  p->name = name;
  p->nameDecl = nameDecl;
  p->next = NULL;
  return p;
}

static OptNodeP newOpt(name, srcp)
  char *name;			/* Option name */
  TmkSrcp srcp;			/* Option srcp */
{
  OptNodeP p = (OptNodeP) malloc(sizeof(OptNode));
  p->name = name;
  p->srcp = srcp;
  p->next = NULL;
  return p;
}


/* END %%DECLARATIONS */


/*----------------------------------------------------------------------------
 * tmkPaSema - The semantic actions
 *----------------------------------------------------------------------------
 */
void tmkPaSema(
int rule			/* IN production number */
)
{
    switch (rule) {
          case 1: { /* tmk_document = option_section other_sections; */

          if (!(srcpOptional || tmkEnv->srcpNode))
	    /* SRCP section not found */
            tmkLog(NULL, 64, sevERR, "SRCP");
		break;}
    case 8: { /* option_section =; */

	  srcpOptional = TRUE;
		break;}
    case 9: { /* option_section = '%%OPTIONS' optional_end; */

	  srcpOptional = TRUE;
		break;}
    case 10: { /* option_section = '%%OPTIONS' option_directives optional_end; */

	  srcpOptional = TRUE;
          setOpts(tmkEnv->optTab, tmkSeSt[tmkStkP+2].dir);
          setCliOpts(tmkEnv->cliTab, tmkEnv->argc, tmkEnv->argv, &dummy);
	  tmkEscape = *getStrOpt(tmkEnv->escapeOpt);
		break;}
    case 13: { /* option_directives = option_directive; */

	  tmkSeSt[tmkStkP+1].dir = tmkSeSt[tmkStkP+1].dir;
		break;}
    case 14: { /* option_directives = option_directives option_directive; */
{
	  TmoNodeP p;

	  if (tmkSeSt[tmkStkP+1].dir == NULL)
	    tmkSeSt[tmkStkP+1].dir = tmkSeSt[tmkStkP+2].dir;
	  else {
	    for (p = tmkSeSt[tmkStkP+1].dir; p->next; p = p->next);
	    p->next = tmkSeSt[tmkStkP+2].dir;
	    tmkSeSt[tmkStkP+1].dir= tmkSeSt[tmkStkP+1].dir;
	  }
	}	break;}
    case 15: { /* option_directive = identifier ';'; */
{
	  TmoNodeP p = (TmoNodeP) malloc(sizeof(TmoNode));
	  p->name = tmkSeSt[tmkStkP+1].sval;
	  p->srcp = tmkSeSt[tmkStkP+1].srcp;
	  p->dirKind = BOOL_TMO;
	  p->oval.bval = TRUE;
	  p->next = NULL;
	  tmkSeSt[tmkStkP+1].dir = p;
	}	break;}
    case 16: { /* option_directive = 'NO' identifier ';'; */
{
	  TmoNodeP p = (TmoNodeP) malloc(sizeof(TmoNode));
	  p->name = tmkSeSt[tmkStkP+2].sval;
	  p->srcp = tmkSeSt[tmkStkP+2].srcp;
	  p->dirKind = BOOL_TMO;
	  p->oval.bval = FALSE;
	  p->next = NULL;
	  tmkSeSt[tmkStkP+1].dir = p;
	}	break;}
    case 17: { /* option_directive = identifier NUMBER ';'; */
{
	  TmoNodeP p = (TmoNodeP) malloc(sizeof(TmoNode));
	  p->name = tmkSeSt[tmkStkP+1].sval;
	  p->srcp = tmkSeSt[tmkStkP+1].srcp;
	  p->dirKind = NUM_TMO;
	  p->oval.ival = tmkSySt[tmkStkP+2].ival;
	  p->next = NULL;
	  tmkSeSt[tmkStkP+1].dir = p;
	}	break;}
    case 18: { /* option_directive = identifier STRING ';'; */
{
	  TmoNodeP p = (TmoNodeP) malloc(sizeof(TmoNode));
	  p->name = tmkSeSt[tmkStkP+1].sval;
	  p->srcp = tmkSeSt[tmkStkP+1].srcp;
	  p->dirKind = STR_TMO;
	  p->oval.sval = tmkSySt[tmkStkP+2].sval;
	  p->next = NULL;
	  tmkSeSt[tmkStkP+1].dir = p;
	}	break;}
    case 19: { /* option_directive = identifier options ';'; */
{
	  TmoNodeP p = (TmoNodeP) malloc(sizeof(TmoNode));
	  p->name = tmkSeSt[tmkStkP+1].sval;
	  p->srcp = tmkSeSt[tmkStkP+1].srcp;
	  p->dirKind = SET_TMO;
	  p->oval.opts = tmkSeSt[tmkStkP+2].opt;
	  p->next = NULL;
          tmkSeSt[tmkStkP+1].dir = p;
	}	break;}
    case 20: { /* options = identifier; */

	  tmkSeSt[tmkStkP+1].opt = newOpt(tmkSeSt[tmkStkP+1].sval, tmkSeSt[tmkStkP+1].srcp);
		break;}
    case 21: { /* options = options ',' identifier; */
{
	  OptNodeP p;

	  if (tmkSeSt[tmkStkP+1].opt == NULL)
	    tmkSeSt[tmkStkP+1].opt = newOpt(tmkSeSt[tmkStkP+3].sval, tmkSeSt[tmkStkP+3].srcp);
	  else {
	    for (p = tmkSeSt[tmkStkP+1].opt; p->next; p = p->next);
	    p->next = newOpt(tmkSeSt[tmkStkP+3].sval, tmkSeSt[tmkStkP+3].srcp);
	    tmkSeSt[tmkStkP+1].opt = tmkSeSt[tmkStkP+1].opt;
	  }
	}	break;}
    case 22: { /* import_section = '%%IMPORT' optional_end; */

	  if (tmkEnv->importSection)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 60, sevERR, "");
	  else
  	    tmkEnv->importSection = tmkNewCode(tmkSySt[tmkStkP+1].fpos, tmkSySt[tmkStkP+1].length);
		break;}
    case 23: { /* token_section = token_header token_decls optional_end; */
{
          Boolean declFound = FALSE;
          Boolean declOmitted = FALSE;
          TokenAttrListP attrs;

	  if (tmkEnv->tokenNode->name == NULL)
            /* Token type must have a name */
	    tmkLog(&tmkSeSt[tmkStkP+1].srcp, 62, sevERR, "NAME");

	  if (tmkEnv->tokenNode->code == NULL)
            /* Token must have a code part */
	    tmkLog(&tmkSeSt[tmkStkP+1].srcp, 62, sevERR, "CODE");

          /* check declarations */
          if (tmkEnv->tokenNode->codeDecl)
            declFound = TRUE;
          else
            declOmitted = TRUE;

          if (tmkEnv->tokenNode->srcpDecl)
            declFound = TRUE;

          for (attrs = tmkEnv->tokenNode->attrs; 
               attrs && (!declFound || !declOmitted); 
               attrs = attrs->next)
            if (attrs->nameDecl)
              declFound = TRUE;
            else 
              declOmitted = TRUE;

          if (declFound && declOmitted)
            /* If there exists declarations all fields (except SRCP) must have it */
            tmkLog(&tmkSeSt[tmkStkP+1].srcp, 65, sevERR, "token");

          srcpOptional = (!declFound || tmkEnv->tokenNode->srcpDecl || !tmkEnv->tokenNode->srcp);
	}	break;}
    case 24: { /* token_header = '%%TOKEN'; */

          tmkEnv->tokenNode = (TokenNodeP) calloc(1,sizeof(TokenNode));
          tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 27: { /* token_decl = 'NAME' identifier ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->tokenNode->name)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else
	    tmkEnv->tokenNode->name = tmkSeSt[tmkStkP+2].sval;
		break;}
    case 28: { /* token_decl = 'CODE' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->tokenNode->code)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->tokenNode->code = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->tokenNode->codeDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 29: { /* token_decl = 'SRCP' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->tokenNode->srcp)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->tokenNode->srcp = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->tokenNode->srcpDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 30: { /* token_decl = 'ATTRIBUTES' token_attributes ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->tokenNode->attrs)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else
	    tmkEnv->tokenNode->attrs = tmkSeSt[tmkStkP+2].attr;
		break;}
    case 31: { /* token_attributes = token_attribute; */

	  tmkSeSt[tmkStkP+1].attr = tmkSeSt[tmkStkP+1].attr;
		break;}
    case 32: { /* token_attributes = token_attributes ',' token_attribute; */
{
	  TokenAttrListP p;

	  if (tmkSeSt[tmkStkP+1].attr == NULL)
	    tmkSeSt[tmkStkP+1].attr = tmkSeSt[tmkStkP+3].attr;
	  else {
	    for (p = tmkSeSt[tmkStkP+1].attr; p->next; p = p->next);
	    p->next = tmkSeSt[tmkStkP+3].attr;
	    tmkSeSt[tmkStkP+1].attr = tmkSeSt[tmkStkP+1].attr;
	  }
	}	break;}
    case 33: { /* token_attribute = identifier optional_decl; */

	  tmkSeSt[tmkStkP+1].attr = newAttr(tmkSeSt[tmkStkP+1].sval, tmkSeSt[tmkStkP+2].sval);
		break;}
    case 34: { /* optional_decl =; */

	  tmkSeSt[tmkStkP+1].sval = NULL;
		break;}
    case 35: { /* optional_decl = '%%'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
		break;}
    case 36: { /* srcp_section = srcp_header srcp_decls optional_end; */
{
          Boolean declFound = FALSE;
          Boolean declOmitted = FALSE;

	  if (tmkEnv->srcpNode->name == NULL)
            /* Source position type must have a name */
	    tmkLog(&tmkSeSt[tmkStkP+1].srcp, 63, sevERR, "NAME");

          if (tmkEnv->srcpNode->row || tmkEnv->srcpNode->col ||
	      tmkEnv->srcpNode->file || tmkEnv->srcpNode->pos) {
            /* check declarations */
            if (tmkEnv->srcpNode->row)
              if (tmkEnv->srcpNode->rowDecl)
                declFound = TRUE;
              else
                declOmitted = TRUE;
            if (tmkEnv->srcpNode->col)
              if (tmkEnv->srcpNode->colDecl)
                declFound = TRUE;
              else
                declOmitted = TRUE;
            if (tmkEnv->srcpNode->file)
              if (tmkEnv->srcpNode->fileDecl)
                declFound = TRUE;
              else
                declOmitted = TRUE;
            if (tmkEnv->srcpNode->pos)
              if (tmkEnv->srcpNode->posDecl)
                declFound = TRUE;
              else
                declOmitted = TRUE;
            if (declFound && declOmitted)
              /* If there exists declarations all fields must have it */
              tmkLog(&tmkSeSt[tmkStkP+1].srcp, 65, sevERR, "srcp");
	  } else
            /* Source position must have at least one member */
            tmkLog(&tmkSeSt[tmkStkP+1].srcp, 66, sevERR, "");  
	}	break;}
    case 37: { /* srcp_header = '%%SRCP'; */

          tmkEnv->srcpNode = (SrcpNodeP) calloc(1,sizeof(SrcpNode));
          tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 40: { /* srcp_decl = 'NAME' identifier ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->srcpNode->name)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else
 	    tmkEnv->srcpNode->name = tmkSeSt[tmkStkP+2].sval;
		break;}
    case 41: { /* srcp_decl = 'ROW' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->srcpNode->row)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->srcpNode->row = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->srcpNode->rowDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 42: { /* srcp_decl = 'COLUMN' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->srcpNode->col)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->srcpNode->col = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->srcpNode->colDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 43: { /* srcp_decl = 'FILE' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->srcpNode->file)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->srcpNode->file = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->srcpNode->fileDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 44: { /* srcp_decl = 'POSITION' identifier optional_decl ';'; */

	  free(tmkSySt[tmkStkP+1].sval);
	  if (tmkEnv->srcpNode->pos)
	    tmkLog(&tmkSySt[tmkStkP+1].srcp, 61, sevERR, "");
	  else {
	    tmkEnv->srcpNode->pos = tmkSeSt[tmkStkP+2].sval;
	    tmkEnv->srcpNode->posDecl = tmkSeSt[tmkStkP+3].sval;
	  }
		break;}
    case 45: { /* skip_section = SKIPHEADER optional_end; */

      if (tmkEnv->fileType == TMK_FILE)
        tmkLog(&tmkSySt[tmkStkP+1].srcp, 51, sevERR, "");
    	break;}
    case 46: { /* identifier = IDENTIFIER; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
        	break;}
    case 47: { /* identifier = 'ATTRIBUTES'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 48: { /* identifier = 'NAME'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 49: { /* identifier = 'CODE'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 50: { /* identifier = 'SRCP'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 51: { /* identifier = 'ROW'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 52: { /* identifier = 'COLUMN'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 53: { /* identifier = 'FILE'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 54: { /* identifier = 'POSITION'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    case 55: { /* identifier = 'NO'; */

	  tmkSeSt[tmkStkP+1].sval = tmkSySt[tmkStkP+1].sval;
	  tmkSeSt[tmkStkP+1].srcp = tmkSySt[tmkStkP+1].srcp;
		break;}
    default: break; }
}/*tmkPaSema()*/

