/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-04-30/tools@wolf
 * CREATED: 1993-04-16
 * 
 * SoftLab ab (c) 1993
 *
 * $Header: /Repository/ToolMaker/src/smk/token.c,v 1.1 2002/06/25 20:05:02 Thomas Nilsson Exp $
 *
 * $Log: token.c,v $
 * Revision 1.1  2002/06/25 20:05:02  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.3  1993/04/30 12:33:53  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:22:01  tools
 * Completely rewritten, replaces old voc.c.
 *
 */

#include <stdio.h>
#include "common.h"
#include "smalloc.h"
#include "token.h"

Token tokenGetByName(Token tokens, Name name)
{
  for(;tokens;tokens=tokens->next)
    if(tokens->name==name) return tokens;
  return 0;
}

Token tokenGetByCode(Token tokens, Code code)
{
  for(;tokens;tokens=tokens->next)
    if(tokens->code==code) return tokens;
  return 0;
}

Token tokenNew(Token* tokens, Name name, Code code)
{
  Token token;
  if((*tokens)==0) {
    *tokens=token=(Token)smalloc(sizeof(TokenItem));
    token->name=name;
    token->code=code;
    token->vocabulary=0;
    token->defined=NO;
    token->screening=NO;
    token->next=0;
    return token;
  }
  else for(token=(*tokens);;) {
    if(token->name==name || (token->code==code && code!=codeSKIP))
      return 0;
    else if(token->next)
      token=token->next;
    else {
      token=(token->next=(Token)smalloc(sizeof(TokenItem)));
      token->name=name;
      token->code=code;
      token->vocabulary=0;
      token->defined=NO;
      token->screening=NO;
      token->next=0;
      return token;
    }
  }
}

void tokenDump(Token token)
{
  printf("  %%TOKEN code=%3d   name='%s'\n", 
	 token->code,
	 token->name);
}
