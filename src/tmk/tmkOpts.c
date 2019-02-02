/*------------------------------------------------------------------- */
/* TITLE                                                              */
/* ------                                                             */
/* tmkOpts.c                                                          */
/*                                                                    */
/* VERSION:   1.0                                                     */
/* ------------------------------------------------------------------ */
/*                                                                    */
/* REVISION DATA                                                      */
/* -------------                                                      */
/* CREATED:   92-04-30  Micael Dahlgren                               */
/* BASED ON:                                                          */
/* MODIFIED:                                                          */
/* ------------------------------------------------------------------ */
/*                                                                    */
/* DESCRIPTION                                                        */
/* -----------                                                        */
/* General option handler for the ToolMaker system                    */
/*                                                                    */
/* ------------------------------------------------------------------ */
/* IMPORT */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tmk.h"
#include "tmkList.h"
#include "version.h"

/* UNIT CONSTANTS */
#define BOOLNUM_FALSE 0x80000000
#define BOOLSTR_FALSE "__BOOLSTR_FALSE"
#define SET_EMPTY     0x0000
typedef enum MatchKind {
  MATCH_NOT,
  MATCH_PREFIX,
  MATCH_EXACT
} MatchKind;

/* UNIT TYPES */
typedef struct OptDbRec {
  TmoKind dirKind;		/* Kind of option */
  Boolean assigned;		/* Has an assignment been made */
  Boolean cliass;		/* Has an assignment been made on cli */
  union {
    int ival;		    /* Value of number option */
    char *sval;			/* Value of string option */
    Boolean bval;		/* Value of boolean option */
    unsigned setval;		/* Value of set option */
    unsigned eval;		/* Value of enum option */
  } oval;
} OptDbRec;

/* UNIT DATA */
static int locOptTabLast = 0;	/* Size of option sem table -1 */
static OptTabRec *locOptTab;	/* Pointer to option sem table */
static OptDbRec *optDb;		/* Pointer to option database */
static char *thisprg = NULL;	/* This program (argv[0]) */
static char *helpopt = NULL;    /* Name of help option (or NULL) */

/* UNIT FUNCTIONS */
#define lwr(c) (isupper(c) ? tolower(c) : c)

/*----------------------------------------------------------------------
    perr

    print error message and exit

*/
static void perr(errmsg, arg)
  char *errmsg;			/* IN error message text */
  char *arg;			/* IN error message argument */
{
  fprintf(stderr, "%s: %s %s\n", thisprg, errmsg, arg);
  exit(2);
}

/*----------------------------------------------------------------------
    pusage

    print usage message

*/
static void pusage()
{
  if (helpopt)
    fprintf(stderr, "Usage: %s [-%s] [options] <input file>\n", thisprg, helpopt);
  else
    fprintf(stderr, "Usage: %s [options] <input file>\n", thisprg);
}

/*----------------------------------------------------------------------
    phelp

    print help information

*/
void phelp(optTab)
  OptTabRec *optTab;		/* IN table with allowed options */
{
  char tempstr[256];
  int i;

  fprintf(stderr, "%s\n\n", product.longHeader);
  pusage();
  fprintf(stderr, "Options:\n");

  /* go through options */
  for (i = 0; optTab[i].optTabKind != locOptTabLast; i++) {
    if (optTab[i].cliName && strcmp(optTab[i].cliName, "") != 0) {
      strcpy(tempstr, "-");
      if (optTab[i].dirKind == BOOL_TMO ||
          optTab[i].dirKind == BOOLNUM_TMO ||
          optTab[i].dirKind == BOOLSTR_TMO ||
          optTab[i].dirKind == SET_TMO)
        strcat(tempstr, "[-]");
      strcat(tempstr, optTab[i].cliName);
      fprintf(stderr, "  %-17s %s\n", tempstr, optTab[i].optHelp);
    }
  }

  exit(0);
}

/*----------------------------------------------------------------------
    isOpt

    check if argv item is option

*/
static Boolean isOpt(argin, argout, bval)
  char *argin;
  char **argout;
  Boolean *bval;
{
  *argout = argin;
  *bval = TRUE;
  if (**argout != '-') return FALSE;
  if (*++(*argout) == '-') {
    *bval = FALSE;
    (*argout)++;
  }
  return (**argout != '\0');
}

/*----------------------------------------------------------------------
    strmatch

    match strings (ignore case)

*/
static MatchKind strmatch(s1, s2)
  char *s1;			/* IN tab string */
  char *s2;			/* IN string to be checked */
                /* RETURN MATCH_EXACT if exact match,
                                 *        MATCH_PREFIX if only prefix match
                                 *    and MATCH_NOT if no match */
{
  while (*s2) {
    if (*s1 <= ' ' || lwr(*s1) != lwr(*s2))
      return MATCH_NOT;
    s1++; s2++;
  }
  return (*s1 <= ' ' ? MATCH_EXACT : MATCH_PREFIX);
}

/*----------------------------------------------------------------------
    dirmatch

    checks if options in table and directive matches

*/
static Boolean dirmatch(tabopt, diropt)
  TmoKind tabopt;		/* IN directive in table */
  TmoKind diropt;		/* IN directive in option */
                /* RETURN TRUE if directives matches */
{
  return ((tabopt == diropt) ||
      (tabopt == ENUM_TMO && diropt == SET_TMO) ||
      (tabopt == SET_TMO && diropt == BOOL_TMO) ||
      (tabopt == BOOLNUM_TMO && diropt == BOOL_TMO) ||
      (tabopt == BOOLNUM_TMO && diropt == NUM_TMO) ||
      (tabopt == BOOLSTR_TMO && diropt == BOOL_TMO) ||
      (tabopt == BOOLSTR_TMO && diropt == STR_TMO));
}

/*----------------------------------------------------------------------
    calcSet

    calculate set value

*/
static Boolean calcSet(diritem, tabitems, setval)
  char *diritem;		/* IN itemvalue in directive */
  char *tabitems[];		/* IN allowed setitems */
  unsigned *setval;		/* OUT calculated set value */
                /* RETURN TRUE if allowed setitem */
{
  int i;

  for (i = 0; tabitems[i]; i++)
    if (strmatch(tabitems[i], diritem) == MATCH_EXACT) {
      *setval |= (1 << i);
      return TRUE;
    }
  return FALSE;
}

/*----------------------------------------------------------------------
    calcEnum

    calculate enum value

*/
static Boolean calcEnum(diritem, tabitems, enumval)
  char *diritem;		/* IN itemvalue in directive */
  char *tabitems[];		/* IN allowed enum items */
  unsigned *enumval;		/* OUT calculated enum value */
                /* RETURN TRUE if allowed setitem */
{
  int i;

  for (i = 0; tabitems[i]; i++)
    if (strmatch(tabitems[i], diritem) == MATCH_EXACT) {
      *enumval = i;
      return TRUE;
    }
  return FALSE;
}

/*======================================================================
    initOpts()

    intitalization of option database

*/
void initOpts(optTabLast, optTab)
  int optTabLast;		/* IN position of last option in table */
  OptTabRec *optTab;		/* IN table with allowed options */
{
  int i;

  /* save sem table references */
  locOptTabLast = optTabLast;
  locOptTab = optTab;

  /* create option database */
  optDb	= (OptDbRec *) malloc(sizeof(OptDbRec) * (optTabLast + 1));

  /* reset option database */
  for (i = 0; i < locOptTabLast; i++) {
    optDb[i].dirKind = NOTUSED_TMO;
    optDb[i].assigned = FALSE;
    optDb[i].cliass = FALSE;
  }

  /* initialize option database and find help option */
  for (i = 0; optTab[i].optTabKind != locOptTabLast; i++) {
    /* store option kind */
    optDb[optTab[i].optTabKind].dirKind = optTab[i].dirKind;

    if (optTab[i].dirKind == HELP_TMO)
      helpopt = optTab[i].cliName;
    else {
      /* initialize option value with default value
         the integer structure variant can be used because all variants
         have the same size */
      optDb[optTab[i].optTabKind].oval.ival = optTab[i].defval;
    }
  }
}

/*----------------------------------------------------------------------

    checkOptRedef()

    Check the list of options stored in dirNode for options that are
    defined more than once. For every such option, issue a warning.

*/

static void checkOptRedef(dirNode)
  TmoNodeP dirNode;		/* IN list with directive nodes */
{
  TmoNodeP p;			/* Used to search to end of list */
  Boolean foundRedef;		/* Found a redefinition */

  /* Go through the entire option list. */
  while (dirNode) {
    /* Search from current position in option list to end or until
       the first redefinition of the current option is found.
       */
    p = dirNode->next;
    foundRedef = FALSE;
    while (p && !foundRedef) {
      if (strmatch(dirNode->name, p->name) == MATCH_EXACT) {
    /* Redefinition was found. Issue warning. */
    /* WARNING: Option redefined, old option skipped. */
    tmkLog(&p->srcp, 67, sevWAR, "");
    foundRedef = TRUE;
      }
      else p = p->next;
    }
    dirNode = dirNode->next;
  }
}

/*======================================================================
    setOpts()

    set options according to option section in file

*/
void setOpts(optTab, dirNode)
  OptTabRec *optTab;		/* IN table with allowed options */
  TmoNodeP dirNode;		/* IN list with directive nodes */
{
  int i;
  OptNodeP p;
  Boolean oldAss;

  /* Check for options that are defined more than once. */
  checkOptRedef(dirNode);

  /* go through options found in description file */
  for (; dirNode; dirNode = dirNode->next) {
    /* search for option in table */
    for (i = 0; optTab[i].optTabKind != locOptTabLast; i++) {
      if (strmatch(optTab[i].optName, dirNode->name) == MATCH_EXACT &&
      dirmatch(optTab[i].dirKind, dirNode->dirKind)) {

    switch (optTab[i].dirKind) {
    case BOOL_TMO:
    case STR_TMO:
      optDb[optTab[i].optTabKind].assigned = TRUE;
      optDb[optTab[i].optTabKind].oval.bval = dirNode->oval.bval;
      break;

    case NUM_TMO:
      /* check value against max/min */
      if (dirNode->oval.ival >= optTab[i].irange.mini &&
          dirNode->oval.ival <= optTab[i].irange.maxi) {
        optDb[optTab[i].optTabKind].assigned = TRUE;
        optDb[optTab[i].optTabKind].oval.ival = dirNode->oval.ival;
      } else
        tmkLog(&dirNode->srcp, 50, sevWAR, "");
      break;

    case SET_TMO:
      if (dirNode->dirKind == BOOL_TMO) {
        optDb[optTab[i].optTabKind].oval.setval =
          (dirNode->oval.bval ? optTab[i].defval : SET_EMPTY);
        optDb[optTab[i].optTabKind].assigned = TRUE;
      } else {
        optDb[optTab[i].optTabKind].oval.setval = SET_EMPTY;
        oldAss = optDb[optTab[i].optTabKind].assigned;
        optDb[optTab[i].optTabKind].assigned = TRUE;
        for (p = dirNode->oval.opts; p; p = p->next)
          if (!calcSet(p->name, optTab[i].sitems,
              &optDb[optTab[i].optTabKind].oval.setval)) {
        tmkLog(&dirNode->srcp, 50, sevWAR, "");
        optDb[optTab[i].optTabKind].assigned = oldAss;
          }
      }
      break;

    case ENUM_TMO:
      if (dirNode->oval.opts->next != NULL)
        tmkLog(&dirNode->srcp, 50, sevWAR, "");
      else
        if (!calcEnum(dirNode->oval.opts->name, optTab[i].sitems,
             &optDb[optTab[i].optTabKind].oval.setval))
          tmkLog(&dirNode->srcp, 50, sevWAR, "");
        else
          optDb[optTab[i].optTabKind].assigned = TRUE;
      break;

    case BOOLNUM_TMO:
      if (dirNode->dirKind == BOOL_TMO) {
        optDb[optTab[i].optTabKind].assigned = TRUE;
        optDb[optTab[i].optTabKind].oval.ival =
          (dirNode->oval.bval ? optTab[i].defval : BOOLNUM_FALSE);
      } else
        /* check value against max/min */
        if (dirNode->oval.ival >= optTab[i].irange.mini &&
        dirNode->oval.ival <= optTab[i].irange.maxi) {
          optDb[optTab[i].optTabKind].assigned = TRUE;
          optDb[optTab[i].optTabKind].oval.ival = dirNode->oval.ival;
        } else
          tmkLog(&dirNode->srcp, 50, sevWAR, "");
      break;

    case BOOLSTR_TMO:
      if (dirNode->dirKind == BOOL_TMO) {
        optDb[optTab[i].optTabKind].assigned = TRUE;
        optDb[optTab[i].optTabKind].oval.sval =
          (dirNode->oval.bval ? (char *) optTab[i].defval : BOOLSTR_FALSE);
      } else {
        optDb[optTab[i].optTabKind].assigned = TRUE;
        optDb[optTab[i].optTabKind].oval.sval = dirNode->oval.sval;
      }
      break;

    default:;
    }

    break;
      }
    }

    /* report error if this option is not found */
    if (optTab[i].optTabKind == locOptTabLast)
      tmkLog(&dirNode->srcp, 50, sevWAR, "");
  }
}

/*======================================================================
    setCliOpts()

    set options according to command line

*/
void setCliOpts(optTab, argc, argv, argout)
  OptTabRec *optTab;		/* IN table with allowed options */
  int argc;			/* IN argument counter */
  char *argv[];			/* IN argument vector */
  char **argout;		/* OUT file argument */
{
  Boolean bval = TRUE, errOpt = FALSE;
  int ival;
  int i,j;
  char *arg;
  int noOfHits, pos;
  MatchKind mk;

  /* initialize */
  thisprg = argv[0];
  *argout = NULL;
  for (i = 0; i < locOptTabLast; i++)
    optDb[i].cliass = FALSE;

  /* go through options found in command line */
  for (j = 1; j < argc; j++) {
    if (isOpt(argv[j], &arg, &bval)) {
      /* search for option in table */
      noOfHits = 0;
      for (i = 0; optTab[i].optTabKind != locOptTabLast; i++) {
    if ((mk = strmatch(optTab[i].cliName, arg)) == MATCH_EXACT) {
      noOfHits = 1;
      pos = i;
      break;
        } else if (mk == MATCH_PREFIX) {
      noOfHits++;
      pos = i;
    }
      }

      /* report error if this option is not found or found
         more than once */
      switch (noOfHits) {
      case 0:
    perr("incorrect option:", arg);
      case 1:
    break;
      default:
    perr("ambigious option:", arg);
      }

      /* interpret option and set value */
      if (!bval && (optTab[pos].dirKind == STR_TMO ||
            optTab[pos].dirKind == NUM_TMO ||
            optTab[pos].dirKind == ENUM_TMO)) {
    perr("not allowed to turn off option:", arg);
      } else {
    /* check option with argument */
    if (optTab[pos].dirKind != BOOL_TMO &&
        optTab[pos].dirKind != HELP_TMO && bval)
      if (++j >= argc)
        perr("missing value for option:", arg);

    switch (optTab[pos].dirKind) {
    case BOOL_TMO:
      optDb[optTab[pos].optTabKind].oval.bval = bval;
      optDb[optTab[pos].optTabKind].assigned = TRUE;
      break;

    case STR_TMO:
      optDb[optTab[pos].optTabKind].oval.sval = argv[j];
      optDb[optTab[pos].optTabKind].assigned = TRUE;
      break;

    case NUM_TMO:
      if (sscanf(argv[j], "%i", &ival) != 1) {
        perr("incorrect numeric value:", argv[j]);

      } else {
        /* check value against max/min */
        if (ival >= optTab[pos].irange.mini &&
        ival <= optTab[pos].irange.maxi) {
          optDb[optTab[pos].optTabKind].assigned = TRUE;
          optDb[optTab[pos].optTabKind].oval.ival = ival;
        } else
          perr("incorrect numeric value:", argv[j]);
      }
      break;

    case SET_TMO:
      if (bval == FALSE) {
        optDb[optTab[pos].optTabKind].assigned = TRUE;
        optDb[optTab[pos].optTabKind].oval.setval = SET_EMPTY;
      } else {
        /* the first time a set option appears on cli,
           it's value will be reset */
        if (!optDb[optTab[pos].optTabKind].cliass)
          optDb[optTab[pos].optTabKind].oval.setval = SET_EMPTY;
        if (!calcSet(argv[j], optTab[pos].sitems,
             &optDb[optTab[pos].optTabKind].oval.setval))
          perr("incorrect set value:", argv[j]);
        else
          optDb[optTab[pos].optTabKind].assigned = TRUE;
      }
      break;

    case ENUM_TMO:
      if (!calcEnum(argv[j], optTab[pos].sitems,
            &optDb[optTab[pos].optTabKind].oval.eval))
        perr("incorrect enum value:", argv[j]);
      else
        optDb[optTab[pos].optTabKind].assigned = TRUE;
      break;

    case BOOLNUM_TMO:
      if (bval == FALSE) {
        optDb[optTab[pos].optTabKind].assigned = TRUE;
        optDb[optTab[pos].optTabKind].oval.ival = BOOLNUM_FALSE;
      } else {
        if (sscanf(argv[j], "%i", &ival) != 1) {
          perr("incorrect numeric value:", argv[j]);

        } else {
          /* check value against max/min */
          if (ival >= optTab[pos].irange.mini &&
          ival <= optTab[pos].irange.maxi) {
        optDb[optTab[pos].optTabKind].assigned = TRUE;
        optDb[optTab[pos].optTabKind].oval.ival = ival;
          } else
        perr("incorrect numeric value:", argv[j]);
        }
      }
      break;

    case BOOLSTR_TMO:
      optDb[optTab[pos].optTabKind].assigned = TRUE;
      optDb[optTab[pos].optTabKind].oval.sval =
        (bval ? argv[j] : BOOLSTR_FALSE);
      break;

    case HELP_TMO:
      phelp(optTab);
      break;
    }
      }

      /* indicate that this option has been assigned on cli */
      optDb[optTab[pos].optTabKind].cliass = TRUE;
    } else {
      /* argument */
      if (*argout)
    perr("non-matching argument:", argv[j]);
      else
    *argout = argv[j];
    }
  }

  /* print usage message if no arguments */
  if (*argout == NULL) {
    pusage();
    exit(0);
  }
}

/*======================================================================
    getBoolOpt()

    get value of boolean option

*/
Boolean getBoolOpt(opt)
  int opt;			/* IN option */
                /* RETURN option value */
{
  if (opt <= locOptTabLast) {
    switch (optDb[opt].dirKind) {
    case BOOL_TMO:
      return (optDb[opt].oval.bval);
    case BOOLSTR_TMO:
      return (strcmp(optDb[opt].oval.sval, BOOLSTR_FALSE) != 0);
    case BOOLNUM_TMO:
      return (optDb[opt].oval.ival != BOOLNUM_FALSE);
    default:
      ;
    }
  }
  /* error */;
}

/*======================================================================
    getNumOpt()

    get value of numeric option

*/
int getNumOpt(opt)
  int opt;			/* IN option */
                /* RETURN option value */

{
  if (opt <= locOptTabLast) {
    switch (optDb[opt].dirKind) {
    case NUM_TMO:
    case ENUM_TMO:
    case BOOLNUM_TMO:
      return optDb[opt].oval.ival;
    default:
      ;
    }
  }
  /* error */;
}

/*======================================================================
    getStrOpt()

    get value of string option

*/
char *getStrOpt(opt)
  int opt;			/* IN option */
                /* RETURN option value */

{
  if (opt <= locOptTabLast) {
    switch (optDb[opt].dirKind) {
    case STR_TMO:
    case BOOLSTR_TMO:
      return optDb[opt].oval.sval;
    default:
      ;
    }
  }
  /* error */;
}

/*======================================================================
    getSetOpt()

    get value of set option

*/
unsigned getSetOpt(opt)
  int opt;			/* IN option */
                /* RETURN option value */

{
  if (opt <= locOptTabLast && optDb[opt].dirKind == SET_TMO)
      return optDb[opt].oval.setval;
  /* error */;
}

/*======================================================================
    optAssigned()

    Has this option been assigned a value ?

*/
Boolean optAssigned(opt)
  int opt;			/* IN option */
                /* RETURN TRUE if option assigned */

{
  if (opt <= locOptTabLast)
    return optDb[opt].assigned;
  else
    /* error */
    return FALSE;
}

/*======================================================================
    printDb()

    print option database (debug)

*/
unsigned printDb(optTab, outfile)
  OptTabRec *optTab;		/* IN table with allowed options */
  FILE *outfile;		/* OUT output file */
{
  int i;

  /* print database */
  for (i = 0; optTab[i].optTabKind != locOptTabLast; i++) {
    if (strcmp(optTab[i].optName, "") != 0)
      fprintf(outfile, "%-20s", optTab[i].optName);
    else
      fprintf(outfile, "%-20s", optTab[i].cliName);

    switch (optDb[optTab[i].optTabKind].dirKind) {
    case BOOL_TMO:
      fprintf(outfile, "%i\n", optDb[optTab[i].optTabKind].oval.bval);
      break;
    case STR_TMO:
    case BOOLSTR_TMO:
      fprintf(outfile, "%s\n", optDb[optTab[i].optTabKind].oval.sval);
      break;
    case NUM_TMO:
    case ENUM_TMO:
    case BOOLNUM_TMO:
      fprintf(outfile, "%i\n", optDb[optTab[i].optTabKind].oval.ival);
      break;
    case SET_TMO:
      fprintf(outfile, "%u\n", optDb[optTab[i].optTabKind].oval.setval);
      break;
    case HELP_TMO:
      fprintf(outfile, "\n");
      break;
    default:
      ;
    }
  }
}

/*======================================================================
    mergeOptions()

    merge a local and a global option

*/
void mergeOptions(locOpt, globOpt, tmkExists)
  int locOpt;			/* IN local option */
  int globOpt;			/* IN global option */
  Boolean tmkExists;		/* IN tmk file exists */
{
  if (tmkExists) {
    if (!optAssigned(locOpt) &&	optAssigned(globOpt)) {
      switch (optDb[locOpt].dirKind) {
      case STR_TMO:
      case BOOLSTR_TMO:
    optDb[locOpt].oval.sval = getStrOpt(globOpt);
    break;
      case BOOL_TMO:
    optDb[locOpt].oval.bval = getBoolOpt(globOpt);
    break;
      case NUM_TMO:
      case ENUM_TMO:
      case BOOLNUM_TMO:
    optDb[locOpt].oval.ival = getNumOpt(globOpt);
    break;
      case SET_TMO:
    optDb[locOpt].oval.setval = getSetOpt(globOpt);
    break;
      }
    }
  } else {
    switch (optDb[globOpt].dirKind) {
    case STR_TMO:
    case BOOLSTR_TMO:
      optDb[globOpt].oval.sval = getStrOpt(locOpt);
      break;
    case BOOL_TMO:
      optDb[globOpt].oval.bval = getBoolOpt(locOpt);
      break;
    case NUM_TMO:
    case ENUM_TMO:
    case BOOLNUM_TMO:
      optDb[globOpt].oval.ival = getNumOpt(locOpt);
      break;
    case SET_TMO:
      optDb[globOpt].oval.setval = getSetOpt(locOpt);
      break;
    }
  }
}
