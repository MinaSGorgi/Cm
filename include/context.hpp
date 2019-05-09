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
        string instruction;
        vector<string> operands;

        virtual string toString() = 0;
};

class AOperation: public AQuadruple {
    public:
        AOperation(string instruction, int numOperands, ...);
        virtual string toString();
        virtual string getLoaded() { return operands[0]; }
        virtual vector<string> getUsed() { return operands; }
};

class ALabel: public AQuadruple {
    public:
        ALabel(string label) { instruction = label; }
        virtual string toString() { return instruction + ":\n"; }
};

class Symbol {
    public:
        const int type;
        const bool constant;
        bool initialized, used;
        string reference;

        Symbol(const int& type, const bool& constant, const bool& initialized,
            const string& reference, bool used=false): type(type), constant(constant),
            initialized(initialized), reference(reference), used(used) { }
        string getType();
        void setInitialized(bool init=true) { initialized = init; }
        void setUsed(bool use=true) { used = use; }
};

class Context {
    private:
        int lablesIndex;
        int referencesIndex;
        deque<SymbolTable> symbolTables;
        list<AQuadruple*> program;
        list<string> unused;

    public:
        Context(): lablesIndex(0), referencesIndex(0) { newScope(); }

        void addQuadruple(AQuadruple *quadruple) { program.push_back(quadruple); }
        void compile();
        void printWarnings();

        string createLabel() { return "L" + to_string(lablesIndex++); }
        string createReference() { return "%" + to_string(referencesIndex++); }
        
        Symbol *insertSymbol(const string& name, const int& type, const bool& initialized,
            const bool& constant);
        Symbol *getSymbol(const string& name);
        void newScope() { symbolTables.push_back(SymbolTable()); }
        void deleteScope();
};

#endif /* CONTEXT_H */