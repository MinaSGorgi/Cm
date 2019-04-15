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
	NVariableDeclaration *_pvar_deceleration;
	std::vector<NVariableDeclaration*> *_pvardecl_vec;
	std::vector<NExpression*> *_pexpr_vec;
}

/* Tokens definitions */
%token <_pstring> TIDENTIFIER TCHAR TINTEGER TDOUBLE
%token <_int> TLPAREN TRPAREN TLBRACE TRBRACE
%token <_int> TRETURN TCOMMA
%token <_int> TPLUS TMINUS TMUL TDIV TMOD
%token <_int> TEQUAL TNOT_EQUAL TGREATER TLESS TGREATER_EGQUAL TLESS_EQUAL
%token <_int> TAND TOR TNOT
%token <_int> TASSIGN

/* Define the type of nonterminal symbols.
   The types refer to the %union declaration above.
 */
%type <_pblock> program statements block
%type <_pstatement> statement var_deceleration func_deceleration
%type <_pvardecl_vec> funcdecl_args
%type <_pexpr_vec> call_args
%type <_pexpression> expression numeric
%type <_pidentifier> identifier
%type <_int> binary_operation

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

statement : var_deceleration | func_deceleration
	 	  | expression { $$ = new NExpressionStatement(*$1); }
		  | TRETURN expression { $$ = new NReturnStatement(*$2); }
     	  ;

block : TLBRACE statements TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); }
	  ;

var_deceleration : identifier identifier { $$ = new NVariableDeclaration(*$1, *$2); }
		 		 | identifier identifier TASSIGN expression { $$ = new NVariableDeclaration(*$1, *$2, $4); }
		 		 ;

func_deceleration : identifier identifier TLPAREN funcdecl_args TRPAREN block 
					{ $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
		  		  ;

funcdecl_args : /*blank*/  { $$ = new NVariableList(); }
		  	  | var_deceleration { $$ = new NVariableList(); $$->push_back($<_pvar_deceleration>1); }
		  	  | funcdecl_args TCOMMA var_deceleration { $1->push_back($<_pvar_deceleration>3); }
		      ;

identifier : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
	  	   ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
		| TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
		;

expression : identifier TASSIGN expression { $$ = new NAssignment(*$<_pidentifier>1, *$3); }
	 	   | identifier TLPAREN call_args TRPAREN { $$ = new NFunctionCall(*$1, *$3); delete $3; }
	 	   | identifier { $<_pidentifier>$ = $1; }
	 	   | numeric
           | expression binary_operation expression { $$ = new NBinaryOperator(*$1, $2, *$3); }
     	   | TLPAREN expression TRPAREN { $$ = $2; }
	 	   ;

call_args : /*blank*/  { $$ = new NExpressionList(); }
		  | expression { $$ = new NExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expression  { $1->push_back($3); }
		  ;

binary_operation : TPLUS | TMINUS | TMUL | TDIV | TMOD
				 | TEQUAL | TNOT_EQUAL | TGREATER | TLESS | TGREATER_EGQUAL | TLESS_EQUAL
				 | TAND | TOR
				 ;
%%

int main(int argc, char **argv) {
	yyparse();
	return 0;
}