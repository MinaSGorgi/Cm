#ifndef CONTEXT_H
#define CONTEXT_H

#include <deque>
#include <map>
using namespace std;


class Symbol {
    public:
        const int type;

        Symbol(const int& type): type(type) { }
};

typedef map<string, Symbol> SymbolTable;

class Context {
    private:
        int lablesIndex;
        deque<SymbolTable> symbolTables;

    public:
        Context(): lablesIndex(0) { newScope(); }

        int createLabel() { return lablesIndex++; }
        void insertSymbol(const string& name, const int& type);
        Symbol getSymbol(const string& name);
        void newScope() { symbolTables.push_back(SymbolTable()); }
        void deleteScope() { symbolTables.pop_back(); }
};

#endif /* CONTEXT_H */