package evaluator;

import ast.*;
import environment.Environment;
import objects.B2IntegerObject;
import objects.B2Object;

public class Evaluator {

    public Evaluator() {

    }
    public B2Object eval(ASTNode node, Environment env) {
        switch(node.getType()) {
            case PROGRAM:
                return evalProgram(node, env);
            case EXPRESSION_STATEMENT:
                return evalExpressionStatement(node, env);
            case INFIX_EXPRESSION:
                return evalInfixExpression(node, env);
            case INTEGER:
                return evalIntegerExpression(node, env);
            default:
                System.out.println("UNKNOWM AST NODE EVAL");
                break;
        }
        return null;
    }

    private B2Object evalProgram(ASTNode node, Environment env) {
        ASTProgram program = (ASTProgram) node;
        for (int i = 0; i < program.getStatements().size(); i++) {
            B2Object result = eval(program.getStatements().get(i), env);
            System.out.println(result.inspect());
        }
        return null;
    }

    private B2Object evalExpressionStatement(ASTNode node, Environment env) {
        ASTExpressionStatement stmt = (ASTExpressionStatement) node;
        return eval(stmt.getExpression(), env);
    }

    private B2Object evalInfixExpression(ASTNode node, Environment env) {
        ASTInfixExpression expr = (ASTInfixExpression) node;
        B2IntegerObject left = (B2IntegerObject) eval(expr.getLeft(), env);
        B2IntegerObject right = (B2IntegerObject) eval(expr.getRight(), env);
        B2IntegerObject result = new B2IntegerObject();
        switch(expr.getOperator()) {
            case "+":
                result.setValue(left.getValue() + right.getValue());
                return result;
            case "-":
                result.setValue(left.getValue() - right.getValue());
                return result;
            case "*":
                result.setValue(left.getValue() * right.getValue());
                return result;
            case "/":
                result.setValue(left.getValue() / right.getValue());
                return result;
            default:
                System.out.println("UNKNOWN INFIX EXPRESSION OPERATOR EVAL");
                break;
        }
        return null;
    }

    private B2Object evalIntegerExpression(ASTNode node, Environment env) {
        B2IntegerObject result = new B2IntegerObject();
        ASTInteger integer = (ASTInteger) node;
        result.setValue(integer.getValue());
        return result;
    }
}
