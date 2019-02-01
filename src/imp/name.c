/*
 * AUTHOR : Tony Olsson
 * DATE   : 1991-09-05/tools@heffa
 * CREATED: 1991-08-23
 * 
 * SoftLab ab (c) 1991
 *
 * Insert Name into AVL-tree (but now linjear list)
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef WIN32
#include <io.h>
#define lstat stat
#endif
#include <fcntl.h>
#include "name.h"
#include "ast.h"
#include "impScan.h"
#include "impList.h"

#ifdef WIN32
#define OFLAG _O_BINARY
#else
#define OFLAG 0
#endif

extern char *strdup(const char *);

static Name globNames = NULL;
static Name localNames = NULL;
static ParsedFile parsedFiles = NULL;
static WrittenFile writtenFiles = NULL;
static Region regionRoot = NULL;
static Param localSymtabs = NULL;
static TmSrcp startSrcp = {1, 1, 0};

extern impScContext impcontext;

/*======================================================================
  Symbol table handling
*/
static Name findSymb(name, symtab)
     char *name;
     Name symtab;
{
  int cmpResult;

  if (!symtab)
    return NULL;

  cmpResult = strcmp(name, symtab->name);
  if (cmpResult == 0)
    return symtab;
  else if (cmpResult < 0)
    return findSymb(name, symtab->left);
  else
    return findSymb(name, symtab->right);
}

static void replaceSymb(name, ast, symtab)
     char *name;
     Ast ast;
     Name *symtab;
{
  int cmpResult;
  Name node;

  if (!*symtab) {
    node = (Name)malloc(sizeof(NameItem));
    if (!node) {
      if (!(impAstGarb() && (node = (Name)malloc(sizeof(NameItem)))))
	longjmp(jmpEnv, 1);
    }
    if (!(node->name = strdup(name)))
      if (!(impAstGarb() && (node->name = strdup(name))))
	longjmp(jmpEnv, 1);
    node->undef = FALSE;
    node->ast = ast;
    node->noElems = -1;
    node->left = node->right = NULL;
    *symtab = node;
    return;
  }
  
  cmpResult = strcmp(name, (*symtab)->name);
  if (cmpResult == 0) {
    (*symtab)->noElems = -1;
    impFreeAst((*symtab)->ast);
    (*symtab)->ast = ast;
    (*symtab)->undef = FALSE;
    return;
  } else if (cmpResult < 0)
    replaceSymb(name, ast, &(*symtab)->left);
  else
    replaceSymb(name, ast, &(*symtab)->right);
}

static void appendSymb(name, ast, symtab)
     char *name;
     Ast ast;
     Name *symtab;
{
  int cmpResult;
  Name node;
  
  if (!*symtab) {
    node = (Name)malloc(sizeof(NameItem));
    if (!node) {
      if (!(impAstGarb() && (node = (Name)malloc(sizeof(NameItem)))))
	longjmp(jmpEnv, 1);
    }
    if (!(node->name = strdup(name)))
      if (!(impAstGarb() && (node->name = strdup(name))))
	longjmp(jmpEnv, 1);
    node->undef = FALSE;
    node->ast = ast;
    node->noElems = -1;
    node->left = node->right = NULL;
    *symtab = node;
    return;
  }
  
  cmpResult = strcmp(name, (*symtab)->name);
  if (cmpResult == 0) {
    Ast tmp;
    if (ast) {
      (*symtab)->noElems = -1;
      if (!(*symtab)->undef) {
	tmp = ast;
	while (tmp->next)
	  tmp = tmp->next;
	tmp->next = (*symtab)->ast;
      }
      (*symtab)->undef = FALSE;
      (*symtab)->ast = ast;
      return;
    }
  } else if (cmpResult < 0)
    appendSymb(name, ast, &(*symtab)->left);
  else
    appendSymb(name, ast, &(*symtab)->right);
}

static void insertSymb(symb, symtab)
     Name symb;
     Name *symtab;
{
  if (!*symtab) {
    *symtab = symb;
    return;
  }

  if (strcmp(symb->name, (*symtab)->name) < 0)
    insertSymb(symb, &((*symtab)->left));
  else
    insertSymb(symb, &((*symtab)->right));
}

static void nulifySymtab(symtab)
     Name symtab;
{
  if (!symtab)
    return;
  
  nulifySymtab(symtab->left);
  nulifySymtab(symtab->right);
  symtab->undef = FALSE;
  impFreeAst(symtab->ast);
  symtab->ast = NULL;
}

static void freeSymtab(symtab)
     Name symtab;
{
  if (!symtab)
    return;

  free(symtab->name);
  freeSymtab(symtab->left);
  freeSymtab(symtab->right);
  impFreeAst(symtab->ast);
  symtab->ast = NULL;
  free(symtab);
}

static void freeRegion(symtab)
     Region symtab;
{
  if (!symtab)
    return;
  free(symtab->name);
  freeSymtab(symtab->symtab);
  impFreeAst(symtab->ast);
  while (symtab->params) {
    Plist tmp;
    tmp = symtab->params;
    symtab->params = symtab->params->next;
    free(tmp->name);
    free(tmp);
  }
  freeRegion(symtab->left);
  freeRegion(symtab->right);
  free(symtab);
}


void impFreeSymtabs()
{
  freeSymtab(globNames);
  freeSymtab(localNames);
  freeRegion(regionRoot);
  globNames = localNames = NULL;
  regionRoot = NULL;
}

void impNameUndef(name)
     register char *name;
{
  register Name node;
  
  if ((localNames && (node = findSymb(name, localNames))) ||
      (node = findSymb(name, globNames))) {
    node->undef = TRUE;
    impFreeAst(node->ast);
    node->ast = NULL;
  }
}

void impNamePut(name,ast)
     register char *name;
     register Ast ast;
{
  if (localNames && findSymb(name, localNames)) {
    replaceSymb(name, ast, &localNames);
    return;
  }
  replaceSymb(name, ast, &globNames);
}

void impNameAppend(name,ast)
     register char *name;
     register Ast ast;
{

  if (localNames && findSymb(name, localNames)) {
    appendSymb(name, ast, &localNames);
    return;
  }
  appendSymb(name, ast, &globNames);
}

ImpBoolean impNameGet(name, ast)
     register char *name;
     Ast *ast;
{
  register Name node;
  char *str;

  if ((localNames && (node = findSymb(name, localNames))) ||
      (node = findSymb(name, globNames))) {
    if (node->undef)
      return FALSE;
    *ast = node->ast;
    return TRUE;
  }

  /* Nothing found */
  if (impUseEnv && (str = (char*)getenv(name))) {
    *ast = impAstNode(nulSrcp, nulSrcp, nulSrcp, AST_STRING, strlen(str), str, NULL, NULL, NULL, NULL);
    return TRUE;
  }
  return FALSE;
}

ImpBoolean impNameGetIndexed(name, ast, idxNo)
     register char *name;
     Ast *ast;
     int idxNo;
{
  register Name node = NULL;
  Ast tmp, tail;
  int i;
  char *str;
  TmSrcp srcp;

  if ((localNames && (node = findSymb(name, localNames))) ||
      (node = findSymb(name, globNames)) &&
      !node->undef) {
    if (idxNo == 0) {
      if (node->noElems != -1) {
	str = impItoa(node->noElems);
	*ast = impAstNode(nulSrcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(str), 
			  str, NULL, NULL, NULL, NULL);
      } else {
	i = 0;
	*ast = node->ast;
	while (*ast) {
	  i++;
	  *ast = (*ast)->next;
	}
	if (!(node->noElems = i))
	  srcp = nulSrcp;
	else
	  srcp = node->ast->srcp;
	str = impItoa(i);
	*ast = impAstNode(srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(str), str, 
			  NULL, NULL, NULL, NULL);
      }
    } else {
      if (node->noElems == -1) {
	Ast tmp;
	int j;
	j = 0;
	tmp = node->ast;
	while (tmp) {
	  j++;
	  tmp = tmp->next;
	}
	node->noElems = j;
      }
      if (node->noElems+1-idxNo < 1)
	/* Not enough elements in node */
	return FALSE;
      for (i = 1, *ast = node->ast; i < node->noElems+1-idxNo; i++, *ast = (*ast)->next)
	if (!*ast)
	  return FALSE;
      tail = (*ast)->next;
      (*ast)->next = NULL;
      tmp = impCopyAst(*ast, TRUE);
      (*ast)->next = tail;
      *ast = tmp;
    }
    return TRUE;
  }
  return FALSE;
}

/*----------------------------------------------------------------------
  Region symbol table handling
*/
static Region findRegion(name, regTab)
     char *name;
     Region regTab;
{
  int cmpResult;
  if (!regTab)
    return NULL;
  if ((cmpResult = strcmp(name, regTab->name)) == 0)
    return regTab;
  else if (cmpResult < 0)
    return findRegion(name, regTab->left);
  else
    return findRegion(name, regTab->right);
}

static void insertRegion(name, params, locals, ast, regTab)
     char *name;
     TxtList params;
     TxtList locals;
     Ast ast;
     Region *regTab;
{
  register Region node;
  register Name symbol;
  register Plist par;
  int cmpResult;

  if (!*regTab) {
    /* Region does not exist, define it */
    node = (Region)malloc(sizeof(RegionItem));
    if (!node) {
      if (!(impAstGarb() && (node = (Region)malloc(sizeof(RegionItem)))))
	longjmp(jmpEnv, 1);
    }
    if (!(node->name = strdup(name)))
      if (!(impAstGarb() && (node->name = strdup(name))))
	longjmp(jmpEnv, 1);
    node->ast = ast;
    node->symtab = NULL;
    node->params = NULL;
    while (params) {
      symbol = (Name)malloc(sizeof(NameItem));
      if (!symbol) {
	if (!(impAstGarb() && (symbol = (Name)malloc(sizeof(NameItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(symbol->name = strdup(params->txt)))
	if (!(impAstGarb() && (symbol->name = strdup(params->txt))))
	  longjmp(jmpEnv, 1);
      symbol->ast = NULL;
      symbol->left = symbol->right = NULL;
      insertSymb(symbol, &node->symtab);
      par = (Plist)malloc(sizeof(PlistItem));
      if (!par) {
	if (!(impAstGarb() && (par = (Plist)malloc(sizeof(PlistItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(par->name = strdup(params->txt)))
	if (!(impAstGarb() && (par->name = strdup(params->txt))))
	  longjmp(jmpEnv, 1);
      par->next = node->params;
      node->params = par;
      params = params->next;
    }
    while (locals) {
      symbol = (Name)malloc(sizeof(NameItem));
      if (!symbol) {
	if (!(impAstGarb() && (symbol = (Name)malloc(sizeof(NameItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(symbol->name = strdup(locals->txt)))
	if (!(impAstGarb() && (symbol->name = strdup(locals->txt))))
	  longjmp(jmpEnv, 1);
      symbol->ast = NULL;
      symbol->left = symbol->right = NULL;
      insertSymb(symbol, &node->symtab);
      locals = locals->next;
    }
    node->left = node->right = NULL;
    *regTab = node;
    return;
  }
  
  if ((cmpResult = strcmp(name, (*regTab)->name)) == 0) {
    /* Region already exists, redefine it */
    if ((*regTab)->ast != ast) {
      impFreeAst((*regTab)->ast);
      (*regTab)->ast = ast;
    }
    freeSymtab((*regTab)->symtab);
    (*regTab)->symtab = NULL;
    while ((*regTab)->params) {
      Plist tmp;
      tmp = (*regTab)->params;
      (*regTab)->params = (*regTab)->params->next;
      free(tmp);
    }
    (*regTab)->params = NULL;
    while (params) {
      symbol = (Name)malloc(sizeof(NameItem));
      if (!symbol) {
	if (!(impAstGarb() && (symbol = (Name)malloc(sizeof(NameItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(symbol->name = strdup(params->txt)))
	if (!(impAstGarb() && (symbol->name = strdup(params->txt))))
	  longjmp(jmpEnv, 1);
      symbol->ast = NULL;
      symbol->left = symbol->right = NULL;
      insertSymb(symbol, &(*regTab)->symtab);
      par = (Plist)malloc(sizeof(PlistItem));
      if (!par) {
	if (!(impAstGarb() && (par = (Plist)malloc(sizeof(PlistItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(par->name = strdup(params->txt)))
	if (!(impAstGarb() && (par->name = strdup(params->txt))))
	  longjmp(jmpEnv, 1);
      par->next = (*regTab)->params;
      (*regTab)->params = par;
      params = params->next;
    }
    while (locals) {
      symbol = (Name)malloc(sizeof(NameItem));
      if (!symbol) {
	if (!(impAstGarb() && (symbol = (Name)malloc(sizeof(NameItem)))))
	  longjmp(jmpEnv, 1);
      }
      if (!(symbol->name = strdup(locals->txt)))
	if (!(impAstGarb() && (symbol->name = strdup(locals->txt))))
	  longjmp(jmpEnv, 1);
      symbol->ast = NULL;
      symbol->left = symbol->right = NULL;
      insertSymb(symbol, &(*regTab)->symtab);
      locals = locals->next;
    }
    return;
  } else if (cmpResult < 0)
    insertRegion(name, params, locals, ast, &(*regTab)->left);
  else
    insertRegion(name, params, locals, ast, &(*regTab)->right);
}

/*======================================================================
  impAddRegion - Add a region to the region symbol table.

  Add a region with name name, parameters params and local variables 
  local to the region symbol table contained in regionRoot. If a region 
  named name already exists it is redefined.
*/
void impAddRegion(name, params, locals, ast)
     char *name;
     TxtList params;
     TxtList locals;
     Ast ast;
{
  insertRegion(name, params, locals, ast, &regionRoot);
}

/*======================================================================
  impGetRegion - Get region named name
*/
Region impGetRegion(name)
     register char *name;
{
  register Region region;

  if ((region = findRegion(name, regionRoot)) != NULL)
      return region;

  /* Nothing found */
  return NULL;
}

/*======================================================================
  copySymtab - Make a copy of the given symtab
 */
static Name copySymtab(symtab)
     Name symtab;
{
  Name new;
  if (!symtab)
    return NULL;
  new = (Name)malloc(sizeof(NameItem));
  if (!new) {
    if (!(impAstGarb() && (new = (Name)malloc(sizeof(NameItem)))))
      longjmp(jmpEnv, 1);
  }
  if (!(new->name = strdup(symtab->name)))
    if (!(impAstGarb() && (new->name = strdup(symtab->name))))
      longjmp(jmpEnv, 1);
  new->undef = FALSE;
  new->ast = NULL;
  new->left = copySymtab(symtab->left);
  new->right = copySymtab(symtab->right);
  return new;
}

/*======================================================================
  pushLocalSymtab - Make the given symbol table new local symbol table
 */
void impPushLocalSymtab(symtab)
     Name symtab;
{
  Param new = (Param)malloc(sizeof(ParamItem));
  if (!new) {
    if (!(impAstGarb() && (new = (Param)malloc(sizeof(ParamItem)))))
      longjmp(jmpEnv, 1);
  }
  new->param = copySymtab(symtab);
  new->next = localSymtabs;
  localSymtabs = new;
  localNames = new->param;
}

/*======================================================================
  popLocalSymtab - Restore previous local symbol table if any
 */
void impPopLocalSymtab()
{
  Param tmp = localSymtabs;
  freeSymtab(localSymtabs->param);
  localSymtabs = localSymtabs->next;
  tmp->next = NULL;
  free(tmp);
  if (localSymtabs)
    localNames = localSymtabs->param;
  else
    localNames = NULL;
}

/*======================================================================
  impReportFiles - Call impReportCnt once for each parsed file
*/
void impReportFiles()
{
  ParsedFile node;

  for (node = parsedFiles; node; node = node->next) {
    impReportFile = node->file;
    impReportCnt(node->ast);
  }
}

/*======================================================================
  astGet - get the ast that the file name results in

  astGet first tests if the file name has been parsed already. If it has
  it returns the resulting ast otherwise it parses it and returns the ast.
*/
ParseResult impAstGet(file, srcp, ast)
     register char *file;
     TmSrcp srcp;
     Ast *ast;
{
  ParsedFile pNode;
#ifndef WIN32
  WrittenFile wNode;
#endif
  struct stat buf;

  for (pNode = parsedFiles; pNode; pNode = pNode->next) 
    if (strcmp(file,pNode->file) == 0) {
      if (lstat(file, &buf) != 0){
	*ast = NULL;
	return NO_EXIST;
      }
      if ((pNode->st_ino == buf.st_ino) &&
	  (pNode->st_dev == buf.st_dev) &&
	  (pNode->st_time == buf.st_mtime)) {
	startSrcp.file = ++impFileNo;
	impLiEnter(&srcp, &startSrcp, file);
	*ast = pNode->ast;
	pNode->actCnt++;
	return pNode->result;
      }
    } 

  /* Not found, parse it */
  if (lstat(file, &buf) != 0){
    *ast = NULL;
    return NO_EXIST;
  }
#ifndef WIN32
  /* 4f - st_ino+st_dev not enough as id since st_ino is not unique (0) */
  for (wNode = writtenFiles; wNode; wNode = wNode->next) 
    if ((wNode->st_ino == buf.st_ino) &&
	(wNode->st_dev == buf.st_dev)) {
      if (impLastPass)
	impMyLog(srcp, 217, sevWAR, file);
      *ast = NULL;
      return WRITE_OPEN;
    }
#endif  
  
  impScDelete(impcontext);
  impcontext = impScNew(imp_MAIN_MAIN_Scanner);
  if((impcontext->fd=open(file,OFLAG))<0) {
    *ast = NULL;
    return NO_EXIST;
  } 
  
  impcontext->fileNo = startSrcp.file = ++impFileNo;
  impLiEnter(&srcp, &startSrcp, file);
  impMyResetSev();
  impAstRoot = NULL;
  impParse();
  close(impcontext->fd);
  *ast = impAstRoot;
  pNode = (ParsedFile) malloc(sizeof(ParsedFileItem));
  if (!pNode) {
    if (!(impAstGarb() && (pNode = (ParsedFile) malloc(sizeof(ParsedFileItem)))))
      longjmp(jmpEnv, 1);
  }
  if (!(pNode->file = strdup(file)))
    if (!(impAstGarb() && (pNode->file = strdup(file))))
      longjmp(jmpEnv, 1);
  pNode->ast = impAstRoot;
  pNode->st_ino = buf.st_ino;
  pNode->st_dev  = buf.st_dev;
  pNode->st_time = buf.st_mtime;
  pNode->actCnt = 1;
  pNode->next = parsedFiles;
  parsedFiles = pNode;
  if (impMySeverity() != sevOK)
    pNode->result = SYNTAX_ERROR;
  else
    pNode->result = PARSED_OK;
  return pNode->result;
}

/*======================================================================
  impAstRelease - The specified file is no longer used.
*/
void impAstRelease(file, ast)
     register char *file;
     Ast ast;
{
  ParsedFile node;

  for (node = parsedFiles; node; node = node->next)
    if ((strcmp(file, node->file) == 0) && 
	(ast == node->ast))
      node->actCnt--;
}

/*======================================================================
  impAstGarb - Try to release allocated memory no longer used

  impAstGarb tries to release all memory allocated when processing
  files that are no longer active.
*/
ImpBoolean impAstGarb()
{
  ParsedFile node;
  ImpBoolean result = FALSE;

  for (node = parsedFiles; node; node = node->next) {
    if (node->actCnt == 0) {
      if (node->ast)
	result = TRUE;
      impFreeAst(node->ast);
      node->ast = NULL;
      node->st_ino = -1;
      node->st_dev = -1;
      node->st_time = 0;
      node->actCnt = 0;
    }
  }
  return result;
}

/*======================================================================
*/
FILE *impWriteOpen(file, srcp)
     register char *file;
     register TmSrcp *srcp;
{
  FILE *fd;
  struct stat buf;
  WrittenFile wNode;
  ParsedFile pNode;

  if ((fd = fopen(file, "w")) != NULL) {
    if (lstat(file, &buf) == 0) {
#ifndef WIN32
      /* 4f - st_ino+st_dev not enough as id since st_ino is not unique (0) */
      for (wNode = writtenFiles; wNode; wNode = wNode->next) 
	if ((wNode->st_ino == buf.st_ino) &&
	    (wNode->st_dev == buf.st_dev)) {
	  if (impLastPass)
	    impMyLog(srcp, 216, sevWAR, file);
	  fclose(fd);
	  return NULL;
	}
#endif
      wNode = (WrittenFile)malloc(sizeof(WrittenFileItem));
      if (!wNode) {
	if (!(impAstGarb() && (wNode = (WrittenFile) malloc(sizeof(WrittenFileItem)))))
	  longjmp(jmpEnv, 1);
      }
      wNode->file = fd;
      wNode->st_ino = buf.st_ino;
      wNode->st_dev = buf.st_dev;
      wNode->next = writtenFiles;
      writtenFiles = wNode;
      for (pNode = parsedFiles; pNode; pNode = pNode->next)
	if ((strcmp(file,pNode->file) == 0) &&
	    (pNode->st_ino == buf.st_ino) &&
	    (pNode->st_dev == buf.st_dev) &&
	    (pNode->st_time == buf.st_mtime))
	  pNode->st_time = 0;
    } else {
      fclose(fd);
      fd = NULL;
    }
  }
  return fd;
}

/*======================================================================
*/
void impWriteClose(file)
     register FILE *file;
{
  WrittenFile node, prev;

  prev = NULL;
  for (node = writtenFiles; node; node = node->next) {
    if (file == node->file) {
      fclose(file);
      if (prev == NULL) {
	writtenFiles = node->next;
      } else {
	prev->next = node->next;
      }
      free(node);
      return;
    }
    prev = node;
  }
}
