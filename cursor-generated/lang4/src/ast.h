#pragma once

#include "token.h"

#include <memory>
#include <string>
#include <vector>

struct Expression;
struct Statement;

struct Program {
  std::vector<std::unique_ptr<Statement>> statements;
};

struct BlockStatement {
  Token token;
  std::vector<std::unique_ptr<Statement>> statements;
};

struct Identifier {
  Token token;
  std::string value;
};

struct IntegerLiteral {
  Token token;
  int64_t value{0};
};

struct StringLiteral {
  Token token;
  std::string value;
};

struct BooleanLiteral {
  Token token;
  bool value{false};
};

struct PrefixExpression {
  Token op;
  std::unique_ptr<Expression> right;
};

struct InfixExpression {
  Token op;
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;
};

struct IfExpression {
  Token token;
  std::unique_ptr<Expression> condition;
  std::unique_ptr<BlockStatement> consequence;
  std::unique_ptr<BlockStatement> alternative;
};

struct FunctionLiteral {
  Token token;
  std::vector<Identifier> parameters;
  std::unique_ptr<BlockStatement> body;
  bool is_async{false};
};

struct CallExpression {
  Token token;
  std::unique_ptr<Expression> function;
  std::vector<std::unique_ptr<Expression>> arguments;
};

struct SpawnExpression {
  Token token;
  std::unique_ptr<Expression> function;
  std::vector<std::unique_ptr<Expression>> arguments;
};

struct AwaitExpression {
  Token token;
  std::unique_ptr<Expression> operand;
};

struct NewExpression {
  Token token;
  Identifier class_name;
  std::vector<std::unique_ptr<Expression>> arguments;
};

struct MemberExpression {
  Token token;
  std::unique_ptr<Expression> object;
  Identifier member;
};

struct AssignExpression {
  Token token;
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> value;
};

struct ArrayLiteral {
  Token token;
  std::vector<std::unique_ptr<Expression>> elements;
};

struct IndexExpression {
  Token token;
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> index;
};

struct ThisExpression {
  Token token;
};

struct ExpressionStatement {
  Token token;
  std::unique_ptr<Expression> expression;
};

struct LetStatement {
  Token token;
  Identifier name;
  std::unique_ptr<Expression> value;
};

struct ReturnStatement {
  Token token;
  std::unique_ptr<Expression> return_value;
};

struct MethodDefinition {
  Token token;
  Identifier name;
  std::vector<Identifier> parameters;
  std::unique_ptr<BlockStatement> body;
};

struct ClassStatement {
  Token token;
  Identifier name;
  std::vector<MethodDefinition> methods;
};

struct Expression {
  virtual ~Expression() = default;
};

struct IntegerLiteralExpr : Expression, IntegerLiteral {};
struct StringLiteralExpr : Expression, StringLiteral {};
struct BooleanLiteralExpr : Expression, BooleanLiteral {};
struct IdentifierExpr : Expression, Identifier {};
struct PrefixExpressionExpr : Expression, PrefixExpression {};
struct InfixExpressionExpr : Expression, InfixExpression {};
struct IfExpressionExpr : Expression, IfExpression {};
struct FunctionLiteralExpr : Expression, FunctionLiteral {};
struct CallExpressionExpr : Expression, CallExpression {};
struct SpawnExpressionExpr : Expression, SpawnExpression {};
struct AwaitExpressionExpr : Expression, AwaitExpression {};
struct NewExpressionExpr : Expression, NewExpression {};
struct MemberExpressionExpr : Expression, MemberExpression {};
struct AssignExpressionExpr : Expression, AssignExpression {};
struct ArrayLiteralExpr : Expression, ArrayLiteral {};
struct IndexExpressionExpr : Expression, IndexExpression {};
struct ThisExpressionExpr : Expression, ThisExpression {};

struct Statement {
  virtual ~Statement() = default;
};

struct ExpressionStatementStmt : Statement, ExpressionStatement {};
struct LetStatementStmt : Statement, LetStatement {};
struct ReturnStatementStmt : Statement, ReturnStatement {};
struct BlockStatementStmt : Statement, BlockStatement {};
struct ClassStatementStmt : Statement, ClassStatement {};
