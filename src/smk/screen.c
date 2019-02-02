/*
 * AUTHOR : Tony Olsson
 * DATE   : 1993-08-20/tony@wolf
 * CREATED: 1990-06-28
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/screen.c,v 1.1 2002/06/25 20:04:50 Thomas Nilsson Exp $
 *
 * $Log: screen.c,v $
 * Revision 1.1  2002/06/25 20:04:50  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.5  1997/01/13 10:20:51  thoni
 * Fixed Memory Access errors
 *
 * Revision 1.4  1993/08/20 11:33:52  tony
 * Conforms more to ANSI C standard.
 *
 * Revision 1.3  1993/04/30  12:33:21  tools
 * Adoption to ANSI-C completed.
 * Explicit register allocation removed.
 *
 * Revision 1.2  1993/04/23  11:12:47  tools
 * Totaly rewritten to correctly handle vocabularies and rules.
 *
 * Revision 1.1  1993/03/24  09:24:43  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.3  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.2  91/07/11  10:38:37  tools
 * Added Inherited scanners and Undefined tokens
 * 
 * Revision 1.1  1991/01/10  13:52:10  tools
 * Initial revision
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "common.h"
#include "rule.h"
#include "scanner.h"
#include "screen.h"
#include "set.h"
#include "smalloc.h"
#include "vocabulary.h"

/*
 * Structure of screen tables:
 *
 *	screenCheckScan[scanner]	-> YES or NO if scanner has screening ON or OFF (default all ON)
 *					   This table may be turned on and off in runtime.
 *	screenCheckCode[icode]		-> YES or NO if rule screens another rule.
 *
 *	screenTableBegin[scanner]	-> Where is the first screened string for the scanner (see table below)
 *	screenTableEnd[scanner]		-> Where is the last screened string for the scanner (see table below)
 *
 *	screenTokenLength[table index]	-> Length of token
 *	screenTokenStart[table index]	-> Start of token in token table
 *	screenTokenCode[table index]	-> Internal code of token, if negative screening is turned OFF
 *					   This table may be turned on and off in runtime.
 *
 *	screenTokens[index]		-> Packed token table
 */


int *screenCheckScan=0;
int *screenCheckCode=0;
int *screenCheckCodeScan=0;
int *screenTableBegin=0;
int *screenTableEnd=0;
int *screenTokenLength=0;
int *screenTokenStart=0;
int *screenTokenCode=0;
int *screenTokens=0;

int screenCheckScanSize=0;
int screenCheckCodeSize=0;
int screenTableSize=0;
int screenTokenSize=0;
int screenTokensSize=0;
int screenTokensPackedSize=0;

Bool screenHasScreening=NO;

/*
 * This function is used to compare two strings in an array of strings using UNIX qsort
 */

typedef struct ScreenedTokens {
  char *name;
  int length;
  Rule rule;
} *ScreenedTokens, ScreenedTokensItem;

static int screenTokenQSortCmp(const ScreenedTokens elem1, const ScreenedTokens elem2)
{
  if(elem1->length<elem2->length) return -1;
  if(elem1->length>elem2->length) return 1;
  return strcmp(elem1->name,elem2->name);
}

/*
 * This function inserts a string in screenTokens table. Returns the start of the string 
 *
 * uses: screenTokens, screenTokensPackedSize and screenTokensSize
 */

static int screenPackToken(char *string, int length)
{
  int start;
  int i;
  
  /*
   * Check if string is somewhere in screenTokens
   */
  for(start=0;start<screenTokensPackedSize-length;start++) {
    for(i=0;i<length && screenTokens[start+i]==string[i];i++);
    if(i==length) return start;
  }
  /*
   * Nope, it wasn't. Try to but the string at the end of the screenTokens if possible make it part
   * of the end of screenTokens' last string.
   */
  for(;start<screenTokensPackedSize;start++)
    for(i=0;i<length && start+i<screenTokensPackedSize && screenTokens[start+i]==string[i];i++);
  for(i=screenTokensPackedSize-start;i<length;i++) screenTokens[start+i]=string[i];
  screenTokensPackedSize=start+length;
  return start;
}

void screenCreate()
{
  Vocabulary vocabulary;
  Scanner scanner;
  Rule rule;
  int tokenTableIndex;
  int i;
  ScreenedTokens screenedTokens;
    
  /*
   * Allocate check tables
   */
  screenCheckScanSize=scannerCodes;
  screenCheckScan=(int *)smalloc(sizeof(int)*screenCheckScanSize);
  screenCheckCodeSize=ruleCodes;
  screenCheckCode=(int *)smalloc(sizeof(int)*screenCheckCodeSize);
  screenCheckCodeScan=(int *)smalloc(sizeof(int)*screenCheckCodeSize);
  /*
   * Allocate table begin/end tables
   */
  screenTableSize=scannerCodes;
  screenTableBegin=(int *)smalloc(sizeof(int)*screenTableSize);
  screenTableEnd=(int *)smalloc(sizeof(int)*screenTableSize);
  /*
   * Allocate token length/start/code tables
   * Allocate tokens table (pessemistic approach: names can not be packed)
   */
  screenTokenSize=0;
  screenTokensSize=0;
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next)
      for(rule=scanner->rules;rule;rule=rule->next) 
	if(rule->screening==YES) {
	  screenTokenSize++;
	  screenTokensSize+=astSequenceLength(rule->ast);
	}
  screenTokenLength=(int *)smalloc(sizeof(int)*screenTokenSize);
  screenTokenStart=(int *)smalloc(sizeof(int)*screenTokenSize);
  screenTokenCode=(int *)smalloc(sizeof(int)*screenTokenSize);
  screenTokens=(int *)smalloc(sizeof(int)*screenTokensSize);
 
  /*
   * Create check tables
   */
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      screenCheckScan[scanner->code]=NO;
      for(rule=scanner->rules;rule;rule=rule->next) {
	if (rule->type != ruleUNDEF) {
	  screenCheckCodeScan[rule->code]=scanner->code;
	  if(rule->screens==YES) {
	    screenCheckScan[scanner->code]=2;
	    screenCheckCode[rule->code]=2;
	  }
	  else
	    screenCheckCode[rule->code]=0;
	}
      }
    }
  
  /*
   * Create token tables
   */
  tokenTableIndex=0;
  screenedTokens=(ScreenedTokens)smalloc(sizeof(ScreenedTokensItem)*screenTokenSize);
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next)
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      screenTableBegin[scanner->code]=tokenTableIndex;
      for(rule=scanner->rules;rule;rule=rule->next) 
	if(rule->screening==YES) {
	  screenedTokens[tokenTableIndex].name=strdup(astToName(rule->ast));
	  screenedTokens[tokenTableIndex].length=astSequenceLength(rule->ast);
	  screenedTokens[tokenTableIndex].rule=rule;
	  for(i=0;i<screenedTokens[tokenTableIndex].length;i++)
	    screenedTokens[tokenTableIndex].name[i]=setTable[screenedTokens[tokenTableIndex].name[i]];
	  tokenTableIndex++;
	}
      screenTableEnd[scanner->code]=tokenTableIndex-1;
      /*
       * Sort screenTokenTable per scanner (per scanner is important)
       */
      qsort(screenedTokens+screenTableBegin[scanner->code],
	    screenTableEnd[scanner->code]-screenTableBegin[scanner->code]+1,
	    sizeof(ScreenedTokensItem),
	    (int (*)(const void *, const void *))screenTokenQSortCmp);
      /*
       * Insert tokens in tokens table (start in reverse order for each scanners)
       */
      for(i=screenTableEnd[scanner->code];i>=screenTableBegin[scanner->code];i--) {
	screenTokenLength[i]=screenedTokens[i].length;
	screenTokenStart[i]=screenPackToken(screenedTokens[i].name, screenedTokens[i].length);
	screenTokenCode[i]=screenedTokens[i].rule->code;
      }
    }
  for(i=0;i<screenTokenSize;i++) free(screenedTokens[i].name);
  free(screenedTokens);

  screenHasScreening=screenTokensPackedSize>0 ? YES : NO;
}

void screenDump()
{
  Vocabulary vocabulary;
  Scanner scanner;
  int i;
  int j;
  
  for(vocabulary=vocabularies;vocabulary;vocabulary=vocabulary->next) {
    printf( "Vocabulary: %s\n", vocabulary->name);
    for(scanner=vocabulary->scanners;scanner;scanner=scanner->next) {
      printf("    Scanner: %s   screening=%s\n", scanner->name, screenCheckScan[scanner->code]==YES ? "YES" : "NO");
      for(i=screenTableBegin[scanner->code];i<=screenTableEnd[scanner->code];i++)  {
	printf("\tlength=%3d start=%3d code=%3d \"",
	       screenTokenLength[i],
	       screenTokenStart[i],
	       screenTokenCode[i]);
	for(j=0;j<screenTokenLength[i];j++)
	  printf("%c", screenTokens[screenTokenStart[i]+j]);
	printf("\"\n");
      }
    }
  }
  printf("Packed table used size %d/%d=%5.2g%%\n", screenTokensPackedSize,screenTokensSize,(100.0*screenTokensPackedSize)/screenTokensSize);
}
