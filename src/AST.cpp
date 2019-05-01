#include <iostream>
#include <stdio.h>
#include "../include/AST.hpp"
#include "../build/parser.hpp"
using namespace std;


Symbol NBlock::generateCode(Context &context) {
    context.newScope();
    for(NStatement *statement: statements) {
        statement->generateCode(context);
    }
    context.deleteScope();
    return Symbol(DTVOID, "");
}

NBlock::~NBlock() {
    for(NStatement *statement: statements) {
        delete statement;
    }
}

Symbol NInteger::generateCode(Context &context) {
    return Symbol(DTINT, to_string(value));
}

Symbol NDouble::generateCode(Context &context) {
    return Symbol(DTDOUBLE, to_string(value));
}

Symbol NVariable::generateCode(Context &context) {
    return context.getSymbol(*name);
}

NVariable::~NVariable() {
    delete name;
}

Symbol NBinaryOperation::generateCode(Context &context) {
    Symbol slhs = lhs->generateCode(context);
    Symbol srhs = rhs->generateCode(context);
    // TODO: check types 
    Symbol result = Symbol(DTINT, context.createReference());

    cout << context.createQuadruple(*operation, 3, result.reference.c_str(), slhs.reference.c_str(),
           srhs.reference.c_str());
    return result;
}

NBinaryOperation::~NBinaryOperation() {
    delete operation;
    delete lhs;
    delete rhs;
}

Symbol NAssignment::generateCode(Context &context) {
    Symbol srhs = rhs->generateCode(context);
    Symbol var = context.getSymbol(*(id->name));

    // TODO: optimize for a var on both sides
    cout << context.createQuadruple("MOV", 2, id->name->c_str(), srhs.reference.c_str());
    return var;
}

NAssignment::~NAssignment() {
    delete id;
    delete rhs;
}

Symbol NExpressionStatement::generateCode(Context &context) {
    if(expression) {
        expression->generateCode(context);
    }
    return Symbol(DTVOID, "");
}

NExpressionStatement::~NExpressionStatement() {
    if(expression) {
        delete expression;
    }
}

Symbol NVarDeclStatement::generateCode(Context &context) {
    context.insertSymbol(*varName, type);
    switch (type)
    {
        case DTINT:
            cout << context.createQuadruple("LOADi", 1, varName->c_str());
            break;
        case DTDOUBLE:
            cout << context.createQuadruple("LOADd", 1, varName->c_str());
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

Symbol NWhileStatement::generateCode(Context &context) {
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();

    cout << lbl1 << ":\n";
    expression->generateCode(context);
    cout << context.createQuadruple("JZ", 1, lbl2.c_str());
    block->generateCode(context);
    cout << context.createQuadruple("JMP", 1, lbl1.c_str());
    cout << lbl2 << ":\n";
    return Symbol(DTVOID, "");
}

Symbol NIfStatement::generateCode(Context &context) {
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();

    expression->generateCode(context);
    cout << context.createQuadruple("JZ", 1, lbl1.c_str());
    block->generateCode(context);
    if (elseBlock) {
        cout << context.createQuadruple("JMP", 1, lbl2.c_str());
        cout << lbl1 << ":\n";
        elseBlock->generateCode(context);
        cout << lbl2 << ":\n";
    } else {
        cout << lbl1 << ":\n";
    }
    return Symbol(DTVOID, "");
}

NIfStatement::~NIfStatement() {
    if(elseBlock) {
        delete elseBlock;
    }
}