package utils;

import ast.ASTExpressionStatement;
import ast.ASTInfixExpression;
import ast.ASTNode;
import ast.ASTProgram;

public class ASTNodeUtils {
    public static void printASTNode(ASTNode node, int level) {
        for (int i = 0; i < level; i++) {
            System.out.print(" ");
        }
        switch(node.getType()) {
            case PROGRAM:
                System.out.println("-> Program");
                for (int i = 0; i < ((ASTProgram) node).getStatements().size(); i++) {
                    printASTNode(((ASTProgram) node).getStatements().get(i), level + 2);
                }
                break;
            case INTEGER:
                System.out.println("-> Integer [" + node.inspect() + "]");
                break;
            case INFIX_EXPRESSION:
                ASTInfixExpression infixExpression = (ASTInfixExpression) node;
                System.out.println("-> InfixExpression [" + infixExpression.getOperator() + "]");
                printASTNode(infixExpression.getLeft(), level + 2);
                printASTNode(infixExpression.getRight(), level + 2);
                break;
            case EXPRESSION_STATEMENT:
                ASTExpressionStatement expressionStatement = (ASTExpressionStatement) node;
                System.out.println("-> ExpressionStatement");
                printASTNode(expressionStatement.getExpression(), level + 2);
                break;
            default:
                System.out.println("UNKWOWN AST NODE");
                break;
        }
    }
}
