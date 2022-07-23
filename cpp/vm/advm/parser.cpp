#include "parser.h"

Parser::Parser() {
    prefixParseFns.insert(std::make_pair(TT_IDENT, &Parser::parseIdent));
    prefixParseFns.insert(std::make_pair(TT_MINUS, &Parser::parsePrefixExpression));
    infixParseFns.insert(std::make_pair(TT_PLUS, &Parser::parseInfixExpression));
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
    return NULL;
}

ASTNode* Parser::parsePrefixExpression() {
    return NULL;
}

ASTNode* Parser::parseInfixExpression(ASTNode* left) {
    return NULL;
}