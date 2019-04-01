%{
    #include <string>

	extern int yylex();
	void yyerror(const char *s) { std::printf("Error: %s\n", s); }
%}

/* Represents the different ways to access token data */
%union {
    int _int;
	std::string *_pstring;
}

/* Tokens definitions */
%token <_pstring> TIDENTIFIER TCHAR TINTEGER TDOUBLE
%token <_int> TPLUS TMINUS TMUL TDIV TMOD
%token <_int> TEQUAL TNOT_EQUAL TGREATER TLESS TGREATER_EGQUAL TLESS_EQUAL
%token <_int> TAND TOR TNOT
%token <_int> TASSIGN

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

program : statements
        ;

statements : statement 
      	   | statements statement 
		   ;

statement : ;

%%

int main(int argc, char **argv) {
	yyparse();
	return 0;
}