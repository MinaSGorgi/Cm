#include <string>
#include <fstream>
#include "../build/parser.hpp"
#include "../build/scanner.hpp"
using namespace std;


int main() {
    string program =
        "if(x / 2 == 1) {"
            ";"
        "};";
    
    string expected = 
            "\tpush\tx\n"
            "\tpush\t2\n"
            "\tDIV\n"
            "\tpush\t1\n"
            "\tCEQ\n"
            "\tjz\tL000\n"
        "L000:\n";

    int buffer_size = 1024;
    char output[buffer_size];
    memset(output, 0, sizeof(output));
    FILE *f = freopen("/dev/null", "w", stdout);
    setvbuf(stdout, output, _IOFBF, buffer_size);

    fflush(stdout);
    yy_scan_string(program.c_str());
    yyparse();
    fclose(f);

    if(expected.compare(string(output)) != 0) {
        FILE *o = fopen("testIf.txt", "w");
        fprintf(o, "Expected:\n%sFound:\n%s", expected.c_str(), string(output).c_str());
        fclose(o);
        return 1;
    } else {
        return 0;
    }
}