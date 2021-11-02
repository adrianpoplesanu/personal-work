package token;

public class Token {
    private String type;
    private String val;

    public Token(String type, String val) {
        this.type = type;
        this.val = val;
    }

    public String toString() {
        return "token.Token[type: " + type + ", val: " + val + "]";
    }

    public String getType() {
        return type;
    }

    public String getVal() {
        return val;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setVal(String val) {
        this.val = val;
    }
}
