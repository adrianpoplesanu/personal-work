package parser;

import ast.ASTNode;

public class InfixParserExpression implements InfixParser {
    private Parser parser;

    public InfixParserExpression(Parser parser) {
        this.parser = parser;
    }

    @Override
    public ASTNode call(ASTNode left) {
        return parser.parseInfixExpression(left);
    }
}
