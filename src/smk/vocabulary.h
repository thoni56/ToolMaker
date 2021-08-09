/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 *
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/vocabulary.h,v 1.1 2002/06/25 20:05:04 Thomas Nilsson Exp $
 *
 * $Log: vocabulary.h,v $
 * Revision 1.1  2002/06/25 20:05:04  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:34:05  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/27  14:22:21  tools
 * scannerPrefix changed to smkPrefix.
 * Port of ScannerMaker to ANSI-C started.
 *
 * Revision 1.1  1993/04/23  10:34:36  tools
 * Initial revision.
 *
 */

#ifndef _vocabulary_h_
#define _vocabulary_h_

typedef struct Vocabulary *Vocabulary;

#include "common.h"
#include "tmkCommon.h"
#include "name.h"
#include "token.h"
#include "scanner.h"

/*
 * UNIQUE KEY: name
 */

typedef struct Vocabulary {
  TmkSrcp srcp;
  Name name;            /* The vocabulary name */
  Bool external;        /* Vocabulary defined in vocabulary file */
  Token tokens;         /* The tokens in the vocabulary */
  Scanner scanners;     /* The scanners in the vocabulary */
  Vocabulary next;
} VocabularyItem;

extern Vocabulary vocabularies;
extern Vocabulary currentVocabulary;

extern Vocabulary vocabularyGet(Vocabulary  vocabulary, Name name);
extern Vocabulary vocabularyNew(Vocabulary* vocabulary, Name name);
extern Bool vocabularyCheckTokens(Vocabulary vocabulary);
extern void vocabularyRead(Name file);
extern void vocabularyDump(Vocabulary vocabulary);
extern void vocabularyPrint();

#endif
