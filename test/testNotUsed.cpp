#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 128;

    string program = "int x;";
    
    string expected;
    expected.reserve(program_len);
    expected.append(AOperation("LOADi", 1, "x%0").toString());
    expected.append("Warning: variable `x%0` is not used\n");

    return runTest(program, expected, program_len, "NotUsed");
}