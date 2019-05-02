#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 512;

    string program =
    "int x;"
    "x = 3;"
    "if(x / 2 == 1) {"
        ";"
    "};";
    
    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel();
    expected.append(AOperation("LOADi", 1, "x%0").toString());
    expected.append(AOperation("MOV", 2, "x%0", "3").toString());
    expected.append(AOperation("DIV", 3, "%0", "x%0", "2").toString());
    expected.append(AOperation("CEQ", 3, "%1", "%0", "1").toString());
    expected.append(AOperation("JZ", 1, lbl1.c_str()).toString());
    expected.append(ALabel(lbl1).toString());

    return runTest(program, expected, program_len, "If");
}