#include "ast.h"

std::string ASTNode::toString() {
    return "unimplemented in subclass";
}

std::string ASTNode::inspect() {
    return "unimplemented in subclass";
}

void Ad_INCREF(ASTNode* node) {
    if (node) node->ref_count++;
}

void Ad_DECREF(ASTNode* node) {
    if (node) node->ref_count--;
}