#ifndef TEST_H
#define TEST_H

#include <fstream>
#include <string>
#include "../build/parser.hpp"
#include "../build/scanner.hpp"
using namespace std;


int runTest(string program, string expected, int bufferSize, string testName) {
    char output[bufferSize];
    memset(output, 0, sizeof(output));
    FILE *f = freopen("/dev/null", "w", stdout);
    setvbuf(stdout, output, _IOFBF, bufferSize);

    fflush(stdout);
    yy_scan_string(program.c_str());
    yyparse();
    fclose(f);

    if(expected.compare(string(output)) != 0) {
        string fileName = "test" + testName + ".txt";
        FILE *o = fopen(fileName.c_str(), "w");
        fprintf(o, "Expected:\n%sFound:\n%s", expected.c_str(), string(output).c_str());
        fclose(o);
        return 1;
    } else {
        return 0;
    }
}

#endif /* TEST_H */