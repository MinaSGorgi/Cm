#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"


void NBlock::generateCode(Context &context) {
    for(NStatement *statement: statements) {
        statement->generateCode(context);
    }
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

void NIdentifier::generateCode(Context &context) {
    printf("\tpush\t%c\n", index + 'a');
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
    printf("\tpop\t%c\n", (id->index + 'a'));
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