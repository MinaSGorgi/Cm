#include <cstdarg>
#include <iostream>
#include <iterator>
#include "../include/context.hpp"
#include "../include/errors.hpp"


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

void Context::compile() {
    // TODO: add optimizations
    list <AQuadruple*>::iterator it; 
    for(it = program.begin(); it != program.end(); ++it) {
        cout << (*it)->toString();
        delete (*it);
    } 
}

Symbol Context::getSymbol(const string& name) {
    deque<SymbolTable>::reverse_iterator table;
    SymbolTable::const_iterator symbol;

    for(table = symbolTables.rbegin(); table != symbolTables.rend(); ++table) {
        symbol = table->find(name);
        if(symbol != table->end()) {
            return symbol->second;
        }
    }

    throw UndefinedReference(name);
}

void Context::insertSymbol(const string& name, const int& type, const bool& constant) {
    if(symbolTables.back().find(name) != symbolTables.back().end()) {
        throw MultipleDefinition(name);
    }

    pair<string, Symbol> symbol(name, Symbol(type, constant, name));
    symbolTables.back().insert(symbol);
}