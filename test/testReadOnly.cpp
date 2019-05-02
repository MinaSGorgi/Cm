#include "test.hpp"
#include "../include/context.hpp"
#include "../include/errors.hpp"


int main() {
    Context context;
    int program_len = 0;

    string program =
    "const int x = 3;"
    "x = 4;";

    string expected = "";

    try {
        runTest(program, expected, program_len, "ReadOnly");
        return 1;
    } catch(const ReadOnly& e) {
        return 0;
    }
}