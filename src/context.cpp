#include "../include/context.hpp"
#include "../include/errors.hpp"


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

    pair<string, Symbol> symbol(name, Symbol(type, createReference()));
    symbolTables.back().insert(symbol);
}