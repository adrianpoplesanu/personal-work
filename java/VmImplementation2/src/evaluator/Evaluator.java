package evaluator;

import ast.AstNode;
import environment.Environment;
import objects.AdObject;

public class Evaluator {
    public AdObject eval(AstNode node, Environment environment) {
        switch(node.getType()) {
            case PROGRAM:
                return evalProgram(node, environment);
            case INTEGER:
                return evalInteger(node, environment);
        }
        return null;
    }

    private AdObject evalProgram(AstNode node, Environment environment) {
        return null;
    }

    private AdObject evalInteger(AstNode node, Environment environment) {
        return null;
    }
}
