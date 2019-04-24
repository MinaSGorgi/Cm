#ifndef AST_H
#define AST_h

#include "../src/context.h"

#include <string>
#include <vector>

class Context;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> NStatementList;
typedef std::vector<NExpression*> NExpressionList;
typedef std::vector<NVariableDeclaration*> NVariableList;

class Node {
public:
	virtual ~Node() { }
	virtual Symbol generateQuadruple(Context& context) const { return Symbol("", NONE); }
};

class NExpression : public Node {
};

class NStatement : public Node {
};

class NChar : public NExpression {
public:
	const char value;
	NChar(char value) : value(value) { }
	virtual Symbol generateQuadruple (Context& context) const;
};

class NInteger : public NExpression {
public:
	const int value;
	NInteger(int value) : value(value) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NDouble : public NExpression {
public:
	const double value;
	NDouble(double value) : value(value) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NIdentifier : public NExpression {
public:
	const std::string name;
	NIdentifier(const std::string& name) : name(name) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NBinaryOperator : public NExpression {
public:
	const int op;
	const NExpression lhs, rhs;
	NBinaryOperator(const NExpression& lhs, int op, const NExpression& rhs) :
		op(op), lhs(lhs), rhs(rhs) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NUnaryOperator : public NExpression {
public:
	const int op;
	const NExpression expression;
	NUnaryOperator(int op, const NExpression& expression) :
		op(op), expression(expression) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NAssignment : public NExpression {
public:
	const NIdentifier lhs;
	const NExpression rhs;
	NAssignment(const NIdentifier& lhs, const NExpression& rhs) : 
		lhs(lhs), rhs(rhs) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NBlock : public NExpression {
public:
    NStatementList statements;
    NBlock() { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NExpressionStatement : public NStatement {
public:
	const NExpression expression;
	NExpressionStatement(const NExpression& expression) : 
		expression(expression) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NFunctionCall : public NExpression {
public:
	const NIdentifier id;
	NExpressionList arguments;
	NFunctionCall(const NIdentifier& id, NExpressionList& arguments) :
		id(id), arguments(arguments) { }
	NFunctionCall(const NIdentifier& id) : id(id) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NReturnStatement : public NStatement {
public:
	const NExpression expression;
	NReturnStatement(const NExpression& expression) : 
		expression(expression) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NVariableDeclaration : public NStatement {
public:
	const NIdentifier type;
	const NIdentifier id;
	const NExpression *assignmentExpr;
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
		type(type), id(id), assignmentExpr(NULL) { }
	NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
		type(type), id(id), assignmentExpr(assignmentExpr) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

class NFunctionDeclaration : public NStatement {
public:
	const NIdentifier type;
	const NIdentifier id;
	NVariableList arguments;
	const NBlock block;
	NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id, 
			const NVariableList& arguments, NBlock& block) :
		type(type), id(id), arguments(arguments), block(block) { }
	virtual Symbol generateQuadruple(Context& context) const;
};

#endif /* AST_H */