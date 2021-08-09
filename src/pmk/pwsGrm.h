#ifndef _pwsGrm
#define _pwsGrm

#include "pws.h"
#include "pwSymSet.h"
#include "pmkSymTab.h"

/* Vocabulary
 * ----------
 */
typedef enum sym_kind { /* Classification of vocabulary symbols */
    t_symb,                 /* Terminal */
    nts_symb,               /* Non terminal */
    attr_symb,              /* Attributes */
    unknown_symb            /* Dont't know */
} sym_kind;

typedef enum attr_kind { /* Classification of attributes */
    t_attr,                 /* Terminal attribute */
    nts_attr,               /* Non terminal attribute */
    voc_attr,               /* Terminal & non terminal attribute */
    unk_attr                /* Unknown type */
} attr_kind;

typedef enum search_kind { /* Search result type in symbol table */
    new_search,
    found_search,
    confl_search
} search_kind;

typedef struct { /* Substructure in sym_rec below */
    int  icost;             /* Insert cost */
    int  dcost;             /* Delete cost */
    char *psymb;            /* Print symbol */
} ter_variant;

typedef union { /* Substructure in sym_rec below */
    ter_variant ter_info;
    int firstp;             /* First rule with LHS */
    attr_kind attr_class;   /* Attribute class */
} variants;

typedef struct { /* Structure in symbol table  */
    char *name;
    int code;               /* Internal code */
    int left, right;        /* Symbol table pointers */
    sym_kind symbol_typ;
    variants syminfo;
} sym_rec;

typedef sym_rec *sym_ref;


/* Error Recovery
 * --------------
 */
typedef struct {
    SymSet separators;
    SymSet fiducials;
    SymSet skips;
    int meta_cnt;
} recovery_rec;


/* Productions
 * -----------
 */

typedef struct {
    SymSet red;
    SymSet nored;
} modify_rec;

typedef modify_rec *modify_ref;

typedef struct {
    int start;          /* Start of rule in PVEC */
    int nxtls;          /* Next rule with same LHS */
    int rssz;           /* Number of symbols in RHS */
    int orig;           /* Original order */
    modify_ref modify;  /* Modifiers */
    int actno;          /* Action number */
    int orig_prod;      /* Production derived from */
} prod_rec;

typedef int *pvec_arr_typ;


/* Abstract syntax tree for productions
 * ------------------------------------
 */
typedef enum prod_elnode_kind {
    act_node_kind,      /* Semantic action */
    sym_node_kind,      /* Vocabulary symbol (inc. gen. nonterms) */
    mod_node_kind,      /* Production modifier */
    null_node_kind      /* Null rhs or alternative */
} prod_elnode_kind;

/* Type of nodes for which a new symbol node is substituted.
 */
typedef enum rplc_kind {
    rept_rplc,
    altrs_rplc,
    act_rplc,
    null_rplc
}  rplc_kind;

struct prod_elnode;

/* Element in an alternation list ( (a | b | c) ).
 */
typedef struct altr_lst {
    struct prod_elnode *altr;
    struct altr_lst *nxtalt;
} altr_lst;

typedef struct {
    int sym_ind ;                 /* Index in vocabulary */
    Boolean lhs_sym;              /* Lefthand side symbol */
    Boolean newnont;              /* Nonterm created by pws */
    rplc_kind rplc_info;          /* Replacement type if newnont */
    struct prod_elnode *rplc_seq; /* Replaced symbol or EBNF constructs seq. */
    altr_lst *altrs_seq;          /* Dito alternatives */
} sym_node_variant;

typedef struct {
    long act_start;     /* Start position in temporary file */
    long act_length;    /* Length */
    int ass_actno;      /* Number assigned to action after analysis. */
                        /* Number is unique for a group of actions. */
    TmkSrcp act_srcp;   /* Actions start in original file */
} act_node_variant;

/* Prod_elnode variants
 */
typedef union {
    sym_node_variant sym_node;
    act_node_variant act_node;
    modify_ref modify_node;
} node_cntnt;

/* Nodes in abstarct syntax tree
 */
typedef struct prod_elnode {
    node_cntnt node_info;
    struct prod_elnode *nxtnode;
    prod_elnode_kind node_kind;
} prod_elnode;

/* List cells for lists of righthand sides
 */
typedef struct rhs_node {
    prod_elnode *rhs;
    struct rhs_node *nxtrhs;
} rhs_node;


/* Production processing queue
 * ---------------------------
 */
typedef enum analysis_kind {
    rept_analysis,
    altrs_analysis,
    sem_act_analysis
} analysis_kind;


/* Actions
 * -------
 */

/* Semantic actions
 */
typedef struct SemActRepr {
    int prod;           /* The production index of the action */
    char *act;          /* The semantic action text */
    int line;           /* The start line of the semantic action */
} SemActRepr;

/* Temporary attribute reference structure.
 */
typedef struct {
    int ruleno;         /* Production */
    int actno;          /* Acion number */
    int actPos;         /* Attribute reference position in action */
    int voc_sym;        /* Attribute's Vocabulary symbol */
    int symins;         /* Symbols instance */
    int pos;            /* voc_sym index in the rule */
    int att;            /* Attribute */
    Boolean no_errm;    /* No error messages in final */
                        /* final verification. */
    TmkSrcp attref_srcp;
} attref_rec;

typedef attref_rec **attref_rec_arr;

/* Final attribute reference structure.
 */
typedef struct {
    int ruleno;         /* Production */
    int actPos;         /* Attribute reference position in action */
    int sym;            /* Attribute's Vocabulary symbol */
    int pos;            /* voc_sym index in the rule */
    int att;            /* Attribute */
} attref;

/* Type of legal attribute references (to outer EBNF constructs) in a
 * semantic action.
 */
typedef enum action_analysis_kind {
    rept_first,         /* 1OEBNF, 2OEBNF */
    rept_second,        /* 1OEBNF */
    alter,              /* 1OEBNF */
    top                 /* None */
} action_analysis_kind;


extern int orig_prod_max;   /* Max. number of EBNF productions */
extern int prod_max;        /* Max. number of BNF productions */
extern int sym_max;         /* Max. size of symbols */
extern int pvec_sz;         /* Size of production array */
extern int action_max;      /* Max. number of actions */
extern int att_max;         /* Size of internal attribute ref record */

/* Vocabulary
 * ----------
 */
extern sym_ref *vocabulary;     /* Vocabulary */
extern int vocCnt;              /* Number of symbols */
extern int vocMaxLn;            /* Length of longest vocabulary name */
extern int termCnt;             /* Number of terminals */
extern int nonTermCnt;          /* Number of non terminals */
extern int attrCnt;             /* Number of attributes */
extern int gramSymCnt;          /* Number of terminals + non terminals */
extern int goal_sym;            /* Goal symbol */
extern int tc_val;              /* Highest terminal code value */
extern SymSet on_right;         /* Set fo symbols occuring on rhs */
extern int gen_nonterms_cnt;    /* Number of generated non terminals */
extern Boolean term_sec_given;  /* Terminal section flag */
extern int icostMax;            /* Max insertion cost */
extern int dcostMax;            /* Max deletion cost */


/* Error Recovery
 * --------------
 */
extern recovery_rec recovery_spec; /* Improvments of the recovery */


/* Productions
 * -----------
 */
extern pvec_arr_typ global_pvec_tbl;  /* Storage for the grammar */
extern int global_pvec_ptr;           /* Grammar storage pointer */
extern prod_rec **global_prod_tbl;    /* Production data */
extern int global_prod_cnt;           /* Production data */

extern prod_elnode **orig_prod_tbl; /* Abstract syntax trees for productions */
extern int orig_prod_cnt;           /* Number of original Productions */
extern int rsszMax;                 /* Max size of right hand side */

/* Actions
 * -------
 */
extern SemActRepr *semAct;            /* Semantic actions */
extern int semActCnt;                 /* Number of semantic actions */
extern attref_rec_arr attref_storage; /* Storage for attribute references */
extern int attref_cnt;
extern attref *global_attref_sto;     /* Final attribute reference storage */
extern int global_attref_cnt;         /* Number of correct attribute references */

extern void init_grm();
extern void init_action_structs();
extern altr_lst *altr_lstAlloc();
extern prod_elnode *prod_elnodeAlloc();
extern rhs_node *rhs_nodeAlloc();
extern modify_ref modify_recAlloc();
extern char *gensym();
extern void analyze_rhss();

#endif
