#ifndef __PARSER
#define __PARSER

#include "lexer.h"
#include "token.h"
#include "ast.h"

class Parser {
public:
    Lexer lexer;
    std::string source;
    Token current_token;
    Token peek_token;

    void load(std::string);
    Token currentToken();
    Token peekToken();
    void nextToken();
    void parseProgram(ASTProgram&);
    ASTNode* parseStatement();
    ASTNode* parseExpressionStatement();
};

#endif
