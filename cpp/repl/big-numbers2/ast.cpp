#include "ast.h"

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