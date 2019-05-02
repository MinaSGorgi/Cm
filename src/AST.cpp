#include <iostream>
#include <stdio.h>
#include "../include/AST.hpp"
#include "../include/errors.hpp"
#include "../build/parser.hpp"
using namespace std;


Symbol NBlock::generateQuadruple(Context &context) {
    context.newScope();
    for(NStatement *statement: statements) {
        statement->generateQuadruple(context);
    }
    context.deleteScope();
    return Symbol(DTVOID, true, true, "");
}

NBlock::~NBlock() {
    for(NStatement *statement: statements) {
        delete statement;
    }
}

Symbol NInteger::generateQuadruple(Context &context) {
    return Symbol(DTINT, true, true, to_string(value));
}

Symbol NDouble::generateQuadruple(Context &context) {
    return Symbol(DTDOUBLE, true, true, to_string(value));
}

Symbol NVariable::generateQuadruple(Context &context) {
    return *context.getSymbol(*name);
}

NVariable::~NVariable() {
    delete name;
}

Symbol NUnaryOperation::generateQuadruple(Context &context) {
    Symbol sexpr = expr->generateQuadruple(context);
    Symbol result = Symbol(sexpr.type, true, true, context.createReference());
    if(!sexpr.initialized) {
        throw Uninitialized(sexpr.reference);
    }

    context.addQuadruple(new AOperation(*operation, 2, result.reference.c_str(),
                                        sexpr.reference.c_str()));
    return result;
}

NUnaryOperation::~NUnaryOperation() {
    delete operation;
    delete expr;
}

Symbol NBinaryOperation::generateQuadruple(Context &context) {
    Symbol slhs = lhs->generateQuadruple(context);
    Symbol srhs = rhs->generateQuadruple(context);
    if(slhs.type != srhs.type) {
        throw TypeMismatch(slhs.reference, srhs.reference, slhs.getType(), srhs.getType());
    }

    Symbol result = Symbol(slhs.type, true, true, context.createReference());
    if(!slhs.initialized) {
        throw Uninitialized(slhs.reference);
    }
    if(!srhs.initialized) {
        throw Uninitialized(srhs.reference);
    }

    context.addQuadruple(new AOperation(*operation, 3, result.reference.c_str(),
                                        slhs.reference.c_str(), srhs.reference.c_str()));
    return result;
}

NBinaryOperation::~NBinaryOperation() {
    delete operation;
    delete lhs;
    delete rhs;
}

Symbol NAssignment::generateQuadruple(Context &context) {
    Symbol srhs = rhs->generateQuadruple(context);
    Symbol *var = context.getSymbol(*(id->name));
    if(var->type != srhs.type) {
        throw TypeMismatch(var->reference, srhs.reference, var->getType(), srhs.getType());
    }
    if(var->constant) {
        throw ReadOnly(var->reference.c_str());
    }
    var->initialized = true;

    context.addQuadruple(new AOperation("MOV", 2, id->name->c_str(), srhs.reference.c_str()));

    return *var;
}

NAssignment::~NAssignment() {
    delete id;
    delete rhs;
}

Symbol NExpressionStatement::generateQuadruple(Context &context) {
    if(expression) {
        expression->generateQuadruple(context);
    }
    return Symbol(DTVOID, true, true, "");
}

NExpressionStatement::~NExpressionStatement() {
    if(expression) {
        delete expression;
    }
}

Symbol NVarDeclStatement::generateQuadruple(Context &context) {
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

    bool initialized = false;
    if(rhs) {
        initialized = true;
        Symbol srhs = rhs->generateQuadruple(context);
        context.addQuadruple(new AOperation("MOV", 2, varName->c_str(), srhs.reference.c_str()));
    }

    context.insertSymbol(*varName, type, initialized, constant);
    return Symbol(DTVOID, true, true, "");
}

NVarDeclStatement::~NVarDeclStatement() {
    delete varName;
    if(rhs) {
        delete rhs;
    }
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
    return Symbol(DTVOID, true, true, "");
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
    return Symbol(DTVOID, true, true, "");
}

NIfStatement::~NIfStatement() {
    if(elseBlock) {
        delete elseBlock;
    }
}