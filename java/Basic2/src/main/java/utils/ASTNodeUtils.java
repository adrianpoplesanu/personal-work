package utils;

import ast.ASTNode;

public class ASTNodeUtils {
    public void printASTNode(ASTNode node, int level) {
        for (int i = 0; i < level; i++) {
            System.out.print(" ");
        }
        switch(node.getType()) {
            case PROGRAM:
                break;
            case INTGER:
                break;
            case INFIX_EXPRESSION:
                break;
            case EXPRESSION_STATEMENT:
                break;
            default:
                System.out.println("UNKWOWN AST NODE");
                break;
        }
    }
}
