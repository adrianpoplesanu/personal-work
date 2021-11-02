package parser;

import ast.ASTNode;

public class PrefixParserInteger implements PrefixParser {
    private Parser parser;

    public PrefixParserInteger(Parser parser) {
        this.parser = parser;
    }

    @Override
    public ASTNode call() {
        return parser.parseInteger();
    }
}
