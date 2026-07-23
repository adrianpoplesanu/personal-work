import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.security.NoSuchAlgorithmException;

public class AESKeyGenerator {
    private SecretKey key;

    public AESKeyGenerator(SecretKey key) {
        this.key = key;
    }

    public SecretKey getKey() {
        return key;
    }

    public void setKey(SecretKey key) {
        this.key = key;
    }

    SecretKey generateKey() throws NoSuchAlgorithmException {
        // Generate AES-256 key
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
        keyGenerator.init(256);

        SecretKey aesKey = keyGenerator.generateKey();
        this.key = aesKey;

        return aesKey;
    }
}
