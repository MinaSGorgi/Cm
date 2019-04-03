#ifndef AST_H
#define AST_h

#include <string>


class NStatement;
class NExpression;
class NVariableDeclaration;


class Node {
public:
	virtual ~Node() {}
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NChar : public NExpression {
public:
	char value;
	NChar(char value) : value(value) { }
};

class NInteger : public NExpression {
public:
	int value;
	NInteger(int value) : value(value) { }
};

class NDouble : public NExpression {
public:
	double value;
	NDouble(double value) : value(value) { }
};

class NIdentifier : public NExpression {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
};

class NBinaryOperator : public NExpression {
public:
	int op;
	NExpression& lhs;
	NExpression& rhs;
	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
		lhs(lhs), rhs(rhs), op(op) { }
};

class NUnaryOperator : public NExpression {
public:
	int op;
	NExpression& expr;
	NUnaryOperator(int op, NExpression& expr) :
		op(op), expr(expr) { }
};

class NAssignment : public NExpression {
public:
	NIdentifier& lhs;
	NExpression& rhs;
	NAssignment(NIdentifier& lhs, NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& expression) : 
		expression(expression) { }
};


class NVariableDeclaration : public NStatement {
public:
	const NIdentifier& type;
	NIdentifier& id;
	NExpression *assignmentExpr;
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
		type(type), id(id) { assignmentExpr = NULL; }
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
		type(type), id(id), assignmentExpr(assignmentExpr) { }
};

#endif /* AST_H */