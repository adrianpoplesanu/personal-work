#include "ast.h"

std::string ASTNode::toString() {
    return "unimplemented in subclass";
}

std::string ASTNode::inspect() {
    return "unimplemented in subclass";
}

std::string AstProgram::toString() {
    return "AstProgram";
}

std::string AstProgram::inspect() {
    return "AstProgram";
}

void Ad_INCREF(ASTNode* node) {
    if (node) node->ref_count++;
}

void Ad_DECREF(ASTNode* node) {
    if (node) node->ref_count--;
}