#ifndef AST_H
#define AST_h

#include "../src/asm.h"
#include "../src/context.h"

#include <string>
#include <vector>


class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
public:
	virtual ~Node() {}
	virtual Quadruple* generateQuadruple(Context& context) { return NULL; }
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NChar : public NExpression {
public:
	char value;
	NChar(char value) : value(value) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NInteger : public NExpression {
public:
	int value;
	NInteger(int value) : value(value) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NDouble : public NExpression {
public:
	double value;
	NDouble(double value) : value(value) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NIdentifier : public NExpression {
public:
	std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NBinaryOperator : public NExpression {
public:
	int op;
	NExpression& lhs;
	NExpression& rhs;
	NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
		lhs(lhs), rhs(rhs), op(op) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NUnaryOperator : public NExpression {
public:
	int op;
	NExpression& expr;
	NUnaryOperator(int op, NExpression& expr) :
		op(op), expr(expr) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NAssignment : public NExpression {
public:
	NIdentifier& lhs;
	NExpression& rhs;
	NAssignment(NIdentifier& lhs, NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NBlock : public NExpression {
public:
    StatementList statements;
    NBlock() { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& expression) : 
		expression(expression) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NFunctionCall : public NExpression {
public:
	const NIdentifier& id;
	ExpressionList arguments;
	NFunctionCall(const NIdentifier& id, ExpressionList& arguments) :
		id(id), arguments(arguments) { }
	NFunctionCall(const NIdentifier& id) : id(id) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

class NReturnStatement : public NStatement {
public:
	NExpression& expression;
	NReturnStatement(NExpression& expression) : 
		expression(expression) { }
	virtual Quadruple* generateQuadruple(Context& context);
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
	virtual Quadruple* generateQuadruple(Context& context);
};

class NFunctionDeclaration : public NStatement {
public:
	const NIdentifier& type;
	const NIdentifier& id;
	VariableList arguments;
	NBlock& block;
	NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
			const VariableList& arguments, NBlock& block) :
		type(type), id(id), arguments(arguments), block(block) { }
	virtual Quadruple* generateQuadruple(Context& context);
};

#endif /* AST_H */