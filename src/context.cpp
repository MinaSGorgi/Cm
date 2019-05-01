#include <cstdarg>
#include "../include/context.hpp"
#include "../include/errors.hpp"


string Context::createQuadruple(string instruction, int numOperands, ...) {
    string quadruple;
    quadruple.reserve(256);
    quadruple.append("\t");
    quadruple.append(instruction);
    quadruple.append("\t");

    va_list arguments;                   
    va_start(arguments, numOperands);
    for (int i = 0; i < numOperands; ++i) {
        quadruple.append(" ");
        quadruple.append(va_arg(arguments, const char*));
        quadruple.append(",");
    }
    va_end(arguments);

    quadruple[quadruple.length() - 1] = '\n';
    return quadruple;
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

    throw new UndefinedReference(name);
}

void Context::insertSymbol(const string& name, const int& type) {
    if(symbolTables.back().find(name) != symbolTables.back().end()) {
        throw new MultipleDefinition(name);
    }

    pair<string, Symbol> symbol(name, Symbol(type, name));
    symbolTables.back().insert(symbol);
}