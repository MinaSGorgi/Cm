#include "../include/context.hpp"
#include "../include/errors.hpp"


Symbol Context::getSymbol(const string& name) {
    deque<SymbolTable>::const_iterator table;
    SymbolTable::const_iterator symbol;

    for(table = symbolTables.end(); table != symbolTables.begin(); --table) {
        symbol = table->find(name);
        if(symbol != table->end()) {
            return symbol->second;
        }
    }

    throw new UndefinedReference(name);
}

void Context::insertSymbol(const string& name, const int& type) {
    if(symbolTables.end()->find(name) != symbolTables.end()->end()) {
        throw new MultipleDefinition(name);
    }

    pair<string, Symbol> symbol(name, Symbol(type));
    symbolTables.end()->insert(symbol);
}