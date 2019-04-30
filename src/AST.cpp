#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"


void NBlock::generateCode(Context &context) {
    context.newScope();
    for(NStatement *statement: statements) {
        statement->generateCode(context);
    }
    context.deleteScope();
}

NBlock::~NBlock() {
    for(NStatement *statement: statements) {
        delete statement;
    }
}

void NInteger::generateCode(Context &context) {
    printf("\tpush\t%d\n", value);
}

void NDouble::generateCode(Context &context) {
    printf("\tpush\t%f\n", value);
}

void NVariable::generateCode(Context &context) {
    Symbol symbol = context.getSymbol(*name);
    printf("\tpush\t%s\n", name->c_str());
}

NVariable::~NVariable() {
    delete name;
}

void NBinaryOperation::generateCode(Context &context) {
    lhs->generateCode(context);
    rhs->generateCode(context);
    printf("\t%s\n", operation->c_str());
}

NBinaryOperation::~NBinaryOperation() {
    delete operation;
    delete lhs;
    delete rhs;
}

void NAssignment::generateCode(Context &context) {
    rhs->generateCode(context);
    Symbol symbol = context.getSymbol(*(id->name));
    printf("\tpop\t%s\n", (id->name->c_str()));
}

NAssignment::~NAssignment() {
    delete id;
    delete rhs;
}

void NExpressionStatement::generateCode(Context &context) {
    if(expression) {
        expression->generateCode(context);
    }
}

NExpressionStatement::~NExpressionStatement() {
    if(expression) {
        delete expression;
    }
}

void NVarDeclStatement::generateCode(Context &context) {
    context.insertSymbol(*varName, type);
    switch (type)
    {
        case DTINT:
            printf("\tloadi\t%s\n", varName->c_str());
            break;
        case DTDOUBLE:
            printf("\tloadd\t%s\n", varName->c_str());
            break;
    }
}

NVarDeclStatement::~NVarDeclStatement() {
    delete varName;
}

NControlFlowStatement::~NControlFlowStatement() {
    delete expression;
    delete block;
}

void NWhileStatement::generateCode(Context &context) {
    int lbl1, lbl2;

    printf("L%03d:\n", lbl1 = context.createLabel());
    expression->generateCode(context);
    printf("\tjz\tL%03d\n", lbl2 = context.createLabel());
    block->generateCode(context);
    printf("\tjmp\tL%03d\n", lbl1);
    printf("L%03d:\n", lbl2);
}

void NIfStatement::generateCode(Context &context) {
    int lbl1, lbl2;

    expression->generateCode(context);
    printf("\tjz\tL%03d\n", lbl1 = context.createLabel());
    block->generateCode(context);
    if (elseBlock) {       
        printf("\tjmp\tL%03d\n", lbl2 = context.createLabel());
        printf("L%03d:\n", lbl1);
        elseBlock->generateCode(context);
        printf("L%03d:\n", lbl2);
    } else {
        printf("L%03d:\n", lbl1);
    }
}

NIfStatement::~NIfStatement() {
    if(elseBlock) {
        delete elseBlock;
    }
}