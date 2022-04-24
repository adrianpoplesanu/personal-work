package token;

public class Token {
    private TokenType type;
    private String tokenLiteral;

    public Token() {

    }

    public Token(TokenType type) {
        this.type = type;
    }

    public TokenType getType() {
        return type;
    }

    public void setType(TokenType type) {
        this.type = type;
    }

    public String getTokenLiteral() {
        return tokenLiteral;
    }

    public void setTokenLiteral(String tokenLiteral) {
        this.tokenLiteral = tokenLiteral;
    }
}
