#ifndef AST_H
#define AST_H


class Node {
    public:
    virtual ~Node() { }
    virtual void generateCode() = 0;
};

class ConstantNode: public Node {
    public:
    const int value;

    ConstantNode(const int& value): value(value) { }
    virtual void generateCode();
};

class IdentifierNode: public Node {
    public:
    const int index;

    IdentifierNode(const int& index): index(index) { }
    virtual void generateCode();
};

class OperationNode: public Node {
    public:
    const int operation;
    const int nOperands;
    Node **operands;

    OperationNode(const int& operation, const int& nOperands, Node **operands):
        operation(operation), nOperands(nOperands), operands(operands) { }
    virtual ~OperationNode();
    virtual void generateCode();

};

extern int sym[26];

#endif /* AST_H */