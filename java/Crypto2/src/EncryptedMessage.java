public class EncryptedMessage {
    private String ciphertext = "";

    public String getCiphertext() {
        return ciphertext;
    }

    public void setCiphertext(String ciphertext) {
        this.ciphertext = ciphertext;
    }

    @Override
    public String toString() {
        return "EncryptedMessage{" +
                "ciphertext='" + ciphertext + '\'' +
                '}';
    }
}
