package token;

public class Token {
    private TokenType type;
    private String literal;

    public TokenType getType() {
        return type;
    }

    public void setType(TokenType type) {
        this.type = type;
    }

    public String getLiteral() {
        return literal;
    }

    public void setLiteral(String literal) {
        this.literal = literal;
    }

    public String toString() {
        return "Token [" + type.name() + "] <" + literal + ">";
    }
}
