#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.h"
#include "ast.h"

enum PrecedenceType {
    PT_LOWEST,
    PT_ASSIGN,
    PT_EQUALS,
    PT_CONDITIONAL,
    PT_LESSGREATER,
    PT_SUM,
    PT_PRODUCT,
    PT_PLUSPLUS,
    PT_PREFIX,
    PT_CALL,
    PT_INDEX,
    PT_MEMBERACCESS
};

std::map<TokenType, PrecedenceType> precedenceMap = {
    {TT_ASSIGN, PT_ASSIGN},
    {TT_EQ, PT_EQUALS},
    {TT_NOT_EQ, PT_EQUALS},
    {TT_LT, PT_LESSGREATER},
    {TT_GT, PT_LESSGREATER},
    {TT_LTE, PT_LESSGREATER},
    {TT_GTE, PT_LESSGREATER},
    {TT_AND, PT_CONDITIONAL},
    {TT_OR, PT_CONDITIONAL},
    {TT_PLUS, PT_SUM},
    {TT_MINUS, PT_SUM},
    {TT_DIVIDE, PT_PRODUCT},
    {TT_MODULUS, PT_PRODUCT},
    {TT_MULTIPLY, PT_PRODUCT},
    {TT_LPAREN, PT_CALL},
    {TT_LBRACKET, PT_INDEX},
    {TT_DOT, PT_MEMBERACCESS},
    {TT_PLUSPLUS, PT_PLUSPLUS},
    {TT_MINUSMINUS, PT_PLUSPLUS},
    {TT_PLUS_EQ, PT_ASSIGN},
    {TT_MINUS_EQ, PT_ASSIGN}
};

class Parser {
public:
    Lexer lexer;
    Token currentToken;
    Token peekToken;

    typedef ASTNode* (Parser::*PrefixCallback)();
    typedef ASTNode* (Parser::*InfixCallback)(ASTNode*);

    std::map<TokenType, PrefixCallback> statementParseFns;
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
    bool expectPeek(TokenType type);
    ASTNode *parseStatement();
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
    ASTNode* parseBooleanExpression();
    ASTNode* parseGroupedExpression();
    ASTNode* parseIfStatement();
    ASTNode* parseSingleBlockStatement();
    ASTNode* parseBlockStatement();
    ASTNode* parseNullExpression();
    ASTNode* parseStringLiteral();
    ASTNode* parseListLiteral();
    std::vector<ASTNode*> parseListExpressions();
    ASTNode* parseHashLiteral();
    ASTNode* parseIndexExpression(ASTNode*);
    ASTNode* parseFunctionLiteral();
    std::pair<std::vector<ASTNode*>, std::vector<ASTNode*>> parseFunctionParameters();
};

#endif