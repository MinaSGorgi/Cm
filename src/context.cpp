#include "../src/context.h"
#include "../src/errors.h"


Reference Context::get_reference(const std::string& local) const {
    std::deque<SymbolTable>::const_iterator table;
    std::map<std::string, Reference>::const_iterator reference;

    for(table = symbolTables.end(); table != symbolTables.begin(); --table) {
        reference = table->find(local);
        if(reference != table->end()) {
            return reference->second;
        }
    }

    throw new UndefinedReference(local);
}

void Context::insert_reference(const std::string& local) {
    if(symbolTables.end()->find(local) != symbolTables.end()->end()) {
        throw new MultipleDefinition(local);
    }
    symbolTables.end()->insert(local, "%" + local);
}