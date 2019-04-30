#include "test.hpp"


int main() {
    string program =
    "int x;"
    "if(x / 2 == 1) {"
        ";"
    "};";
    
    string expected = 
        "\tloadi\tx\n"
        "\tpush\tx\n"
        "\tpush\t2\n"
        "\tDIV\n"
        "\tpush\t1\n"
        "\tCEQ\n"
        "\tjz\tL000\n"
    "L000:\n";

    return runTest(program, expected, 512, "If");
}