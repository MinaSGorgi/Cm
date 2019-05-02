#include <fstream>
#include "../build/parser.hpp"
#include "../build/scanner.hpp"


int main(int argc, char **argv) {
    ifstream inpFile;
    FILE *outFile;

    if(argc > 1) {
        inpFile.open(argv[1]);
        string program((istreambuf_iterator<char>(inpFile)), istreambuf_iterator<char>());
        yy_scan_string(program.c_str());
        if(argc > 2) {
            outFile = freopen(argv[2], "w", stdout);
        }
    }
    
    yyparse();

    if(argc > 1) {
        inpFile.close();
        if(argc > 2) {
            fclose(outFile);
        }
    }
    return 0;
} 