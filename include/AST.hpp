#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
using namespace std;

class Node {
    public:
        virtual ~Node() { }
        virtual void generateCode() = 0;
};

class NExpression: public Node {
    public:
        virtual ~NExpression() { }
        virtual void generateCode() = 0;
};

class NStatement: public Node {
    public:
        virtual ~NStatement() { }
        virtual void generateCode() = 0;
};

class NBlock: public Node {
    public:
        vector<NStatement*> statements;

        NBlock(NStatement *statement): statements(vector<NStatement*>{statement}) { }
        virtual ~NBlock();
        virtual void generateCode();
};

class NConstant: public NExpression {
    public:
        const int value;

        NConstant(const int& value): value(value) { }
        virtual void generateCode();
};

class NIdentifier: public NExpression {
    public:
        const int index;

        NIdentifier(const int& index): index(index) { }
        virtual void generateCode();
};

class NBinaryOperation: public NExpression {
    public:
        string *operation;
        NExpression *lhs, *rhs;

        NBinaryOperation(string *operation, NExpression *lhs, NExpression *rhs):
            operation(operation), lhs(lhs), rhs(rhs) { }
        virtual void generateCode();
        virtual ~NBinaryOperation();
};

class NAssignment: public NExpression {
    public:
        NIdentifier *id;
        NExpression *rhs;

        NAssignment(NIdentifier *id, NExpression *rhs): id(id), rhs(rhs) { }
        virtual void generateCode();
        virtual ~NAssignment();
};

class NExpressionStatement: public NStatement {
    public:
        NExpression *expression;

        NExpressionStatement(NExpression *expression): expression(expression) { }
        virtual void generateCode();
        virtual ~NExpressionStatement();
};

class NControlFlowStatement: public NStatement {
    public:
        NExpression *expression;
        NBlock *block;

        NControlFlowStatement(NExpression *expression, NBlock *block): expression(expression),
            block(block) { }
        virtual void generateCode() = 0;
        virtual ~NControlFlowStatement();
};

class NWhileStatement: public NControlFlowStatement {
    public:
        NWhileStatement(NExpression *expression, NBlock *block):
            NControlFlowStatement(expression, block) { }
        virtual void generateCode();
};

class NIfStatement: public NControlFlowStatement {
    public:
        NBlock *elseBlock;

        NIfStatement(NExpression *expression, NBlock *block, NBlock *elseBlock):
            NControlFlowStatement(expression, block), elseBlock(elseBlock) { }
        NIfStatement(NExpression *expression, NBlock *block):
            NIfStatement(expression, block, NULL) { }
        virtual void generateCode();
        virtual ~NIfStatement();
};

extern int sym[26];

#endif /* AST_H */