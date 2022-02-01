#include <stdio.h>
#ifdef WIN32
#define popen _popen
#define pclose _pclose
#endif
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include "impMacro.h"
#include "name.h"
#include "ast.h"

#define STRINGIFY(token) #token

#define NOCLOSE_FILE 0
#define CLOSE_FILE 1

Ast impAstRoot = NULL;
char *impReportFile = NULL;
TmSrcp nulSrcp = {0,0,0};

extern char *strdup(const char *);

static int levelsOfEvaluation = 0;

static void outputOff();
static void outputOn();
static void print();
static void pushOutput();
static void popOutput();
static void pushOutBuf();
static char *popOutBuf();
static void pushContext();
static void popContext();
static void addText();
static Ast revList();
static ImpBoolean subtractSet();
static ImpBoolean expandSet();
static ImpBoolean evalExpr();
static ImpBoolean isInteger();

typedef struct OutputStackItem *OutputStack;
typedef struct OutputStackItem {
    FILE *file;
    ImpBoolean toBeClosed;
    OutputStack next;
} OutputStackItem;
static OutputStack outputStack;

typedef enum Ctxt {
                   TEXT_REGION,
                   LIST_CONTEXT
} Ctxt;
typedef struct ContextStackItem *ContextStack;
typedef struct ContextStackItem {
    Ctxt context;
    ContextStack next;
} ContextStackItem;
static ContextStack contextStack;

typedef enum OutMedia {
                       OUTPUT_FILE,
                       INTERNAL_BUF,
                       NO_OUTPUT
} OutMedia;
static OutMedia outMedia = OUTPUT_FILE;

static ImpBoolean ignoreEscape = TRUE;
static ImpBoolean ignoreErrors = FALSE;
typedef struct BufferStackItem *BufferStack;
typedef struct BufferStackItem {
    char *internalBuffer;
    OutMedia prevOutMedia;
    BufferStack next;
} BufferStackItem;
static BufferStack bufferStack = NULL;

/*======================================================================
  impMyLog - interface to impLog
*/
static impSev maxsev;
void impMyResetSev()
{
    maxsev = sevOK;
}
impSev impMySeverity()
{
    return maxsev;
}

void impMyLog(pos, ecode, sev, istrs)
     TmSrcp *pos;               /* IN - Source position */
     int ecode;                 /* IN - The error code */
     impSev sev;                /* IN - Severity code */
     char istrs[];              /* IN - Insert strings */
{
    if (ignoreErrors)
        return;
    if(sev > maxsev && sev <= sevSYS)
        maxsev = sev;
    impLog(pos, ecode, sev, istrs);
}


/*----------------------------------------------------------------------*/
static void systemError(str, file, line)
     char *str;
     char *file;
     int line;
{
    char msg[1000];
    sprintf(msg, "%s (%s:%d)", str, file, line);
    impMyLog(NULL, 999, sevFAT, msg);
}

#define SYSERR(msg) systemError(msg, __FILE__, __LINE__)



/******************************************************************************
 *
 *    A S T   A C C E S S   R O U T I N E S
 *    =====================================
 *
 ******************************************************************************/
/*----------------------------------------------------------------------
  getInteger - Read an integer value from an AST

  If the ast can be interpreted as an integer the value of that integer
  is returned in result and the function returns TRUE otherwise it returns
  FALSE
*/
static ImpBoolean getInteger(ast, result)
     Ast ast;
     int *result;
{
    if (!ast || ast->next)
        return FALSE;

    switch (ast->type) {
    case AST_INTEGER:
        *result = atoi(ast->item.ast_integer.text);
        return TRUE;
    case AST_STRING:
    case AST_UNQUOTED_STRING:
        if (isInteger(ast->item.ast_string.text)) {
            *result = atoi(ast->item.ast_string.text);
            return TRUE;
        } else
            return FALSE;
    case AST_VALUE_LIST:
        return getInteger(ast->item.ast_valueList.valueList, result);
    default:
        return FALSE;
    }
}


/******************************************************************************
 *
 *    A S T   C R E A T I O N   R O U T I N E S
 *    =========================================
 *
 ******************************************************************************/
/******************************************************************************
 *
 * Functionname: impAstNode
 *
 *    Parameter:     Type:
 *      type           Ast_type
 *      ast0           Ast
 *      ast1           Ast
 *      ast2           Ast
 *    Return:        Type:
 *      ast            Ast
 *
 * Purpose:
 *    Create a node of type 'type'. Return the created node and link it to the
 *    ast-tree
 *
 *
 * Created    : Otto Strukelj
 * Date       : 1991-09-20
 *
 ******************************************************************************/
Ast impAstNode(srcp,endSrcp,elseSrcp,type,ival,ast0,ast1,ast2,ast3,ast4)
     TmSrcp srcp;
     TmSrcp endSrcp;
     TmSrcp elseSrcp;
     register AstType type;
     int ival;
     register Ast ast0;
     register Ast ast1;
     register Ast ast2;
     register Ast ast3;
     register Ast ast4;
{
    register Ast ast;

    ast = (Ast)malloc(sizeof(AstItem));
    if (!ast) {
        if (!(impAstGarb() && (ast = (Ast)malloc(sizeof(AstItem)))))
            longjmp(jmpEnv, 1);
    }
    ast->srcp = srcp;
    ast->endSrcp = endSrcp;
    ast->elseSrcp = elseSrcp;
    ast->evalCnt = 0;
    ast->failedToEvaluate = FALSE;
    ast->type = type;
    ast->next = NULL;
    switch (type) {
        /* Statement nodes */
    case AST_SEQ:
        ast->item.ast_seq.seq = ast0;
        break;
    case AST_TEXT:
        ast->item.ast_text.text = (char*)ast0;
        ast->item.ast_text.length = ival;
        break;
    case AST_KEEP:
        ast->item.ast_keep.text = (char*)ast0;
        ast->item.ast_keep.length = ival;
        break;
    case AST_ASSIGN:
        ast->item.ast_assign.ident = ast0;
        ast->item.ast_assign.expression = ast1;
        break;
    case AST_APPEND:
        ast->item.ast_append.ident = ast0;
        ast->item.ast_append.expression = ast1;
        break;
    case AST_EVAL:
        ast->item.ast_eval.expression = ast0;
        if (!ast1) {
            if (!(ast->item.ast_eval.trailingBlanks = strdup("")))
                if (!(impAstGarb() && (ast->item.ast_eval.trailingBlanks = strdup(""))))
                    longjmp(jmpEnv, 1);
        } else
            ast->item.ast_eval.trailingBlanks = (char*)ast1;
        break;
    case AST_REGION:
        ast->item.ast_region.beginId = ast0;
        ast->item.ast_region.params = ast1;
        ast->item.ast_region.locals = ast2;
        ast->item.ast_region.statement = ast3;
        ast->item.ast_region.endId = ast4;
        break;
    case AST_IF:
        ast->item.ast_if.condition = ast0;
        ast->item.ast_if.then_clause = ast1;
        ast->item.ast_if.else_clause = ast2;
        break;
    case AST_ELSIF:
        ast->item.ast_elsif.condition = ast0;
        ast->item.ast_elsif.then_clause = ast1;
        ast->item.ast_elsif.else_clause = ast2;
        break;
    case AST_LOOP1:
    case AST_LOOP2:
        ast->item.ast_loop.beginId = ast0;
        ast->item.ast_loop.expression = ast1;
        ast->item.ast_loop.statement = ast2;
        ast->item.ast_loop.endId = ast3;
        break;
        /* Condition nodes */
    case AST__OR:
        ast->item.ast_or.condition1 = ast0;
        ast->item.ast_or.condition2 = ast1;
        break;
    case AST__AND:
        ast->item.ast_and.condition1 = ast0;
        ast->item.ast_and.condition2 = ast1;
        break;
    case AST__NOT:
        ast->item.ast_not.condition = ast0;
        break;
    case AST__EQ:
        ast->item.ast_eq.expression1 = ast0;
        ast->item.ast_eq.expression2 = ast1;
        break;
    case AST__NEQ:
        ast->item.ast_neq.expression1 = ast0;
        ast->item.ast_neq.expression2 = ast1;
        break;
    case AST__GT:
        ast->item.ast_gt.expression1 = ast0;
        ast->item.ast_gt.expression2 = ast1;
        break;
    case AST__LT:
        ast->item.ast_lt.expression1 = ast0;
        ast->item.ast_lt.expression2 = ast1;
        break;
    case AST__GE:
        ast->item.ast_ge.expression1 = ast0;
        ast->item.ast_ge.expression2 = ast1;
        break;
    case AST__LE:
        ast->item.ast_le.expression1 = ast0;
        ast->item.ast_le.expression2 = ast1;
        break;
    case AST__DEFINED:
    case AST__RDEFINED:
        ast->item.ast_defined.ident = ast0;
        break;
    case AST__NONEMPTY:
        ast->item.ast_nonempty.ident = ast0;
        break;
    case AST__IN:
        ast->item.ast_in.ident = ast0;
        ast->item.ast_in.expression = ast1;
        break;
    case AST__SYSTEM:
        ast->item.ast_system.cmd = ast0;
        ast->item.ast_system.ident = ast1;
        break;
    case AST__STRINGMATCH:
        ast->item.ast_stringmatch.expression = ast0;
        ast->item.ast_stringmatch.pattern = ast1;
        ast->item.ast_stringmatch.position = ast2;
        break;
    case AST_GET:
        ast->item.ast_get.ident = ast0;
        ast->item.ast_get.index = ast1;
        break;
    case AST_INCLUDE:
        ast->item.ast_include.ident = ast0;
        ast->item.ast_include.expression = ast1;
        if (!ast2) {
            if (!(ast->item.ast_include.trailingBlanks = strdup("")))
                if (!(impAstGarb() && (ast->item.ast_include.trailingBlanks = strdup(""))))
                    longjmp(jmpEnv, 1);
        } else
            ast->item.ast_include.trailingBlanks = (char*)ast2;
        break;
    case AST_PROCESS:
        ast->item.ast_process.infile = ast0;
        ast->item.ast_process.outfile = ast1;
        ast->item.ast_process.silent = (ImpBoolean)ast2;
        if (!ast3) {
            if (!(ast->item.ast_process.trailingBlanks = strdup("")))
                if (!(impAstGarb() && (ast->item.ast_process.trailingBlanks = strdup(""))))
                    longjmp(jmpEnv, 1);
        } else
            ast->item.ast_process.trailingBlanks = (char*)ast3;
        break;
    case AST__PLUS:
        ast->item.ast_plus.expression = ast0;
        ast->item.ast_plus.term = ast1;
        break;
    case AST__MINUS:
        ast->item.ast_minus.expression = ast0;
        ast->item.ast_minus.term = ast1;
        break;
    case AST__BITAND:
        ast->item.ast_bitand.expression = ast0;
        ast->item.ast_bitand.term = ast1;
        break;
    case AST__BITOR:
        ast->item.ast_bitor.expression = ast0;
        ast->item.ast_bitor.term = ast1;
        break;
    case AST__TIMES:
        ast->item.ast_times.term = ast0;
        ast->item.ast_times.factor = ast1;
        break;
    case AST__DIVID:
        ast->item.ast_divid.term = ast0;
        ast->item.ast_divid.factor = ast1;
        break;
    case AST__MOD:
        ast->item.ast_mod.term = ast0;
        ast->item.ast_mod.factor = ast1;
        break;
    case AST__STRLEN:
        ast->item.ast_strlen.expression = ast0;
        break;
    case AST__CONCAT:
        ast->item.ast_concat.head = ast0;
        ast->item.ast_concat.tail = ast1;
        break;
    case AST__NEG:
        ast->item.ast_neg.factor = ast0;
        break;
    case AST_MESSAGE:
        ast->item.ast_message.expression = ast0;
        break;
    case AST_EXIT:
        ast->item.ast_exit.expression1 = ast0;
        ast->item.ast_exit.expression2 = ast1;
        break;
    case AST_INTEGER:
        ast->item.ast_integer.text = (char*)ast0;
        ast->item.ast_integer.length = ival;
        break;
    case AST_UNQUOTED_STRING:
    case AST_STRING:
        ast->item.ast_string.text = (char*)ast0;
        ast->item.ast_string.length = ival;
        break;
    case AST_IDENT:
        ast->item.ast_ident.ident = ast0;
        break;
    case AST_VALUE_LIST:
        ast->item.ast_valueList.valueList = ast0;
        break;
    case AST_PARAMS:
        ast->item.ast_params.params = ast0;
        break;
    }
    return(ast);
}

/*----------------------------------------------------------------------
  impCopyAst - copy an AST to a new memory location without removing the original
*/
Ast impCopyAst(old, copyTail)
     Ast old;
     ImpBoolean copyTail;
{
    register Ast new;

    if (!old)
        return NULL;

    new = (Ast)malloc(sizeof(AstItem));
    if (!new) {
        if (!(impAstGarb() && (new = (Ast)malloc(sizeof(AstItem)))))
            longjmp(jmpEnv, 1);
    }
    new->failedToEvaluate = old->failedToEvaluate;
    new->srcp = old->srcp;
    new->type = old->type;
    new->evalCnt = old->evalCnt;
    if (copyTail && old->next)
        new->next = impCopyAst(old->next, copyTail);
    else
        new->next = NULL;
    switch (old->type) {
    case AST_SEQ:
        new->item.ast_seq.seq = impCopyAst(old->item.ast_seq.seq, TRUE);
        break;
    case AST_TEXT:
        if (!(new->item.ast_text.text = strdup(old->item.ast_text.text)))
            if (!(impAstGarb() && (new->item.ast_text.text = strdup(old->item.ast_text.text))))
                longjmp(jmpEnv, 1);
        new->item.ast_text.length = old->item.ast_text.length;
        break;
    case AST_KEEP:
        if (!(new->item.ast_keep.text = strdup(old->item.ast_keep.text)))
            if (!(impAstGarb() && (new->item.ast_keep.text = strdup(old->item.ast_keep.text))))
                longjmp(jmpEnv, 1);
        new->item.ast_keep.length = old->item.ast_keep.length;
        break;
    case AST_ASSIGN:
        new->item.ast_assign.ident = impCopyAst(old->item.ast_assign.ident, copyTail);
        new->item.ast_assign.expression = impCopyAst(old->item.ast_assign.expression, copyTail);
        break;
    case AST_APPEND:
        new->item.ast_append.ident = impCopyAst(old->item.ast_append.ident, copyTail);
        new->item.ast_append.expression = impCopyAst(old->item.ast_append.expression, copyTail);
        break;
    case AST_EVAL:
        new->item.ast_eval.expression = impCopyAst(old->item.ast_eval.expression, copyTail);
        if (!(new->item.ast_eval.trailingBlanks = strdup(old->item.ast_eval.trailingBlanks)))
            if (!(impAstGarb() && (new->item.ast_eval.trailingBlanks = strdup(old->item.ast_eval.trailingBlanks))))
                longjmp(jmpEnv, 1);
        break;
    case AST_REGION:
        new->item.ast_region.beginId = impCopyAst(old->item.ast_region.beginId, copyTail);
        new->item.ast_region.params = impCopyAst(old->item.ast_region.params, copyTail);
        new->item.ast_region.locals = impCopyAst(old->item.ast_region.locals, copyTail);
        new->item.ast_region.statement = impCopyAst(old->item.ast_region.statement, copyTail);
        new->item.ast_region.endId = impCopyAst(old->item.ast_region.endId, copyTail);
        break;
    case AST_IF:
        new->item.ast_if.condition = impCopyAst(old->item.ast_if.condition, copyTail);
        new->item.ast_if.then_clause = impCopyAst(old->item.ast_if.then_clause, copyTail);
        new->item.ast_if.else_clause = impCopyAst(old->item.ast_if.else_clause, copyTail);
        break;
    case AST_ELSIF:
        new->item.ast_elsif.condition = impCopyAst(old->item.ast_elsif.condition, copyTail);
        new->item.ast_elsif.then_clause = impCopyAst(old->item.ast_elsif.then_clause, copyTail);
        new->item.ast_elsif.else_clause = impCopyAst(old->item.ast_elsif.else_clause, copyTail);
        break;
    case AST_LOOP1:
    case AST_LOOP2:
        new->item.ast_loop.beginId = impCopyAst(old->item.ast_loop.beginId, copyTail);
        new->item.ast_loop.expression = impCopyAst(old->item.ast_loop.expression, copyTail);
        new->item.ast_loop.statement = impCopyAst(old->item.ast_loop.statement, copyTail);
        new->item.ast_loop.endId = impCopyAst(old->item.ast_loop.endId, copyTail);
        break;
        /* Condition nodes */
    case AST__OR:
        new->item.ast_or.condition1 = impCopyAst(old->item.ast_or.condition1, copyTail);
        new->item.ast_or.condition2 = impCopyAst(old->item.ast_or.condition2, copyTail);
        break;
    case AST__AND:
        new->item.ast_and.condition1 = impCopyAst(old->item.ast_and.condition1, copyTail);
        new->item.ast_and.condition2 = impCopyAst(old->item.ast_and.condition2, copyTail);
        break;
    case AST__NOT:
        new->item.ast_not.condition = impCopyAst(old->item.ast_not.condition, copyTail);
        break;
    case AST__EQ:
        new->item.ast_eq.expression1 = impCopyAst(old->item.ast_eq.expression1, copyTail);
        new->item.ast_eq.expression2 = impCopyAst(old->item.ast_eq.expression2, copyTail);
        break;
    case AST__NEQ:
        new->item.ast_neq.expression1 = impCopyAst(old->item.ast_neq.expression1, copyTail);
        new->item.ast_neq.expression2 = impCopyAst(old->item.ast_neq.expression2, copyTail);
        break;
    case AST__GT:
        new->item.ast_gt.expression1 = impCopyAst(old->item.ast_gt.expression1, copyTail);
        new->item.ast_gt.expression2 = impCopyAst(old->item.ast_gt.expression2, copyTail);
        break;
    case AST__LT:
        new->item.ast_lt.expression1 = impCopyAst(old->item.ast_lt.expression1, copyTail);
        new->item.ast_lt.expression2 = impCopyAst(old->item.ast_lt.expression2, copyTail);
        break;
    case AST__GE:
        new->item.ast_ge.expression1 = impCopyAst(old->item.ast_ge.expression1, copyTail);
        new->item.ast_ge.expression2 = impCopyAst(old->item.ast_ge.expression2, copyTail);
        break;
    case AST__LE:
        new->item.ast_le.expression1 = impCopyAst(old->item.ast_le.expression1, copyTail);
        new->item.ast_le.expression2 = impCopyAst(old->item.ast_le.expression2, copyTail);
        break;
    case AST__RDEFINED:
    case AST__DEFINED:
        new->item.ast_defined.ident = impCopyAst(old->item.ast_defined.ident, copyTail);
        break;
    case AST__NONEMPTY:
        new->item.ast_nonempty.ident = impCopyAst(old->item.ast_nonempty.ident, copyTail);
        break;
    case AST__IN:
        new->item.ast_in.ident = impCopyAst(old->item.ast_in.ident, copyTail);
        new->item.ast_in.expression = impCopyAst(old->item.ast_in.expression, copyTail);
        break;
    case AST__SYSTEM:
        new->item.ast_system.ident = impCopyAst(old->item.ast_system.ident, copyTail);
        new->item.ast_system.cmd = impCopyAst(old->item.ast_system.cmd, copyTail);
        break;
    case AST__STRINGMATCH:
        new->item.ast_stringmatch.expression = impCopyAst(old->item.ast_stringmatch.expression, copyTail);
        new->item.ast_stringmatch.pattern = impCopyAst(old->item.ast_stringmatch.pattern, copyTail);
        new->item.ast_stringmatch.position = impCopyAst(old->item.ast_stringmatch.position, copyTail);
        break;

        /* Not yet implemented nodes */
    case AST_GET:
        new->item.ast_get.ident = impCopyAst(old->item.ast_get.ident, copyTail);
        new->item.ast_get.index = impCopyAst(old->item.ast_get.index, copyTail);
        break;
    case AST_INCLUDE:
        new->item.ast_include.ident = impCopyAst(old->item.ast_include.ident, copyTail);
        new->item.ast_include.expression = impCopyAst(old->item.ast_include.expression, copyTail);
        if (!(new->item.ast_include.trailingBlanks = strdup(old->item.ast_include.trailingBlanks)))
            if (!(impAstGarb() &&
                  (new->item.ast_include.trailingBlanks = strdup(old->item.ast_include.trailingBlanks))))
                longjmp(jmpEnv, 1);
        break;
    case AST_PROCESS:
        new->item.ast_process.infile = impCopyAst(old->item.ast_process.infile, copyTail);
        new->item.ast_process.outfile = impCopyAst(old->item.ast_process.outfile, copyTail);
        new->item.ast_process.silent = (ImpBoolean)old->item.ast_process.silent;
        if (!(new->item.ast_process.trailingBlanks = strdup(old->item.ast_process.trailingBlanks)))
            if (!(impAstGarb() &&
                  (new->item.ast_process.trailingBlanks = strdup(old->item.ast_process.trailingBlanks))))
                longjmp(jmpEnv, 1);
        break;
    case AST__PLUS:
        new->item.ast_plus.expression = impCopyAst(old->item.ast_plus.expression, copyTail);
        new->item.ast_plus.term = impCopyAst(old->item.ast_plus.term, copyTail);
        break;
    case AST__MINUS:
        new->item.ast_minus.expression = impCopyAst(old->item.ast_minus.expression, copyTail);
        new->item.ast_minus.term = impCopyAst(old->item.ast_minus.term, copyTail);
        break;
    case AST__BITAND:
        new->item.ast_bitand.expression = impCopyAst(old->item.ast_bitand.expression, copyTail);
        new->item.ast_bitand.term = impCopyAst(old->item.ast_bitand.term, copyTail);
        break;
    case AST__BITOR:
        new->item.ast_bitor.expression = impCopyAst(old->item.ast_bitor.expression, copyTail);
        new->item.ast_bitor.term = impCopyAst(old->item.ast_bitor.term, copyTail);
        break;
    case AST__TIMES:
        new->item.ast_times.term = impCopyAst(old->item.ast_times.term, copyTail);
        new->item.ast_times.factor = impCopyAst(old->item.ast_times.factor, copyTail);
        break;
    case AST__DIVID:
        new->item.ast_divid.term = impCopyAst(old->item.ast_divid.term, copyTail);
        new->item.ast_divid.factor = impCopyAst(old->item.ast_divid.factor, copyTail);
        break;
    case AST__MOD:
        new->item.ast_mod.term = impCopyAst(old->item.ast_mod.term, copyTail);
        new->item.ast_mod.factor = impCopyAst(old->item.ast_mod.factor, copyTail);
        break;
    case AST__STRLEN:
        new->item.ast_strlen.expression = impCopyAst(old->item.ast_strlen.expression, copyTail);
        break;
    case AST__CONCAT:
        new->item.ast_concat.head = impCopyAst(old->item.ast_concat.head, copyTail);
        new->item.ast_concat.tail = impCopyAst(old->item.ast_concat.tail, copyTail);
        break;
    case AST__NEG:
        new->item.ast_neg.factor = impCopyAst(old->item.ast_neg.factor, copyTail);
        break;
    case AST_MESSAGE:
        new->item.ast_message.expression = impCopyAst(old->item.ast_message.expression, copyTail);
        break;
    case AST_EXIT:
        new->item.ast_exit.expression1 = impCopyAst(old->item.ast_exit.expression1, copyTail);
        new->item.ast_exit.expression2 = impCopyAst(old->item.ast_exit.expression2, copyTail);
        break;
    case AST_INTEGER:
        if (!(new->item.ast_integer.text = strdup(old->item.ast_integer.text)))
            if (!(impAstGarb() &&
                  (new->item.ast_integer.text = strdup(old->item.ast_integer.text))))
                longjmp(jmpEnv, 1);
        new->item.ast_integer.length = old->item.ast_integer.length;
        break;
    case AST_STRING:
    case AST_UNQUOTED_STRING:
        if (!(new->item.ast_string.text = strdup(old->item.ast_string.text)))
            if (!(impAstGarb() &&
                  (new->item.ast_string.text = strdup(old->item.ast_string.text))))
                longjmp(jmpEnv, 1);
        new->item.ast_string.length = old->item.ast_string.length;
        break;
    case AST_IDENT:
        new->item.ast_ident.ident = impCopyAst(old->item.ast_ident.ident, copyTail);
        break;
    case AST_VALUE_LIST:
        new->item.ast_valueList.valueList = impCopyAst(old->item.ast_valueList.valueList, copyTail);
        break;
    case AST_PARAMS:
        new->item.ast_params.params = impCopyAst(old->item.ast_params.params, copyTail);
        break;
    }
    return new;
}
/*----------------------------------------------------------------------
  impFreeAst - free all memory allocated to an ast
*/
void impFreeAst(ast)
     Ast ast;
{
    if (!ast)
        return;

    impFreeAst(ast->next);
    switch (ast->type) {
    case AST_SEQ:
        impFreeAst(ast->item.ast_seq.seq);
        break;
    case AST_TEXT:
        free(ast->item.ast_text.text);
        break;
    case AST_KEEP:
        free(ast->item.ast_keep.text);
        break;
    case AST_ASSIGN:
        impFreeAst(ast->item.ast_assign.ident);
        impFreeAst(ast->item.ast_assign.expression);
        break;
    case AST_APPEND:
        impFreeAst(ast->item.ast_append.ident);
        impFreeAst(ast->item.ast_append.expression);
        break;
    case AST_EVAL:
        free(ast->item.ast_eval.trailingBlanks);
        impFreeAst(ast->item.ast_eval.expression);
        break;
    case AST_REGION:
        impFreeAst(ast->item.ast_region.beginId);
        impFreeAst(ast->item.ast_region.params);
        impFreeAst(ast->item.ast_region.locals);
        /* Do not free statement ast since it is saved in symbol table */
        /*  impFreeAst(ast->item.ast_region.statement);*/
        impFreeAst(ast->item.ast_region.endId);
        break;
    case AST_IF:
        impFreeAst(ast->item.ast_if.condition);
        impFreeAst(ast->item.ast_if.then_clause);
        impFreeAst(ast->item.ast_if.else_clause);
        break;
    case AST_ELSIF:
        impFreeAst(ast->item.ast_elsif.condition);
        impFreeAst(ast->item.ast_elsif.then_clause);
        impFreeAst(ast->item.ast_elsif.else_clause);
        break;
    case AST_LOOP1:
    case AST_LOOP2:
        impFreeAst(ast->item.ast_loop.beginId);
        impFreeAst(ast->item.ast_loop.expression);
        impFreeAst(ast->item.ast_loop.statement);
        impFreeAst(ast->item.ast_loop.endId);
        break;
        /* Condition nodes */
    case AST__OR:
        impFreeAst(ast->item.ast_or.condition1);
        impFreeAst(ast->item.ast_or.condition2);
        break;
    case AST__AND:
        impFreeAst(ast->item.ast_and.condition1);
        impFreeAst(ast->item.ast_and.condition2);
        break;
    case AST__NOT:
        impFreeAst(ast->item.ast_not.condition);
        break;
    case AST__EQ:
        impFreeAst(ast->item.ast_eq.expression1);
        impFreeAst(ast->item.ast_eq.expression2);
        break;
    case AST__NEQ:
        impFreeAst(ast->item.ast_neq.expression1);
        impFreeAst(ast->item.ast_neq.expression2);
        break;
    case AST__GT:
        impFreeAst(ast->item.ast_gt.expression1);
        impFreeAst(ast->item.ast_gt.expression2);
        break;
    case AST__LT:
        impFreeAst(ast->item.ast_lt.expression1);
        impFreeAst(ast->item.ast_lt.expression2);
        break;
    case AST__GE:
        impFreeAst(ast->item.ast_ge.expression1);
        impFreeAst(ast->item.ast_ge.expression2);
        break;
    case AST__LE:
        impFreeAst(ast->item.ast_le.expression1);
        impFreeAst(ast->item.ast_le.expression2);
        break;
    case AST__RDEFINED:
    case AST__DEFINED:
        impFreeAst(ast->item.ast_defined.ident);
        break;
    case AST__NONEMPTY:
        impFreeAst(ast->item.ast_nonempty.ident);
        break;
    case AST__IN:
        impFreeAst(ast->item.ast_in.ident);
        impFreeAst(ast->item.ast_in.expression);
        break;
    case AST__SYSTEM:
        impFreeAst(ast->item.ast_system.ident);
        impFreeAst(ast->item.ast_system.cmd);
        break;
    case AST__STRINGMATCH:
        impFreeAst(ast->item.ast_stringmatch.expression);
        impFreeAst(ast->item.ast_stringmatch.pattern);
        impFreeAst(ast->item.ast_stringmatch.position);
        break;
    case AST_GET:
        impFreeAst(ast->item.ast_get.ident);
        impFreeAst(ast->item.ast_get.index);
        break;
    case AST_INCLUDE:
        free(ast->item.ast_include.trailingBlanks);
        impFreeAst(ast->item.ast_include.ident);
        impFreeAst(ast->item.ast_include.expression);
        break;
    case AST_PROCESS:
        free(ast->item.ast_process.trailingBlanks);
        impFreeAst(ast->item.ast_process.infile);
        impFreeAst(ast->item.ast_process.outfile);
        break;
    case AST__PLUS:
        impFreeAst(ast->item.ast_plus.expression);
        impFreeAst(ast->item.ast_plus.term);
        break;
    case AST__MINUS:
        impFreeAst(ast->item.ast_minus.expression);
        impFreeAst(ast->item.ast_minus.term);
        break;
    case AST__BITAND:
        impFreeAst(ast->item.ast_bitand.expression);
        impFreeAst(ast->item.ast_bitand.term);
        break;
    case AST__BITOR:
        impFreeAst(ast->item.ast_bitor.expression);
        impFreeAst(ast->item.ast_bitor.term);
        break;
    case AST__TIMES:
        impFreeAst(ast->item.ast_times.term);
        impFreeAst(ast->item.ast_times.factor);
        break;
    case AST__DIVID:
        impFreeAst(ast->item.ast_divid.term);
        impFreeAst(ast->item.ast_divid.factor);
        break;
    case AST__MOD:
        impFreeAst(ast->item.ast_mod.term);
        impFreeAst(ast->item.ast_mod.factor);
        break;
    case AST__STRLEN:
        impFreeAst(ast->item.ast_strlen.expression);
        break;
    case AST__CONCAT:
        impFreeAst(ast->item.ast_concat.head);
        impFreeAst(ast->item.ast_concat.tail);
        break;
    case AST__NEG:
        impFreeAst(ast->item.ast_neg.factor);
        break;
    case AST_MESSAGE:
        impFreeAst(ast->item.ast_message.expression);
        break;
    case AST_EXIT:
        impFreeAst(ast->item.ast_exit.expression1);
        impFreeAst(ast->item.ast_exit.expression2);
        break;
    case AST_INTEGER:
        free(ast->item.ast_integer.text);
        break;
    case AST_STRING:
    case AST_UNQUOTED_STRING:
        free(ast->item.ast_string.text);
        break;
    case AST_IDENT:
        impFreeAst(ast->item.ast_ident.ident);
        break;
    case AST_VALUE_LIST:
        impFreeAst(ast->item.ast_valueList.valueList);
        break;
    case AST_PARAMS:
        impFreeAst(ast->item.ast_params.params);
        break;
    }
    free(ast);
    return;
}
/******************************************************************************
 *
 *    S E T   H A N D L I N G   R O U T I N E S
 *    =========================================
 *
 ******************************************************************************/
typedef struct ValueListItem *ValueList;
typedef struct ValueListItem {
    ImpBoolean defined;
    char *value;
    ValueList next;
} ValueListItem;

static void freeValueList(list)
     ValueList list;
{
    ValueList tmp;
    while (list) {
        free(list->value);
        tmp = list->next;
        free(list);
        list = tmp;
    }
}

static void subtractSetFromAst(set, ast, lDef)
     ValueList *set;
     Ast ast;
     ImpBoolean *lDef;
{
    Ast tmpAst;
    char *value, *exprTxt;
    ImpBoolean defined;
    ValueList tmp, prev = NULL;
    *lDef = TRUE;
    while (ast) {
        tmp = *set;
        switch (ast->type) {
        case AST_STRING:
        case AST_UNQUOTED_STRING:
            while (tmp) {
                if (tmp->defined &&
                    strcmp(tmp->value, ast->item.ast_string.text) == 0) {
                    if (*set == tmp) {
                        /* First element */
                        free((*set)->value);
                        tmp = (*set)->next;
                        free(*set);
                        *set = tmp;
                    } else {
                        tmp = tmp->next;
                        free(prev->next->value);
                        free(prev->next);
                        prev->next = tmp;
                    }
                    if (!*set)
                        return;
                } else {
                    prev = tmp;
                    tmp = tmp->next;
                }
            }
            break;
        case AST_INTEGER:
            while (tmp) {
                if (tmp->defined &&
                    strcmp(tmp->value, ast->item.ast_integer.text) == 0) {
                    if (*set == tmp) {
                        /* First element */
                        free((*set)->value);
                        tmp = (*set)->next;
                        free(*set);
                        *set = tmp;
                    } else {
                        tmp = tmp->next;
                        free(prev->next->value);
                        free(prev->next);
                        prev->next = tmp;
                    }
                    if (!*set)
                        return;
                } else {
                    prev = tmp;
                    tmp = tmp->next;
                }
            }
            break;

        case AST_EVAL:
            pushOutBuf();
            if (evalExpr(ast->item.ast_eval.expression, &tmpAst)) {
                ValueList tmpList1, tmpList2;
                free(popOutBuf());
                expandSet(tmpAst, &tmpList1);
                subtractSet(set, tmpList1);
                while (tmpList1) {
                    free(tmpList1->value);
                    tmpList2 = tmpList1;
                    tmpList1 = tmpList1->next;
                    free(tmpList2);
                }
            } else {
                *lDef = FALSE;
                exprTxt = popOutBuf();
                pushOutBuf();
                print("%%(", 3);
                print(exprTxt, strlen(exprTxt));
                print(")", 1);
                value = popOutBuf();
                while (tmp) {
                    if (!tmp->defined &&
                        strcmp(tmp->value, value) == 0) {
                        if (*set == tmp) {
                            /* First element */
                            free((*set)->value);
                            tmp = (*set)->next;
                            free(*set);
                            *set = tmp;
                        } else {
                            tmp = tmp->next;
                            free(prev->next->value);
                            free(prev->next);
                            prev->next = tmp;
                        }
                        if (!*set) {
                            free(value);
                            free(exprTxt);
                            impFreeAst(tmpAst);
                            return;
                        }
                    } else {
                        prev = tmp;
                        tmp = tmp->next;
                    }
                }
                free(value);
                free(exprTxt);
            }
            impFreeAst(tmpAst);
            break;

        case AST_VALUE_LIST:
            pushOutBuf();
            if (!(defined = impInterpretAst(ast)))
                *lDef = FALSE;
            value = popOutBuf();
            while (tmp) {
                if (tmp->defined == defined &&
                    strcmp(tmp->value, value) == 0) {
                    if (*set == tmp) {
                        /* First element */
                        free((*set)->value);
                        tmp = (*set)->next;
                        free(*set);
                        *set = tmp;
                    } else {
                        tmp = tmp->next;
                        free(prev->next->value);
                        free(prev->next);
                        prev->next = tmp;
                    }
                    if (!*set)
                        return;
                } else {
                    prev = tmp;
                    tmp = tmp->next;
                }
            }
            free(value);
            break;
        default:
            *lDef = FALSE;
            impMyLog(ast->srcp, 302, sevERR, "subtractSetFromAst()");
            break;
        }
        ast = ast->next;
    }
    return;
}

static ImpBoolean subtractSet(lSet, rSet)
     ValueList *lSet;
     ValueList rSet;
{
    ValueList result = NULL, prev = NULL, tmp;
    ImpBoolean defined = TRUE, found;
    while (*lSet) {
        found = FALSE;
        for (tmp = rSet; tmp; tmp = tmp->next)
            if (((*lSet)->defined == tmp->defined) &&
                (strcmp((*lSet)->value, tmp->value) == 0)) {
                /* found in rSet ==> delete from lSet */
                found = TRUE;
                break;
            }
        if (found) {
            tmp = (*lSet)->next;
            free((*lSet)->value);
            free(*lSet);
            *lSet = tmp;
        } else {
            if (!((*lSet)->defined))
                defined = FALSE;
            if (result) {
                prev->next = *lSet;
                prev = prev->next;
            } else {
                result = *lSet;
                prev = *lSet;
            }
            *lSet = (*lSet)->next;
        }
        if (prev)
            prev->next = NULL;
    }
    *lSet = result;
    return defined;
}

static ImpBoolean definedSet(set)
     ValueList set;
{
    while (set)
        if (!set->defined)
            return FALSE;
        else
            set = set->next;
    return TRUE;
}

static ImpBoolean totUndefinedSet(set)
     ValueList set;
{
    while (set)
        if (set->defined)
            return FALSE;
        else
            set = set->next;
    return TRUE;
}

static void printSet(set)
     ValueList set;
{
    if (outMedia == NO_OUTPUT)
        return;
    while (set) {
        print(set->value, strlen(set->value));
        set = set->next;
        if (set)
            print(", ", 2);
    }
}

static ImpBoolean expandSet(ast, resultList)
     Ast ast;
     ValueList *resultList;
{
    ImpBoolean prevLastPass;
    ValueList new;
    /* ImpBoolean partEval = FALSE; */
    char *txt;
    Ast tmp;
    *resultList = NULL;
    while (ast) {
        switch (ast->type) {
        case AST__CONCAT:
            new = (ValueList)malloc(sizeof(ValueListItem));
            if (!new) {
                if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                    longjmp(jmpEnv, 1);
            }
            pushOutBuf();
            impInterpretAst(ast);
            new->value = popOutBuf();
            new->defined = TRUE;
            new->next = *resultList;
            *resultList = new;
            break;
        case AST_STRING:
        case AST_UNQUOTED_STRING:
            new = (ValueList)malloc(sizeof(ValueListItem));
            if (!new) {
                if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                    longjmp(jmpEnv, 1);
            }
            if (!(new->value = strdup(ast->item.ast_string.text)))
                if (!(impAstGarb() && (new->value = strdup(ast->item.ast_string.text))))
                    longjmp(jmpEnv, 1);
            new->defined = TRUE;
            new->next = *resultList;
            *resultList = new;
            break;
        case AST_INTEGER:
            new = (ValueList)malloc(sizeof(ValueListItem));
            if (!new) {
                if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                    longjmp(jmpEnv, 1);
            }
            if (!(new->value = strdup(ast->item.ast_integer.text)))
                if (!(impAstGarb() && (new->value = strdup(ast->item.ast_integer.text))))
                    longjmp(jmpEnv, 1);
            new->defined = TRUE;
            new->next = *resultList;
            *resultList = new;
            break;

        case AST_EVAL: {
            levelsOfEvaluation++;
            if (levelsOfEvaluation > MAX_LEVELS) {
                char *tmp;
                tmp = impItoa(MAX_LEVELS);
                impMyLog(&ast->srcp, 215, sevERR, tmp);
                free(tmp);
                levelsOfEvaluation = 0;
                return 0;
                break;
            }
            pushOutBuf();
            if (evalExpr(ast->item.ast_eval.expression, &tmp)) {
                ValueList tmpList1, tmpList2;
                free(popOutBuf());
                if (!expandSet(tmp, &tmpList1))
                    /* partEval = TRUE */;
                if (tmpList1) {
                    tmpList2 = tmpList1;
                    while (tmpList1->next)
                        tmpList1 = tmpList1->next;
                    tmpList1->next = *resultList;
                    *resultList = tmpList2;
                }
            } else {
                txt = popOutBuf();
                new = (ValueList)malloc(sizeof(ValueListItem));
                if (!new) {
                    if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                        longjmp(jmpEnv, 1);
                }
                pushOutBuf();
                print("%%(", 3);
                print(txt, strlen(txt));
                print(")", 1);
                free(txt);
                new->value = popOutBuf();
                new->defined = FALSE;
                new->next = *resultList;
                *resultList = new;
            }
            levelsOfEvaluation--;
            impFreeAst(tmp);
            break;
        }

        case AST_GET: {
            Ast tmpAst;
            ValueList tmpList1, tmpList2;
            char *ident;
            pushOutBuf();
            impInterpretAst(ast->item.ast_get.ident); /* Interpret identifier */
            ident = popOutBuf();
            if (impNameGet(ident, &tmpAst)) {
                free(ident);
                prevLastPass = impLastPass;
                impLastPass = FALSE;
                if (!expandSet(tmpAst, &tmpList1))
                    /* partEval = TRUE */;
                if (tmpList1) {
                    tmpList2 = tmpList1;
                    while (tmpList1->next)
                        tmpList1 = tmpList1->next;
                    tmpList1->next = *resultList;
                    *resultList = tmpList2;
                }
                impLastPass = prevLastPass;
            } else if (isInteger(ident)) {
                new = (ValueList)malloc(sizeof(ValueListItem));
                if (!new) {
                    if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                        longjmp(jmpEnv, 1);
                }
                new->value = ident;
                new->defined = TRUE;
                new->next = *resultList;
            } else {
                if (impLastPass)
                    impMyLog(&(ast->item.ast_get.ident->srcp), 204, sevWAR, ident);
                new = (ValueList)malloc(sizeof(ValueListItem));
                if (!new) {
                    if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                        longjmp(jmpEnv, 1);
                }
                pushOutBuf();
                print("%%(", 3);
                print(ident, strlen(ident));
                print(")", 1);
                free(ident);
                new->value = popOutBuf();
                new->defined = FALSE;
                new->next = *resultList;
                *resultList = new;
            }
            break;
        }

        case AST_VALUE_LIST:
            pushOutBuf();
            new = (ValueList)malloc(sizeof(ValueListItem));
            if (!new) {
                if (!(impAstGarb() && (new = (ValueList)malloc(sizeof(ValueListItem)))))
                    longjmp(jmpEnv, 1);
            }
            new->defined = impInterpretAst(ast);
            new->value = popOutBuf();
            new->next = *resultList;
            *resultList = new;
            break;

        default:
            break;
        }
        ast = ast->next;
    }
    return 1;
}


/******************************************************************************
 *
 *    A S T   E V A L U A T I O N   R O U T I N E S
 *    =============================================
 *
 ******************************************************************************/

typedef enum BoolResult {
                         IMP_TRUE,
                         IMP_FALSE,
                         IMP_UNKNOWN
} BoolResult;

static BoolResult astBoolean(ast)
     register Ast ast;
{
    char *result, *resstr;
    FILE *resFile;
    Ast tmpAst, exprAst;
    ValueList rightSet;
    ImpBoolean evalCmd, leftDef, rightDef, leftInt, rightInt, prevIgnErr , evalIdent, evalIdx, evalToInt, evalEx, evalPat, evalPos;
    char *txt, *lTxt, *rTxt, *idTxt, *idxTxt, *extxt, *pattxt, *postxt;

    int iLeft, iRight, i, j, len;
    leftDef = rightDef = TRUE;
    outputOff();
    ast->evalCnt++;
    switch (ast->type) {
    case AST__DEFINED:
        if ((ast->item.ast_defined.ident->item.ast_get.ident->type == AST_IDENT) &&
            !(impInterpretAst(ast->item.ast_defined.ident->item.ast_get.ident->item.ast_ident.ident))) {
            /* Variable is an identifier that cannot be evaluated */
            outputOn();
            return IMP_UNKNOWN;
        }
        prevIgnErr = ignoreErrors;
        ignoreErrors = TRUE;;
        if (evalExpr(ast->item.ast_defined.ident, NULL)) {
            ignoreErrors = prevIgnErr;
            outputOn();
            return IMP_TRUE;
        } else {
            ignoreErrors = prevIgnErr;
            outputOn();
            return IMP_FALSE;
        }
        break;

    case AST__RDEFINED:
        prevIgnErr = ignoreErrors;
        ignoreErrors = TRUE;;
        if (!ast->item.ast_defined.ident->item.ast_get.index &&
            (ast->item.ast_defined.ident->item.ast_get.ident->type == AST_IDENT) &&
            evalExpr(ast->item.ast_defined.ident->item.ast_get.ident->item.ast_ident.ident, &tmpAst) &&
            impGetRegion(tmpAst->item.ast_string.text)) {
            ignoreErrors = prevIgnErr;
            outputOn();
            return IMP_TRUE;
        } else {
            ignoreErrors = prevIgnErr;
            outputOn();
            return IMP_FALSE;
        }
        break;

    case AST__NONEMPTY:
        if (evalExpr(ast->item.ast_nonempty.ident, &tmpAst)) {
            if (tmpAst) {
                if ((tmpAst->type == AST_VALUE_LIST) &&
                    !tmpAst->item.ast_valueList.valueList) {
                    /* Value is a value list with no elements, treated as no value */
                    impFreeAst(tmpAst);
                    outputOn();
                    return IMP_FALSE;
                } else {
                    impFreeAst(tmpAst);
                    outputOn();
                    return IMP_TRUE;
                }
            } else {
                outputOn();
                return IMP_FALSE;
            }
        } else {
            impFreeAst(tmpAst);
            outputOn();
            return IMP_UNKNOWN;
        }
        break;

    case AST__IN: {
        Ast tmp, leftList=NULL;

        if (ast->item.ast_in.ident->item.ast_get.ident->type == AST_IDENT) {
            pushOutBuf();
            evalIdent = impInterpretAst(ast->item.ast_in.ident->item.ast_get.ident);
            idTxt = popOutBuf();
            if (!evalIdent) {
                outputOn();
                return IMP_UNKNOWN;
            }
            if (ast->item.ast_in.ident->item.ast_get.index) {
                pushOutBuf();
                evalIdx = evalExpr(ast->item.ast_in.ident->item.ast_get.index, &exprAst);
                idxTxt = popOutBuf();
                if (!(evalIdx &&
                      (evalToInt = getInteger(exprAst, &i)) &&
                      impNameGetIndexed(idTxt, &leftList, i))) {
                    impFreeAst(exprAst);
                    outputOn();
                    if (impLastPass) {
                        if (evalIdx && !evalToInt)
                            impMyLog(&(ast->item.ast_in.ident->item.ast_get.index->srcp), 208, sevERR, idxTxt);
                        else if (!impNameGet(idTxt, &tmpAst))
                            impMyLog(&(ast->item.ast_in.ident->item.ast_get.ident->srcp), 204, sevWAR, idTxt);
                        else if (evalIdx)
                            impMyLog(&(ast->item.ast_in.ident->item.ast_get.index->srcp), 209, sevERR, idxTxt);
                    }
                    impFreeAst(leftList);
                    free(idTxt);
                    free(idxTxt);
                    return IMP_UNKNOWN;
                }
                free(idxTxt);
                impFreeAst(exprAst);
            } else {
                Ast tmpLeft;
                if (!impNameGet(idTxt, &tmpLeft)) {
                    if (impLastPass)
                        impMyLog(&(ast->item.ast_in.ident->item.ast_get.ident->srcp), 204, sevWAR, idTxt);
                    outputOn();
                    free(idTxt);
                    return IMP_UNKNOWN;
                }
                leftList = impCopyAst(tmpLeft, TRUE);
            }
            free(idTxt);
        } else {
            /* AST_VALUE_LIST */
            if (ast->item.ast_in.ident->item.ast_get.index) {
                pushOutBuf();
                evalIdx = evalExpr(ast->item.ast_in.ident->item.ast_get.index, &exprAst);
                idxTxt = popOutBuf();
                if (!(evalIdx &&
                      getInteger(exprAst, &i))) {
                    if (impLastPass)
                        impMyLog(&(ast->item.ast_in.ident->item.ast_get.ident->srcp), 208, sevWAR, idxTxt);
                    impFreeAst(exprAst);
                    outputOn();
                    return IMP_UNKNOWN;
                } else {
                    if (i == 0) {
                        Ast tmpLeft;
                        tmpLeft = impCopyAst(ast->item.ast_in.ident->item.ast_get.ident->item.ast_valueList.valueList, TRUE);
                        while (tmpLeft) {
                            i++;
                            tmpLeft = tmpLeft->next;
                        }
                        lTxt = impItoa(i);
                        leftList = impAstNode(ast->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                              NULL, NULL, NULL, NULL);
                    } else {
                        tmp = leftList;
                        j = 0;
                        while (tmp) {
                            j++;
                            tmp = tmp->next;
                        }
                        if (i > j) {
                            lTxt = impItoa(i);
                            impMyLog(&(ast->item.ast_in.ident->item.ast_get.index->srcp), 209 ,sevERR, lTxt);
                            free(lTxt);
                            outputOn();
                            return IMP_UNKNOWN;
                        } else {
                            tmp = leftList;
                            while (i != j) {
                                tmp = tmp->next;
                                i++;
                            }
                            leftList = impCopyAst(tmp, FALSE);
                        }
                    }
                }
            } else {
                leftList = impCopyAst(ast->item.ast_in.ident->item.ast_get.ident->item.ast_valueList.valueList, TRUE);
            }
        }

        expandSet(ast->item.ast_in.expression, &rightSet);
        subtractSetFromAst(&rightSet, leftList, &leftDef);
        impFreeAst(leftList);
        outputOn();
        if (!rightSet) {
            return IMP_TRUE;
        }
        if (leftDef && !totUndefinedSet(rightSet)) {
            freeValueList(rightSet);
            return IMP_FALSE;
        }
        freeValueList(rightSet);
        return IMP_UNKNOWN;
        break;
    }

    case AST__OR: {
        BoolResult r1, r2;
        if ((r1 = astBoolean(ast->item.ast_or.condition1)) == IMP_TRUE) {
            outputOn();
            return IMP_TRUE;
        }
        if ((r2 = astBoolean(ast->item.ast_or.condition2)) == IMP_TRUE) {
            outputOn();
            return IMP_TRUE;
        }
        if ((r1 == IMP_FALSE) && (r2 == IMP_FALSE)) {
            outputOn();
            return IMP_FALSE;
        }
        outputOn();
        return IMP_UNKNOWN;
        break;
    }

    case AST__AND: {
        BoolResult r1, r2;
        if ((r1 = astBoolean(ast->item.ast_and.condition1)) == IMP_FALSE) {
            outputOn();
            return IMP_FALSE;
        }
        if ((r2 = astBoolean(ast->item.ast_and.condition2)) == IMP_FALSE) {
            outputOn();
            return IMP_FALSE;
        }
        if ((r1 == IMP_TRUE) && (r2 == IMP_TRUE)) {
            outputOn();
            return FALSE;
        }
        outputOn();
        return IMP_UNKNOWN;
        break;
    }

    case AST__NOT:
        switch (astBoolean(ast->item.ast_not.condition)) {
        case IMP_TRUE:
            outputOn();
            return IMP_FALSE;
        case IMP_FALSE:
            outputOn();
            return IMP_TRUE;
        case IMP_UNKNOWN:
            outputOn();
            return IMP_UNKNOWN;
        }
        break;

    case AST__EQ: {
        char *condL, *condR;
        ImpBoolean knownL, knownR;
        pushOutBuf();
        knownL = evalExpr(ast->item.ast_eq.expression1, NULL);
        condL = popOutBuf();
        pushOutBuf();
        knownR = evalExpr(ast->item.ast_eq.expression2, NULL);
        condR = popOutBuf();
        if (knownL && knownR) {
            if (strcmp(condL, condR) == 0) {
                free(condL);free(condR);
                outputOn();
                return IMP_TRUE;
            } else  {
                free(condL);free(condR);
                outputOn();
                return IMP_FALSE;
            }
        } else {
            free(condL);free(condR);
            outputOn();
            return IMP_UNKNOWN;
        }
    }

    case AST__NEQ: {
        char *condL, *condR;
        ImpBoolean knownL, knownR;
        pushOutBuf();
        knownL = evalExpr(ast->item.ast_neq.expression1, NULL);
        condL = popOutBuf();
        pushOutBuf();
        knownR = evalExpr(ast->item.ast_neq.expression2, NULL);
        condR = popOutBuf();
        if (knownL && knownR) {
            if (strcmp(condL, condR) != 0) {
                free(condL);free(condR);
                outputOn();
                return IMP_TRUE;
            } else  {
                free(condL);free(condR);
                outputOn();
                return IMP_FALSE;
            }
        } else {
            free(condL);free(condR);
            outputOn();
            return IMP_UNKNOWN;
        }
    }

    case AST__GT:
    case AST__LT:
    case AST__GE:
    case AST__LE:
        /* First take care of left side in expression */
        pushOutBuf();
        if (evalExpr(ast->item.ast_gt.expression1, &tmpAst)) {
            lTxt = popOutBuf();
            leftInt = (getInteger(tmpAst, &iLeft));
            impFreeAst(tmpAst);
        } else {
            impFreeAst(tmpAst);
            lTxt = popOutBuf();
            leftDef = FALSE;
        }
        /* Then take care of right side in expression */
        pushOutBuf();
        if (evalExpr(ast->item.ast_gt.expression2, &tmpAst)) {
            rTxt = popOutBuf();
            rightInt = (getInteger(tmpAst, &iRight));
            impFreeAst(tmpAst);
        } else {
            impFreeAst(tmpAst);
            rTxt = popOutBuf();
            rightDef = FALSE;
        }
        outputOn();
        if (leftDef && rightDef) {
            switch (ast->type) {
            case AST__GT:
                if (rightInt && leftInt) {
                    free(rTxt); free(lTxt);
                    if (iLeft > iRight)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                } else {
                    i = strcmp(lTxt, rTxt);
                    free(rTxt); free(lTxt);
                    if (i > 0)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                }
            case AST__LT:
                if (rightInt && leftInt) {
                    free(rTxt); free(lTxt);
                    if (iLeft < iRight)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                } else {
                    i = strcmp(lTxt, rTxt);
                    free(rTxt); free(lTxt);
                    if (i < 0)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                }
            case AST__GE:
                if (rightInt && leftInt) {
                    free(rTxt); free(lTxt);
                    if (iLeft >= iRight)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                } else {
                    i = strcmp(lTxt, rTxt);
                    free(rTxt); free(lTxt);
                    if (i >= 0)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                }
            case AST__LE:
                if (rightInt && leftInt) {
                    free(rTxt); free(lTxt);
                    if (iLeft <= iRight)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                } else {
                    i = strcmp(lTxt, rTxt);
                    free(rTxt); free(lTxt);
                    if (i <= 0)
                        return IMP_TRUE;
                    else
                        return IMP_FALSE;
                }
            default:
                SYSERR("Unexpected value in case()");
                return IMP_UNKNOWN;
            }
        } else {
            free(rTxt); free(lTxt);
            return IMP_UNKNOWN;
        }
        break;

    case AST__SYSTEM:
        pushOutBuf();
        evalCmd = impInterpretAst(ast->item.ast_system.cmd);
        txt = popOutBuf();
        if (!evalCmd) {
            outputOn();
            free(txt);
            return IMP_UNKNOWN;
        }
        pushOutBuf();
        evalIdent = impInterpretAst(ast->item.ast_system.ident);
        idTxt = popOutBuf();
        if (!evalIdent) {
            outputOn();
            free(txt);
            free(idTxt);
            return IMP_UNKNOWN;
        }
        if ((resFile = popen(txt, "r")) == NULL) {
            longjmp(jmpEnv, 1);
        }

        i = 0;
        result = malloc(1024);
        if (!result) {
            if (!(impAstGarb() && (result = malloc(1024))))
                longjmp(jmpEnv, 1);
        }
        while ((len = fread(&result[i], 1, 1024, resFile)) == 1024) {
            i = i+1024;
            result = realloc(result, i+1024);
            if (!result) {
                longjmp(jmpEnv, 1);
            }
        }
        if (len+i == 0) {
            result[0] = '\0';
            impNamePut(idTxt, impAstNode(ast->srcp, nulSrcp, nulSrcp, AST_TEXT, 0, result,
                                         NULL, NULL, NULL, NULL));
        } else {
            if (result[len+i-1] == '\n')
                result[len+i-1] = '\0';
            else
                result[len+i] = '\0';
            impNamePut(idTxt, impAstNode(ast->srcp, nulSrcp, nulSrcp, AST_TEXT, len+i-1, result,
                                         NULL, NULL, NULL, NULL));
        }
        outputOn();
        free(txt);
        free(idTxt);
        if (pclose(resFile) == 0) {
            ast->item.ast_system.evaluatedOK = IMP_TRUE;
            return IMP_TRUE;
        } else {
            ast->item.ast_system.evaluatedOK = IMP_FALSE;
            return IMP_FALSE;
        }
        break;

    case AST__STRINGMATCH:
        pushOutBuf();
        evalEx = impInterpretAst(ast->item.ast_stringmatch.expression);
        extxt = popOutBuf();
        if(!evalEx) {
            outputOn();
            free(extxt);
            return IMP_UNKNOWN;
        }

        pushOutBuf();
        evalPat = impInterpretAst(ast->item.ast_stringmatch.pattern);
        pattxt = popOutBuf();
        if(!evalPat) {
            outputOn();
            free(extxt);
            free(pattxt);
            return IMP_UNKNOWN;
        }

        pushOutBuf();
        evalPos = impInterpretAst(ast->item.ast_stringmatch.position);
        postxt = popOutBuf();
        if(!evalPos) {
            outputOn();
            free(extxt);
            free(pattxt);
            free(postxt);
            return IMP_UNKNOWN;
        }

        resstr = strstr(pattxt, extxt);
        if (resstr == NULL)
            result = impItoa(0);
        else
            result = impItoa(resstr - pattxt + 1);

        impNamePut(postxt, impAstNode(ast->srcp, nulSrcp, nulSrcp, AST_INTEGER,
                                      sizeof(result), result, NULL, NULL, NULL, NULL));

        outputOn();
        free(extxt);
        free(pattxt);
        free(postxt);

        if (resstr == NULL)
            return IMP_FALSE;
        else
            return IMP_TRUE;
        break;


    default:
        outputOn();
        return IMP_UNKNOWN;
        break;
    }

    SYSERR("Reached end of non-void function");
    return IMP_UNKNOWN;
}

static BoolResult peBoolean(ast, cond)
     register Ast *ast;
     char **cond;
{
    Ast tmpAst;
    ValueList leftSet, rightSet;
    ImpBoolean leftDef, rightDef, leftInt, rightInt, prevLastPass, evalCmd, evalIdent, evalEx, evalPat, evalPos;
    char *txt, *lTxt, *rTxt, *idTxt, *extxt, *pattxt, *postxt;
    int iLeft, iRight, i;
    leftDef = rightDef = TRUE;
    switch ((*ast)->type) {
    case AST__DEFINED:
        pushOutBuf();
        if (((*ast)->item.ast_defined.ident->item.ast_get.ident->type == AST_IDENT) &&
            !(impInterpretAst((*ast)->item.ast_defined.ident->item.ast_get.ident->item.ast_ident.ident))) {
            /* Variable is an identifier that cannot be evaluated */
            print("(?)",3);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }
        prevLastPass = impLastPass;
        impLastPass = FALSE;
        if (evalExpr((*ast)->item.ast_defined.ident, NULL)) {
            impLastPass = prevLastPass;
            *cond = popOutBuf();
            return IMP_TRUE;
        } else {
            impLastPass = prevLastPass;
            *cond = popOutBuf();
            return IMP_FALSE;
        }
        break;

    case AST__RDEFINED:
        if (!(*ast)->item.ast_defined.ident->item.ast_get.index &&
            ((*ast)->item.ast_defined.ident->item.ast_get.ident->type == AST_IDENT) &&
            evalExpr((*ast)->item.ast_defined.ident->item.ast_get.ident->item.ast_ident.ident, &tmpAst) &&
            impGetRegion(tmpAst->item.ast_string.text)) {
            outputOn();
            return IMP_TRUE;
        } else {
            outputOn();
            return IMP_FALSE;
        }
        break;

    case AST__NONEMPTY:
        pushOutBuf();
        if (evalExpr((*ast)->item.ast_nonempty.ident, &tmpAst)) {
            *cond = popOutBuf();
            if (tmpAst) {
                if ((tmpAst->type == AST_VALUE_LIST) &&
                    !tmpAst->item.ast_valueList.valueList) {
                    /* Value is a value list with no elements, treated as no value */
                    impFreeAst(tmpAst);
                    return IMP_FALSE;
                } else {
                    impFreeAst(tmpAst);
                    return IMP_TRUE;
                }
            } else
                return IMP_FALSE;
        } else {
            print("(*)", 3);
            *cond = popOutBuf();
            impFreeAst(tmpAst);
            return IMP_UNKNOWN;
        }
        break;

    case AST__IN:
        pushOutBuf();
        if (evalExpr((*ast)->item.ast_in.ident, NULL)) {
            *cond = popOutBuf();
            rightDef = expandSet((*ast)->item.ast_in.expression, &rightSet);
            if ((*ast)->item.ast_in.ident &&
                (*ast)->item.ast_in.ident->item.ast_get.ident->type == AST_VALUE_LIST) {
                leftDef = expandSet((*ast)->item.ast_in.ident->item.ast_get.ident->item.ast_valueList.valueList,
                                    &leftSet);
            } else {
                leftDef = expandSet((*ast)->item.ast_in.ident, &leftSet);
            }
            subtractSet(&rightSet, leftSet);
            if (!rightSet) {
                freeValueList(leftSet);
                return IMP_TRUE;
            }
            if (definedSet(leftSet) && !totUndefinedSet(rightSet)) {
                freeValueList(rightSet);
                freeValueList(leftSet);
                return IMP_FALSE;
            }
            free(*cond);
            pushOutBuf();
            print("{", 1);
            printSet(leftSet);
            print("}", 1);
            print(" ", 1);
            print("(", 1);
            printSet(rightSet);
            print(")", 1);
            *cond = popOutBuf();
            freeValueList(rightSet);
            freeValueList(leftSet);
            return IMP_UNKNOWN;
        } else {
            print("(", 1);
            pushContext(LIST_CONTEXT);
            impInterpretAst((*ast)->item.ast_in.expression);
            popContext();
            print(")", 2);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }
        break;

    case AST__OR: {
        BoolResult r1, r2;
        char *c1 = NULL;
        char *c2 = NULL;
        /* c1 and c2 must be initialized to NULL in order to make free()
           safe on them. This is becaues c1 and c2 are not always assigned
           values by peBoolean().
        */
        if ((r1 = peBoolean(&((*ast)->item.ast_or.condition1), &c1)) == IMP_TRUE) {
            free(c1);
            return IMP_TRUE;
        }
        if ((r2 = peBoolean(&((*ast)->item.ast_or.condition2), &c2)) == IMP_TRUE) {
            free(c1);
            free(c2);
            return IMP_TRUE;
        }
        if ((r1 == IMP_FALSE) && (r2 == IMP_FALSE)) {
            free(c1);
            free(c2);
            return IMP_FALSE;
        }
        if (r1 == IMP_UNKNOWN)
            if (r2 == IMP_UNKNOWN) {
                pushOutBuf();
                print(c1, strlen(c1));
                print(" OR ", 4);
                print(c2, strlen(c2));
                free(c1); free(c2);
                *cond = popOutBuf();
            } else {
                free(c2);
                *cond = c1;
            }
        else {
            /* (r2 == IMP_UNKNOWN) && (r1 == IMP_FALSE) */
            free(c1);
            *cond = c2;
        }
        return IMP_UNKNOWN;
        break;
    }

    case AST__AND: {
        BoolResult r1, r2;
        char *c1 = NULL;
        char *c2 = NULL;
        /* c1 and c2 must be initialized to NULL in order to make free()
           safe on them. This is becaues c1 and c2 are not always assigned
           values by peBoolean().
        */
        if ((r1 = peBoolean(&((*ast)->item.ast_and.condition1), &c1)) == IMP_FALSE) {
            free(c1);
            return IMP_FALSE;
        }
        if ((r2 = peBoolean(&((*ast)->item.ast_and.condition2), &c2)) == IMP_FALSE) {
            free(c1);
            free(c2);
            return IMP_FALSE;
        }
        if ((r1 == IMP_TRUE) && (r2 == IMP_TRUE)) {
            free(c1);
            free(c2);
            return FALSE;
        }
        if (r1 == IMP_UNKNOWN)
            if (r2 == IMP_UNKNOWN) {
                pushOutBuf();
                print(c1, strlen(c1));
                print(" AND ", 5);
                print(c2, strlen(c2));
                *cond = popOutBuf();
            } else {
                free(c2);
                *cond = c1;
            }
        else {
            /* (r2 == IMP_UNKNOWN) && (r1 == IMP_TRUE) */
            free(c1);
            *cond = c2;
        }
        return IMP_UNKNOWN;
        break;
    }

    case AST__NOT:
        pushOutBuf();
        switch (peBoolean(&((*ast)->item.ast_not.condition), cond)) {
        case IMP_TRUE:
            free(popOutBuf());
            return IMP_FALSE;
        case IMP_FALSE:
            free(popOutBuf());
            return IMP_TRUE;
        case IMP_UNKNOWN:
            txt = popOutBuf();
            pushOutBuf();
            print("NOT", 3);
            print(txt, strlen(txt));
            free(txt);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }
        break;

    case AST__EQ: {
        char *condL, *condR;
        ImpBoolean knownL, knownR;
        pushOutBuf();
        knownL = evalExpr((*ast)->item.ast_eq.expression1, NULL);
        condL = popOutBuf();
        pushOutBuf();
        knownR = evalExpr((*ast)->item.ast_eq.expression2, NULL);
        condR = popOutBuf();
        if (knownL && knownR) {
            if (strcmp(condL, condR) == 0) {
                free(condL);
                free(condR);
                return IMP_TRUE;
            } else {
                free(condL);
                free(condR);
                return IMP_FALSE;
            }
        } else {
            pushOutBuf();
            print(condL, strlen(condL));
            print(" = ", 3);
            print(condR, strlen(condR));
            free(condL);
            free(condR);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }
    }

    case AST__NEQ: {
        char *condL, *condR;
        ImpBoolean knownL, knownR;
        pushOutBuf();
        knownL = evalExpr((*ast)->item.ast_neq.expression1, NULL);
        condL = popOutBuf();
        pushOutBuf();
        knownR = evalExpr((*ast)->item.ast_neq.expression2, NULL);
        condR = popOutBuf();
        if (knownL && knownR) {
            if (strcmp(condL, condR) != 0) {
                free(condL);
                free(condR);
                return IMP_TRUE;
            } else {
                free(condL);
                free(condR);
                return IMP_FALSE;
            }
        } else {
            pushOutBuf();
            print(condL, strlen(condL));
            print(" # ", 3);
            print(condR, strlen(condR));
            free(condL);
            free(condR);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }
    }

    case AST__GT:
    case AST__LT:
    case AST__GE:
    case AST__LE:
        /* First take care of left side in expression */
        pushOutBuf();
        if (evalExpr((*ast)->item.ast_gt.expression1, &tmpAst)) {
            lTxt = popOutBuf();
            leftInt = (getInteger(tmpAst, &iLeft));
            impFreeAst(tmpAst);
        } else {
            impFreeAst(tmpAst);
            lTxt = popOutBuf();
            leftDef = FALSE;
        }
        /* Then take care of right side in expression */
        pushOutBuf();
        if (evalExpr((*ast)->item.ast_gt.expression2, &tmpAst)) {
            rTxt = popOutBuf();
            rightInt = (getInteger(tmpAst, &iRight));
            impFreeAst(tmpAst);
        } else {
            impFreeAst(tmpAst);
            rTxt = popOutBuf();
            rightDef = FALSE;
        }
        if (leftDef && rightDef) {
            switch ((*ast)->type) {
            case AST__GT:
                if (rightInt && leftInt) {
                    if (iLeft > iRight) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                } else {
                    i = strcmp(lTxt, rTxt);
                    if (i > 0)  {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                }
            case AST__LT:
                if (rightInt && leftInt) {
                    if (iLeft < iRight) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                } else {
                    i = strcmp(lTxt, rTxt);
                    if (i < 0) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                }
            case AST__GE:
                if (rightInt && leftInt) {
                    if (iLeft >= iRight) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                } else {
                    i = strcmp(lTxt, rTxt);
                    if (i >= 0) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                }
            case AST__LE:
                if (rightInt && leftInt) {
                    if (iLeft <= iRight) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                } else {
                    i = strcmp(lTxt, rTxt);
                    if (i <= 0) {
                        free(rTxt); free(lTxt);
                        return IMP_TRUE;
                    } else {
                        free(rTxt); free(lTxt);
                        return IMP_FALSE;
                    }
                }
            default:
                SYSERR("Unexpected value in case()");
                break;
            }
        } else {
            pushOutBuf();
            print(lTxt, strlen(lTxt));
            switch ((*ast)->type) {
            case AST__GT:
                print(" > ", 3);
                break;
            case AST__LT:
                print(" < ", 3);
                break;
            case AST__GE:
                print(" >= ", 4);
                break;
            case AST__LE:
                print(" <= ", 4);
                break;
            default:
                SYSERR("Unexpected value in case()");
                break;
            }
            print(rTxt, strlen(rTxt));
            free(rTxt); free(lTxt);
            *cond = popOutBuf();
            return IMP_UNKNOWN;
        }

    case AST__SYSTEM:
        pushOutBuf();
        evalCmd = impInterpretAst((*ast)->item.ast_system.cmd);
        txt = popOutBuf();
        pushOutBuf();
        evalIdent = impInterpretAst((*ast)->item.ast_system.ident);
        idTxt = popOutBuf();
        pushOutBuf();
        print("IMP$SYSTEM(\"", 12);
        print(txt, strlen(txt));
        print("\", ",3);
        print(idTxt, strlen(idTxt));
        print(") ",2);
        free(txt); free(idTxt);
        *cond = popOutBuf();
        if (!(evalIdent && evalCmd))
            return IMP_UNKNOWN;
        if ((*ast)->item.ast_system.evaluatedOK == IMP_TRUE)
            return IMP_TRUE;
        else
            return IMP_FALSE;
        break;

    case AST__STRINGMATCH:
        pushOutBuf();
        evalEx = impInterpretAst((*ast)->item.ast_stringmatch.expression);
        extxt = popOutBuf();
        pushOutBuf();
        evalPat = impInterpretAst((*ast)->item.ast_stringmatch.pattern);
        pattxt = popOutBuf();
        pushOutBuf();
        evalPos = impInterpretAst((*ast)->item.ast_stringmatch.position);
        postxt = popOutBuf();
        pushOutBuf();
        print("IMP$STRSEARCH(\"",15);
        print(extxt, strlen(extxt));
        print("\", \"",4);
        print(pattxt, strlen(pattxt));
        print("\", ",3);
        print(postxt, strlen(postxt));
        print(") ",2);
        free(extxt); free(pattxt); free(postxt);
        *cond = popOutBuf();
        if (!(evalEx && evalPat && evalPos))
            return IMP_UNKNOWN;
        if ((*ast)->item.ast_stringmatch.evaluatedOK == IMP_TRUE)
            return IMP_TRUE;
        else
            return IMP_FALSE;
        break;

    default:
        return IMP_UNKNOWN;
        break;
    }

    SYSERR("Reached end of non-void function");
    return IMP_UNKNOWN;
}

/*======================================================================
  evalExpr - Evaluate expression

  evalExpr() takes an abstract syntax tree produced by impParse() and
  tries to evaluate all nodes in it. The tree has to represent an expression.
  If partial evaluation are used somewhere in a subtree it returns an ast
  with as much as possible evaluated in outAst. If it succeeds to evaluate
  the whole tree it returns TRUE otherwise FALSE;
  If evalExpr evaluated to a value list with just one element just that element
  is returned and no list.
*/
static ImpBoolean evalExpr(inXpr, outXpr)
     register Ast inXpr;        /* Expression to evaluate */
     register Ast *outXpr;      /* Partially evaluated expression */
{
    int iResult = 0,            /* Integer result of expression evaluation */
        tmpInt;                 /* Temporary holder of integer */
    char *lTxt = NULL,          /* Text for left side in expression */
        *rTxt = NULL,           /* Text for right side in expression */
        *xprTxt = NULL,         /* Text for expression */
        *errTxt = NULL,         /* Text for error message or warning */
        *idxTxt = NULL,         /* Text for index expression */
        *intTxt = NULL,         /* Text for integer value */
        *idTxt = NULL;          /* Text for identifier name */
    ImpBoolean evalIdent,       /* Did we succeed in evaluating an identifier name */
        evalIdx,                /* Did we succeed in evaluating an index expression */
        evalToInt,              /* Succeeded in evaluating ast into an integer value */
        partEval,               /* Has partial evaluation been used */
        evalHead,               /* Head of an CONCAT node evaluated OK */
        evalTail,               /* Tail of an CONCAT node evaluated OK */
        success = TRUE,         /* Evaluation of expression OK */
        errType,                /* Has the expression wrong type (not integer) */
        prevLastPass;           /* Previous value of lastPass */
    Ast
        tmpAst, tmpAst2,        /* Temporary holder of ast reference */
        valueList;              /* Values of ident-ast in an AST_GET node */

    if (inXpr)
        inXpr->evalCnt++;
    if (outXpr)
        *outXpr = impCopyAst(inXpr, FALSE);
    if (inXpr == NULL)
        return TRUE;

    if (inXpr->next) {
        success = evalExpr(inXpr->next, (outXpr ? &((*outXpr)->next) : NULL));
        if (contextStack->context == LIST_CONTEXT)
            print(",",1);
    }

    partEval = errType = FALSE;
    switch (inXpr->type) {
    case AST__PLUS:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_plus.expression);
        if (evalExpr(inXpr->item.ast_plus.expression, (outXpr ? &((*outXpr)->item.ast_plus.expression) : &tmpAst))) {
            /* Expression evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_plus.expression : tmpAst), &iResult)) {
                /* Expression evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_plus.expression->srcp), 208, sevERR, lTxt);
                print(lTxt, strlen(lTxt));
                print("+", 1);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate expression */
            lTxt = popOutBuf();
            print(lTxt, strlen(lTxt));
            print("+", 1);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_plus.term);
        if (evalExpr(inXpr->item.ast_plus.term, (outXpr ? &((*outXpr)->item.ast_plus.term) : &tmpAst))) {
            /* Term evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate expression */
                print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_plus.term : tmpAst), &tmpInt))
                /* Successfully evaluated term and hence the whole plus expression */
                iResult = iResult+tmpInt;
            else {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_plus.term->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print("+", 1);
                print(rTxt, strlen(rTxt));
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print("+", 1);
            }
            print(rTxt, strlen(rTxt));
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__MINUS:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_minus.expression);
        if (evalExpr(inXpr->item.ast_minus.expression, (outXpr ? &((*outXpr)->item.ast_minus.expression) : &tmpAst))) {
            /* Expression evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_minus.expression : tmpAst), &iResult)) {
                /* Expression evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_minus.expression->srcp), 208, sevERR, lTxt);
                print(lTxt, strlen(lTxt));
                print("-", 1);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate expression */
            lTxt = popOutBuf();
            print(lTxt, strlen(lTxt));
            print("-", 1);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_minus.term);
        if (evalExpr(inXpr->item.ast_minus.term,
                     (outXpr ? &((*outXpr)->item.ast_minus.term) : &tmpAst))) {
            /* Term evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate expression */
                print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_minus.term : tmpAst), &tmpInt))
                /* Successfully evaluated term and hence the whole minus expression */
                iResult = iResult-tmpInt;
            else {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_minus.term->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print("-", 1);
                print(rTxt, strlen(rTxt));
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print("-", 1);
            }
            print(rTxt, strlen(rTxt));
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__BITAND:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_bitand.expression);
        if (evalExpr(inXpr->item.ast_bitand.expression, (outXpr ? &((*outXpr)->item.ast_bitand.expression) : &tmpAst))) {
            /* Expression evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_bitand.expression : tmpAst), &iResult)) {
                /* Expression evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_bitand.expression->srcp), 208, sevERR, lTxt);
                print(lTxt, strlen(lTxt));
                print(" BITAND ", 9);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate expression */
            lTxt = popOutBuf();
            print(lTxt, strlen(lTxt));
            print(" BITAND ", 9);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_bitand.term);
        if (evalExpr(inXpr->item.ast_bitand.term, (outXpr ? &((*outXpr)->item.ast_bitand.term) : &tmpAst))) {
            /* Term evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate expression */
                print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_bitand.term : tmpAst), &tmpInt))
                /* Successfully evaluated term and hence the whole bitand expression */
                iResult = iResult & tmpInt;
            else {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_bitand.term->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print(" BITAND ", 9);
                print(rTxt, strlen(rTxt));
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print(" BITAND ", 9);
            }
            print(rTxt, strlen(rTxt));
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__BITOR:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_bitor.expression);
        if (evalExpr(inXpr->item.ast_bitor.expression, (outXpr ? &((*outXpr)->item.ast_bitor.expression) : &tmpAst))) {
            /* Expression evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_bitor.expression : tmpAst), &iResult)) {
                /* Expression evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_bitor.expression->srcp), 208, sevERR, lTxt);
                print(lTxt, strlen(lTxt));
                print(" BITOR ", 8);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate expression */
            lTxt = popOutBuf();
            print(lTxt, strlen(lTxt));
            print(" BITOR ", 8);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_bitor.term);
        if (evalExpr(inXpr->item.ast_bitor.term, (outXpr ? &((*outXpr)->item.ast_bitor.term) : &tmpAst))) {
            /* Term evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate expression */
                print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_bitor.term : tmpAst), &tmpInt))
                /* Successfully evaluated term and hence the whole bitor expression */
                iResult = iResult | tmpInt;
            else {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_bitor.term->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print(" BITOR ", 8);
                print(rTxt, strlen(rTxt));
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print(" BITOR ", 8);
            }
            print(rTxt, strlen(rTxt));
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__TIMES:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_times.term);
        if (evalExpr(inXpr->item.ast_times.term, (outXpr ? &((*outXpr)->item.ast_times.term) : &tmpAst))) {
            /* Term evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_times.term : tmpAst), &iResult)) {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_times.term->srcp), 208, sevERR, lTxt);
                print(lTxt, strlen(lTxt));
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate term */
            lTxt = popOutBuf();
            if ((outXpr ? (*outXpr)->item.ast_times.term->type : tmpAst->type) == AST_GET) {
                print(lTxt, strlen(lTxt));
            } else {
                print("(", 1);
                print(lTxt, strlen(lTxt));
                print(")", 1);
            }
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        tmpAst = NULL;
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_times.factor);
        if (evalExpr(inXpr->item.ast_times.factor, (outXpr ? &((*outXpr)->item.ast_times.factor) : &tmpAst))) {
            /* Factor evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval) {
                /* Previously failed to evaluate term */
                if (!(getInteger((outXpr ? (*outXpr)->item.ast_times.factor : tmpAst), &tmpInt) &&
                      tmpInt == 1)) {
                    print("*", 1);
                    if (((outXpr ? (*outXpr)->item.ast_times.factor->type : tmpAst->type) != AST_INTEGER) &&
                        ((outXpr ? (*outXpr)->item.ast_times.factor->type : tmpAst->type)!= AST_GET)) {
                        print("(", 1);
                        print(rTxt, strlen(rTxt));
                        print(")", 1);
                    } else
                        print(rTxt, strlen(rTxt));
                } else if (outXpr) {
                    Ast term;
                    term = (*outXpr)->item.ast_times.term;
                    (*outXpr)->item.ast_times.term = NULL;
                    impFreeAst(*outXpr);
                    *outXpr = term;
                }
            } else if (getInteger((outXpr ? (*outXpr)->item.ast_times.factor : tmpAst), &tmpInt))
                /* Successfully evaluated factor and hence the whole times expression */
                iResult = iResult*tmpInt;
            else {
                /* Factor evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_times.factor->srcp), 208, sevERR, rTxt);
                if (iResult != 1) {
                    print(lTxt, strlen(lTxt));
                    print("*", 1);
                }
                if ((outXpr ? (*outXpr)->item.ast_times.factor->type :tmpAst->type) == AST_GET) {
                    print(rTxt, strlen(rTxt));
                } else {
                    print("(", 1);
                    print(rTxt, strlen(rTxt));
                    print(")", 1);
                }
                if (outXpr && iResult == 1) {
                    Ast factor;
                    factor = (*outXpr)->item.ast_times.factor;
                    (*outXpr)->item.ast_times.factor = NULL;
                    impFreeAst(*outXpr);
                    *outXpr = factor;
                }
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                if (iResult != 1) {
                    print(lTxt, strlen(lTxt));
                    print("*", 1);
                }
            } else
                print("*", 1);
            if ((outXpr ? (*outXpr)->item.ast_times.factor->type :tmpAst->type) == AST_GET) {
                print(rTxt, strlen(rTxt));
            } else {
                print("(", 1);
                print(rTxt, strlen(rTxt));
                print(")", 1);
            }
            if (outXpr && !partEval && !errType && iResult == 1) {
                Ast factor;
                factor = (*outXpr)->item.ast_times.factor;
                (*outXpr)->item.ast_times.factor = NULL;
                impFreeAst(*outXpr);
                *outXpr = factor;
            }
            partEval = TRUE;
            free(rTxt);
        }
        if (tmpAst != NULL) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__DIVID:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_divid.term);
        if (evalExpr(inXpr->item.ast_divid.term, (outXpr ? &((*outXpr)->item.ast_divid.term) : &tmpAst))) {
            /* Term evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_divid.term :tmpAst), &iResult)) {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_divid.term->srcp), 208, sevERR, lTxt);
                if (outXpr &&
                    (*outXpr)->item.ast_divid.term &&
                    (*outXpr)->item.ast_divid.term->type == AST_GET) {
                    print(lTxt, strlen(lTxt));
                } else {
                    print("(", 1);
                    print(lTxt, strlen(lTxt));
                    print(")", 1);
                }
                print("/", 1);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate term */
            lTxt = popOutBuf();
            if ((outXpr ? (*outXpr)->item.ast_divid.term->type : tmpAst->type) == AST_GET) {
                print(lTxt, strlen(lTxt));
            } else {
                print("(", 1);
                print(lTxt, strlen(lTxt));
                print(")", 1);
            }
            print("/", 1);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_divid.factor);
        if (evalExpr(inXpr->item.ast_divid.factor, (outXpr ? &((*outXpr)->item.ast_divid.factor) : &tmpAst))) {
            /* Factor evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate term */
                if (((outXpr ? (*outXpr)->item.ast_divid.factor->type : tmpAst->type) != AST_INTEGER) &&
                    ((outXpr ? (*outXpr)->item.ast_divid.factor->type : tmpAst->type) != AST_GET)) {
                    print("(", 1);
                    print(rTxt, strlen(rTxt));
                    print(")", 1);
                } else
                    print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_divid.factor : tmpAst), &tmpInt))
                /* Successfully evaluated factor and hence the whole divid expression */
                iResult = iResult/tmpInt;
            else {
                /* Factor evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_divid.factor->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print("/", 1);
                if ((outXpr ? (*outXpr)->item.ast_divid.factor->type : tmpAst->type) == AST_GET) {
                    print(rTxt, strlen(rTxt));
                } else {
                    print("(", 1);
                    print(rTxt, strlen(rTxt));
                    print(")", 1);
                }
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print("/", 1);
            }
            if ((outXpr ? (*outXpr)->item.ast_divid.factor->type : tmpAst->type) == AST_GET) {
                print(rTxt, strlen(rTxt));
            } else {
                print("(", 1);
                print(rTxt, strlen(rTxt));
                print(")", 1);
            }
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__MOD:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_mod.term);
        if (evalExpr(inXpr->item.ast_mod.term, (outXpr ? &((*outXpr)->item.ast_mod.term) : &tmpAst))) {
            /* Term evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_mod.term :tmpAst), &iResult)) {
                /* Term evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_mod.term->srcp), 208, sevERR, lTxt);
                if (outXpr &&
                    (*outXpr)->item.ast_mod.term &&
                    (*outXpr)->item.ast_mod.term->type == AST_GET) {
                    print(lTxt, strlen(lTxt));
                } else {
                    print("(", 1);
                    print(lTxt, strlen(lTxt));
                    print(")", 1);
                }
                print(" MOD ", 5);
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate term */
            lTxt = popOutBuf();
            if ((outXpr ? (*outXpr)->item.ast_mod.term->type : tmpAst->type) == AST_GET) {
                print(lTxt, strlen(lTxt));
            } else {
                print("(", 1);
                print(lTxt, strlen(lTxt));
                print(")", 1);
            }
            print(" MOD ", 5);
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        /* Take care of right side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_mod.factor);
        if (evalExpr(inXpr->item.ast_mod.factor, (outXpr ? &((*outXpr)->item.ast_mod.factor) : &tmpAst))) {
            /* Factor evaluated successfully */
            rTxt = popOutBuf();
            if (errType || partEval)
                /* Previously failed to evaluate term */
                if (((outXpr ? (*outXpr)->item.ast_mod.factor->type : tmpAst->type) != AST_INTEGER) &&
                    ((outXpr ? (*outXpr)->item.ast_mod.factor->type : tmpAst->type) != AST_GET)) {
                    print("(", 1);
                    print(rTxt, strlen(rTxt));
                    print(")", 1);
                } else
                    print(rTxt, strlen(rTxt));
            else if (getInteger((outXpr ? (*outXpr)->item.ast_mod.factor : tmpAst), &tmpInt))
                /* Successfully evaluated factor and hence the whole modulus expression */
                iResult = iResult % tmpInt;
            else {
                /* Factor evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_mod.factor->srcp), 208, sevERR, rTxt);
                print(lTxt, strlen(lTxt));
                print(" MOD ", 5);
                if ((outXpr ? (*outXpr)->item.ast_mod.factor->type : tmpAst->type) == AST_GET) {
                    print(rTxt, strlen(rTxt));
                } else {
                    print("(", 1);
                    print(rTxt, strlen(rTxt));
                    print(")", 1);
                }
                errType = TRUE;
            }
            free(rTxt);
        } else {
            rTxt = popOutBuf();
            if (!partEval && !errType) {
                print(lTxt, strlen(lTxt));
                print(" MOD ", 5);
            }
            if ((outXpr ? (*outXpr)->item.ast_mod.factor->type : tmpAst->type) == AST_GET) {
                print(rTxt, strlen(rTxt));
            } else {
                print("(", 1);
                print(rTxt, strlen(rTxt));
                print(")", 1);
            }
            partEval = TRUE;
            free(rTxt);
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__STRLEN:
        /* First take care of left side in expression */
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_strlen.expression);
        if (evalExpr(inXpr->item.ast_strlen.expression, (outXpr ? &((*outXpr)->item.ast_strlen.expression) : &tmpAst))) {
            /* Term evaluated successfully */
            lTxt = popOutBuf();
        } else {
            /* Failed to evaluate term */
            lTxt = popOutBuf();
            if ((outXpr ? (*outXpr)->item.ast_strlen.expression->type : tmpAst->type) == AST_GET) {
                print(lTxt, strlen(lTxt));
            } else {
                print("IMP$STRLEN(", 11);
                print(lTxt, strlen(lTxt));
                print(")", 1);
            }
            partEval = TRUE;
        }
        iResult = strlen(lTxt);
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST__NEG:
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_neg.factor);
        if (evalExpr(inXpr->item.ast_neg.factor, (outXpr ? &((*outXpr)->item.ast_neg.factor) : &tmpAst))) {
            /* Factor evaluated successfully */
            lTxt = popOutBuf();
            if (!getInteger((outXpr ? (*outXpr)->item.ast_neg.factor : tmpAst), &iResult)) {
                /* Factor evaluated to wrong type */
                impMyLog(&(inXpr->item.ast_neg.factor->srcp), 208, sevERR, lTxt);
                print("-", 1);
                if (((outXpr ? (*outXpr)->item.ast_neg.factor->type : tmpAst->type) != AST_INTEGER) &&
                    ((outXpr ? (*outXpr)->item.ast_neg.factor->type : tmpAst->type) != AST_GET)) {
                    print("(", 1);
                    print(lTxt, strlen(lTxt));
                    print(")", 1);
                } else
                    print(lTxt, strlen(lTxt));
                errType = TRUE;
            }
        } else {
            /* Failed to evaluate factor */
            lTxt = popOutBuf();
            print("-", 1);
            print(lTxt, strlen(lTxt));
            partEval = TRUE;
        }
        if (!outXpr) impFreeAst(tmpAst);
        if (!partEval && !errType) {
            free(lTxt);
            lTxt = impItoa(-iResult);
            if (outXpr) {
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_INTEGER, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
            }
            print(lTxt, strlen(lTxt));
            if (!outXpr)
                free(lTxt);
        } else {
            success = FALSE;
            free(lTxt);
        }
        break;

    case AST_GET:
        if ((inXpr->item.ast_get.ident->type == AST_INTEGER) &&
            (inXpr->item.ast_get.index)) {
            impMyLog(&(inXpr->item.ast_get.index->srcp), 211, sevERR, "");
            pushOutBuf();
            evalIdent = impInterpretAst(inXpr->item.ast_get.ident);
            idTxt = popOutBuf();
            pushOutBuf();
            if (outXpr)
                impFreeAst((*outXpr)->item.ast_get.index);
            evalIdx = evalExpr(inXpr->item.ast_get.index, (outXpr ? &((*outXpr)->item.ast_get.index) : NULL));
            idxTxt = popOutBuf();
            print(idTxt, strlen(idTxt));
            print("[", 1);
            print(idxTxt, strlen(idxTxt));
            print("]", 1);
            success = FALSE;
            free(idTxt);
            free(idxTxt);
        } else {
            /* This test fails on HP !!! */
            if (inXpr->item.ast_get.ident->type == AST_IDENT) {
                /* Evaluating a variable */
                pushOutBuf();
                evalIdent = impInterpretAst(inXpr->item.ast_get.ident);
                idTxt = popOutBuf();
                pushOutBuf();
                if (outXpr)
                    impFreeAst((*outXpr)->item.ast_get.index);
                evalIdx = evalExpr(inXpr->item.ast_get.index, (outXpr ? &((*outXpr)->item.ast_get.index) : &tmpAst));
                idxTxt = popOutBuf();
                if (evalIdent) {
                    /* Succeeded in evaluating identifier */
                    pushContext(LIST_CONTEXT);
                    if (inXpr->item.ast_get.index) {
                        if (!(evalIdx &&
                              (evalToInt = getInteger((outXpr ? (*outXpr)->item.ast_get.index : tmpAst), &iResult)) &&
                              impNameGetIndexed(idTxt, &valueList, iResult))) {
                            /* Failed to evaluate index to an integer or to get value from symbol table */
                            print(idTxt, strlen(idTxt));
                            print("[", 1);
                            print(idxTxt, strlen(idxTxt));
                            print("]", 1);
                            if (impLastPass) {
                                if (evalIdx && !evalToInt)
                                    impMyLog(&(inXpr->item.ast_get.index->srcp), 208, sevERR, idxTxt);
                                else if (!impNameGet(idTxt, &tmpAst2))
                                    impMyLog(&(inXpr->item.ast_get.ident->srcp), 204, sevWAR, idTxt);
                                else if (evalIdx)
                                    impMyLog(&(inXpr->item.ast_get.index->srcp), 209, sevERR, idxTxt);
                            }
                            success = FALSE;
                        } else {
                            prevLastPass = impLastPass;
                            impLastPass = FALSE;
                            if (outXpr) {
                                impFreeAst(*outXpr);
                                *outXpr = impCopyAst(valueList, TRUE);
                            }
                            impInterpretAst(valueList);
                            impFreeAst(valueList);
                            impLastPass = prevLastPass;
                        }
                    } else if (isInteger(idTxt)) {
                        if (outXpr) {
                            char *tmpTxt;
                            TmSrcp tmpSrcp;
                            tmpSrcp = (*outXpr)->item.ast_get.ident->srcp;
                            impFreeAst(*outXpr);
                            if (!(tmpTxt = strdup(idTxt)))
                                if (!(impAstGarb() && (tmpTxt = strdup(idTxt))))
                                    longjmp(jmpEnv, 1);
                            *outXpr = impAstNode(tmpSrcp, nulSrcp,
                                                 nulSrcp, AST_INTEGER, strlen(tmpTxt),
                                                 tmpTxt, NULL, NULL, NULL, NULL);
                        }
                        print(idTxt, strlen(idTxt));
                    } else {
                        if (!(impNameGet(idTxt, &valueList))) {
                            if (impLastPass)
                                impMyLog(&(inXpr->item.ast_get.ident->srcp), 204, sevWAR, idTxt);
                            print(idTxt, strlen(idTxt));
                            success = FALSE;
                        } else {
                            prevLastPass = impLastPass;
                            impLastPass = FALSE;
                            if (outXpr) {
                                impFreeAst(*outXpr);
                                *outXpr = impCopyAst(valueList, TRUE);
                            }
                            impInterpretAst(valueList);
                            impLastPass = prevLastPass;
                        }
                    }
                    popContext();
                } else {
                    /* Failed to evaluate identifier */
                    pushOutBuf();
                    print(idTxt, strlen(idTxt));
                    if (inXpr->item.ast_get.index) {
                        print("[", 1);
                        print(idxTxt, strlen(idxTxt));
                        print("]", 1);
                    }
                    errTxt = popOutBuf();
                    if (impLastPass)
                        impMyLog(&(inXpr->item.ast_get.ident->srcp), 204, sevWAR, errTxt);
                    print(errTxt, strlen(errTxt));
                    free(errTxt);
                    success = FALSE;
                }
                free(idTxt);
                free(idxTxt);
                if (!outXpr)
                    impFreeAst(tmpAst);
            } else { /* inXpr->item.ast_get.ident->type == AST_VALUE_LIST */
                /* Evaluating a value list */
                pushOutBuf();
                if (outXpr)
                    impFreeAst((*outXpr)->item.ast_get.index);
                evalIdx = evalExpr(inXpr->item.ast_get.index,
                                   (outXpr ? &((*outXpr)->item.ast_get.index) : &tmpAst));
                idxTxt = popOutBuf();
                if (inXpr->item.ast_get.index) {
                    if (!(evalIdx &&
                          getInteger((outXpr ? (*outXpr)->item.ast_get.index : tmpAst), &iResult))) {
                        /* Failed to evaluate index to an integer */
                        impInterpretAst(inXpr->item.ast_get.ident);
                        print("[", 1);
                        print(idxTxt, strlen(idxTxt));
                        print("]", 1);
                        if (impLastPass)
                            impMyLog(&(inXpr->item.ast_get.ident->srcp), 208, sevWAR, idxTxt);
                        success = FALSE;
                    } else if (iResult == 0) {
                        valueList = inXpr->item.ast_get.ident->item.ast_valueList.valueList;
                        while (valueList) {
                            iResult++;
                            valueList = valueList->next;
                        }
                        intTxt = impItoa(iResult);
                        print(intTxt, strlen(intTxt));
                        if (outXpr) {
                            impFreeAst(*outXpr);
                            *outXpr = impAstNode(inXpr->srcp, nulSrcp,
                                                 nulSrcp, AST_INTEGER, strlen(intTxt), intTxt, NULL, NULL, NULL, NULL);
                        } else
                            free(intTxt);
                    } else {
                        valueList = revList(impCopyAst(inXpr->item.ast_get.ident->item.ast_valueList.valueList, TRUE));
                        while (iResult > 1) {
                            Ast tmpList;
                            iResult--;
                            tmpList = valueList;
                            valueList = valueList->next;
                            tmpList->next = NULL;
                            impFreeAst(tmpList);
                            if (!valueList)
                                /* Too high index */
                                break;
                        }
                        if (valueList) {
                            Ast tmpList;
                            tmpList = valueList;
                            valueList = impCopyAst(valueList, FALSE);
                            impFreeAst(tmpList);
                            if (outXpr) {
                                impFreeAst(*outXpr);
                                *outXpr = valueList;
                            }
                            impInterpretAst(valueList);
                            if (!outXpr)
                                impFreeAst(valueList);
                        } else {
                            /* Too high index */
                            pushOutBuf();
                            pushContext(LIST_CONTEXT);
                            impInterpretAst(inXpr->item.ast_get.ident);
                            popContext();
                            print("[", 1);
                            print(idxTxt, strlen(idxTxt));
                            print("]", 1);
                            errTxt = popOutBuf();
                            impMyLog(&(inXpr->item.ast_get.index->srcp), 209, sevERR, idxTxt);
                            print(errTxt, strlen(errTxt));
                            free(errTxt);
                            success = FALSE;
                        }
                    }
                } else {
                    pushContext(LIST_CONTEXT);
                    if (outXpr)
                        impFreeAst(*outXpr);
                    evalExpr(inXpr->item.ast_get.ident, (outXpr ? outXpr : NULL));
                    popContext();
                }
                if (!outXpr)
                    impFreeAst(tmpAst);
                free(idxTxt);
            }}
        break;

    case AST_EVAL:
        levelsOfEvaluation++;
        if (levelsOfEvaluation > MAX_LEVELS) {
            impMyLog(&inXpr->srcp, 215, sevERR, impItoa(MAX_LEVELS));
            levelsOfEvaluation = 0;
            return FALSE;
            break;
        }
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_eval.expression);
        if (evalExpr(inXpr->item.ast_eval.expression, (outXpr ? &((*outXpr)->item.ast_eval.expression) : NULL))) {
            xprTxt = popOutBuf();
            print(xprTxt, strlen(xprTxt));
            if (outXpr) {
                Ast list, tmp;
                tmpAst = (*outXpr)->next;
                free((*outXpr)->item.ast_eval.trailingBlanks);
                tmp = (*outXpr)->item.ast_eval.expression;
                (*outXpr)->item.ast_eval.expression = NULL;
                free(*outXpr);
                if ((*outXpr = tmp)) {
                    for (list = *outXpr; list->next; list = list->next)
                        ;
                    list->next = tmpAst;
                } else
                    *outXpr = tmpAst;
            }
        } else {
            xprTxt = popOutBuf();
            print("%%(", 3);
            print(xprTxt, strlen(xprTxt));
            print(")", 1);
            success = FALSE;
        }
        free(xprTxt);
        levelsOfEvaluation--;
        break;

    case AST_STRING:
    case AST_UNQUOTED_STRING:
        print(inXpr->item.ast_string.text, (int)inXpr->item.ast_string.length);
        break;

    case AST_INTEGER:
        print(inXpr->item.ast_integer.text, (int)inXpr->item.ast_integer.length);
        break;

    case AST_VALUE_LIST: {
        char *tmpTxt;

        if (!(tmpTxt = strdup("{")))
            if (!(impAstGarb() && (tmpTxt = strdup("{"))))
                longjmp(jmpEnv, 1);
        print(tmpTxt, 1);
        free(tmpTxt);
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_valueList.valueList);
        evalExpr(inXpr->item.ast_valueList.valueList,
                 (outXpr ? &((*outXpr)->item.ast_valueList.valueList) : NULL));
        if (!(tmpTxt = strdup("}")))
            if (!(impAstGarb() && (tmpTxt = strdup("}"))))
                longjmp(jmpEnv, 1);
        print(tmpTxt, 1);
        free(tmpTxt);
    } break;

    case AST__CONCAT:
        pushOutBuf();
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_concat.head);
        evalHead = evalExpr(inXpr->item.ast_concat.head, (outXpr ? &((*outXpr)->item.ast_concat.head) : NULL));
        if (outXpr)
            impFreeAst((*outXpr)->item.ast_concat.tail);
        evalTail = evalExpr(inXpr->item.ast_concat.tail, (outXpr ? &((*outXpr)->item.ast_concat.tail) : NULL));
        lTxt = popOutBuf();
        print(lTxt, strlen(lTxt));
        if (evalHead && evalTail) {
            if (outXpr) {
                tmpAst = (*outXpr)->next;
                (*outXpr)->next = NULL;
                impFreeAst(*outXpr);
                *outXpr = impAstNode(inXpr->srcp, nulSrcp, nulSrcp, AST_STRING, strlen(lTxt), lTxt,
                                     NULL, NULL, NULL, NULL);
                (*outXpr)->next = tmpAst;
            }
            return TRUE;
        } else {
            if (outXpr)
                (*outXpr)->failedToEvaluate = TRUE;
            return FALSE;
        }
        break;
    default:
        success = FALSE;
    }
    if (outXpr && *outXpr)
        (*outXpr)->failedToEvaluate = !success;
    return success;
}


/*======================================================================
  impInterpretAst - Interpret an IMP ast.

  impInterpretAst() takes an abstract syntax tree produced by impParse() and
  tries to evaluate all nodes in it. If partial evaluation are used some-
  where in a subtree it returns an ast with as much as possible evaluated.
  If it succeeds to evaluate the whole tree it returns NULL.
*/
ImpBoolean impInterpretAst(inAst)
     register Ast inAst;        /* Ast to interpret */
{
    char *exprTxt,              /* Expression text */
        *stmTxt,                /* Statement text */
        *identTxt,              /* Identifier name */
        *beginLabel,            /* Begin label in loop and region */
        *endLabel,              /* End label in loop and region */
        *param,                 /* Parameter name */
        *localVar,              /* Local variable name */
        *cond;                  /* Boolean condition */
    int i,                      /* Common integer variable */
        loopVar;                /* Variable to hold loop value when evaluating loop statement */
    Ast list,                   /* Ast list */
        exprAst,                /* Expression ast */
        tmp;                    /* Temporary ast reference */
    Region region;
    Plist regParams;
    ImpBoolean partEval,        /* Use partial evaluation */
        setParams,              /* Are we trying to set parameters */
        evalFlg,                /* Has we succeded in evaluation of node */
        badHead,                /* Begin label does not match end label */
        evalHead,               /* Head of an CONCAT node evaluated OK */
        evalTail,               /* Tail of an CONCAT node evaluated OK */
        prevIgnErr;             /* Previous value of ignoreErrors */
    TxtList paramList,          /* Parameter list */
        localList;              /* Local variable list */


    /*  if (malloc_verify()) { */
    /* Stop here */
    /*    badHead = badHead;
          }
    */

    if (inAst == NULL) {
        /* Empty ast, successfully evaluated to nothing */
        return TRUE;
    }

    if (!contextStack)
        /* Initialize context to text */
        pushContext(TEXT_REGION);

    if (inAst->next) {
        /* Interpret next ast in list before this one */
        impInterpretAst(inAst->next);
        if (contextStack->context == LIST_CONTEXT)
            print(",",1);
    }

    inAst->evalCnt++;
    switch (inAst->type) {
    case AST_SEQ:
        return impInterpretAst(inAst->item.ast_seq.seq);
        break;

    case AST_TEXT:
        ignoreEscape = FALSE;
        print(inAst->item.ast_text.text, inAst->item.ast_text.length);
        ignoreEscape = TRUE;
        return TRUE;
        break;

    case AST_KEEP:
        ignoreEscape = TRUE;
        print(inAst->item.ast_keep.text, inAst->item.ast_keep.length);
        ignoreEscape = FALSE;
        return TRUE;
        break;

    case AST_APPEND:
    case AST_ASSIGN:
        pushOutBuf();
        if (impInterpretAst(inAst->item.ast_assign.ident)) {
            identTxt = popOutBuf();
            /* Succeeded in evaluation of identifier, set value but do not output anything */
            outputOff();
            evalExpr(inAst->item.ast_assign.expression, &exprAst);
            outputOn();
            if (inAst->type == AST_ASSIGN)
                impNamePut(identTxt, exprAst);
            else /* inAst->type == AST_APPEND */
                impNameAppend(identTxt, exprAst);
            free(identTxt);
            return TRUE;
        } else {
            identTxt = popOutBuf();
            pushOutBuf();
            pushContext(LIST_CONTEXT);
            impInterpretAst(inAst->item.ast_assign.expression);
            popContext();
            exprTxt = popOutBuf();
            print("%%SET ", 6);
            print(identTxt, strlen(identTxt));
            print(" (", 2);
            print(exprTxt, strlen(exprTxt));
            print(")\n", 2);
            inAst->failedToEvaluate = TRUE;
            free(identTxt);
            free(exprTxt);
            return FALSE;
        }
        break;

    case AST_EVAL:
        if (levelsOfEvaluation++ > MAX_LEVELS) {
            impMyLog(&inAst->srcp, 215, sevERR, impItoa(MAX_LEVELS));
            levelsOfEvaluation = 0;
            inAst->failedToEvaluate = TRUE;
            return FALSE;
        }
        pushOutBuf();
        if (evalExpr(inAst->item.ast_eval.expression, NULL)) {
            exprTxt = popOutBuf();
            print(exprTxt, strlen(exprTxt));
            print(inAst->item.ast_eval.trailingBlanks, strlen(inAst->item.ast_eval.trailingBlanks));
            free(exprTxt);
        } else {
            exprTxt = popOutBuf();
            print("%%(", 3);
            print(exprTxt, strlen(exprTxt));
            print(")", 1);
            print(inAst->item.ast_eval.trailingBlanks, strlen(inAst->item.ast_eval.trailingBlanks));
            levelsOfEvaluation--;
            inAst->failedToEvaluate = TRUE;
            free(exprTxt);
            return FALSE;
        }
        levelsOfEvaluation--;
        return TRUE;
        break;

    case AST_REGION:
        badHead = FALSE;
        pushOutBuf();
        if (impInterpretAst(inAst->item.ast_region.beginId)) {
            beginLabel = popOutBuf();
        } else {
            /* Not possible to evaluate BEGIN label, log error and return */
            beginLabel = popOutBuf();
            impMyLog(&(inAst->item.ast_region.beginId->srcp), 212, sevERR, beginLabel);
            badHead = TRUE;
        }

        pushOutBuf();
        if (impInterpretAst(inAst->item.ast_region.endId)) {
            endLabel = popOutBuf();
        } else {
            /* Not possible to evaluate END label, log error and return */
            endLabel = popOutBuf();
            impMyLog(&(inAst->item.ast_region.endId->srcp), 212, sevERR, endLabel);
            badHead = TRUE;
        }

        if (strcmp(endLabel, beginLabel) != 0) {
            /* BEGIN and END labels does not correspond, log warning and use beginLabel */
            impMyLog(&(inAst->item.ast_region.endId->srcp), 203, sevWAR, endLabel);
        }

        /* Add parameters to local symbol table, exit if not possible to evaluate parameter name */
        list = impCopyAst(inAst->item.ast_region.params, TRUE);
        paramList = NULL;
        while (list) {
            tmp = list;
            list = list->next;
            tmp->next = NULL;
            pushOutBuf();
            if (!impInterpretAst(tmp)) {
                /* Not possible to evaluate parameter name, log error and return */
                param = popOutBuf();
                impMyLog(&(tmp->srcp), 212, sevERR, param);
                badHead = TRUE;
            } else
                param = popOutBuf();
            addText(param, &paramList);
            impFreeAst(tmp);
        }

        /* Add variables to local symbol table, exit if not possible to evaluate variable name */
        list = impCopyAst(inAst->item.ast_region.locals, TRUE);
        localList = NULL;
        while (list) {
            tmp = list;
            list = list->next;
            tmp->next = NULL;
            pushOutBuf();
            if (!impInterpretAst(tmp)) {
                /* Not possible to evaluate parameter name, log error and return */
                localVar = popOutBuf();
                impMyLog(&(tmp->srcp), 212, sevERR, localVar);
                badHead = TRUE;
            } else
                localVar = popOutBuf();
            addText(localVar, &localList);
            impFreeAst(tmp);
        }

        if (badHead) {
            inAst->failedToEvaluate = TRUE;
            free(beginLabel);
            free(endLabel);

            return FALSE;
        }

        impAddRegion(beginLabel, paramList, localList,
                     inAst->item.ast_region.statement);
        /* Free allocated memory */
        while (paramList) {
            TxtList tmp;
            tmp = paramList->next;
            free(paramList->txt);
            free(paramList);
            paramList = tmp;
        }
        while (localList) {
            TxtList tmp;
            tmp = localList->next;
            free(localList->txt);
            free(localList);
            localList = tmp;
        }
        free(endLabel);
        free(beginLabel);

        return TRUE;
        break;

    case AST_IF:
        switch (astBoolean(inAst->item.ast_if.condition)) {
        case IMP_TRUE:
            /* Condition evaluates to TRUE ==> interpret then-clause */
            impInterpretAst(inAst->item.ast_if.then_clause);
            return TRUE;
            break;
        case IMP_FALSE:
            if ((inAst->item.ast_if.else_clause) &&
                (inAst->item.ast_if.else_clause->type == AST_ELSIF))
                inAst->item.ast_if.else_clause->type = AST_IF;
            impInterpretAst(inAst->item.ast_if.else_clause);
            return TRUE;
            break;
        case IMP_UNKNOWN:
            prevIgnErr = ignoreErrors;
            ignoreErrors = TRUE;
            peBoolean(&(inAst->item.ast_if.condition), &cond);
            ignoreErrors = prevIgnErr;
            print("%%IF (", 6);
            print(cond, strlen(cond));
            print(")\n", 2);
            impInterpretAst(inAst->item.ast_if.then_clause);
            if ((inAst->item.ast_if.else_clause) &&
                (inAst->item.ast_if.else_clause->type != AST_ELSIF))
                print("%%ELSE\n", 7);
            impInterpretAst(inAst->item.ast_if.else_clause);
            print("%%ENDIF\n", 8);
            free(cond);
            return FALSE;
            break;
        }
        break;

    case AST_ELSIF:
        switch (astBoolean(inAst->item.ast_elsif.condition)) {
        case IMP_TRUE:
            /* Condition evaluates to TRUE ==> interpret then-clause */
            print("%%ELSE\n", 7);
            impInterpretAst(inAst->item.ast_elsif.then_clause);
            return TRUE;
            break;
        case IMP_FALSE:
            impInterpretAst(inAst->item.ast_elsif.else_clause);
            return TRUE;
            break;
        case IMP_UNKNOWN:
            prevIgnErr = ignoreErrors;
            ignoreErrors = TRUE;
            peBoolean(&(inAst->item.ast_elsif.condition), &cond);
            ignoreErrors = prevIgnErr;
            print("%%ELSIF (", 9);
            print(cond, strlen(cond));
            print(")\n", 2);
            impInterpretAst(inAst->item.ast_elsif.then_clause);
            if ((inAst->item.ast_if.else_clause) &&
                (inAst->item.ast_if.else_clause->type != AST_ELSIF))
                print("%%ELSE\n", 7);
            impInterpretAst(inAst->item.ast_elsif.else_clause);
            free(cond);
            return FALSE;
            break;
        }
        break;

    case AST_LOOP1:
    case AST_LOOP2:
        badHead = FALSE;
        pushOutBuf();
        if (!impInterpretAst(inAst->item.ast_loop.beginId)) {
            /* Not possible to evaluate BEGIN label, log error and return */
            beginLabel = popOutBuf();
            impMyLog(&(inAst->item.ast_loop.beginId->srcp), 212, sevERR, beginLabel);
            badHead = TRUE;
        } else
            beginLabel = popOutBuf();

        pushOutBuf();
        if (!impInterpretAst(inAst->item.ast_loop.endId)) {
            /* Not possible to evaluate END label, log error and return */
            endLabel = popOutBuf();
            impMyLog(&(inAst->item.ast_loop.endId->srcp), 212, sevERR, beginLabel);
            badHead = TRUE;
        } else
            endLabel = popOutBuf();

        if (strcmp(endLabel, beginLabel) != 0) {
            /* BEGIN and END labels does not correspond, log error and return */
            impMyLog(&(inAst->item.ast_loop.endId->srcp), 203, sevWAR, endLabel);
        }

        if (badHead) {
            inAst->failedToEvaluate = TRUE;
            free(endLabel);free(beginLabel);
            return FALSE;
        }

        if (inAst->type == AST_LOOP1) {
            /* For beginLabel = 1 TO value */
            pushOutBuf();
            if (evalExpr(inAst->item.ast_loop.expression, &exprAst)) {
                exprTxt = popOutBuf();
                if (getInteger(exprAst, &i)) {
                    char *tmpTxt;

                    for (loopVar = 1; loopVar <= i; loopVar++) {
                        free(exprTxt);
                        exprTxt = impItoa(loopVar);
                        if (!(tmpTxt = strdup(exprTxt)))
                            if (!(impAstGarb() && (tmpTxt = strdup(exprTxt))))
                                longjmp(jmpEnv, 1);
                        impNamePut(beginLabel, impAstNode(inAst->srcp, nulSrcp, nulSrcp,
                                                          AST_STRING, strlen(tmpTxt),
                                                          tmpTxt, NULL, NULL, NULL, NULL));
                        impInterpretAst(inAst->item.ast_loop.statement);
                    }
                    free(exprTxt);
                    exprTxt = impItoa(i+1);
                    if (!(tmpTxt = strdup(exprTxt)))
                        if (!(impAstGarb() && (tmpTxt = strdup(exprTxt))))
                            longjmp(jmpEnv, 1);
                    impNamePut(beginLabel, impAstNode(inAst->srcp, nulSrcp, nulSrcp,
                                                      AST_STRING, strlen(exprTxt), tmpTxt,
                                                      NULL, NULL, NULL, NULL));
                    free(exprTxt);
                    impFreeAst(exprAst);
                } else {
                    impFreeAst(exprAst);
                    impNameUndef(beginLabel);
                    print("%%LOOP(", 7);
                    print(beginLabel, strlen(beginLabel));
                    print("<=", 2);
                    print(exprTxt, strlen(exprTxt));
                    print(")\n", 2);
                    pushOutBuf();
                    impInterpretAst(inAst->item.ast_loop.statement);
                    stmTxt = popOutBuf();
                    print(stmTxt, strlen(stmTxt));
                    print("%%ENDLOOP(",10);
                    print(endLabel, strlen(endLabel));
                    print(")\n", 2);
                    impMyLog(&(inAst->srcp), 208, sevERR, exprTxt);
                    inAst->failedToEvaluate = TRUE;
                    free(exprTxt);
                    free(stmTxt);
                    free(endLabel);free(beginLabel);
                    return FALSE;
                }
            } else {
                impFreeAst(exprAst);
                impNameUndef(beginLabel);
                exprTxt = popOutBuf();
                print("%%LOOP(", 7);
                print(beginLabel, strlen(beginLabel));
                print("<=", 2);
                print(exprTxt, strlen(exprTxt));
                print(")\n", 2);
                pushOutBuf();
                impInterpretAst(inAst->item.ast_loop.statement);
                stmTxt = popOutBuf();
                print(stmTxt, strlen(stmTxt));
                print("%%ENDLOOP(",10);
                print(endLabel, strlen(endLabel));
                print(")\n", 2);
                free(exprTxt);
                free(stmTxt);
                free(endLabel);free(beginLabel);
                return FALSE;
            }
        } else { /* (ast->type == AST_LOOP2) */
            pushOutBuf();
            if (evalExpr(inAst->item.ast_loop.expression, &tmp)) {
                if ((inAst->item.ast_loop.expression->type == AST_GET) &&
                    (inAst->item.ast_loop.expression->item.ast_get.ident->type == AST_VALUE_LIST)) {
                    Ast tmp2;
                    tmp2 = tmp;
                    tmp = tmp->item.ast_valueList.valueList;
                    tmp2->item.ast_valueList.valueList = NULL;
                    impFreeAst(tmp2);
                }
                exprTxt = popOutBuf();
                tmp = revList(tmp);
                exprAst = tmp;
                while (exprAst) {
                    if (exprAst->failedToEvaluate) {
                        /* Not possible to evaluate loop expression */
                        impNameUndef(beginLabel);
                        print("%%LOOP(", 7);
                        print(beginLabel, strlen(beginLabel));
                        print(",", 1);
                        print(exprTxt, strlen(exprTxt));
                        print(")\n", 2);
                        pushOutBuf();
                        impInterpretAst(inAst->item.ast_loop.statement);
                        stmTxt = popOutBuf();
                        print(stmTxt, strlen(stmTxt));
                        print("%%ENDLOOP(",10);
                        print(endLabel, strlen(endLabel));
                        print(")\n", 2);
                        impNamePut(beginLabel, NULL);
                        inAst->failedToEvaluate = TRUE;
                        free(exprTxt);
                        free(stmTxt);
                        free(endLabel);free(beginLabel);
                        impFreeAst(tmp);
                        return FALSE;
                    }
                    exprAst = exprAst->next;
                }
                while (tmp) {
                    exprAst = tmp;
                    tmp = tmp->next;
                    exprAst->next = NULL;
                    impNamePut(beginLabel, exprAst);
                    impInterpretAst(inAst->item.ast_loop.statement);
                }
                impNamePut(beginLabel, NULL);
                free(exprTxt);
            } else {
                /* Not possible to evaluate loop expression */
                impFreeAst(tmp);
                impNameUndef(beginLabel);
                exprTxt = popOutBuf();
                print("%%LOOP(", 7);
                print(beginLabel, strlen(beginLabel));
                print(",", 1);
                print(exprTxt, strlen(exprTxt));
                print(")\n", 2);
                pushOutBuf();
                impInterpretAst(inAst->item.ast_loop.statement);
                stmTxt = popOutBuf();
                print(stmTxt, strlen(stmTxt));
                print("%%ENDLOOP(",10);
                print(endLabel, strlen(endLabel));
                print(")\n", 2);
                impNamePut(beginLabel, NULL);
                free(exprTxt);
                free(stmTxt);
                free(endLabel);free(beginLabel);
                return FALSE;
            }
        }
        free(beginLabel);
        free(endLabel);
        return TRUE;
        break;

    case AST_MESSAGE:
        pushOutput(stderr, FALSE);
        evalExpr(inAst->item.ast_message.expression, NULL);
        print("\n", 1);
        levelsOfEvaluation--;
        popOutput();
        return TRUE;
        break;

    case AST_EXIT:
        pushOutBuf();
        if (evalExpr(inAst->item.ast_exit.expression1, &exprAst)) {
            exprTxt = popOutBuf();
            if (getInteger(exprAst, &i)) {
                impFreeAst(exprAst);
                pushOutput(stderr, FALSE);
                evalExpr(inAst->item.ast_exit.expression2, NULL);
                print("\n", 1);
                levelsOfEvaluation--;
                popOutput();
                impExitCode = i;
                free(exprTxt);
                longjmp(jmpExit, 1);
            } else {
                impFreeAst(exprAst);
                print("%%EXIT(", 7);
                print(exprTxt, strlen(exprTxt));
                print(", ", 2);
                evalExpr(inAst->item.ast_exit.expression2, NULL);
                print(")\n", 2);
                impMyLog(&(inAst->srcp), 208, sevERR, exprTxt);
                free(exprTxt);
            }
        } else {
            exprTxt = popOutBuf();
            impFreeAst(exprAst);
            print("%%EXIT(", 7);
            print(exprTxt, strlen(exprTxt));
            print(", ", 2);
            evalExpr(inAst->item.ast_exit.expression2, NULL);
            print(")\n", 2);
            free(exprTxt);
        }
        return TRUE;
        break;

    case AST_INCLUDE:
        partEval = FALSE;
        pushOutBuf();
        setParams = (inAst->item.ast_include.expression != NULL);
        pushOutBuf();
        pushContext(LIST_CONTEXT);
        if (setParams) {
            evalFlg = evalExpr(inAst->item.ast_include.expression->item.ast_params.params, &tmp);
        } else {
            evalFlg = TRUE;
        }
        popContext();
        exprTxt = popOutBuf();
        if (impInterpretAst(inAst->item.ast_include.ident)) {
            /* Succeeded in evaluating id, get region */
            identTxt = popOutBuf();
            if ((region = impGetRegion(identTxt))) {
                if (evalFlg) {
                    impPushLocalSymtab(region->symtab);
                    if (setParams) {
                        /* Set parameters */
                        if ((regParams = region->params)) {
                            /* Set parameters and check that correct number of them are supplied */
                            list = revList(impCopyAst(tmp, TRUE));
                            while (regParams) {
                                if (!list) {
                                    impPopLocalSymtab();
                                    impMyLog(&(inAst->srcp), 213, sevERR, "");
                                    free(exprTxt);
                                    free(identTxt);
                                    impFreeAst(tmp);
                                    return FALSE;
                                }
                                exprAst = list;
                                list = list->next;
                                exprAst->next = NULL;
                                impNamePut(regParams->name, exprAst);
                                regParams = regParams->next;
                            }
                            if (list) {
                                impFreeAst(list);
                                impMyLog(&(inAst->srcp), 213, sevERR, "");
                                impPopLocalSymtab();
                                free(exprTxt);
                                impFreeAst(tmp);
                                free(identTxt);
                                return FALSE;
                            }
                        }
                        /* Set global region-variable */
                        impNamePut(region->name, tmp);
                    }
                    impInterpretAst(region->ast);
                    impPopLocalSymtab();
                } else {
                    if (setParams)
                        impFreeAst(tmp);
                    partEval = TRUE;
                }
            } else {
                /* Region does not exist */
                if (setParams)
                    impFreeAst(tmp);
                partEval = TRUE;
                if (impLastPass)
                    impMyLog(&(inAst->item.ast_include.ident->srcp), 205, sevWAR, identTxt);
            }
        } else  {
            if (setParams)
                impFreeAst(tmp);
            identTxt = popOutBuf();
            partEval = TRUE;
        }

        if (partEval) {
            /* Failed to evaluate identifier, use partial evaluation */
            print("%%INCLUDE(", 10);
            print(identTxt, strlen(identTxt));
            if (setParams) {
                print(" (", 2);
                print(exprTxt, strlen(exprTxt));
                print(")", 1);
            }
            print(")", 1);
            print(inAst->item.ast_include.trailingBlanks, strlen(inAst->item.ast_include.trailingBlanks));
            free(identTxt);
            free(exprTxt);
            return FALSE;
        }
        free(identTxt);
        free(exprTxt);
        return TRUE;

    case AST_PROCESS: {
        char *inTxt, *outTxt;
        Ast inFile = NULL;
        ImpBoolean inEval, outEval;
        FILE *fp;

        pushOutBuf();
        inEval = impInterpretAst(inAst->item.ast_process.infile);
        inTxt = popOutBuf();
        if (inEval && inTxt[0] == '\0') {
            impFreeAst(inAst->item.ast_process.infile);
            inAst->item.ast_process.infile = NULL;
        }
        pushOutBuf();
        outEval = impInterpretAst(inAst->item.ast_process.outfile);
        outTxt = popOutBuf();
        if (outEval && outTxt[0] == '\0') {
            impFreeAst(inAst->item.ast_process.outfile);
            inAst->item.ast_process.outfile = NULL;
        }

        if (!(inAst->item.ast_process.infile || inAst->item.ast_process.outfile)) {
            popOutput();
            pushOutput(stdout, FALSE);
        }
        if (inAst->item.ast_process.infile) {
            if (inEval) {
                ImpBoolean noExFlag = FALSE;
                /* Infile given, test if it does exist */
                switch (impAstGet(inTxt, inAst->srcp, &inFile)) {
                case NO_EXIST:
                    noExFlag = TRUE;
                case WRITE_OPEN:
                    if (impLastPass) {
                        if (noExFlag)
                            impMyLog(&(inAst->item.ast_process.infile->srcp), 201, sevWAR, inTxt);
                        else
                            impMyLog(&(inAst->item.ast_process.infile->srcp), 218, sevWAR, inTxt);
                    }
                case SYNTAX_ERROR:
                    if (!inAst->item.ast_process.outfile &&
                        !inAst->item.ast_process.silent) {
                        /* Infile does not exist, use partial evaluation */
                        print("%%INCLUDE(\"",11);
                        print(inTxt, strlen(inTxt));
                        print("\")",2);
                        print(inAst->item.ast_process.trailingBlanks, strlen(inAst->item.ast_process.trailingBlanks));
                        free(inTxt);
                        free(outTxt);
                        return FALSE;
                    } else {
                        /* Infile does not exist, use partial evaluation */
                        print("%%PROCESS(\"", 11);
                        print(inTxt, strlen(inTxt));
                        if (inAst->item.ast_process.outfile) {
                            /* Outfile given */
                            print("\", \"", 4);
                            print(outTxt, strlen(outTxt));
                        }
                        print("\")", 2);
                        print(inAst->item.ast_process.trailingBlanks, strlen(inAst->item.ast_process.trailingBlanks));
                        free(inTxt);
                        free(outTxt);
                        return FALSE;
                    }
                    break;
                case PARSED_OK:
                    break;
                }
            } else {
                /* Cannot evaluate infile name, use partial evaluation */
                print("%%PROCESS(\"", 11);
                print(inTxt, strlen(inTxt));
                if (inAst->item.ast_process.outfile) {
                    /* Outfile given */
                    print("\", \"", 4);
                    print(outTxt, strlen(outTxt));
                }
                print("\")", 2);
                print(inAst->item.ast_process.trailingBlanks, strlen(inAst->item.ast_process.trailingBlanks));
                if (impLastPass) {
                    impMyLog(&(inAst->item.ast_process.infile->srcp), 201, sevWAR, inTxt);
                }
                free(inTxt);
                free(outTxt);
                return FALSE;
            }
        }
        if (inAst->item.ast_process.outfile) {
            if (outEval) {
                /* Outfile given, test if it does exist */
                if ((fp = impWriteOpen(outTxt,&(inAst->item.ast_process.outfile->srcp))) == NULL) {
                    /* No it does not exist */
                    if (impLastPass) {
                        impMyLog(&(inAst->item.ast_process.outfile->srcp), 207, sevWAR, outTxt);
                    }
                    print("%%PROCESS(\"", 11);
                    print(inTxt, strlen(inTxt));
                    print("\", \"", 4);
                    print(outTxt, strlen(outTxt));
                    print("\")", 2);
                    print(inAst->item.ast_process.trailingBlanks, strlen(inAst->item.ast_process.trailingBlanks));
                    free(inTxt);
                    free(outTxt);
                    return FALSE;
                } else if (inAst->item.ast_process.infile) {
                    pushOutput(fp, TRUE);
                    impInterpretAst(inFile);
                    impAstRelease(inTxt, inFile);
                    popOutput();
                } else {
                    popOutput();
                    pushOutput(fp, TRUE);
                }
            } else {
                print("%%PROCESS(\"", 11);
                print(inTxt, strlen(inTxt));
                print("\", \"", 4);
                print(outTxt, strlen(outTxt));
                print("\")", 2);
                print(inAst->item.ast_process.trailingBlanks, strlen(inAst->item.ast_process.trailingBlanks));
                if (impLastPass) {
                    impMyLog(&(inAst->item.ast_process.outfile->srcp), 201, sevWAR, outTxt);
                }
                free(inTxt);
                free(outTxt);
                return FALSE;
            }
        } else if (inAst->item.ast_process.silent) {
            /* No outfile given, process this file silently */
            fp = NULL;
            pushOutput(fp, TRUE);
            impInterpretAst(inFile);
            impAstRelease(inTxt, inFile);
            popOutput();
        } else {
            impInterpretAst(inFile);
            impAstRelease(inTxt, inFile);
        }
        free(inTxt);
        free(outTxt);
        return TRUE;
        break;
    }  /* End case AST_PROCESS: */

    case AST_IDENT:
        pushOutBuf();
        evalFlg = impInterpretAst(inAst->item.ast_ident.ident);
        identTxt = popOutBuf();
        if (identTxt[0] != '\0') {
            print(identTxt, strlen(identTxt));
            inAst->failedToEvaluate = !evalFlg;
            free(identTxt);
            return evalFlg;
        } else {
            /* Identifier without a name not allowed */
            free(identTxt);
            print("<NULL>",6);
            impMyLog(&inAst->srcp, 214, sevERR, NULL);
            inAst->failedToEvaluate = TRUE;
            return FALSE;
        }
        break;

    case AST_INTEGER:
        print(inAst->item.ast_integer.text, (int)inAst->item.ast_integer.length);
        return TRUE;
        break;

    case AST__CONCAT:
        evalHead = impInterpretAst(inAst->item.ast_concat.head);
        evalTail = impInterpretAst(inAst->item.ast_concat.tail);
        if (evalHead && evalTail)
            return TRUE;
        else {
            inAst->failedToEvaluate = TRUE;
            return FALSE;
        }
        break;

    case AST_UNQUOTED_STRING:
    case AST_STRING:
        print(inAst->item.ast_string.text, (int)inAst->item.ast_string.length);
        return TRUE;
        break;

    case AST_VALUE_LIST: {
        char *tmpTxt;

        if (!(tmpTxt = strdup("{")))
            if (!(impAstGarb() && (tmpTxt = strdup("{"))))
                longjmp(jmpEnv, 1);
        print(tmpTxt ,1);
        free(tmpTxt);
        impInterpretAst(inAst->item.ast_valueList.valueList);
        if (!(tmpTxt = strdup("}")))
            if (!(impAstGarb() && (tmpTxt = strdup("}"))))
                longjmp(jmpEnv, 1);
        print(tmpTxt, 1);
        free(tmpTxt);
        return TRUE;
    } break;
    default:
        fprintf(stderr, "UNKNOWN NODE\n");
        inAst->failedToEvaluate = TRUE;
        return FALSE;
        break;
    }

    SYSERR("Reached end of non-void function");
    return IMP_UNKNOWN;
}

/*======================================================================
  impReportCnt - Interpret an IMP ast.

  impReportCnt() takes an abstract syntax tree produced by impParse() and
  tries to evaluate all nodes in it. If partial evaluation are used some-
  where in a subtree it returns an ast with as much as possible evaluated.
  If it succeeds to evaluate the whole tree it returns NULL.
*/
void impReportCnt(inAst)
     register Ast inAst;        /* Ast to report */
{
    if (inAst == NULL) {
        return;
    }

    if (inAst->next) {
        impReportCnt(inAst->next);
    }

    switch (inAst->type) {
    case AST_SEQ:
        impReportCnt(inAst->item.ast_seq.seq);
        break;

    case AST_TEXT:
    case AST_KEEP:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        break;


    case AST_ASSIGN:
    case AST_APPEND:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_assign.ident);
            impReportCnt(inAst->item.ast_assign.expression);
        }
        break;

    case AST_EVAL:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_eval.expression);
        }
        break;

    case AST_REGION:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_region.beginId);
            impReportCnt(inAst->item.ast_region.params);
            impReportCnt(inAst->item.ast_region.locals);
            impReportCnt(inAst->item.ast_region.statement);
            impReportCnt(inAst->item.ast_region.endId);
        }
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->endSrcp.line,inAst->endSrcp.col,inAst->evalCnt);
        break;

    case AST_IF:
    case AST_ELSIF:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_if.condition);
            impReportCnt(inAst->item.ast_if.then_clause);
            if ((inAst->item.ast_if.else_clause) &&
                (inAst->item.ast_if.else_clause->type != AST_ELSIF))
                if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
                    fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->elseSrcp.line,
                            inAst->elseSrcp.col,inAst->item.ast_if.else_clause->evalCnt);
            impReportCnt(inAst->item.ast_if.else_clause);
        }
        if (inAst->type == AST_IF)
            if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
                fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->endSrcp.line,
                        inAst->endSrcp.col,inAst->evalCnt);
        break;

    case AST_LOOP1:
    case AST_LOOP2:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_loop.beginId);
            impReportCnt(inAst->item.ast_loop.statement);
            impReportCnt(inAst->item.ast_loop.endId);
        }
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,
                    inAst->endSrcp.line,inAst->endSrcp.col,inAst->evalCnt);
        break;

    case AST_MESSAGE:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_message.expression);
        }
        break;

    case AST_INCLUDE:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_include.ident);
            impReportCnt(inAst->item.ast_include.expression);
        }
        break;

    case AST_PROCESS:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_process.infile);
            impReportCnt(inAst->item.ast_process.outfile);
        }
        break;

    case AST_IDENT:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_ident.ident);
        }
        break;

    case AST__CONCAT:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_concat.head);
            impReportCnt(inAst->item.ast_concat.tail);
        }
        break;

    case AST__OR:
    case AST__AND:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_or.condition1);
            impReportCnt(inAst->item.ast_or.condition2);
        }
        break;

    case AST__NOT:
        if (inAst->evalCnt != 0)
            impReportCnt(inAst->item.ast_not.condition);
        break;

    case AST__EQ:
    case AST__NEQ:
    case AST__GT:
    case AST__LT:
    case AST__GE:
    case AST__LE:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        break;

    case AST__DEFINED:
    case AST__RDEFINED:
    case AST__NONEMPTY:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0)
            impReportCnt(inAst->item.ast_defined.ident);
        break;

    case AST__IN:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_in.ident);
            impReportCnt(inAst->item.ast_in.expression);
        }
        break;

    case AST__PLUS:
    case AST__MINUS:
    case AST__BITAND:
    case AST__BITOR:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_plus.expression);
            impReportCnt(inAst->item.ast_plus.term);
        }
        break;

    case AST__TIMES:
    case AST__DIVID:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_times.term);
            impReportCnt(inAst->item.ast_times.factor);
        }
        break;

    case AST_GET:
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_get.ident);
            impReportCnt(inAst->item.ast_get.index);
        }
        break;

    case AST__NEG:
        if (inAst->evalCnt != 0)
            impReportCnt(inAst->item.ast_neg.factor);
        break;

    case AST_PARAMS:
        if (inAst->evalCnt != 0)
            impReportCnt(inAst->item.ast_params.params);
        break;

    case AST__SYSTEM:
        if ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_system.ident);
            impReportCnt(inAst->item.ast_system.cmd);
        }
        break;

    case AST__STRINGMATCH:
        if  ((inAst->srcp.line != 0) && (inAst->srcp.col != 0))
            fprintf(impCcFile, "%s:%d:%d:%d\n",impReportFile,inAst->srcp.line,inAst->srcp.col,inAst->evalCnt);
        if (inAst->evalCnt != 0) {
            impReportCnt(inAst->item.ast_stringmatch.expression);
            impReportCnt(inAst->item.ast_stringmatch.pattern);
        }
        break;

    case AST__STRLEN:
    case AST_EXIT:
    case AST__MOD:
        /* Don't know what to do about these... */
        SYSERR("Unexpected value in case()");
        break;

    case AST_INTEGER:
    case AST_UNQUOTED_STRING:
    case AST_STRING:
    case AST_VALUE_LIST:
        break;
    }
}

/******************************************************************************
 *
 *    P R I N T I N G   R O U T I N E S
 *    =================================
 *
 ******************************************************************************/
void impInitOutput(file, toBeClosed)
     FILE *file;
     ImpBoolean toBeClosed;
{
    outputStack = (OutputStack)malloc(sizeof(OutputStackItem));
    if (!outputStack) {
        if (!(impAstGarb() && (outputStack = (OutputStack)malloc(sizeof(OutputStackItem)))))
            longjmp(jmpEnv, 1);
    }
    outputStack->file = file;
    outputStack->toBeClosed = FALSE;
    outputStack->next = NULL;
}

static void pushOutput(file, toBeClosed)
     FILE *file;
     ImpBoolean toBeClosed;
{
    OutputStack new = (OutputStack)malloc(sizeof(OutputStackItem));
    if (!new) {
        if (!(impAstGarb() && (new = (OutputStack)malloc(sizeof(OutputStackItem)))))
            longjmp(jmpEnv, 1);
    }
    new->file = file;
    new->toBeClosed = toBeClosed;
    new->next = outputStack;
    outputStack = new;
}

static void popOutput()
{
    OutputStack old = outputStack;
    if (outputStack->toBeClosed && outputStack->file)
        impWriteClose(outputStack->file);
    outputStack = outputStack->next;
    free(old);
}

static void pushContext(context)
     Ctxt context;
{
    ContextStack new = (ContextStack)malloc(sizeof(ContextStackItem));
    if (!new) {
        if (!(impAstGarb() && (new = (ContextStack)malloc(sizeof(ContextStackItem)))))
            longjmp(jmpEnv, 1);
    }
    new->context = context;
    new->next = contextStack;
    contextStack = new;
}

static void popContext()
{
    ContextStack old = contextStack;
    contextStack = contextStack->next;
    free(old);
}

static void outputOff()
{
    BufferStack new = (BufferStack)malloc(sizeof(BufferStackItem));
    if (!new) {
        if (!(impAstGarb() && (new = (BufferStack)malloc(sizeof(BufferStackItem)))))
            longjmp(jmpEnv, 1);
    }

    new->internalBuffer = NULL;
    new->prevOutMedia = outMedia;
    new->next = bufferStack;
    bufferStack = new;
    outMedia = NO_OUTPUT;
}

static void outputOn()
{
    BufferStack top = bufferStack;
    bufferStack = bufferStack->next;
    outMedia = top->prevOutMedia;
    free(top);
}

static void pushOutBuf()
{
    BufferStack new = (BufferStack)malloc(sizeof(BufferStackItem));
    if (!new) {
        if (!(impAstGarb() && (new = (BufferStack)malloc(sizeof(BufferStackItem)))))
            longjmp(jmpEnv, 1);
    }

    new->internalBuffer = (char*)malloc(1);
    if (!new->internalBuffer) {
        if (!(impAstGarb() && (new->internalBuffer = (char*)malloc(1))))
            longjmp(jmpEnv, 1);
    }
    new->internalBuffer[0] = '\0';
    new->prevOutMedia = outMedia;
    new->next = bufferStack;
    bufferStack = new;
    outMedia = INTERNAL_BUF;
}

static char *appStr(to, from, length)
     char *to;
     char *from;
     int length;
{
    if (from != NULL) {
        if (to != NULL) {
            length = length + strlen(to);
            to = (char*) realloc(to, length + 1);
            if (!to) {
                longjmp(jmpEnv, 1);
            }
            strcat(to, from);
        } else {
            return from;
        }
    }
    return to;
}

static char *popOutBuf()
{
    char *result;
    BufferStack top = bufferStack;
    bufferStack = bufferStack->next;
    outMedia = top->prevOutMedia;
    result = top->internalBuffer;
    free(top);
    return result;
}
/*======================================================================
  print - Print a text to the current output media

  Prints a given number of bytes to the current media (current output
  file or internal textbuffer)
*/
static void print(ptr, size)
     char *ptr;
     int size;
{
    char *esc;
    int len;
    switch (outMedia) {
    case NO_OUTPUT:
        break;
    case OUTPUT_FILE:
        if (outputStack->file) {
            if (ignoreEscape)
                fwrite(ptr, size, 1, outputStack->file);
            else
                while (size > 0) {
                    esc = strchr(ptr, impEsc);
                    if (esc) {
                        len = esc-ptr;
                        fwrite(ptr, len, 1, outputStack->file);
                        ptr = esc+1;
                        fwrite(ptr, 1, 1, outputStack->file);
                        ptr++;
                        size = size-(len+2);
                    } else {
                        fwrite(ptr, size, 1, outputStack->file);
                        size = 0;
                    }
                }
        }
        break;
    case INTERNAL_BUF:
        bufferStack->internalBuffer = appStr(bufferStack->internalBuffer, ptr, size);
        break;
    }
}

static void reverse(s)
     char *s;
{
    int c, i, j;
    for (i = 0, j =strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char *impItoa(n)
     int n;
{
    char *s;
    int i, sign;
    s = (char*)malloc(128);             /* Just to make sure */
    if (!s) {
        if (!(impAstGarb() && (s = (char*)malloc(128))))
            longjmp(jmpEnv, 1);
    }
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return s;
}

static ImpBoolean isInteger(txt)
     char *txt;
{
    char i;
    if ((*txt == '-') || (*txt == '+'))
        ++txt;
    for (i = *txt; i; i = *(++txt))
        if (!isdigit(i))
            return(FALSE);
    return TRUE;
}

static void addText(txt, list)
     char *txt;
     TxtList *list;
{
    TxtList new = (TxtList)malloc(sizeof(TxtListItem));
    TxtList tmp = *list;

    if (!new) {
        if (!(impAstGarb() && (new = (TxtList)malloc(sizeof(TxtListItem)))))
            longjmp(jmpEnv, 1);
    }

    new->txt = txt;
    new->next = NULL;
    if (tmp) {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    } else
        *list = new;
}

static Ast revList(list)
     Ast list;
{
    Ast rev, next;
    if (list && list->next) {
        rev = list;
        list = list->next;
        rev->next = NULL;
        next = list->next;
        list->next = rev;
        rev = list;
        while (next) {
            list = next;
            next = next->next;
            list->next = rev;
            rev = list;
        }
        return rev;
    } else
        return list;
}
