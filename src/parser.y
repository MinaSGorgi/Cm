%code requires {
	#include "../src/AST.h"
}

%code {
	NBlock *g_programBlock; /* the top level root node of AST */
	
	extern int yylex();
	void yyerror(const char *s) { std::printf("Error: %s\n", s); }
}

/* Represents the different ways to access token data */
%union {
    int _int;
	std::string *_pstring;
	Node *_pnode;
	NBlock *_pblock;
	NExpression *_pexpression;
	NStatement *_pstatement;
	NIdentifier *_pidentifier;
	NVariableDeclaration *_pvarDeceleration;
}

/* Tokens definitions */
%token <_pstring> TIDENTIFIER TCHAR TINTEGER TDOUBLE
%token <_int> TPLUS TMINUS TMUL TDIV TMOD
%token <_int> TEQUAL TNOT_EQUAL TGREATER TLESS TGREATER_EGQUAL TLESS_EQUAL
%token <_int> TAND TOR TNOT
%token <_int> TASSIGN

/* Define the type of nonterminal symbols.
   The types refer to the %union declaration above.
 */
%type <_pblock> program statements
%type <_pidentifier> identifier
%type <_pexpression> expression numeric
%type <_pstatement> statement varDeceleration
%type <_int> comparison

/* Operators precedence */
%right TASSIGN
%left TOR
%left TAND
%left TEQUAL TNOT_EQUAL
%left TGREATER TLESS TGREATER_EGQUAL TLESS_EQUAL
%left TPLUS TMINUS
%left TMUL TDIV TMOD
%right TNOT

%start program

%%

program : statements { g_programBlock = $1; }
		;
		
statements : statement { $$ = new NBlock(); $$->statements.push_back($<_pstatement>1); }
	  	   | statements statement { $1->statements.push_back($<_pstatement>2); }
	  	   ;

statement : varDeceleration
	 	  | expression { $$ = new NExpressionStatement(*$1); }
     	  ;

varDeceleration : identifier identifier { $$ = new NVariableDeclaration(*$1, *$2); }
		 		| identifier identifier TASSIGN expression { $$ = new NVariableDeclaration(*$1, *$2, $4); }
		 		;

identifier : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
	  	   ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
		;
	
expression : numeric
	 	   | identifier { $<_pidentifier>$ = $1; }
		   | identifier TASSIGN expression { $$ = new NAssignment(*$<_pidentifier>1, *$3); }
           | expression TMUL expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
           | expression TDIV expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
           | expression TPLUS expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
           | expression TMINUS expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
 	       | expression comparison expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
	       ;

comparison : TEQUAL | TNOT_EQUAL | TGREATER | TLESS | TGREATER_EGQUAL | TLESS_EQUAL
		   ;

%%

int main(int argc, char **argv) {
	yyparse();
	return 0;
}