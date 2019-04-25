%{
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include "../include/AST.hpp"
    using namespace std;

    /* prototypes */
    OperationNode *opr(int oper, int nops, ...);
    int yylex(void);
    void yyerror(char const *s);
    int sym[26]; /* symbol table */
%}

%union {
    int iValue; /* integer value */
    char sIndex; /* symbol table index */
    Node *nPtr; /* node pointer */
    string *text; /* yytext */
};

%type <nPtr> stmt expr stmt_list
%type <text> binary_operation

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token <text> TADD TSUB TMUL TDIV TGE TLE TEQ TNE TLT TGT 
%token WHILE IF PRINT

%nonassoc IFX
%nonassoc ELSE
%left TGE TLE TEQ TNE TLT TGT 
%left TADD TSUB
%left TMUL TDIV
%nonassoc UMINUS

%%
program:
    function { exit(0); }
    ;

function:
    function stmt { $2->generateCode(); delete $2;}
    | /* NULL */
    ;

stmt:
    ';' { $$ = opr(';', 2, NULL, NULL); }
    | expr ';' { $$ = $1; }
    | PRINT expr ';' { $$ = opr(PRINT, 1, $2); }
    | VARIABLE '=' expr ';' { $$ = opr('=', 2, new IdentifierNode($1), $3); }
    | WHILE '(' expr ')' stmt { $$ = opr(WHILE, 2, $3, $5); }
    | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
    | IF '(' expr ')' stmt ELSE stmt
    { $$ = opr(IF, 3, $3, $5, $7); }
    | '{' stmt_list '}' { $$ = $2; }
    ;

stmt_list:
    stmt { $$ = $1; }
    | stmt_list stmt { $$ = opr(';', 2, $1, $2); }
    ;

expr:
    INTEGER { $$ = new ConstantNode($1); }
    | VARIABLE { $$ = new IdentifierNode($1); }
    | TSUB expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
    | expr binary_operation expr { $$ = new BinaryOperationNode($2, 2, $1, $3); }
    | '(' expr ')' { $$ = $2; }
    ;

binary_operation:
                TADD | TSUB | TMUL | TDIV | TGE | TLE | TEQ | TNE | TLT | TGT
                ;     
%%

OperationNode *opr(int oper, int nops, ...) {
    va_list ap;
    Node **operands = new Node*[nops];
    va_start(ap, nops);
    for (int i = 0; i < nops; i++)
       operands[i] = va_arg(ap, Node*);
    va_end(ap);
    return new OperationNode(oper, nops, operands);
}

void yyerror(char const *s) {
    printf("Error: %s\n", s);
}

int main(void) {
    yyparse();
    return 0;
} 