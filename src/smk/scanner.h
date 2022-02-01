/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 *
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/scanner.h,v 1.1 2002/06/25 20:04:49 Thomas Nilsson Exp $
 *
 * $Log: scanner.h,v $
 * Revision 1.1  2002/06/25 20:04:49  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:18  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:12:35  tools
 * Totally rewritten to correctly handle vocabularies and rules.
 *
 */

#ifndef _scanner_h_
#define _scanner_h_

typedef struct Scanner *Scanner;

#include "tmkCommon.h"
#include "common.h"
#include "vocabulary.h"
#include "name.h"
#include "rule.h"
#include "nfas.h"
#include "dfa.h"

/*
 * UNIQUE KEY: name
 */

typedef struct Scanner {
  TmkSrcp srcp;           /* The scanner source position */
  Name name;              /* The scanner name */
  Vocabulary vocabulary;  /* The vocabulary which the scanner is defined in */
  Code code;              /* The global scanner number */
  Rule rules;             /* The scanners rules */
  NFAs nfa;               /* The NFA recognizing the scanners rules */
  DFA dfa;                /* The DFA recognizing the scanner rules */
  Scanner next;
} ScannerItem;

extern Scanner currentScanner;
extern Code scannerCodes;

extern Scanner scannerGet(Scanner  scanners, Name name);
extern Scanner scannerNew(Scanner* scanners, Name name);
extern void scannerCopy(Scanner to, Scanner from);
extern Bool scannerCheckRules(Scanner scanner);
extern void scannerCheckRedefinedPredefined(Scanner firstScanner, Scanner scanner);
extern void scannerDump(Scanner scanner);

#endif
