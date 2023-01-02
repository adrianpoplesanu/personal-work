#ifndef __PARSER
#define __PARSER

#include "lexer.h"
#include "token.h"
#include "ast.h"

#include <map>

enum PrecedenceTypeEnum {
    PT_LOWEST,
    PT_SUM,
    PT_MULTIPLY
};

std::map<TokenTypeEnum, PrecedenceTypeEnum> precedences = {
    {TT_PLUS, PT_SUM},
    {TT_MINUS, PT_SUM},
    {TT_MULTIPLY, PT_MULTIPLY},
    {TT_DIVIDE, PT_MULTIPLY}
};

class Parser {
    typedef ASTNode* (Parser::*PrefixCallback)();
    typedef ASTNode* (Parser::*InfixCallback)(ASTNode*);

public:
    Lexer lexer;
    std::string source;
    Token current_token;
    Token peek_token;
    std::map<TokenTypeEnum, PrefixCallback> prefixParseFns;
    std::map<TokenTypeEnum, InfixCallback> infixParseFns;

    Parser();
    void load(std::string);
    Token currentToken();
    Token peekToken();
    bool currentTokenIs(TokenTypeEnum);
    bool peekTokenIs(TokenTypeEnum);
    bool expectPeek(TokenTypeEnum);
    PrecedenceTypeEnum currentPrecedence();
    PrecedenceTypeEnum peekPrecedence();
    void nextToken();
    void parseProgram(ASTProgram&);
    ASTNode* parseStatement();
    ASTNode* parseExpressionStatement();
    ASTNode* parseExpression(PrecedenceTypeEnum);
    ASTNode* parsePrefixExpression();
    ASTNode* parseInfixExpression(ASTNode*);
    ASTNode* parseIntegerExpression();
    ASTNode* parseGroupedExpression();
};

#endif
