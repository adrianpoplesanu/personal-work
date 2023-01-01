#include "parser.h"

void Parser::load(std::string s) {
    source = s;
    lexer.load(source);
    nextToken();
    nextToken();
}

void Parser::nextToken() {
    current_token = peek_token;
    peek_token = lexer.nextToken();
}

Token Parser::currentToken() {
    return current_token;
}

Token Parser::peekToken() {
    return peek_token;
}

void Parser::parseProgram(ASTProgram& program) {
    while(current_token.type != TT_EOF) {
        std::cout << current_token.toString() << "\n";
        ASTNode* node = parseStatement();
        program.statements.push_back(node);
        nextToken();
    }
}

ASTNode* Parser::parseStatement() {
    return NULL;
}

ASTNode* Parser::parseExpressionStatement() {
    return NULL;
}