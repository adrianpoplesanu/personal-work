#include "parser.h"

#include <sstream>

namespace {

Precedence tokenToPrecedence(TokenType t) {
  switch (t) {
    case TokenType::EQ:
    case TokenType::NOT_EQ:
      return Precedence::EQUALS;
    case TokenType::LT:
    case TokenType::GT:
    case TokenType::LT_EQ:
    case TokenType::GT_EQ:
      return Precedence::LESSGREATER;
    case TokenType::PLUS:
    case TokenType::MINUS:
      return Precedence::SUM;
    case TokenType::ASTERISK:
    case TokenType::SLASH:
    case TokenType::PERCENT:
      return Precedence::PRODUCT;
    case TokenType::LPAREN:
      return Precedence::CALL;
    case TokenType::LBRACKET:
      return Precedence::INDEX;
    case TokenType::DOT:
      return Precedence::MEMBER;
    case TokenType::ASSIGN:
      return Precedence::ASSIGN;
    default:
      return Precedence::LOWEST;
  }
}

bool isAssignable(const Expression* expr) {
  return dynamic_cast<const IdentifierExpr*>(expr) != nullptr ||
         dynamic_cast<const MemberExpressionExpr*>(expr) != nullptr ||
         dynamic_cast<const IndexExpressionExpr*>(expr) != nullptr;
}

bool isGenericInfixPeek(TokenType t) {
  switch (t) {
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::SLASH:
    case TokenType::ASTERISK:
    case TokenType::PERCENT:
    case TokenType::EQ:
    case TokenType::NOT_EQ:
    case TokenType::LT:
    case TokenType::GT:
    case TokenType::LT_EQ:
    case TokenType::GT_EQ:
      return true;
    default:
      return false;
  }
}

}  // namespace

Parser::Parser(Lexer&& lexer) : lexer_(std::move(lexer)) {
  nextToken();
  nextToken();
}

void Parser::nextToken() {
  cur_token_ = peek_token_;
  peek_token_ = lexer_.nextToken();
}

bool Parser::curTokenIs(TokenType t) const { return cur_token_.type == t; }

bool Parser::peekTokenIs(TokenType t) const { return peek_token_.type == t; }

bool Parser::expectPeek(TokenType t) {
  if (peekTokenIs(t)) {
    nextToken();
    return true;
  }
  std::ostringstream os;
  os << "expected next token to be " << Token::typeName(t) << ", got "
     << Token::typeName(peek_token_.type) << " instead";
  errors_.push_back(os.str());
  return false;
}

Precedence Parser::peekPrecedence() const { return tokenToPrecedence(peek_token_.type); }

Precedence Parser::curPrecedence() const { return tokenToPrecedence(cur_token_.type); }

std::unique_ptr<Program> Parser::parseProgram() {
  auto program = std::make_unique<Program>();
  while (!curTokenIs(TokenType::END)) {
    if (curTokenIs(TokenType::SEMICOLON)) {
      nextToken();
      continue;
    }
    auto stmt = parseStatement();
    if (stmt) {
      program->statements.push_back(std::move(stmt));
    }
    nextToken();
  }
  return program;
}

std::unique_ptr<Statement> Parser::parseStatement() {
  switch (cur_token_.type) {
    case TokenType::LET:
      return parseLetStatement();
    case TokenType::RETURN:
      return parseReturnStatement();
    case TokenType::CLASS:
      return parseClassStatement();
    case TokenType::LBRACE: {
      auto block = parseBlockStatement();
      auto stmt = std::make_unique<BlockStatementStmt>();
      stmt->token = block->token;
      stmt->statements = std::move(block->statements);
      return stmt;
    }
    default:
      return parseExpressionStatement();
  }
}

std::unique_ptr<LetStatementStmt> Parser::parseLetStatement() {
  auto stmt = std::make_unique<LetStatementStmt>();
  stmt->token = cur_token_;
  if (!expectPeek(TokenType::IDENT)) {
    return nullptr;
  }
  stmt->name = Identifier{cur_token_, cur_token_.literal};
  if (!expectPeek(TokenType::ASSIGN)) {
    return nullptr;
  }
  nextToken();
  stmt->value = parseExpression(Precedence::LOWEST);
  if (peekTokenIs(TokenType::SEMICOLON)) {
    nextToken();
  }
  return stmt;
}

std::unique_ptr<ReturnStatementStmt> Parser::parseReturnStatement() {
  auto stmt = std::make_unique<ReturnStatementStmt>();
  stmt->token = cur_token_;
  nextToken();
  if (!curTokenIs(TokenType::SEMICOLON)) {
    stmt->return_value = parseExpression(Precedence::LOWEST);
  }
  if (peekTokenIs(TokenType::SEMICOLON)) {
    nextToken();
  }
  return stmt;
}

std::unique_ptr<ExpressionStatementStmt> Parser::parseExpressionStatement() {
  auto stmt = std::make_unique<ExpressionStatementStmt>();
  stmt->token = cur_token_;
  stmt->expression = parseExpression(Precedence::LOWEST);
  if (peekTokenIs(TokenType::SEMICOLON)) {
    nextToken();
  }
  return stmt;
}

std::unique_ptr<BlockStatement> Parser::parseBlockStatement() {
  auto block = std::make_unique<BlockStatement>();
  block->token = cur_token_;
  nextToken();
  while (!curTokenIs(TokenType::RBRACE) && !curTokenIs(TokenType::END)) {
    auto stmt = parseStatement();
    if (stmt) {
      block->statements.push_back(std::move(stmt));
    }
    nextToken();
  }
  return block;
}

std::unique_ptr<ClassStatementStmt> Parser::parseClassStatement() {
  auto stmt = std::make_unique<ClassStatementStmt>();
  stmt->token = cur_token_;
  if (!expectPeek(TokenType::IDENT)) {
    return nullptr;
  }
  stmt->name = Identifier{cur_token_, cur_token_.literal};
  if (!expectPeek(TokenType::LBRACE)) {
    return nullptr;
  }
  nextToken();
  while (curTokenIs(TokenType::FUNCTION)) {
    stmt->methods.push_back(parseMethodDefinition());
    nextToken();
  }
  if (!curTokenIs(TokenType::RBRACE)) {
    errors_.push_back("expected } after class body");
    return nullptr;
  }
  return stmt;
}

MethodDefinition Parser::parseMethodDefinition() {
  MethodDefinition m;
  m.token = cur_token_;
  if (!expectPeek(TokenType::IDENT)) {
    return m;
  }
  m.name = Identifier{cur_token_, cur_token_.literal};
  if (!expectPeek(TokenType::LPAREN)) {
    return m;
  }
  m.parameters = parseFunctionParameters();
  if (!expectPeek(TokenType::LBRACE)) {
    return m;
  }
  m.body = parseBlockStatement();
  return m;
}

std::vector<Identifier> Parser::parseFunctionParameters() {
  std::vector<Identifier> params;
  if (peekTokenIs(TokenType::RPAREN)) {
    nextToken();
    return params;
  }
  nextToken();
  params.push_back(Identifier{cur_token_, cur_token_.literal});
  while (peekTokenIs(TokenType::COMMA)) {
    nextToken();
    if (!expectPeek(TokenType::IDENT)) {
      return params;
    }
    params.push_back(Identifier{cur_token_, cur_token_.literal});
  }
  if (!expectPeek(TokenType::RPAREN)) {
    return params;
  }
  return params;
}

std::unique_ptr<Expression> Parser::parseExpression(Precedence prec) {
  auto left = parsePrefixExpression();
  if (!left) {
    return nullptr;
  }
  while (!peekTokenIs(TokenType::SEMICOLON) && prec < peekPrecedence()) {
    if (peekTokenIs(TokenType::LPAREN)) {
      nextToken();
      auto call = std::make_unique<CallExpressionExpr>();
      call->token = cur_token_;
      call->function = std::move(left);
      if (!peekTokenIs(TokenType::RPAREN)) {
        nextToken();
        call->arguments.push_back(parseExpression(Precedence::LOWEST));
        while (peekTokenIs(TokenType::COMMA)) {
          nextToken();
          nextToken();
          call->arguments.push_back(parseExpression(Precedence::LOWEST));
        }
      }
      if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
      }
      left = std::move(call);
      continue;
    }
    if (peekTokenIs(TokenType::DOT)) {
      nextToken();
      auto mem = std::make_unique<MemberExpressionExpr>();
      mem->token = cur_token_;
      mem->object = std::move(left);
      if (!expectPeek(TokenType::IDENT)) {
        return nullptr;
      }
      mem->member = Identifier{cur_token_, cur_token_.literal};
      left = std::move(mem);
      continue;
    }
    if (peekTokenIs(TokenType::LBRACKET)) {
      nextToken();
      auto ix = std::make_unique<IndexExpressionExpr>();
      ix->token = cur_token_;
      ix->left = std::move(left);
      nextToken();
      ix->index = parseExpression(Precedence::LOWEST);
      if (!expectPeek(TokenType::RBRACKET)) {
        return nullptr;
      }
      left = std::move(ix);
      continue;
    }
    if (peekTokenIs(TokenType::ASSIGN)) {
      if (!isAssignable(left.get())) {
        errors_.push_back("left side of = must be identifier or member expression");
        return left;
      }
      nextToken();
      auto asg = std::make_unique<AssignExpressionExpr>();
      asg->token = cur_token_;
      asg->left = std::move(left);
      nextToken();
      asg->value = parseExpression(Precedence::LOWEST);
      left = std::move(asg);
      continue;
    }
    if (!isGenericInfixPeek(peek_token_.type)) {
      return left;
    }
    nextToken();
    auto inf = std::make_unique<InfixExpressionExpr>();
    inf->op = cur_token_;
    inf->left = std::move(left);
    Precedence p = curPrecedence();
    nextToken();
    inf->right = parseExpression(p);
    left = std::move(inf);
  }
  return left;
}

std::unique_ptr<Expression> Parser::parsePrefixExpression() {
  switch (cur_token_.type) {
    case TokenType::IDENT:
      return parseIdentifier();
    case TokenType::THIS:
      return parseThisExpression();
    case TokenType::LBRACKET:
      return parseArrayLiteral();
    case TokenType::INT:
      return parseIntegerLiteral();
    case TokenType::STRING:
      return parseStringLiteral();
    case TokenType::TRUE:
    case TokenType::FALSE:
      return parseBooleanLiteral();
    case TokenType::BANG:
    case TokenType::MINUS: {
      auto expr = std::make_unique<PrefixExpressionExpr>();
      expr->op = cur_token_;
      nextToken();
      expr->right = parseExpression(Precedence::PREFIX);
      return expr;
    }
    case TokenType::LPAREN: {
      nextToken();
      auto e = parseExpression(Precedence::LOWEST);
      if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
      }
      return e;
    }
    case TokenType::IF:
      return parseIfExpression();
    case TokenType::FUNCTION:
      return parseFunctionLiteral();
    case TokenType::NEW:
      return parseNewExpression();
    default: {
      std::ostringstream os;
      os << "no prefix parse function for " << Token::typeName(cur_token_.type);
      errors_.push_back(os.str());
      return nullptr;
    }
  }
}

std::unique_ptr<Expression> Parser::parseIdentifier() {
  auto e = std::make_unique<IdentifierExpr>();
  e->token = cur_token_;
  e->value = cur_token_.literal;
  return e;
}

std::unique_ptr<Expression> Parser::parseIntegerLiteral() {
  auto lit = std::make_unique<IntegerLiteralExpr>();
  lit->token = cur_token_;
  try {
    lit->value = std::stoll(cur_token_.literal);
  } catch (...) {
    errors_.push_back("could not parse " + cur_token_.literal + " as integer");
    return nullptr;
  }
  return lit;
}

std::unique_ptr<Expression> Parser::parseStringLiteral() {
  auto lit = std::make_unique<StringLiteralExpr>();
  lit->token = cur_token_;
  lit->value = cur_token_.literal;
  return lit;
}

std::unique_ptr<Expression> Parser::parseBooleanLiteral() {
  auto lit = std::make_unique<BooleanLiteralExpr>();
  lit->token = cur_token_;
  lit->value = cur_token_.type == TokenType::TRUE;
  return lit;
}

std::unique_ptr<Expression> Parser::parseIfExpression() {
  auto expr = std::make_unique<IfExpressionExpr>();
  expr->token = cur_token_;
  if (!expectPeek(TokenType::LPAREN)) {
    return nullptr;
  }
  nextToken();
  expr->condition = parseExpression(Precedence::LOWEST);
  if (!expectPeek(TokenType::RPAREN)) {
    return nullptr;
  }
  if (!expectPeek(TokenType::LBRACE)) {
    return nullptr;
  }
  expr->consequence = parseBlockStatement();
  if (peekTokenIs(TokenType::ELSE)) {
    nextToken();
    if (!expectPeek(TokenType::LBRACE)) {
      return nullptr;
    }
    expr->alternative = parseBlockStatement();
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parseFunctionLiteral() {
  auto lit = std::make_unique<FunctionLiteralExpr>();
  lit->token = cur_token_;
  if (!expectPeek(TokenType::LPAREN)) {
    return nullptr;
  }
  lit->parameters = parseFunctionParameters();
  if (!expectPeek(TokenType::LBRACE)) {
    return nullptr;
  }
  lit->body = parseBlockStatement();
  return lit;
}

std::unique_ptr<Expression> Parser::parseNewExpression() {
  auto expr = std::make_unique<NewExpressionExpr>();
  expr->token = cur_token_;
  if (!expectPeek(TokenType::IDENT)) {
    return nullptr;
  }
  expr->class_name = Identifier{cur_token_, cur_token_.literal};
  if (!expectPeek(TokenType::LPAREN)) {
    return nullptr;
  }
  nextToken();
  if (!curTokenIs(TokenType::RPAREN)) {
    expr->arguments.push_back(parseExpression(Precedence::LOWEST));
    while (peekTokenIs(TokenType::COMMA)) {
      nextToken();
      nextToken();
      expr->arguments.push_back(parseExpression(Precedence::LOWEST));
    }
  }
  if (!expectPeek(TokenType::RPAREN)) {
    return nullptr;
  }
  return expr;
}

std::unique_ptr<Expression> Parser::parseThisExpression() {
  auto e = std::make_unique<ThisExpressionExpr>();
  e->token = cur_token_;
  return e;
}

std::unique_ptr<Expression> Parser::parseArrayLiteral() {
  auto arr = std::make_unique<ArrayLiteralExpr>();
  arr->token = cur_token_;
  if (peekTokenIs(TokenType::RBRACKET)) {
    nextToken();
    return arr;
  }
  nextToken();
  arr->elements.push_back(parseExpression(Precedence::LOWEST));
  while (peekTokenIs(TokenType::COMMA)) {
    nextToken();
    nextToken();
    arr->elements.push_back(parseExpression(Precedence::LOWEST));
  }
  if (!expectPeek(TokenType::RBRACKET)) {
    return nullptr;
  }
  return arr;
}
