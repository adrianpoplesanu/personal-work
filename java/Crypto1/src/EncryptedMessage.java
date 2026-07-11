import java.util.Base64;

public class EncryptedMessage {

    private final String encryptedAesKey;
    private final String iv;
    private final String ciphertext;

    public EncryptedMessage(String encryptedAesKey,
                            String iv,
                            String ciphertext) {
        this.encryptedAesKey = encryptedAesKey;
        this.iv = iv;
        this.ciphertext = ciphertext;
    }

    public String getEncryptedAesKey() {
        return encryptedAesKey;
    }

    public String getIv() {
        return iv;
    }

    public String getCiphertext() {
        return ciphertext;
    }
}