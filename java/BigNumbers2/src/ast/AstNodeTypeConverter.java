package ast;

import java.util.HashMap;

public class AstNodeTypeConverter {
    private static HashMap<AstNodeType, String> astNodeTypeMap = new HashMap<AstNodeType, String>() {
        {
            put(AstNodeType.UNDEFINED, "UNDEFINED");
            put(AstNodeType.PROGRAM, "PROGRAM");
            put(AstNodeType.ASSIGN_STATEMENT, "ASSIGN_STATEMENT");
            put(AstNodeType.PREFIX_EXPRESSION, "PREFIX_EXPRESSION");
            put(AstNodeType.INFIX_EXPRESSION, "INFIX_EXPRESSION");
            put(AstNodeType.LET_STATEMENT, "LET_STATEMENT");
            put(AstNodeType.IF_STATEMENT, "IF_STATEMENT");
            put(AstNodeType.BIG_NUMBER, "BIG_NUMBER");
            put(AstNodeType.BOOLEAN, "BOOLEAN");
        }
    };

    public static String convertAstNodeType(AstNodeType type) {
        return astNodeTypeMap.get(type);
    }
}
