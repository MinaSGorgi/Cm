#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>
using namespace std;


class UndefinedReference: public exception {
    const string symbol;

public:
    UndefinedReference(const string& symbol): symbol(symbol) {}

    virtual const char* what() const throw() {
        return ("Undefined reference to: " + symbol).c_str();
    }
};

class MultipleDefinition: public exception {
    const string symbol;

public:
    MultipleDefinition(const string& symbol): symbol(symbol) {}

    virtual const char* what() const throw() {
        return ("Multiple Definition of: " + symbol).c_str();
    }
};

class ReadOnly: public exception {
    const string symbol;

public:
    ReadOnly(const string& symbol): symbol(symbol) {}

    virtual const char* what() const throw() {
        return ("Assignment of read-only variable: " + symbol).c_str();
    }
};

#endif /* ERRORS_H */