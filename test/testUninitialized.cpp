#include "test.hpp"
#include "../include/context.hpp"
#include "../include/errors.hpp"


int main() {
    Context context;
    int program_len = 0;

    string program =
    "int x;"
    "x + 3;";

    string expected = "";

    try {
        runTest(program, expected, program_len, "Uninitialized");
        return 1;
    } catch(Uninitialized e) {
        return 0;
    }
}