#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pmkList.h"
#include "pwsGrm.h"

int vocMaxLn = 0;       /* Length of longest vocabulary name */

/*-----------------------------------------------------------------------------
 * insertSymbol - creates a new entry in the vocabulary table.
 *-----------------------------------------------------------------------------
 */
static int insertSymbol(symName)
    char *symName;      /* IN the symbol name to look up  */
                        /* RET the entry in vocabulary */
{
    sym_ref temp;

    vocCnt++;
    if (vocCnt == sym_max) {
        sym_max *= 2;
        vocabulary = (sym_ref *)realloc(vocabulary, sym_max * sizeof(sym_ref));
    }/*if*/
    temp = (sym_ref)malloc(sizeof(sym_rec));
    if (temp != NULL) {
        if (strlen(symName) > vocMaxLn)
            vocMaxLn = strlen(symName);
        temp->name = symName;
        temp->code = -1;
        temp->left = temp->right = 0;
        temp->symbol_typ = unknown_symb;
        vocabulary[vocCnt] = temp;
        return vocCnt;
    } else {
        pmkLog(NULL, 197, sevFAT, "");
    }/*if*/
    return 0;
}/*insertSymbol()*/

/*-----------------------------------------------------------------------------
 * initSymTab - Augments grammar and initializes the vocabulary.
 *              Note that init_gram must be called before this function.
 *-----------------------------------------------------------------------------
 */
void initSymTab()
{
    int i;
    sym_ref temp;

    /* Augment grammar
     */
    temp = (sym_ref)malloc(sizeof(sym_rec));
    if (temp != NULL) {
        temp->name = "ParserMaker";
        temp->code = 0;
        temp->left = temp->right = 0;
        temp->symbol_typ = nts_symb;
        temp->syminfo.firstp = 0;
        vocabulary[0] = temp;
    } else {
        pmkLog(NULL,197,sevFAT,"");
    }/*if*/

    vocCnt = -1;
    i = insertSymbol("Unknown");
    vocabulary[i]->code = 0;
    vocabulary[i]->symbol_typ = t_symb;
    vocabulary[i]->syminfo.ter_info.icost = 255;
    vocabulary[i]->syminfo.ter_info.dcost = 255;
    vocabulary[i]->syminfo.ter_info.psymb = NULL;
    vocabulary[i]->right = 1;
    i = insertSymbol("EndOfText");
    vocabulary[i]->code = 1;
    vocabulary[i]->symbol_typ = t_symb;
    vocabulary[i]->syminfo.ter_info.icost = 255;
    vocabulary[i]->syminfo.ter_info.dcost = 255;
    vocabulary[i]->syminfo.ter_info.psymb = NULL;
}/*initSymTab()*/


/*-----------------------------------------------------------------------------
 * lookup - look for a name in vocabulary. If not found it is inserted.
 *-----------------------------------------------------------------------------
 */
void lookup(symbol, class, ref, search)
    char *symbol;
    SET class;                  /* legal symbol types */
    int *ref;                   /* OUT Index in vocabulary */
    search_kind *search;        /* OUT Search result */
{
    register int i = 0;
    register int key;

    for (;;) {
        if ((key = strcmp(vocabulary[i]->name, symbol)) == 0) break;
        else if (key < 0) {
            if (vocabulary[i]->left) i = vocabulary[i]->left;
            else {
                vocabulary[i]->left = insertSymbol(symbol);
                i = vocabulary[i]->left;
                break;
            }/*if*/
        } else {
            if (vocabulary[i]->right) i = vocabulary[i]->right;
            else {
                vocabulary[i]->right = insertSymbol(symbol);
                i = vocabulary[i]->right;
                break;
            }/*if*/
        }/*if*/
    }/*for*/

    *ref = i;
    if (SetMem(class, vocabulary[i]->symbol_typ)) {
        /* Symbol exists */
        *search = found_search;
    } else if (vocabulary[i]->symbol_typ == unknown_symb) {
        *search = new_search;
    } else {
        *search = confl_search;
    }/*if*/
}/*lookup()*/
