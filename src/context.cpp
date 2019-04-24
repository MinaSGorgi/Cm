#include "../src/context.h"
#include "../src/errors.h"


Symbol Context::get_symbol(const std::string& name) const {
    std::deque<SymbolTable>::const_iterator table;
    SymbolTable::const_iterator symbol;

    for(table = symbolTables.end(); table != symbolTables.begin(); --table) {
        symbol = table->find(name);
        if(symbol != table->end()) {
            return symbol->second;
        }
    }

    throw new UndefinedReference(name);
}

void Context::insert_symbol(const std::string& name, const SymbolType& type) {
    if(symbolTables.end()->find(name) != symbolTables.end()->end()) {
        throw new MultipleDefinition(name);
    }

    std::pair<std::string, Symbol> symbol(name, Symbol(name, type));
    symbolTables.end()->insert(symbol);
}