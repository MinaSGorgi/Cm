#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 512;

    string program =
    "int x;"
    "while(x < 5) {"
        ";"
    "}";
    
    "L000:\n"      
        "\tCLT\t%0, x, 5\n"
        "\tjz	L001\n"
        "\tjmp	L000\n"
    "L001:\n";

    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();
    expected.append(context.createQuadruple("LOADi", 1, "x"));
    expected.append(lbl1 + ":\n");
    expected.append(context.createQuadruple("CLT", 3, "%1", "%0", "1"));
    expected.append(context.createQuadruple("JZ", 1, lbl1.c_str()));
    expected.append(context.createQuadruple("JZ", 1, lbl2.c_str()));
    expected.append(lbl2 + ":\n");

    return runTest(program, expected, program_len, "While");
}