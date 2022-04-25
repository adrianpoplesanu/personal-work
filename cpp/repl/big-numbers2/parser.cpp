#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::load(std::string source) {
    lexer.load(source);
    nextToken();
    nextToken();
}

void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.nextToken();
}

void Parser::buildProgramStatements() {
    while(currentToken.getType() != TT_EOF) {
        std::cout << currentToken.toString() << "\n";
        nextToken();
    }
}