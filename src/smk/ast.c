#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "ast.h"
#include "char.h"
#include "common.h"
#include "name.h"
#include "lmprintf.h"
#include "smalloc.h"
#include "smkList.h"

static ASTItem astEOT_item;     /* Dummy */
static ASTItem astUNKNOWN_item; /* Dummy */

AST astEOT=&astEOT_item;
AST astUNKNOWN=&astUNKNOWN_item;

static AST astNode(char type, AST car, AST cdr)
{
    AST ast;

    ast=(AST)smalloc(sizeof(ASTItem));
    ast->type=type;
    ast->circular=0;
    ast->car=car;
    ast->cdr=cdr;
    return ast;
}

AST astLookahead(AST car, AST cdr)
{
    return astNode('/',car,cdr);
}

AST astSelect(AST car, AST cdr)
{
    return astNode('!',car,cdr);
}

AST astConcat(AST car, AST cdr)
{
    return astNode('.',car,cdr);
}

AST astClosure(AST car, int n, int m)
{
    if(n==0 && m<0)
        return astNode('*',car,NULL);
    else if(n==0 && m==0)
        return astClass("[]");
    else if(n==0 && m==1)
        return astNode('?',car,NULL);
    else if(n==0 && m>1)
        return astClosure(astClosure(car,0,1),m,m);
    else if(n==1 && m<0)
        return astNode('+',car,NULL);
    else if(n>1 && m<0)
        return astConcat(astClosure(car,n-1,n-1),astClosure(car,1,-1));
    else if(n==m)
        if(n==1) return car;
        else if(n&1) return astConcat(astClosure(astConcat(car,car),n>>1,n>>1),car);
        else return astClosure(astConcat(car,car),n>>1,n>>1);
    else
        return astConcat(astClosure(car,n,n),astClosure(astClosure(car,0,1),m-n,m-n));
}

AST astSequence(AST car, AST cdr)
{
    return astNode('-',car,cdr);
}

AST astString(char *string)
{
    short length;
    short n;
    AST ast;

    string=strdup(string);
    if((length=charString((unsigned char *)string))<0) { free(string); return NULL; }
    ast=astNode('c',(AST)((intptr_t)string[0]),(AST)((intptr_t)string[0]));
    for(n=1;n<length;n++)
        ast=astConcat(ast,astNode('c',(AST)((intptr_t)string[n]),(AST)((intptr_t)string[n])));
    free(string);
    return ast;
}

static AST astGenClass(char *class)
{
    short n;
    short min;
    short max;
    AST ast;

    ast=NULL;
    for(n=0;n<256;n++) {
        for(;n<256 && class[n]==0;n++);
        min=n;
        for(;n<256 && class[n]==1;n++);
        max=n-1;
        if(min>max)
            break;
        else if(ast)
            ast=astSelect(ast,astNode('c',(AST)((intptr_t)min),(AST)((intptr_t)max)));
        else
            ast=astNode('c',(AST)((intptr_t)min),(AST)((intptr_t)max));
    }
    return ast;
}

AST astClass(char *string)
{
    char *class;
    AST ast;

    if((class=charClass(string))==NULL) return NULL;
    ast=astGenClass(class);
    free(class);
    return ast;
}

AST astInverse(AST ast)
{
    if(ast)
        switch(ast->type) {
        case '/':
            return astLookahead(astInverse(ast->cdr),astInverse(ast->car));
        case '.':
            return astConcat(astInverse(ast->cdr),astInverse(ast->car));
        case '!':
            return astSelect(astInverse(ast->car),astInverse(ast->cdr));
        case '*':
            return astClosure(astInverse(ast->car),0,-1);
        case '+':
            return astClosure(astInverse(ast->car),1,-1);
        case '?':
            return astClosure(astInverse(ast->car),0,1);
        case '-':
            return astConcat(astInverse(ast->cdr),astClosure(astInverse(ast->car),0,-1));
        case 'c':
            return ast;
        case '#':
            return astNode('c',ast->car,ast->cdr);
        }
    return ast;
}

AST astCut()
{
    return astNode('#',(AST)NULL,(AST)NULL);
}

static void astSetClass(char *class, AST ast, char set)
{
    short n;

    if(ast)
        switch(ast->type) {
        case '!':
            astSetClass(class,ast->car,set);
            astSetClass(class,ast->cdr,set);
            break;
        case 'c':
            for(n=(intptr_t)(ast->car);n<=(intptr_t)(ast->cdr);n++) class[n]=set;
            break;
        }
}

AST astDiff(AST ast1, AST ast2)
{
    char class[256];

    memset(class,0,256);
    astSetClass(class,ast1,1);
    astSetClass(class,ast2,0);
    return astGenClass(class);
}

static void astDump_(int tab, AST ast)
{
    if(ast==NULL)
        printf("***ERROR***\n");
    else
        switch(ast->type) {
        case '/':
            printf("%*sLookahead\n",tab,"");
            astDump_(tab+3,ast->car);
            astDump_(tab+3,ast->cdr);
            break;
        case '!':
            printf("%*sSelection\n",tab,"");
            astDump_(tab+3,ast->car);
            astDump_(tab+3,ast->cdr);
            break;
        case '.':
            printf("%*sConcatenation\n",tab,"");
            astDump_(tab+3,ast->car);
            astDump_(tab+3,ast->cdr);
            break;
        case '*':
            printf("%*sClosure, *\n",tab,"");
            astDump_(tab+3,ast->car);
            break;
        case '+':
            printf("%*sClosure, +\n",tab,"");
            astDump_(tab+3,ast->car);
            break;
        case '?':
            printf("%*sClosure, ?\n",tab,"");
            astDump_(tab+3,ast->car);
            break;
        case '-':
            printf("%*sSequence\n",tab,"");
            astDump_(tab+3,ast->car);
            astDump_(tab+3,ast->cdr);
            break;
        case 'c':
            printf("%*s[",tab,"");
            printf("%p", (void *)ast->car);
            printf("-");
            printf("%p", (void *)ast->cdr);
            printf("]\n");
            break;
        case '@':
            printf("***UNDEFINED***\n");
            break;
        default:
            printf("***ERROR***\n");
            break;
        }
}

void astDump(AST ast)
{
    astDump_(8,ast);
}

void astPrint(AST ast)
{
    if(ast==NULL)
        ;
    else if(ast==astUNKNOWN)
        lmPrintf("_Unknown");
    else if(ast==astEOT)
        lmPrintf("_EndOfText");
    else
        switch(ast->type) {
        case '/':
            astPrint(ast->car);
            lmPrintf("\n\t\t\t\t/ ");
            astPrint(ast->cdr);
            break;
        case '!':
            astPrint(ast->car);
            lmPrintf("\n\t\t\t\t! ");
            astPrint(ast->cdr);
            break;
        case '.':
            if(astSequenceLength(ast)>0)
                lmPrintf("'%s'",astToName(ast));
            else {
                lmPrintf("(");
                astPrint(ast->car);
                lmPrintf(" ");
                astPrint(ast->cdr);
                lmPrintf(")");
            }
            break;
        case '*':
            lmPrintf("(");
            astPrint(ast->car);
            lmPrintf(") *");
            break;
        case '+':
            lmPrintf("(");
            astPrint(ast->car);
            lmPrintf(") +");
            break;
        case '?':
            lmPrintf("(");
            astPrint(ast->car);
            lmPrintf(") ?");
            break;
        case 'c':
            lmPrintf("[");
            lmPrintf((intptr_t)(ast->car)<' '||(intptr_t)(ast->car)>'~' ? "\\x%02X" : "%c", ast->car);
            if(ast->car!=ast->cdr) {
                lmPrintf("-");
                lmPrintf((intptr_t)(ast->cdr)<' '||(intptr_t)(ast->cdr)>'~' ? "\\x%02X" : "%c", ast->cdr);
            }
            lmPrintf("]");
            break;
        default:
            lmPrintf("<<UNDEFINED>>");
            break;
        }
}

int astSequenceLength(AST ast)
{
    int s1,s2;

    if(ast)
        switch(ast->type) {
        case 'c':
            return ast->car==ast->cdr ? 1 : 0;
        case '.':
            s1=astSequenceLength(ast->car);
            if(s1==0) return 0;
            s2=astSequenceLength(ast->cdr);
            return s2 ? s1+s2 : 0;
        default:
            return 0;
        }
    return 0;
}

static int astToSequence(char *buffer, AST ast)
{
    int s1,s2;

    if(ast)
        switch(ast->type) {
        case 'c':
            *buffer=(char)((intptr_t)ast->car);
            return ast->car==ast->cdr && (intptr_t)ast->car>=0 && (intptr_t)ast->car<=255 ? 1 : 0;
        case '.':
            s1=astToSequence(buffer,ast->car);
            if(s1==0) return 0;
            s2=astToSequence(buffer+s1,ast->cdr);
            return s2 ? s1+s2 : 0;
        default:
            return 0;
        }
    return 0;
}

Name astToName(AST ast)
{
    int len;

    len=astSequenceLength(ast);
    if(len) {
        char *buffer;
        Name name;

        buffer=(char *)smalloc(len+1);
        astToSequence(buffer,ast);
        buffer[len]=0;
        name=nameSearch(buffer);
        free(buffer);
        return name;
    }
    else
        return NULL;
}
