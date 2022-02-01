#ifndef _impMacro
#define _impMacro
/*----------------------------------------------------------------------*\

  impMacro.h

  Exported definitions for external call to the IMP proper.


\*---------------------------------------------------------------------- */
#include <stdio.h>
#include <setjmp.h>

extern jmp_buf jmpEnv;
extern jmp_buf jmpExit;

/* Exported routines, C++ needs to be first, some compilers also
   defines __STDC__! */

#if defined(__cplusplus)
extern "C" {
    extern int impSetVar(
        char *str       /* IN variable string, format "Var(val, ...)"*/
        );              /* RET non-zero if syntax/memory error */
}

extern "C" {
    extern int impMacro(
        char *inName,   /* IN input file name */
        char *outName,  /* IN output file name or empty */
        char *msgName,  /* IN file name for imp message file */
        long flags,     /* IN the various flag values */
        int listType,   /* IN type of list or zero */
        char escChar,   /* IN escape character */
        int *exitCode   /* OUT exit code from %%EXIT(), 0 if not */
        );              /* RET imp's severity code */
}

#else
#if defined(__STDC__)

extern int impSetVar(
    char *str           /* IN variable string, format "Var(val, ...)"*/
);                      /* RET non-zero if syntax/memory error */

extern int impMacro(
    char *inName,       /* IN input file name */
    char *outName,      /* IN output file name or empty */
    char *msgName,      /* IN file name for imp message file */
    long flags,         /* IN the various flag values */
    int listType,       /* IN type of list or zero */
    int escChar,        /* IN escape character */
    int *exitCode       /* OUT exit code from %%EXIT(), 0 if not */
);                      /* RET imp's severity code */

#else
extern int impSetVar();
extern int impMacro();
#endif
#endif

/* Bit field values for "flags" parameter in impMacro */
#define verbBit (1 << 0)
#define intBit (1 << 1)
#define envBit (1 << 2)
#define covBit (1 << 3)

/* The return code from %%EXIT */
extern int impExitCode;

/* The escape character */
extern char impEsc;

/* The input file name and number. */
extern int impFileNo;

/* Stack limits, Flag stack, Symbol stack, Output File stack and Input
 * File Name stack.
 */
#define FSTMX 100
#define SSTMX 10
#define OSTMX 10
#define ISTMX 10

/* Flag type */
typedef int ImpBoolean;

/* Flags */
extern ImpBoolean impLastPass;  /* True if this pass is the last macro */
                                /* pass. Used to control output of certain */
                                /* warning messages. Partial evaluation */
                                /* is used iff impLastPass == FALSE */
extern ImpBoolean impUseEnv;    /* True if environment variables should be */
                                /* looked up. */
extern ImpBoolean impCodeCov;   /* True if code coverage should be reported */

/* Code coverage file */
extern FILE *impCcFile;
#endif
