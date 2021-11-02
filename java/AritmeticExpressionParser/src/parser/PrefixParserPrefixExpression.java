package parser;

import ast.ASTNode;

public class PrefixParserPrefixExpression implements PrefixParser {
    private Parser parser;

    public PrefixParserPrefixExpression(Parser parser) {
        this.parser = parser;
    }

    @Override
    public ASTNode call() {
        return parser.parsePrefixExpression();
    }
}
