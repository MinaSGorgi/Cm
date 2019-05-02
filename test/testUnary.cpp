#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 128;

    string program =
    "int x;"
    "x = 3;"
    "x = !x + 3;";
    
    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel();
    expected.append(AOperation("LOADi", 1, "x%0").toString());
    expected.append(AOperation("MOV", 2, "x%0", "3").toString());
    expected.append(AOperation("NOT", 2, "%0", "x%0").toString());
    expected.append(AOperation("ADD", 3, "%1", "%0", "3").toString());
    expected.append(AOperation("MOV", 2, "x%0", "%1").toString());

    return runTest(program, expected, program_len, "Unary");
}