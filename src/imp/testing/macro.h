#ifndef _MACRO_H
#define _MACRO_H

/*
 * MACRO.H
 */

/* Exported routines.
 */
extern void MaPopFile();
extern void MaResFile();

/* The output file.
 */
extern FILE *OutFile;

/* The input file name and number.
 */
extern char *InFileName;
extern int InFileNo, InFileInd;

/* Stack limits, Flag stack, Symbol stack, Output File stack and Input
 * File Name stack.
 */
#define FSTMX 100
#define SSTMX 10
#define OSTMX 10
#define ISTMX 10

/* Flag values.
 */
#define False 0
#define True 1
#define Undef 2
#define MatchAll 3

/* Flag type.
 */
typedef int MaBoolean;

/* Flags.
 */
extern MaBoolean CopyFlag;	/* Used to control the scanner (scancopy). */
extern MaBoolean OutFlag;	/* Controls the output, set by SetOutFlag. */
extern MaBoolean OutFileFlag;	/* True if there is an output file. */
extern MaBoolean KeepFlag;	/* True if we are within a KEEP statement. */
extern MaBoolean IfFlag;	/* Used to control output during IFs. */
extern MaBoolean CommFlag;	/* True within a comment. */
extern MaBoolean ProcFlag;	/* True if a PROCESS statement is active. */
extern MaBoolean IncFlag;	/* True if processing an INCLUDE(label). */
extern MaBoolean MaEof;		/* Set at end of a processed file, used to */
				/* control the switching of output files. */
extern MaBoolean LastPass;	/* True if this pass is the last macro */
				/* pass. Used to control output of certain */
				/* warning messages. */

/* SETOUTFLAG
 *
 * Sets the OutFlag to reflect the different output conditions.
 */
#define SetOutFlag() OutFlag = \
    (OutFileFlag && (KeepFlag || (IfFlag && !CommFlag)))

/* OUT
 *
 * Write a string to the outfile if OutFlag permits it.
 */
#define out(str) if (OutFlag) fprintf(OutFile, "%s", str)

#endif
