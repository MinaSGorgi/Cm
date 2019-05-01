#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <deque>
#include <list> 
#include <map>
#include <vector>
using namespace std;


class Symbol;
typedef map<string, Symbol> SymbolTable;


class AQuadruple {
    public:
        virtual string toString() = 0;
};

class AOperation: public AQuadruple {
    public:
        string instruction;
        vector<string> operands;

        AOperation(string instruction, int numOperands, ...);
        virtual string toString();
};

class ALabel: public AQuadruple {
    public:
        string label;

        ALabel(string label): label(label) { }
        virtual string toString() { return label + ":\n"; }
};

class Symbol {
    public:
        const int type;
        string reference;

        Symbol(const int& type, const string& reference): type(type), reference(reference) { }
};

class Context {
    private:
        int lablesIndex;
        int referencesIndex;
        deque<SymbolTable> symbolTables;
        list<AQuadruple*> program;

    public:
        Context(): lablesIndex(0), referencesIndex(0) { newScope(); }

        void addQuadruple(AQuadruple *quadruple) { program.push_back(quadruple); }
        void compile();

        string createLabel() { return "L" + to_string(lablesIndex++); }
        string createReference() { return "%" + to_string(referencesIndex++); }
        
        void insertSymbol(const string& name, const int& type);
        Symbol getSymbol(const string& name);
        void newScope() { symbolTables.push_back(SymbolTable()); }
        void deleteScope() { symbolTables.pop_back(); }
};

#endif /* CONTEXT_H */