package parser;

import ast.ASTNode;

public interface InfixParser {
    ASTNode call(ASTNode left);
}
