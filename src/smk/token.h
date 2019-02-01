/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 * 
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/token.h,v 1.1 2002/06/25 20:05:02 Thomas Nilsson Exp $
 *
 * $Log: token.h,v $
 * Revision 1.1  2002/06/25 20:05:02  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:55  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:22:10  tools
 * Completely rewritten, replaces old voc.h.
 *
 */

#ifndef _token_h_
#define _token_h_

typedef struct Token *Token;

#include "tmkCommon.h"
#include "vocabulary.h"
#include "common.h"
#include "name.h"

/*
 * UNIQUE KEY: name
 * UNIQUE KEY: code
 */

typedef struct Token {
  TmkSrcp srcp;			/* The token source position */
  Name name;			/* The token name */
  Code code;			/* The tokens external code */
  Vocabulary vocabulary;	/* The vocabulary which the token is defined in */
  Bool defined;			/* Is the token defined */
  Bool screening;		/* Is screening enabled for token (temporary, reset for each scanner and transfered to rule) */
  Token next;
} TokenItem;

extern Token tokenGetByName(Token  tokens, Name name);
extern Token tokenGetByCode(Token  tokens, Code code);
extern Token tokenNew(Token* tokens, Name name, Code code);
extern void tokenDump(Token token);

#endif
