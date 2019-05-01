#ifndef CONTEXT_H
#define CONTEXT_H

#include <deque>
#include <map>
using namespace std;


class Symbol {
    public:
        const int type;
        string reference;

        Symbol(const int& type, const string& reference): type(type), reference(reference) { }
};

typedef map<string, Symbol> SymbolTable;

class Context {
    private:
        int lablesIndex;
        int referencesIndex;
        deque<SymbolTable> symbolTables;

    public:
        Context(): lablesIndex(0), referencesIndex(0) { newScope(); }

        string createQuadruple(string instruction, int numOperands, ...);
        string createLabel() { return "L" + to_string(lablesIndex++); }
        string createReference() { return "%" + to_string(referencesIndex++); }
        
        void insertSymbol(const string& name, const int& type);
        Symbol getSymbol(const string& name);
        void newScope() { symbolTables.push_back(SymbolTable()); }
        void deleteScope() { symbolTables.pop_back(); }
};

#endif /* CONTEXT_H */