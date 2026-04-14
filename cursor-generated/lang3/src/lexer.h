#pragma once

#include "token.h"

#include <string>

class Lexer {
 public:
  explicit Lexer(std::string input);

  Token nextToken();

 private:
  void readChar();
  char peekChar() const;
  void skipWhitespace();
  std::string readIdentifier();
  std::string readNumber();
  std::string readString();
  static TokenType lookupIdent(const std::string& ident);

  std::string input_;
  size_t position_{0};
  size_t read_position_{0};
  char ch_{0};
};
