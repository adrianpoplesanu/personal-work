package token;

public class Token {
    TokenTypeEnum type;
    String tokenLiteral;

    public Token() {

    }

    public Token(TokenTypeEnum type, String tokenLiteral) {
        this.type = type;
        this.tokenLiteral = tokenLiteral;
    }

    public TokenTypeEnum getType() {
        return type;
    }

    public void setType(TokenTypeEnum type) {
        this.type = type;
    }

    public String getTokenLiteral() {
        return tokenLiteral;
    }

    public void setTokenLiteral(String tokenLiteral) {
        this.tokenLiteral = tokenLiteral;
    }

    public String toString() {
        return "Token [" + TokenTypeConverter.covertToken(getType()) + "] <" + getTokenLiteral() + ">";
    }
}
