#ifndef __PARSER
#define __PARSER

#include "lexer.h"
#include "ast.h"

class Parser {
public:
    Lexer lexer;

    void load(std::string);
};

#endif
