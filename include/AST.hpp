#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../include/context.hpp"
using namespace std;


class Node {
    public:
        virtual ~Node() { }
        virtual Symbol generateCode(Context &context) = 0;
};

class NExpression: public Node {
    public:
        virtual ~NExpression() { }
        virtual Symbol generateCode(Context &context) = 0;
};

class NStatement: public Node {
    public:
        virtual ~NStatement() { }
        virtual Symbol generateCode(Context &context) = 0;
};

class NBlock: public Node {
    public:
        vector<NStatement*> statements;

        NBlock(NStatement *statement): statements(vector<NStatement*>{statement}) { }
        virtual ~NBlock();
        virtual Symbol generateCode(Context &context);
};

class NInteger: public NExpression {
    public:
        const int value;

        NInteger(const int& value): value(value) { }
        virtual Symbol generateCode(Context &context);
};

class NDouble: public NExpression {
    public:
        const double value;

        NDouble(const double& value): value(value) { }
        virtual Symbol generateCode(Context &context);
};

class NVariable: public NExpression {
    public:
        string *name;

        NVariable(string *name): name(name) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NVariable();
};

class NBinaryOperation: public NExpression {
    public:
        string *operation;
        NExpression *lhs, *rhs;

        NBinaryOperation(string *operation, NExpression *lhs, NExpression *rhs):
            operation(operation), lhs(lhs), rhs(rhs) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NBinaryOperation();
};

class NAssignment: public NExpression {
    public:
        NVariable *id;
        NExpression *rhs;

        NAssignment(NVariable *id, NExpression *rhs): id(id), rhs(rhs) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NAssignment();
};

class NExpressionStatement: public NStatement {
    public:
        NExpression *expression;

        NExpressionStatement(NExpression *expression): expression(expression) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NExpressionStatement();
};

class NVarDeclStatement: public NStatement {
    public:
        int type;
        string *varName;

        NVarDeclStatement(int type, string *varName): type(type), varName(varName) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NVarDeclStatement();
};

class NControlFlowStatement: public NStatement {
    public:
        NExpression *expression;
        NBlock *block;

        NControlFlowStatement(NExpression *expression, NBlock *block): expression(expression),
            block(block) { }
        virtual Symbol generateCode(Context &context) = 0;
        virtual ~NControlFlowStatement();
};

class NWhileStatement: public NControlFlowStatement {
    public:
        NWhileStatement(NExpression *expression, NBlock *block):
            NControlFlowStatement(expression, block) { }
        virtual Symbol generateCode(Context &context);
};

class NIfStatement: public NControlFlowStatement {
    public:
        NBlock *elseBlock;

        NIfStatement(NExpression *expression, NBlock *block, NBlock *elseBlock):
            NControlFlowStatement(expression, block), elseBlock(elseBlock) { }
        NIfStatement(NExpression *expression, NBlock *block):
            NIfStatement(expression, block, NULL) { }
        virtual Symbol generateCode(Context &context);
        virtual ~NIfStatement();
};

#endif /* AST_H */