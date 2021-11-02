package parser;

import ast.ASTNode;

public class PrefixParserGroupedExpression implements PrefixParser {
    private Parser parser;

    public PrefixParserGroupedExpression(Parser parser) {
        this.parser = parser;
    }

    @Override
    public ASTNode call() {
        return parser.parseGroupedExpression();
    }
}
