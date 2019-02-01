/*
 * AUTHOR : Otto Strukelj
 * CREATED: 1991-09-18
 */

#ifndef _ast_h_
#define _ast_h_
#include "impCommon.h"
#include "impMacro.h"

#define MAX_LEVELS 50
extern char *impReportFile;

extern TmSrcp nulSrcp;

typedef enum ParseResult {
  PARSED_OK,
  SYNTAX_ERROR,
  WRITE_OPEN,
  NO_EXIST
} ParseResult;

typedef enum Boolean {
  FALSE = 0,
  TRUE = 1
  } Boolean;

typedef enum {
  /* Statement nodes */
  AST_SEQ,
  AST_TEXT,
  AST_KEEP,
  AST_ASSIGN,
  AST_APPEND,
  AST_EVAL,
  AST_REGION,
  AST_IF,
  AST_ELSIF,
  AST_LOOP1,
  AST_LOOP2,
  AST_MESSAGE,  
  /* Condition nodes */
  AST__OR,
  AST__AND,
  AST__NOT,
  AST__EQ,
  AST__NEQ,
  AST__GT,
  AST__LT,
  AST__GE,
  AST__LE,
  AST__DEFINED,
  AST__RDEFINED,
  AST__NONEMPTY,
  AST__IN,
  AST__SYSTEM, 
  AST__STRINGMATCH,
  /* Expression nodes */
  AST__PLUS,
  AST__MINUS,
  AST__BITAND,
  AST__BITOR,
  AST__TIMES,
  AST__DIVID,
  AST__MOD,
  AST__STRLEN,
  /* Not yet updated nodes */
  AST_INCLUDE,
  AST_PROCESS,
  AST_EXIT,
  AST_GET,
  AST__NEG,
  AST__CONCAT,
  AST_INTEGER,
  AST_IDENT,
  AST_STRING,
  AST_UNQUOTED_STRING,
  AST_VALUE_LIST,
  /* Miscellaneous nodes */
  AST_PARAMS
} AstType;

typedef struct InputFileListItem *InputFileList;
typedef struct AstItem *Ast;

/*================================ Statement nodes ==================================*/
typedef struct Ast_SeqItem *Ast_Seq;
typedef struct Ast_SeqItem {
  Ast seq;			/* Sequence of nodes */
} Ast_SeqItem;

typedef struct Ast_TextItem *Ast_Text;
typedef struct Ast_TextItem {
  char *text;			/* Character string */
  int length;			/* Length of text */
} Ast_TextItem;

typedef struct Ast_KeepItem *Ast_Keep;
typedef struct Ast_KeepItem {
  char *text;			/* Character string */
  int length;			/* Length of text */
} Ast_KeepItem;

typedef struct Ast_AssignItem *Ast_Assign;
typedef struct Ast_AssignItem {
  Ast ident;			/* Identifier to assign a value list */
  Ast expression;		/* Value list to assign ident */
} Ast_AssignItem;

typedef struct Ast_AppendItem *Ast_Append;
typedef struct Ast_AppendItem {
  Ast ident;			/* Identifier to assign a value list */
  Ast expression;		/* Value list to assign ident */
} Ast_AppendItem;

typedef struct Ast_EvalItem *Ast_Eval;
typedef struct Ast_EvalItem {
  Ast expression;		/* Expression to evaluate */
  char *trailingBlanks;		/* Text string containing trailing blanks */
} Ast_EvalItem;

typedef struct Ast_RegionItem *Ast_Region;
typedef struct Ast_RegionItem {
  Ast beginId;			/* Identifier at BEGIN */
  Ast params;			/* Parameters */
  Ast locals;			/* Local variables */
  Ast statement;		/* Statements inside region */
  Ast endId;			/* Identifier at END */
} Ast_RegionItem;

typedef struct Ast_IfItem *Ast_If;
typedef struct Ast_IfItem {
  Ast condition;		/* Boolean condition */
  Ast then_clause;		/* Statements in THEN-clause */
  Ast else_clause;		/* Statements in ELSE-clause (could be %%ELSIF) */
} Ast_IfItem;

typedef struct Ast_ElsifItem *Ast_Elsif;
typedef struct Ast_ElsifItem {
  Ast condition;		/* Boolean condition */
  Ast then_clause;		/* Statements in THEN-clause */
  Ast else_clause;		/* Statements in ELSE-clause (could be %%ELSIF) */
} Ast_ElsifItem;

typedef struct Ast_LoopItem *Ast_Loop;
typedef struct Ast_LoopItem {
  Ast beginId;			/* Identifier at BEGIN */
  Ast expression;		/* Loop expression */
  Ast statement;		/* Statement inside loop */
  Ast endId;			/* Identifier at END */
} Ast_LoopItem;

typedef struct Ast_MessageItem *Ast_Message;
typedef struct Ast_MessageItem {
  Ast expression;		/* Expression to print on stderr */
} Ast_MessageItem;

typedef struct Ast_ExitItem *Ast_Exit;
typedef struct Ast_ExitItem {
  Ast expression1;		/* Expression to use as arg to exit() */
  Ast expression2;		/* Expression to print on stderr */
} Ast_ExitItem;

/*================================ Condition nodes ==================================*/
typedef struct Ast_OrItem *Ast_Or;
typedef struct Ast_OrItem {
  Ast condition1;
  Ast condition2;
} Ast_OrItem;

typedef struct Ast_AndItem *Ast_And;
typedef struct Ast_AndItem {
  Ast condition1;
  Ast condition2;
} Ast_AndItem;

typedef struct Ast_NotItem *Ast_Not;
typedef struct Ast_NotItem {
  Ast condition;
} Ast_NotItem;

typedef struct Ast_EqItem *Ast_Eq;
typedef struct Ast_EqItem {
  Ast expression1;
  Ast expression2;
} Ast_EqItem;

typedef struct Ast_NeqItem *Ast_Neq;
typedef struct Ast_NeqItem {
  Ast expression1;
  Ast expression2;
} Ast_NeqItem;

typedef struct Ast_GtItem *Ast_Gt;
typedef struct Ast_GtItem {
  Ast expression1;
  Ast expression2;
} Ast_GtItem;

typedef struct Ast_LtItem *Ast_Lt;
typedef struct Ast_LtItem {
  Ast expression1;
  Ast expression2;
} Ast_LtItem;

typedef struct Ast_GeItem *Ast_Ge;
typedef struct Ast_GeItem {
  Ast expression1;
  Ast expression2;
} Ast_GeItem;

typedef struct Ast_LeItem *Ast_Le;
typedef struct Ast_LeItem {
  Ast expression1;
  Ast expression2;
} Ast_LeItem;

typedef struct Ast_DefinedItem *Ast_Defined;
typedef struct Ast_DefinedItem {
  Ast ident;
} Ast_DefinedItem;

typedef struct Ast_NonemptyItem *Ast_Nonempty;
typedef struct Ast_NonemptyItem {
  Ast ident;
} Ast_NonemptyItem;

typedef struct Ast_InItem *Ast_In;
typedef struct Ast_InItem {
  Ast ident;
  Ast expression;
} Ast_InItem;

typedef struct Ast_SystemItem *Ast_System;
typedef struct Ast_SystemItem {
  ImpBoolean evaluatedOK;
  Ast ident;
  Ast cmd;
} Ast_SystemItem;

typedef struct Ast_StringmatchItem *Ast_Stringmatch;
typedef struct Ast_StringmatchItem {
  ImpBoolean evaluatedOK;
  Ast expression;		
  Ast pattern;
  Ast position;  		
} Ast_StringmatchItem;

/*================================ Expression nodes =================================*/
typedef struct Ast_PlusItem *Ast_Plus;
typedef struct Ast_PlusItem {
  Ast expression;
  Ast term;
} Ast_PlusItem;

typedef struct Ast_MinusItem *Ast_Minus;
typedef struct Ast_MinusItem {
  Ast expression;
  Ast term;
} Ast_MinusItem;

typedef struct Ast_BitAndItem *Ast_BitAnd;
typedef struct Ast_BitAndItem {
  Ast expression;
  Ast term;
} Ast_BitAndItem;

typedef struct Ast_BitOrItem *Ast_BitOr;
typedef struct Ast_BitOrItem {
  Ast expression;
  Ast term;
} Ast_BitOrItem;

typedef struct Ast_TimesItem *Ast_Times;
typedef struct Ast_TimesItem {
  Ast term;
  Ast factor;
} Ast_TimesItem;

typedef struct Ast_DividItem *Ast_Divid;
typedef struct Ast_DividItem {
  Ast term;
  Ast factor;
} Ast_DividItem;

typedef struct Ast_ModItem *Ast_Mod;
typedef struct Ast_ModItem {
  Ast term;
  Ast factor;
} Ast_ModItem;

typedef struct Ast_StrlenItem *Ast_Strlen;
typedef struct Ast_StrlenItem {
  Ast expression;
} Ast_StrlenItem;

/*================================ Not yet implemented nodes ========================*/
typedef struct Ast_IncludeItem *Ast_Include;
typedef struct Ast_IncludeItem {
  Ast ident;			/* Region identifier */
  Ast expression;		/* Parameter values */
  char *trailingBlanks;		/* Text string containing trailing blanks */
} Ast_IncludeItem;

typedef struct Ast_ProcessItem *Ast_Process;
typedef struct Ast_ProcessItem {
  Ast infile;			/* Input file name ast */
  Ast outfile;			/* Output file name ast */
  ImpBoolean silent;		/* Process file silently */
  char *trailingBlanks;		/* Text string containing trailing blanks */
} Ast_ProcessItem;

typedef struct Ast_GetItem *Ast_Get;
typedef struct Ast_GetItem {
  Ast ident;
  Ast index;
} Ast_GetItem;

typedef struct Ast_ConcatItem *Ast_Concat;
typedef struct Ast_ConcatItem {
  AstType type;
  Ast head;
  Ast tail;
} Ast_ConcatItem;

typedef struct Ast_NegItem *Ast_Neg;
typedef struct Ast_NegItem {
  Ast factor;
} Ast_NegItem;

typedef struct Ast_IntegerItem *Ast_Integer;
typedef struct Ast_IntegerItem {
  char *text;
  int length;
} Ast_IntegerItem;

typedef struct Ast_StringItem *Ast_String;
typedef struct Ast_StringItem {
  char *text;
  int length;
} Ast_StringItem;

typedef struct Ast_IdentItem *Ast_Ident;
typedef struct Ast_IdentItem {
  Ast ident;
} Ast_IdentItem;

typedef struct Ast_ValueListItem *Ast_ValueList;
typedef struct Ast_ValueListItem {
  Ast valueList;
} Ast_ValueListItem;

typedef struct Ast_ParamsItem *Ast_Params;
typedef struct Ast_ParamsItem {
  Ast params;
} Ast_ParamsItem;

typedef struct AstItem {
  TmSrcp srcp;
  TmSrcp endSrcp;
  TmSrcp elseSrcp;
  ImpBoolean failedToEvaluate;
  AstType type;
  Ast next;
  int evalCnt;
  union {
    /* Statements */
    Ast_SeqItem        ast_seq;
    Ast_TextItem       ast_text;
    Ast_KeepItem       ast_keep;
    Ast_AssignItem     ast_assign;
    Ast_AppendItem     ast_append;
    Ast_EvalItem       ast_eval;
    Ast_RegionItem     ast_region;
    Ast_IfItem         ast_if;
    Ast_ElsifItem      ast_elsif;
    Ast_LoopItem       ast_loop;
    Ast_MessageItem    ast_message; 
    Ast_ExitItem       ast_exit;
    /* Conditions */
    Ast_OrItem         ast_or;
    Ast_AndItem        ast_and;
    Ast_NotItem        ast_not;
    Ast_EqItem         ast_eq;
    Ast_NeqItem        ast_neq;
    Ast_GtItem         ast_gt;
    Ast_LtItem         ast_lt;
    Ast_GeItem         ast_ge;
    Ast_LeItem         ast_le;
    Ast_DefinedItem    ast_defined;
    Ast_NonemptyItem   ast_nonempty;
    Ast_InItem         ast_in;
    Ast_SystemItem     ast_system;
    Ast_StringmatchItem  ast_stringmatch;   
    /* Expressions */
    Ast_PlusItem       ast_plus;
    Ast_MinusItem      ast_minus;
    Ast_BitAndItem     ast_bitand;
    Ast_BitOrItem      ast_bitor;
    Ast_TimesItem      ast_times;
    Ast_DividItem      ast_divid;
    Ast_ModItem        ast_mod;
    Ast_StrlenItem     ast_strlen;

    /* Not yet implemented */
    Ast_IncludeItem    ast_include;
    Ast_ProcessItem    ast_process;
    Ast_GetItem        ast_get;
    Ast_ConcatItem     ast_concat;
    Ast_NegItem        ast_neg;
    Ast_IntegerItem    ast_integer;
    Ast_StringItem     ast_string;
    Ast_IdentItem      ast_ident;
    Ast_ValueListItem  ast_valueList;
    Ast_ParamsItem     ast_params;
  } item;
} AstItem;

typedef enum {
  ASTVALUE_UNDEF        =0,
  ASTVALUE_INTEGER      =1,
  ASTVALUE_STRING       =2,
  ASTVALUE_IDENTIFIER   =4,
  ASTVALUE_SVAL         =6     /* STRING+IDENTIFIER */
} AstValueType;

typedef struct AstValueItem *AstValue;
typedef struct AstValueItem {
  AstValueType type;
  union {
    double fval;
    long ival;
    char *sval;
  } a;
} AstValueItem;

extern Ast impAstRoot;

typedef struct SrcpListItem *SrcpList;
typedef struct SrcpListItem {
  TmSrcp srcp;
  SrcpList next;
} SrcpListItem;

typedef struct InputFileListItem {
  SrcpList pSrcp;
  char* fileName;
  Ast astroot;			/* Ast for this input file */
  ImpBoolean processed;
  int noProcStm;
  InputFileList next;
} InputFileListItem;

typedef struct TxtListItem *TxtList;
typedef struct TxtListItem {
  char *txt;
  TxtList next;
} TxtListItem;

extern InputFileList firstFile;
extern InputFileList inputFiles;
extern InputFileList lastInputFile;
/* Exported routines */
extern Ast impAstNode();
extern void impFreeAst();
extern Ast impCopyAst(Ast old, ImpBoolean copyTail);
extern ImpBoolean impInterpretAst();
extern void impReportCnt();
extern void impInitOutput();
extern char *impItoa();
extern void impResetSev();
extern void impMyLog();
#endif
