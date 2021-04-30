#ifndef __PARSER_H
#define __PARSER_H

#include "ast.h"
#include <vector>

class Parser {
private:
    //...
public:
    Parser();
    ~Parser();
    std::vector<ast::Node> BuildStatements_old();
    std::vector<ast::Node*> BuildStatements();
};

#endif