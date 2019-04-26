#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"


static int lbl;

void NBlock::generateCode() {
    for(NStatement *statement: statements) {
        statement->generateCode();
    }
}

NBlock::~NBlock() {
    for(NStatement *statement: statements) {
        delete statement;
    }
}

void NConstant::generateCode() {
    printf("\tpush\t%d\n", value);
}

void NIdentifier::generateCode() {
    printf("\tpush\t%c\n", index + 'a');
}

void NBinaryOperation::generateCode() {
    lhs->generateCode();
    rhs->generateCode();
    printf("\t%s\n", operation->c_str());
}

NBinaryOperation::~NBinaryOperation() {
    delete operation;
    delete lhs;
    delete rhs;
}

void NAssignment::generateCode() {
    rhs->generateCode();
    printf("\tpop\t%c\n", (id->index + 'a'));
}

NAssignment::~NAssignment() {
    delete id;
    delete rhs;
}

void NExpressionStatement::generateCode() {
    if(expression) {
        expression->generateCode();
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

void NWhileStatement::generateCode() {
    int lbl1, lbl2;

    printf("L%03d:\n", lbl1 = lbl++);
    expression->generateCode();
    printf("\tjz\tL%03d\n", lbl2 = lbl++);
    block->generateCode();
    printf("\tjmp\tL%03d\n", lbl1);
    printf("L%03d:\n", lbl2);
}

void NIfStatement::generateCode() {
    int lbl1, lbl2;

    expression->generateCode();
    printf("\tjz\tL%03d\n", lbl1 = lbl++);
    block->generateCode();
    if (elseBlock) {       
        printf("\tjmp\tL%03d\n", lbl2 = lbl++);
        printf("L%03d:\n", lbl1);
        elseBlock->generateCode();
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