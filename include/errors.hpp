#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>
using namespace std;


class UndefinedReference: public runtime_error {
    public:
        UndefinedReference(const string& symbol): runtime_error("Undefined reference to: " + symbol)
            { }
};

class MultipleDefinition: public runtime_error {
    public:
        MultipleDefinition(const string& symbol): runtime_error("Multiple Definition of: " + symbol)
            { }
};

class ReadOnly: public runtime_error {
    public:
        ReadOnly(const string& symbol): runtime_error("Assignment of read-only variable: " + symbol)
            { }
};

class Uninitialized: public runtime_error {

    public:
        Uninitialized(const string& symbol):
            runtime_error("The variable `" + symbol + "` is being used without being initialized")
            { }
};

class TypeMismatch: public runtime_error {
    public:
        TypeMismatch(const string& symbol1, const string& symbol2, const string& type1,
            const string& type2): runtime_error("Type `" + type1 + "` of variable `" + symbol1 +
                "` doesn't match Type `" + type2 + "` of variable `" + symbol2 + "`") { }
};

#endif /* ERRORS_H */