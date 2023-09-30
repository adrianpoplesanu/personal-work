package ro.adrianus.prototype.ast;

import java.util.HashMap;

public enum AstNodeTypeEnum {
    PROGRAM_STATEMENT,
    LET_STATEMENT,
    RETURN_STATEMENT,
    FUNC_STATEMENT;

    private static HashMap<AstNodeTypeEnum, String> mapToString = new HashMap<AstNodeTypeEnum, String>() {
        private static final long serialVersionUID = 1L;
        {
            put(PROGRAM_STATEMENT, "PROGRAM");
            put(LET_STATEMENT, "LET_STATEMENT");
            put(RETURN_STATEMENT, "RETURN_STATEMENT");
            put(FUNC_STATEMENT, "FUNC_STATEMENT");
        }
    };

    public static String convertToString(AstNodeTypeEnum type) {
        return mapToString.get(type);
    }
}
