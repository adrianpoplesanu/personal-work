#include "parser.h"

Parser::Parser() {
    // ...
}

void Parser::load(std::string source) {
    lexer.load(source);
}

void Parser::buildProgramStatement(AstProgram& program) {
    while(!lexer.isEOF()) {
        Token token = lexer.nextToken();
        std::cout << token.toString() << "\n";
    }
}