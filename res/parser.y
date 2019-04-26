%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include "../include/context.hpp"
    using namespace std;

    void yyerror(char const *s);
    int sym[26]; /* symbol table */
    Context gContext;
%}

%code requires {
    #include "../include/AST.hpp"

    int yylex(void);
}

%union {
    int iValue; /* integer value */
    double dValue; /* double value */
    string *text; /* yytext */

    Node *pNode;
    NBlock *pBlock; 
    NExpression *pExpr;
    NStatement *pStmt;
    NWhileStatement *pWhile;
    NIfStatement *pIf;
};

%token <iValue> INTEGER
%token <dValue> TDOUBLE 
%token <text> VARIABLE TADD TSUB TMUL TDIV TGE TLE TEQ TNE TLT TGT
%token WHILE IF

%type <pBlock> stmt_list
%type <pStmt> stmt
%type <pExpr> expr

%nonassoc IFX
%nonassoc ELSE
%left TGE TLE TEQ TNE TLT TGT 
%left TADD TSUB
%left TMUL TDIV
%nonassoc UMINUS

%%
program:
    function { YYACCEPT; }
    ;

function:
    function stmt { $2->generateCode(gContext); delete $2;}
    | /* NULL */
    ;

stmt:
    ';' { $$ = new NExpressionStatement(NULL); }
    | expr ';' { $$ = new NExpressionStatement($1); }
    | VARIABLE '=' expr ';'
        { $$ = new NExpressionStatement(new NAssignment(new NVariable($1), $3)); }
    | WHILE '(' expr ')' '{' stmt_list '}' { $$ = new NWhileStatement($3, $6); }
    | IF '(' expr ')' '{' stmt_list '}' %prec IFX { $$ = new NIfStatement($3, $6); }
    | IF '(' expr ')' '{' stmt_list '}' ELSE '{' stmt_list '}'
        { $$ = new NIfStatement($3, $6, $10); }
    ;

stmt_list:
    stmt { $$ = new NBlock($1); }
    | stmt_list stmt { $1->statements.push_back($<pStmt>2); }
    ;

expr:
    INTEGER { $$ = new NInteger($1); }
    | TDOUBLE { $$ = new NDouble($1); }
    | VARIABLE { $$ = new NVariable($1); }
    | expr TADD expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TSUB expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TMUL expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TDIV expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TGE expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TLE expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TEQ expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TNE expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TLT expr { $$ = new NBinaryOperation($2, $1, $3); }
    | expr TGT expr { $$ = new NBinaryOperation($2, $1, $3); }
    | '(' expr ')' { $$ = $2; }
    ;
%%

void yyerror(char const *s) {
    printf("Error: %s\n", s);
}