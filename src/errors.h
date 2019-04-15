#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>


class UndefinedReference: public std::exception {
    const std::string symbol;

public:
    UndefinedReference(const std::string& symbol): symbol(symbol) {}

    virtual const char* what() const throw() {
        return ("Undefined reference to: " + symbol).c_str();
    }
};

class MultipleDefinition: public std::exception {
    const std::string symbol;

public:
    MultipleDefinition(const std::string& symbol): symbol(symbol) {}

    virtual const char* what() const throw() {
        return ("Multiple Definition of: " + symbol).c_str();
    }
};

#endif /* ERRORS_H */