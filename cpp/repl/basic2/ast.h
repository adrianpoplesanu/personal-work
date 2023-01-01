#ifndef __AST_H
#define __AST_H

#include <vector>

enum ASTNodeType {
    AST_PROGRAM,
    AST_EXPRESSION_STATEMENT,
    AST_INTEGER
};

class ASTNode {
public:
    ASTNodeType type;
};

class ASTProgram : ASTNode {
public:
    std::vector<ASTNode*> statements;
};

class ASTExpressionStatement : ASTNode {

};

class ASTInteger : ASTNode {

};

#endif
