#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"


static int lbl;

void ConstantNode::generateCode() {
    printf("\tpush\t%d\n", value);
}

void IdentifierNode::generateCode() {
    printf("\tpush\t%c\n", index + 'a');
}

void OperationNode::generateCode() {
    int lbl1, lbl2;

    switch(operation) {
    case WHILE:
        printf("L%03d:\n", lbl1 = lbl++);
        operands[0]->generateCode();
        printf("\tjz\tL%03d\n", lbl2 = lbl++);
        operands[1]->generateCode();
        printf("\tjmp\tL%03d\n", lbl1);
        printf("L%03d:\n", lbl2);
        break;
    case IF:
        operands[0]->generateCode();
        if (nOperands > 2) {
            /* if else */
            printf("\tjz\tL%03d\n", lbl1 = lbl++);
            operands[1]->generateCode();
            printf("\tjmp\tL%03d\n", lbl2 = lbl++);
            printf("L%03d:\n", lbl1);
            operands[2]->generateCode();
            printf("L%03d:\n", lbl2);
        } else {
            /* if */
            printf("\tjz\tL%03d\n", lbl1 = lbl++);
            operands[1]->generateCode();
            printf("L%03d:\n", lbl1);
        }
        break;
    case PRINT:
        operands[0]->generateCode();
        printf("\tprint\n");
        break;
    case '=':
        operands[1]->generateCode();
        printf("\tpop\t%c\n", ((IdentifierNode*)operands[0])->index + 'a');
        break;
    case UMINUS:
        operands[0]->generateCode();
        printf("\tneg\n");
        break;
    default:
        break;
    }
}

OperationNode::~OperationNode() {
    for(int i = 0; i < nOperands; ++i) {
        delete operands[i];
    }
    delete operands;
}

void BinaryOperationNode::generateCode() {
    operands[0]->generateCode();
    operands[1]->generateCode();
    printf("\t%s\n", s_operation->c_str());
}

BinaryOperationNode::~BinaryOperationNode() {
    delete s_operation;
}