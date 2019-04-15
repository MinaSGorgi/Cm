#ifndef CONTEXT_H
#define CONTEXT_h

#include <deque>
#include <map>


class Node;

typedef std::string Reference;
typedef std::map<std::string, Reference> SymbolTable;

class Context {
    int referenceIndex;
    std::deque<SymbolTable> symbolTables;

public:
    Context() { referenceIndex = 0; }

    Reference get_reference(const std::string& local) const;
    void insert_reference(const std::string& local);
};

#endif /* CONTEXT_H */