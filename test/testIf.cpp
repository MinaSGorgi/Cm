#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 512;

    string program =
    "int x;"
    "if(x / 2 == 1) {"
        ";"
    "};";
    
    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel();
    expected.append(context.createQuadruple("LOADi", 1, "x"));
    expected.append(context.createQuadruple("DIV", 3, "%0", "x", "2"));
    expected.append(context.createQuadruple("CEQ", 3, "%1", "%0", "1"));
    expected.append(context.createQuadruple("JZ", 1, lbl1.c_str()));
    expected.append(lbl1 + ":\n");

    return runTest(program, expected, program_len, "If");
}