#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 256;

    string program =
    "int x;"
    "x = 1;"
    "while(x < 5) {"
        "int x;"
        "x = 3;"
    "}";
    
    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();
    expected.append(AOperation("LOADi", 1, "x%0").toString());
    expected.append(AOperation("MOV", 2, "x%0", "1").toString());
    expected.append(ALabel(lbl1).toString());
    expected.append(AOperation("CLT", 3, "%0", "x%0", "5").toString());
    expected.append(AOperation("JZ", 1, lbl2.c_str()).toString());
    expected.append(AOperation("LOADi", 1, "x%1").toString());
    expected.append(AOperation("MOV", 2, "x%1", "3").toString());
    expected.append(AOperation("JMP", 1, lbl1.c_str()).toString());
    expected.append(ALabel(lbl2).toString());

    return runTest(program, expected, program_len, "Scope");
}