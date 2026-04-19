#pragma once

#include "ast.h"
#include "lexer.h"

#include <memory>
#include <string>
#include <vector>

enum class Precedence {
  LOWEST,
  ASSIGN,      // =
  EQUALS,      // ==
  LESSGREATER, // > or <
  SUM,         // +
  PRODUCT,     // *
  PREFIX,      // - or !
  CALL,        // call(
  INDEX,       // [
  MEMBER,      // .
};

class Parser {
 public:
  explicit Parser(Lexer&& lexer);

  std::unique_ptr<Program> parseProgram();

  const std::vector<std::string>& errors() const { return errors_; }

 private:
  void nextToken();
  bool curTokenIs(TokenType t) const;
  bool peekTokenIs(TokenType t) const;
  bool expectPeek(TokenType t);

  Precedence peekPrecedence() const;
  Precedence curPrecedence() const;

  std::unique_ptr<Statement> parseStatement();
  std::unique_ptr<LetStatementStmt> parseLetStatement();
  std::unique_ptr<ReturnStatementStmt> parseReturnStatement();
  std::unique_ptr<ExpressionStatementStmt> parseExpressionStatement();
  std::unique_ptr<BlockStatement> parseBlockStatement();
  std::unique_ptr<ClassStatementStmt> parseClassStatement();

  std::unique_ptr<Expression> parseExpression(Precedence prec);
  std::unique_ptr<Expression> parsePrefixExpression();

  std::unique_ptr<Expression> parseIdentifier();
  std::unique_ptr<Expression> parseIntegerLiteral();
  std::unique_ptr<Expression> parseStringLiteral();
  std::unique_ptr<Expression> parseBooleanLiteral();
  std::unique_ptr<Expression> parseGroupedExpression();
  std::unique_ptr<Expression> parseIfExpression();
  std::unique_ptr<Expression> parseFunctionLiteral(bool is_async = false);
  std::unique_ptr<Expression> parseAwaitExpression();
  std::unique_ptr<Expression> parseNewExpression();
  std::unique_ptr<Expression> parseArrayLiteral();
  std::unique_ptr<Expression> parseThisExpression();
  std::unique_ptr<Expression> parseSpawnExpression();

  std::vector<Identifier> parseFunctionParameters();
  MethodDefinition parseMethodDefinition();

  Lexer lexer_;
  Token cur_token_;
  Token peek_token_;

  std::vector<std::string> errors_;
};
