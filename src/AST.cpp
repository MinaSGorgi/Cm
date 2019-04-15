#include "../src/AST.h"

#include <iostream>


Reference NChar::generateQuadruple(Context& context) const {
    std::cout << "Generating NChar: " << value << std::endl;
    return Reference(1, value);
}

Reference NInteger::generateQuadruple(Context& context) const {
    std::cout << "Generating NInteger: " << value << std::endl;
    return std::to_string(value);
}

Reference NDouble::generateQuadruple(Context& context) const {
    std::cout << "Generating NDouble: " << value << std::endl;
    return std::to_string(value);
}

Reference NIdentifier::generateQuadruple(Context& context) const {
    std::cout << "Generating NIdentifier: " << name << std::endl;
    return context.get_reference(name);
}

Reference NBinaryOperator::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NUnaryOperator::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NAssignment::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NBlock::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NExpressionStatement::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NFunctionCall::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NReturnStatement::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NVariableDeclaration::generateQuadruple(Context& context) const {
    return NULL;
}

Reference NFunctionDeclaration::generateQuadruple(Context& context) const {
    return NULL;
}