#include <fstream>
#include "../build/parser.hpp"
#include "../build/scanner.hpp"


int main(int argc, char **argv) {

    if(argc > 1) {
        ifstream file(argv[1]);
        string program((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        yy_scan_string(program.c_str());
        yyparse();
        file.close();
    } else {
        yyparse();
    }

    return 0;
} 