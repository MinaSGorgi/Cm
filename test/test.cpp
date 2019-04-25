#include <string>
#include <fstream>
#include "../build/parser.hpp"
using namespace std;


int main() {
    string expected = 
        "L000:\n"      
            "\tpush	x\n"
            "\tpush	5\n"
            "\tCLT\n"
            "\tjz	L001\n"
            "\tpush	x\n"
            "\tpush	2\n"
            "\tpush	1\n"
            "\tCEQ\n"
            "\tDIV\n"
            "\tjz	L002\n"
            "\tpush	y\n"
            "\tpush	1\n"
            "\tADD\n"
            "\tpop	y\n"   
            "\tjmp	L003\n"
        "L002:\n"
            "\tpush	z\n"
            "\tpush	3\n"
            "\tSUB\n"
            "\tpop	y\n"
        "L003:\n"
            "\tjmp	L000\n"
        "L001:\n";

    if(freopen("../res/program.txt", "r", stdin) == NULL) {
       perror("Can't open program.txt\n");
       return EXIT_FAILURE;
    }

    int buffer_size = 2047;
    char output[buffer_size];
    FILE *f = freopen("/dev/null", "w", stdout);
    setvbuf(stdout, output, _IOFBF, buffer_size);

    yyparse();
    fclose(f);

    return expected.compare(output);
}