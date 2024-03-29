#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.h"
#include "ast.h"

enum PrecedenceType {
    PT_LOWEST,
    PT_SUM,
    PT_PRODUCT
};

std::map<TokenType, PrecedenceType> precedenceMap = {
    {TT_PLUS, PT_SUM},
    {TT_MINUS, PT_SUM},
    {TT_MULTIPLY, PT_PRODUCT},
    {TT_DIVIDE, PT_PRODUCT}
};

class Parser {
public:
    Lexer lexer;
    Token currentToken;
    Token peekToken;

    typedef ASTNode* (Parser::*PrefixCallback)();
    typedef ASTNode* (Parser::*InfixCallback)(ASTNode*);

    std::map<TokenType, PrefixCallback> prefixParseFns;
    std::map<TokenType, InfixCallback> infixParseFns;

    Parser();
    void load(std::string);
    void buildProgramStatement(ASTProgram*);

    void nextToken();
    PrecedenceType currentPrecedence();
    PrecedenceType peekPrecedence();
    bool currentTokenIs(TokenType);
    bool peekTokenIs(TokenType);
    ASTNode* parseStatement();
    ASTNode* parseExpressionStatement();
    ASTNode* parseLetStatement();
    ASTNode* parseReturnStatement();
    ASTNode* parseBreakStatement();
    ASTNode* parseContinueStatement();
    ASTNode* parseComment();
    ASTNode* parseSingleLineComment();
    ASTNode* parseExpression(PrecedenceType);
    ASTNode* parsePrefixExpression();
    ASTNode* parseInfixExpression(ASTNode*);
    ASTNode* parseIdent();
    ASTNode* parseIntegerLiteral();
};

#endif