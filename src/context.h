#ifndef CONTEXT_H
#define CONTEXT_h

#include <deque>
#include <map>


enum SymbolType {
    CHAR,
    INT,
    DOUBLE,
    VOID,
    NONE
};

class Symbol {
public:
    const std::string reference;
    const SymbolType type;

    Symbol(std::string reference, SymbolType type): reference(reference), type(type) { }
};

typedef std::map<std::string, Symbol> SymbolTable;

class Context {
    std::deque<SymbolTable> symbolTables;

public:
    Context() { }

    Symbol get_symbol(const std::string& name) const;
    void insert_symbol(const std::string& name, const SymbolType& type);
};

#endif /* CONTEXT_H */