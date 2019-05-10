%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include "../include/context.hpp"
    using namespace std;

    void yyerror(char const *s);
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

    NBlock *pBlock; 
    NExpression *pExpr;
    NStatement *pStmt;
};

%token <iValue> INTEGER DTINT DTDOUBLE DTVOID CONSTANT
%token <dValue> TDOUBLE 
%token <text> VARIABLE TNOT TADD TSUB TMUL TDIV TGE TLE TEQ TNE TLT TGT
%token WHILE FOR IF

%type <pBlock> stmt_list
%type <pStmt> simple_stmt complex_stmt stmt
%type <pExpr> expr

%nonassoc IFX
%nonassoc ELSE
%left TGE TLE TEQ TNE TLT TGT 
%left TADD TSUB
%left TMUL TDIV
%right TNOT

%%
program:
    function { gContext.deleteScope(); gContext.compile(); YYACCEPT; }
    ;

function:
    function stmt { $2->generateQuadruple(gContext); delete $2;}
    | /* NULL */
    ;

stmt:
    simple_stmt { $$ = $1; }
    | complex_stmt { $$ = $1; }
    ;

complex_stmt:
    WHILE '(' expr ')' '{' stmt_list '}' { $$ = new NWhileStatement($3, $6); }
    | FOR '(' simple_stmt simple_stmt simple_stmt ')' '{' stmt_list '}'
        { $$ = new NForStatement($3, $4, $5, $8); }
    | IF '(' expr ')' '{' stmt_list '}' %prec IFX { $$ = new NIfStatement($3, $6); }
    | IF '(' expr ')' '{' stmt_list '}' ELSE '{' stmt_list '}'
        { $$ = new NIfStatement($3, $6, $10); }
    ;

simple_stmt:
    ';' { $$ = new NExpressionStatement(NULL); }
    | expr ';' { $$ = new NExpressionStatement($1); }
    | VARIABLE '=' expr ';'
        { $$ = new NExpressionStatement(new NAssignment(new NVariable($1), $3)); }
    | DTINT VARIABLE ';' { $$ = new NVarDeclStatement(DTINT, false, $2, NULL); }
    | DTDOUBLE VARIABLE ';' { $$ = new NVarDeclStatement(DTDOUBLE, false, $2, NULL); }
    | CONSTANT DTINT VARIABLE '=' expr ';' { $$ = new NVarDeclStatement(DTINT, true, $3, $5); }
    | CONSTANT DTDOUBLE VARIABLE '=' expr ';' 
        { $$ = new NVarDeclStatement(DTDOUBLE, true, $3, $5); }
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
    | TNOT expr { $$ = new NUnaryOperation($1, $2); }
    | '(' expr ')' { $$ = $2; }
    ;
%%

void yyerror(char const *s) {
    printf("Unexpected token: %s\n", s);
    exit(0);
}