#include <cstdarg>
#include <iostream>
#include <iterator>
#include "../include/context.hpp"
#include "../include/errors.hpp"
#include "../build/parser.hpp"


AOperation::AOperation(string instruction, int numOperands, ...): instruction(instruction) {
    operands.reserve(numOperands);
    va_list arguments;                   
    va_start(arguments, numOperands);
    for (int i = 0; i < numOperands; ++i) {
        operands.push_back(va_arg(arguments, const char*));
    }
    va_end(arguments);
}

string AOperation::toString() {
    // TODO: optimize
    string quadruple("\t" + instruction + "\t");
    if(operands.size() > 0) {
        for(int i = 0; i < operands.size() - 1; ++i) {
            quadruple += (operands[i] + ", ");
        }
        quadruple += operands[operands.size() - 1] + "\n";
    }
    return quadruple;
}

string Symbol::getType() {
    switch(type) {
        case DTINT:
            return "int";
        case DTDOUBLE:
            return "double";
        default:
            return "void";
    }
}

void Context::compile() {
    // TODO: add optimizations
    list <AQuadruple*>::iterator it; 
    for(it = program.begin(); it != program.end(); ++it) {
        cout << (*it)->toString();
        delete (*it);
    } 
}

Symbol* Context::getSymbol(const string& name) {
    deque<SymbolTable>::reverse_iterator table;
    SymbolTable::iterator symbol;

    for(table = symbolTables.rbegin(); table != symbolTables.rend(); ++table) {
        symbol = table->find(name);
        if(symbol != table->end()) {
            return &(symbol->second);
        }
    }

    throw UndefinedReference(name);
}

Symbol* Context::insertSymbol(const string& name, const int& type, const bool& initialized,
    const bool& constant) {
    if(symbolTables.back().find(name) != symbolTables.back().end()) {
        throw MultipleDefinition(name);
    }

    int scopeIndex = symbolTables.end() - symbolTables.begin() - 1;
    string reference = name + "%" + to_string(scopeIndex);
    pair<string, Symbol> symbolEntry(name, Symbol(type, constant, initialized, reference));
    symbolTables.back().insert(symbolEntry);
    return &((--symbolTables.back().end())->second);
}