%{
    #include <stdio.h>
    #include <string>
    #include "parser.hpp"

    #define STRING_TOKEN(t)  yylval._pstring = new std::string(yytext, yyleng); return t;
    #define INT_TOKEN(t)     yylval._int = t; return t;
%}

%option noyywrap

%%

[ \t\n]					        ;    /* Skip whitespaces */

[a-zA-Z_][a-zA-Z0-9_]*          STRING_TOKEN(TIDENTIFIER)
"'.'"                           STRING_TOKEN(TCHAR)
[0-9]+					        STRING_TOKEN(TINTEGER)
[0-9]+\.[0-9]* 			        STRING_TOKEN(TDOUBLE)

"+"				          		INT_TOKEN(TPLUS)
"-"		          				INT_TOKEN(TMINUS)
"*"		          				INT_TOKEN(TMUL)
"/"				          		INT_TOKEN(TDIV)
"%"				          		INT_TOKEN(TMOD)

"=="						    INT_TOKEN(TEQUAL)
"!="			          		INT_TOKEN(TNOT_EQUAL)
">"				          		INT_TOKEN(TGREATER)
"<"				          		INT_TOKEN(TLESS)
">="					        INT_TOKEN(TGREATER_EGQUAL)
"<="	          				INT_TOKEN(TLESS_EQUAL)

"&&"                            INT_TOKEN(TAND)
"||"                            INT_TOKEN(TOR)
"!"                             INT_TOKEN(TNOT)

"="                             INT_TOKEN(TASSIGN)

.                               printf("Unknown token: %s\n", yytext); yyterminate();

%%