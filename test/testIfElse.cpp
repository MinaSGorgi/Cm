#include "test.hpp"


int main() {
    string program =
    "if(x / 2 == 1) {"
        "y = y + 1;"
    "} else {"
        "y = z - 3;"
    "}";
    
    string expected =  
        "\tpush	x\n"
        "\tpush	2\n"
        "\tDIV\n"
        "\tpush	1\n"
        "\tCEQ\n"
        "\tjz	L000\n"
        "\tpush	y\n"
        "\tpush	1\n"
        "\tADD\n"
        "\tpop	y\n"   
        "\tjmp	L001\n"
    "L000:\n"
        "\tpush	z\n"
        "\tpush	3\n"
        "\tSUB\n"
        "\tpop	y\n"
    "L001:\n";

    return runTest(program, expected, 512, "");
}