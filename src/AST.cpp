#include <iostream>
#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"
using namespace std;


Symbol NBlock::generateQuadruple(Context &context) {
    context.newScope();
    for(NStatement *statement: statements) {
        statement->generateQuadruple(context);
    }
    context.deleteScope();
    return Symbol(DTVOID, "");
}

NBlock::~NBlock() {
    for(NStatement *statement: statements) {
        delete statement;
    }
}

Symbol NInteger::generateQuadruple(Context &context) {
    return Symbol(DTINT, to_string(value));
}

Symbol NDouble::generateQuadruple(Context &context) {
    return Symbol(DTDOUBLE, to_string(value));
}

Symbol NVariable::generateQuadruple(Context &context) {
    return context.getSymbol(*name);
}

NVariable::~NVariable() {
    delete name;
}

Symbol NBinaryOperation::generateQuadruple(Context &context) {
    Symbol slhs = lhs->generateQuadruple(context);
    Symbol srhs = rhs->generateQuadruple(context);
    // TODO: check types 
    Symbol result = Symbol(DTINT, context.createReference());

    context.addQuadruple(new AOperation(*operation, 3, result.reference.c_str(), slhs.reference.c_str(),
           srhs.reference.c_str()));
    return result;
}

NBinaryOperation::~NBinaryOperation() {
    delete operation;
    delete lhs;
    delete rhs;
}

Symbol NAssignment::generateQuadruple(Context &context) {
    Symbol srhs = rhs->generateQuadruple(context);
    Symbol var = context.getSymbol(*(id->name));

    context.addQuadruple(new AOperation("MOV", 2, id->name->c_str(), srhs.reference.c_str()));
    return var;
}

NAssignment::~NAssignment() {
    delete id;
    delete rhs;
}

Symbol NExpressionStatement::generateQuadruple(Context &context) {
    if(expression) {
        expression->generateQuadruple(context);
    }
    return Symbol(DTVOID, "");
}

NExpressionStatement::~NExpressionStatement() {
    if(expression) {
        delete expression;
    }
}

Symbol NVarDeclStatement::generateQuadruple(Context &context) {
    context.insertSymbol(*varName, type);
    switch (type)
    {
        case DTINT:
            context.addQuadruple(new AOperation("LOADi", 1, varName->c_str()));
            break;
        case DTDOUBLE:
            context.addQuadruple(new AOperation("LOADd", 1, varName->c_str()));
            break;
        default:
            break;
    }
    return Symbol(DTVOID, "");
}

NVarDeclStatement::~NVarDeclStatement() {
    delete varName;
}

NControlFlowStatement::~NControlFlowStatement() {
    delete expression;
    delete block;
}

Symbol NWhileStatement::generateQuadruple(Context &context) {
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();

    context.addQuadruple(new ALabel(lbl1));
    expression->generateQuadruple(context);
    context.addQuadruple(new AOperation("JZ", 1, lbl2.c_str()));
    block->generateQuadruple(context);
    context.addQuadruple(new AOperation("JMP", 1, lbl1.c_str()));
    context.addQuadruple(new ALabel(lbl2));
    return Symbol(DTVOID, "");
}

Symbol NIfStatement::generateQuadruple(Context &context) {
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();

    expression->generateQuadruple(context);
    context.addQuadruple(new AOperation("JZ", 1, lbl1.c_str()));
    block->generateQuadruple(context);
    if (elseBlock) {
        context.addQuadruple(new AOperation("JMP", 1, lbl2.c_str()));
        context.addQuadruple(new ALabel(lbl1));
        elseBlock->generateQuadruple(context);
        context.addQuadruple(new ALabel(lbl2));
    } else {
        context.addQuadruple(new ALabel(lbl1));
    }
    return Symbol(DTVOID, "");
}

NIfStatement::~NIfStatement() {
    if(elseBlock) {
        delete elseBlock;
    }
}