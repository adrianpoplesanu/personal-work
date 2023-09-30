package ro.adrianus.prototype.token;

public class Token {
    private TokenTypeEnum type;
    private String literal;

    public Token() {
        type = TokenTypeEnum.ILLEGAL;
        literal = "";
    }

    public Token(TokenTypeEnum type, String literal) {
        this.type = type;
        this.literal = literal;
    }

    @Override
    public String toString() {
        return "Token{" +
                "type=" + type +
                ", literal='" + literal + '\'' +
                '}';
    }

    public TokenTypeEnum getType() {
        return type;
    }

    public void setType(TokenTypeEnum type) {
        this.type = type;
    }

    public String getLiteral() {
        return literal;
    }

    public void setLiteral(String literal) {
        this.literal = literal;
    }
}
