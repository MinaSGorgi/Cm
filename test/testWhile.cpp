#include "test.hpp"


int main() {
    string program =
    "int x;"
    "while(x < 5) {"
        ";"
    "}";
    
    string expected = 
        "\tloadi\tx\n"
    "L000:\n"      
        "\tpush	x\n"
        "\tpush	5\n"
        "\tCLT\n"
        "\tjz	L001\n"
        "\tjmp	L000\n"
    "L001:\n";

    return runTest(program, expected, 512, "While");
}