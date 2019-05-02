#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../include/context.hpp"
using namespace std;


class Node {
    public:
        virtual ~Node() { }
        virtual Symbol generateQuadruple(Context &context) = 0;
};

class NExpression: public Node {
    public:
        virtual ~NExpression() { }
        virtual Symbol generateQuadruple(Context &context) = 0;
};

class NStatement: public Node {
    public:
        virtual ~NStatement() { }
        virtual Symbol generateQuadruple(Context &context) = 0;
};

class NBlock: public Node {
    public:
        vector<NStatement*> statements;

        NBlock(NStatement *statement): statements(vector<NStatement*>{statement}) { }
        virtual ~NBlock();
        virtual Symbol generateQuadruple(Context &context);
};

class NInteger: public NExpression {
    public:
        const int value;

        NInteger(const int& value): value(value) { }
        virtual Symbol generateQuadruple(Context &context);
};

class NDouble: public NExpression {
    public:
        const double value;

        NDouble(const double& value): value(value) { }
        virtual Symbol generateQuadruple(Context &context);
};

class NVariable: public NExpression {
    public:
        string *name;

        NVariable(string *name): name(name) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NVariable();
};

class NBinaryOperation: public NExpression {
    public:
        string *operation;
        NExpression *lhs, *rhs;

        NBinaryOperation(string *operation, NExpression *lhs, NExpression *rhs):
            operation(operation), lhs(lhs), rhs(rhs) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NBinaryOperation();
};

class NAssignment: public NExpression {
    public:
        NVariable *id;
        NExpression *rhs;

        NAssignment(NVariable *id, NExpression *rhs): id(id), rhs(rhs) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NAssignment();
};

class NExpressionStatement: public NStatement {
    public:
        NExpression *expression;

        NExpressionStatement(NExpression *expression): expression(expression) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NExpressionStatement();
};

class NVarDeclStatement: public NStatement {
    public:
        int type;
        bool constant;
        string *varName;
        NExpression *rhs;

        NVarDeclStatement(int type, bool constant, string *varName, NExpression *rhs): type(type),
            constant(constant), varName(varName), rhs(rhs) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NVarDeclStatement();
};

class NControlFlowStatement: public NStatement {
    public:
        NExpression *expression;
        NBlock *block;

        NControlFlowStatement(NExpression *expression, NBlock *block): expression(expression),
            block(block) { }
        virtual Symbol generateQuadruple(Context &context) = 0;
        virtual ~NControlFlowStatement();
};

class NWhileStatement: public NControlFlowStatement {
    public:
        NWhileStatement(NExpression *expression, NBlock *block):
            NControlFlowStatement(expression, block) { }
        virtual Symbol generateQuadruple(Context &context);
};

class NIfStatement: public NControlFlowStatement {
    public:
        NBlock *elseBlock;

        NIfStatement(NExpression *expression, NBlock *block, NBlock *elseBlock):
            NControlFlowStatement(expression, block), elseBlock(elseBlock) { }
        NIfStatement(NExpression *expression, NBlock *block):
            NIfStatement(expression, block, NULL) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NIfStatement();
};

#endif /* AST_H */