#include "test.hpp"


int main() {
    string program =
    "while(x < 5) {"
        "if(x / 2 == 1) {"
            "y = y + 1;"
        "} else {"
            "y = z - 3;"
        "}"
    "}";
    
    
    string expected = 
    "L000:\n"      
        "\tpush	x\n"
        "\tpush	5\n"
        "\tCLT\n"
        "\tjz	L001\n"
        "\tpush	x\n"
        "\tpush	2\n"
        "\tDIV\n"
        "\tpush	1\n"
        "\tCEQ\n"
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

    return runTest(program, expected, 2048, "");
}