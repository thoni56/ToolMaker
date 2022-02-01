/*-----------------------------------------------------------------------------
 * imp - Macro processor main program.
 * @(#)imp.c    1.3 (91/11/25 17:18:33)
 *-----------------------------------------------------------------------------
 * Created:     87-11-10 by Tom
 * Modified:    89-09-28 by Tom. Moved to Sun and Sws2.
 *              89-10-25 by Tom. Option -s introduced.
 *              89-11-21 by Tom. Renamed to IMP.
 *              90-03-14 by Tom. Interface to impMacro changed, environment
 *                               option introduced.
 *              91-04-09 by Tom. Extension ".skl" changed to ".imp".
 *              1991-11-25/reibert@roo impMacro extended with msgName
 *-----------------------------------------------------------------------------
 * Entries:
 *      main
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "impMacro.h"
#include "impList.h"
#include "version.h"

#define USAGE "Usage: imp [-h] [options] <input file> [<output file>]\n"

#ifdef vms
#define HOME "dua1:[root.ToolMaker]"
#else
#define HOME "/usr/local/ToolMaker"
#endif

#define optErr(str) fprintf(stderr,\
"Unknown option: \"%s\". imp -h for list of options\n", str)

/*-----------------------------------------------------------------------------
 * main
 *-----------------------------------------------------------------------------
 */
int main(argc, argv)
int argc;       /* IN argument count. */
char *argv[];   /* IN program arguments. */
{
    short i, start, len;
    impTyp listType = 0;
    ImpBoolean optOn;
    long flags = 0;
    char *inName = NULL, *outName = NULL;
    char escChar = '`';
    int retValue;
    int ecode;

/*  If you want to use malloc_debug link with /usr/lib/debug/malloc.o */
/*  malloc_debug(2); */

#ifdef WIN32
#ifdef TMTEST
    freopen("stderr.txt", "w", stderr);
#else
    /* 4f - redirect to stderr to stdout */
#endif
#endif

    /* Get arguments.
     */
    flags |= envBit;
    for (i = 1; i < argc; i++) {
        len = strlen(argv[i]);
        if (argv[i][0] == '-') {
            start = 1;
            len--;
            optOn = !(argv[i][1] == '-');
            if (!optOn) {
                start++;
                len--;
            }/*if*/

            if (isupper(argv[i][start])) {
                argv[i][start] = tolower(argv[i][start]);
            }/*if*/

            switch(argv[i][start]) {

            case 'l':
                if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                }/*if*/
                if (optOn) listType = liFULL;
                else listType = 0;
                break;

            case 'c':
                if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                }/*if*/
                if (optOn) flags |= covBit;
                else flags &= ~covBit;
                break;

            case 'i':
                if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                }/*if*/
                if (optOn) flags |= intBit;
                else flags &= ~intBit;
                break;

            case 'u':
                if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                }/*if*/
                if (optOn) flags |= envBit;
                else flags &= ~envBit;
                break;

            case 'v':
                if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                }/*if*/
                if (optOn) flags |= verbBit;
                else flags &= ~verbBit;
                break;

            case 'e':
                if (optOn) {
                    if (len < 2) {
                        fprintf(stderr,
                                "No escape character given to -e option\n");
                        return 1;
                    } else if (len > 2) {
                        fprintf(stderr, "Illegal escape character: \"%s\"\n",
                                &argv[i][start + 1]);
                        return 1;
                    } else {
                        escChar = argv[i][start + 1];
                    }/*if*/
                } else if (len != 1) {
                    optErr(argv[i]);
                    return 1;
                } else {
                    escChar = '`';
                }/*if*/
                break;

            case 's':
                if (optOn) {
                  int result;
                    if ((result = impSetVar(&argv[i][start + 1])) > 0) {
                        fprintf(stderr, "Variable syntax error: \"%s\"\n",
                                &argv[i][start + 1]);
                        return 1;
                      } else if (result < 0){
                        fprintf(stderr, "Unable to allocate memory\n");
                        return 1;
                    } /*if*/
                } else {
                    optErr(argv[i]);
                    return 1;
                } /*if*/
                break;

            case 'h':
                if (optOn) {
                    fprintf(stderr, "%s\n", product.longHeader);
                    fprintf(stderr, "\n%s", USAGE);
                    fprintf(stderr, "\nArguments:\n");
                    fprintf(stderr,
"<input file>      input file to process (default \".imp\" extension)\n");
                    fprintf(stderr,
"<output file>     output file (default terminal)\n");
                    fprintf(stderr, "\nOptions:\n");
                    fprintf(stderr,
"-h                show this information\n");
                    fprintf(stderr,
"-[-]l             enable[disable] listing to file\n");
                    fprintf(stderr,
"-[-]i             enable[disable] intermediate pass\n");
                    fprintf(stderr,
"-[-]u             enable[disable] use of environment variables\n");
                    fprintf(stderr,
"-[-]v             enable[disable] timing figures\n");
                    fprintf(stderr,
"-[-]c             enable[disable] code coverage messages\n");
                    fprintf(stderr,
"-ec               set escape character to 'c'\n");
                    fprintf(stderr,
"--e               set the default escape character '`'\n");
                    fprintf(stderr,
"-sVar(Val{,Val})  set the variable \"Var\" to \"Val{,Val}\"\n");
                    return 1;
                }/*if*/
                break;

            default:
                optErr(argv[i]);
                return 1;
            }/*switch*/
        } else if (inName == NULL) {
            inName = argv[i];
        } else if (outName == NULL) {
            outName = argv[i];
        } else {
            fprintf(stderr, USAGE);
            return 1;
        }/*if*/
    }/*for*/

    if (inName == NULL) {
        fprintf(stderr, USAGE);
        return 1;
    }/*if*/

    if (flags & verbBit) printf("%s\n", product.longHeader);

    retValue = impMacro(inName, outName, "", flags, listType, escChar, &ecode);
    if (ecode != 0)
      fprintf(stderr, "  Result from evaluation of %%%%EXIT was %d\n", ecode);

    return (retValue & (sevERR | sevFAT | sevSYS));
}/*main()*/
