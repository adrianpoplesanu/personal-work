#include "lexer.h"

#include <cctype>
#include <unordered_map>

namespace {

bool isLetter(char ch) {
  return std::isalpha(static_cast<unsigned char>(ch)) || ch == '_';
}

bool isDigit(char ch) { return std::isdigit(static_cast<unsigned char>(ch)); }

}  // namespace

Lexer::Lexer(std::string input) : input_(std::move(input)) { readChar(); }

void Lexer::readChar() {
  if (read_position_ >= input_.size()) {
    ch_ = 0;
  } else {
    ch_ = input_[read_position_];
  }
  position_ = read_position_;
  read_position_ += 1;
}

char Lexer::peekChar() const {
  if (read_position_ >= input_.size()) return 0;
  return input_[read_position_];
}

void Lexer::skipWhitespace() {
  while (ch_ == ' ' || ch_ == '\t' || ch_ == '\r' || ch_ == '\n') {
    readChar();
  }
}

std::string Lexer::readIdentifier() {
  size_t pos = position_;
  while (isLetter(ch_) || isDigit(ch_)) {
    readChar();
  }
  return input_.substr(pos, position_ - pos);
}

std::string Lexer::readNumber() {
  size_t pos = position_;
  while (isDigit(ch_)) {
    readChar();
  }
  return input_.substr(pos, position_ - pos);
}

std::string Lexer::readString() {
  readChar();  // skip opening "
  size_t pos = position_;
  while (ch_ != '"' && ch_ != 0) {
    readChar();
  }
  std::string s = input_.substr(pos, position_ - pos);
  if (ch_ == '"') readChar();
  return s;
}

TokenType Lexer::lookupIdent(const std::string& ident) {
  static const std::unordered_map<std::string, TokenType> kws = {
      {"fn", TokenType::FUNCTION},
      {"let", TokenType::LET},
      {"return", TokenType::RETURN},
      {"true", TokenType::TRUE},
      {"false", TokenType::FALSE},
      {"if", TokenType::IF},
      {"else", TokenType::ELSE},
      {"class", TokenType::CLASS},
      {"new", TokenType::NEW},
      {"this", TokenType::THIS},
      {"spawn", TokenType::SPAWN},
      {"async", TokenType::ASYNC},
      {"await", TokenType::AWAIT},
  };
  auto it = kws.find(ident);
  if (it != kws.end()) return it->second;
  return TokenType::IDENT;
}

Token Lexer::nextToken() {
  skipWhitespace();
  Token tok;
  tok.literal = std::string(1, ch_);

  switch (ch_) {
    case '=':
      if (peekChar() == '=') {
        readChar();
        tok.type = TokenType::EQ;
        tok.literal = "==";
      } else {
        tok.type = TokenType::ASSIGN;
      }
      break;
    case '+':
      tok.type = TokenType::PLUS;
      break;
    case '-':
      tok.type = TokenType::MINUS;
      break;
    case '!':
      if (peekChar() == '=') {
        readChar();
        tok.type = TokenType::NOT_EQ;
        tok.literal = "!=";
      } else {
        tok.type = TokenType::BANG;
      }
      break;
    case '*':
      tok.type = TokenType::ASTERISK;
      break;
    case '/':
      tok.type = TokenType::SLASH;
      break;
    case '%':
      tok.type = TokenType::PERCENT;
      break;
    case '<':
      if (peekChar() == '=') {
        readChar();
        tok.type = TokenType::LT_EQ;
        tok.literal = "<=";
      } else {
        tok.type = TokenType::LT;
      }
      break;
    case '>':
      if (peekChar() == '=') {
        readChar();
        tok.type = TokenType::GT_EQ;
        tok.literal = ">=";
      } else {
        tok.type = TokenType::GT;
      }
      break;
    case ',':
      tok.type = TokenType::COMMA;
      break;
    case ';':
      tok.type = TokenType::SEMICOLON;
      break;
    case ':':
      tok.type = TokenType::COLON;
      break;
    case '.':
      tok.type = TokenType::DOT;
      break;
    case '(':
      tok.type = TokenType::LPAREN;
      break;
    case ')':
      tok.type = TokenType::RPAREN;
      break;
    case '{':
      tok.type = TokenType::LBRACE;
      break;
    case '}':
      tok.type = TokenType::RBRACE;
      break;
    case '[':
      tok.type = TokenType::LBRACKET;
      break;
    case ']':
      tok.type = TokenType::RBRACKET;
      break;
    case '"': {
      tok.type = TokenType::STRING;
      tok.literal = readString();
      return tok;
    }
    case 0:
      tok.type = TokenType::END;
      tok.literal = "";
      return tok;
    default:
      if (isLetter(ch_)) {
        tok.literal = readIdentifier();
        tok.type = lookupIdent(tok.literal);
        return tok;
      }
      if (isDigit(ch_)) {
        tok.type = TokenType::INT;
        tok.literal = readNumber();
        return tok;
      }
      tok.type = TokenType::ILLEGAL;
      break;
  }

  readChar();
  return tok;
}
