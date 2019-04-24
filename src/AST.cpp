#include "../src/AST.h"

#include <iostream>


Symbol NChar::generateQuadruple(Context& context) const {
    std::cout << "Generating NChar: " << value << std::endl;
    return Symbol(std::string(1, value), CHAR);
}

Symbol NInteger::generateQuadruple(Context& context) const {
    std::cout << "Generating NInteger: " << value << std::endl;
    return Symbol(std::to_string(value), INT);
}

Symbol NDouble::generateQuadruple(Context& context) const {
    std::cout << "Generating NDouble: " << value << std::endl;
    return Symbol(std::to_string(value), DOUBLE);
}

Symbol NIdentifier::generateQuadruple(Context& context) const {
    std::cout << "Generating NIdentifier: " << name << std::endl;
    return context.get_symbol(name);
}

Symbol NBinaryOperator::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NUnaryOperator::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NAssignment::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NBlock::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NExpressionStatement::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NFunctionCall::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NReturnStatement::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NVariableDeclaration::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}

Symbol NFunctionDeclaration::generateQuadruple(Context& context) const {
    return Symbol("", NONE);
}