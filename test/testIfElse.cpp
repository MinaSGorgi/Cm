#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 1024;

    string program =
    "int x;"
    "int y;"
    "int z;"
    "if(x / 2 == 1) {"
        "y = y + 1;"
    "} else {"
        "y = z - 3;"
    "}";

    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();
    expected.append(context.createQuadruple("LOADi", 1, "x"));
    expected.append(context.createQuadruple("LOADi", 1, "y"));
    expected.append(context.createQuadruple("LOADi", 1, "z"));
    expected.append(context.createQuadruple("DIV", 3, "%0", "x", "2"));
    expected.append(context.createQuadruple("CEQ", 3, "%1", "%0", "1"));
    expected.append(context.createQuadruple("JZ", 1, lbl1.c_str()));
    expected.append(context.createQuadruple("ADD", 3, "%2", "y", "1"));
    expected.append(context.createQuadruple("MOV", 2, "y", "%2"));
    expected.append(context.createQuadruple("JMP", 1, lbl2.c_str()));
    expected.append(lbl1 + ":\n");
    expected.append(context.createQuadruple("SUB", 3, "%3", "z", "3"));
    expected.append(context.createQuadruple("MOV", 2, "y", "%3"));
    expected.append(lbl2 + ":\n");

    return runTest(program, expected, program_len, "IfElse");
}