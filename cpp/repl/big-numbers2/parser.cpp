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

void Parser::buildProgramStatements(AstProgram program) {
    while(currentToken.getType() != TT_EOF) {
        std::cout << currentToken.toString() << "\n";
        AstNode* stmt = parseStatement();
        if (stmt) program.statements.push_back(stmt);
        nextToken();
    }
}

AstNode* Parser::parseStatement() {
    if (currentToken.getType == TT_LET) {
        //... return parseLetStatement();
    }
    //... return ParseExpressionStatement();
    return NULL;
}