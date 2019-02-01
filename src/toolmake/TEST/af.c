/* af.c			Date: 1997-01-20/toolmake

   af -- main program

   1.0 - 1997-01-20/
*/

#include <stdio.h>

#define PRIVATE static
#define PUBLIC


#include "afParse.h"
#include "afList.h"
#include "afScan.h"


char *VERSION= "1.0";
char *NAME   = "af";
char *USAGE= "Usage: af [-h] [-l <name>] <in> [<out>]";



/* -- DATA -- */

PRIVATE char 
    *listFileName= NULL,
    *inFileName= NULL,
    *outFileName= NULL;


/* -- SUBROUTINES -- */

/*----------------------------------------------------------------------
	perr()

	A simple writer of error messages (onto stderr),
	If 'addendum' is NULL it will not be written.
*/
PUBLIC void perr(
    char sev,
    char *desc,
    char *add
)
{
    if (add==NULL)
	fprintf(stderr, "%s: %c! %s\n", NAME, sev, desc);
    else
	fprintf(stderr, "%s: %c! %s: %s\n", NAME, sev, desc, add);

    if (sev=='F' || sev=='S') exit(1);
}


/* -- Argument processing -- */

PRIVATE void processArgs(
    int argc,
    char *argv[]
)
{				/* Go thru arguments, try to act on options */
    int i; 
 
    for (i=1; i<argc; ++i) {
        if (argv[i][0]=='-' && argv[i][1]) {
            switch (argv[i][1]) {
	    case 'l':
		listFileName= argv[++i];
		break;
	    case 'h':
		printf("%s\n\n", USAGE);
		printf("Options:\n");
		printf("  -l <name>  Set list file name\n");
		exit(0);
	    default:
		perr('W', "unknown switch", argv[i]);
		break;
	    }
	}
    	else if (inFileName==NULL) inFileName= argv[i];
    	else if (outFileName==NULL) outFileName= argv[i];
    	else perr('W', "unknown argument", argv[i]);
    }
}


/* -- MAIN -- */

PUBLIC main(
    int argc,
    char *argv[]
)
{
    int stdIn;    

    processArgs(argc, argv);
    printf("%s - %s\n\n", NAME, VERSION);

    if (inFileName == NULL)
        perr('F', "No input file", NULL);

    stdIn= strcmp(inFileName,"-")==0;
    if (stdIn)
	afLiInit(VERSION, "standard input",  af_ENGLISH_Messages);
    else
	afLiInit(VERSION, inFileName,  af_ENGLISH_Messages);
    lexContext = afScNew(af_MAIN_MAIN_Scanner);
    if ((lexContext->fd = open(inFileName, 0)) < 0) {
        afLog(NULL, 199, sevFAT, inFileName);
	afList("", 0, 78, liTINY, sevALL);
    } else {
	lexContext->fileName = inFileName;
	afParse();
	close(lexContext->fd);
        if (stdIn) {		/* This gives an idea of own processing of
				   error messages */
	    int i;
	    char err[1024];
	    TmSrcp srcp;

	    /* Print a list on the terminal if errors detected. */
	    for (i=1; afMsg(i, &srcp, err); i++)
		printf("\"-\", line %d: %s (column %d)\n",
		       srcp.line, err, srcp.col);
	} else {
	    /* Print a TINY list on the terminal */
	    afList("", 0, 78, liTINY, sevALL);
	    /* And a list file if asked to. */
	    if (!stdIn && listFileName != NULL) {
		afList(listFileName, 60, 132, liFULL, sevALL);
            }
	}
    }
    afLiTerminate();
}
