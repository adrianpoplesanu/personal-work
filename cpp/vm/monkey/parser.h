#ifndef __PARSER_H
#define __PARSER_H

#include "lexer.h"
#include "ast.h"

class Parser {
public:
    Lexer lexer;

    Parser();
    void load(std::string);
    void buildProgramStatement(AstProgram&);
};

#endif