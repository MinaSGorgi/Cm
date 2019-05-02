#include "test.hpp"
#include "../include/context.hpp"
#include "../include/errors.hpp"


int main() {
    Context context;
    int program_len = 0;

    string program =
    "int x;"
    "double y;"
    "x = 3;"
    "y = 3.0;" 
    "x = x + y;";

    string expected = "";

    try {
        runTest(program, expected, program_len, "TypeMismatch");
        return 1;
    } catch(const TypeMismatch& e) {
        return 0;
    }
}