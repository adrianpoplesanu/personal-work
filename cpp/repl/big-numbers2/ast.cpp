#include "ast.h"

std::string AstNode::tokenLiteral() {
    return "implement in subclass";
}

std::string AstNode::toString() {
    return "implement in subclass";
}

AstProgram::AstProgram() {
    
}

AstProgram::~AstProgram() {
    
}

std::string AstProgram::tokenLiteral() {
    return "";
}

std::string AstProgram::toString() {
    return "AstNode [AstProgam]";
}

void AstProgram::reset() {
    statements.clear();
}

/*
    utils functions
*/

void BN_INCREF(AstNode* node) {
    if (node) {
        node->ref_count++;
    }
}

void BN_DECREF(AstNode* node) {
    if (node) {
        node->ref_count--;
    }
}

void free_AST_node_memory(AstNode* node) {
    if (!node) return;
    if (node->ref_count > 0) return;
    switch(node->type) {
        default:
            std::cout << "MEMORY ERROR: unknown ast deallocation for: " << ast_node_type_converter[node->type] << "\n";
        break;
    }
}

void printAstSubTree(AstNode* node, int level) {

}