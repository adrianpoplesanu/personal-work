#pragma once

#include <string>

enum class TokenType {
  ILLEGAL,
  END,

  IDENT,
  INT,
  STRING,

  ASSIGN,
  PLUS,
  MINUS,
  BANG,
  ASTERISK,
  SLASH,
  PERCENT,

  LT,
  GT,
  LT_EQ,
  GT_EQ,
  EQ,
  NOT_EQ,

  COMMA,
  SEMICOLON,
  COLON,
  DOT,

  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  LBRACKET,
  RBRACKET,

  FUNCTION,
  LET,
  RETURN,
  TRUE,
  FALSE,
  IF,
  ELSE,

  CLASS,
  NEW,
  THIS,
  SPAWN,
  ASYNC,
  AWAIT,
};

struct Token {
  TokenType type{TokenType::ILLEGAL};
  std::string literal;

  static std::string typeName(TokenType t);
};
