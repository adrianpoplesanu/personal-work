#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.h"
#include "ast.h"

enum PrecedenceType {
    PT_LOWEST,
    PT_SUM,
    PT_PRODUCT
};

class Parser {
public:
    Lexer lexer;

    Parser();
    void load(std::string);
    void buildProgramStatement(AstProgram&);

    // parseExpressionStatement
    // parseLetStatement
    // parseReturnStatement
    // parseExpression(LOWEST)
    // parsePrefixExpression
    // parseInfixExpression
};

#endif