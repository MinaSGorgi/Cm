%{
    #include <stdlib.h>
    #include "../include/AST.hpp"
    #include "parser.hpp"

    #define SAVE_TOKEN(member, value, token) { yylval.member = value; return token; }
    #define SAVE_STRING_TOKEN(member, value, token) { yylval.member = value; return token; }

    void yyerror(char const *);
%}

%%
"while"                     return WHILE;
"for"                       return FOR;
"if"                        return IF;
"else"                      return ELSE;
"const"                     return CONSTANT;
"int"                       return DTINT;
"double"                    return DTDOUBLE;

[a-zA-Z_][a-zA-Z0-9_]*      SAVE_TOKEN(text, new string(yytext), VARIABLE)
[0-9]+"."[0-9]*             SAVE_TOKEN(dValue, atof(yytext), TDOUBLE)
[0-9]+                      SAVE_TOKEN(iValue, atoi(yytext), INTEGER)
[=();{}.]                   return *yytext;

"!"                         SAVE_TOKEN(text, new string("NOT"), TNOT)
"-"                         SAVE_TOKEN(text, new string("SUB"), TSUB)
"+"                         SAVE_TOKEN(text, new string("ADD"), TADD)
"*"                         SAVE_TOKEN(text, new string("MUL"), TMUL)
"/"                         SAVE_TOKEN(text, new string("DIV"), TDIV)
"<"                         SAVE_TOKEN(text, new string("CLT"), TLT)
">"                         SAVE_TOKEN(text, new string("CGT"), TGT)
">="                        SAVE_TOKEN(text, new string("CGE"), TGE)
"<="                        SAVE_TOKEN(text, new string("CLE"), TLE)
"=="                        SAVE_TOKEN(text, new string("CEQ"), TEQ)
"!="                        SAVE_TOKEN(text, new string("CNE"), TNE)

[ \t\n]+                    ; /* ignore whitespace */
.                           yyerror((char *)"Unknown character");
%%

int yywrap(void) {
    return 1;
}