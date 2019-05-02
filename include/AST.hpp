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

class NUnaryOperation: public NExpression {
    public:
        string *operation;
        NExpression *expr;

        NUnaryOperation(string *operation, NExpression *expr): operation(operation), expr(expr) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NUnaryOperation();
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
        NBlock *block;

        NControlFlowStatement(NBlock *block): block(block) { }
        virtual Symbol generateQuadruple(Context &context) = 0;
        virtual ~NControlFlowStatement();
};

class NWhileStatement: public NControlFlowStatement {
    public:
        NExpression *expression;

        NWhileStatement(NExpression *expression, NBlock *block): NControlFlowStatement(block),
            expression(expression) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NWhileStatement();
};

class NForStatement: public NControlFlowStatement {
    NStatement *statement1, *statement2, *statement3;

    public:
        NForStatement(NStatement *statement1, NStatement *statement2, NStatement *statement3,
            NBlock *block): NControlFlowStatement(block), statement1(statement1),
            statement2(statement2), statement3(statement3) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NForStatement();
};

class NIfStatement: public NControlFlowStatement {
    public:
        NExpression *expression;
        NBlock *elseBlock;

        NIfStatement(NExpression *expression, NBlock *block, NBlock *elseBlock):
            NControlFlowStatement(block), expression(expression), elseBlock(elseBlock) { }
        NIfStatement(NExpression *expression, NBlock *block):
            NIfStatement(expression, block, NULL) { }
        virtual Symbol generateQuadruple(Context &context);
        virtual ~NIfStatement();
};

#endif /* AST_H */