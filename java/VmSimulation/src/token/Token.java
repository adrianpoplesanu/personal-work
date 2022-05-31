package token;

public class Token {
    public TokenType type;
    public String literal;

    public Token () {

    }

    public Token(TokenType type, String literal) {
        this.type = type;
        this.literal = literal;
    }

    public TokenType getType() {
        return type;
    }

    @Override
    public String toString() {
        return "Token [" + type + "] <" + literal + ">";
    }
}
