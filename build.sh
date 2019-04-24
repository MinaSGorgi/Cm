rm lex.yy.c scanner.tab.c scanner.tab.h
bison -d scanner.y
flex parser.l
gcc lex.yy.c scanner.tab.c compiler.c -o Cm