#include "parser.h"

Parser::Parser() {
    prefixParseFns.insert(std::make_pair(TT_IDENT, &Parser::parseIdent));
    prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
    infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_MULTIPLY, &Parser::parseInfixExpression));
    infixParseFns.insert(std::make_pair(TT_DIVIDE, &Parser::parseInfixExpression));
}

PrecedenceType Parser::currentPrecedence() {
    return precedenceMap[currentToken.type];
}

PrecedenceType Parser::peekPrecedence() {
    return precedenceMap[currentToken.type];
}

void Parser::load(std::string source) {
    lexer.load(source);
}

void Parser::buildProgramStatement(ASTProgram& program) {
    while(!lexer.isEOF()) {
        Token token = lexer.nextToken();
        std::cout << token.toString() << "\n";
    }
}

ASTNode* Parser::parseIdent() {
    ASTIdentifier *ident = new ASTIdentifier(currentToken, currentToken.stringLiteral);
    return ident;
}

ASTNode* Parser::parsePrefixExpression() {
    ASTPrefixExpression *expr = new ASTPrefixExpression();
    return NULL;
}

ASTNode* Parser::parseInfixExpression(ASTNode* left) {
    return NULL;
}

ASTNode* Parser::parseExpression(PrecedenceType precedence) {
    //...
    return NULL;
}