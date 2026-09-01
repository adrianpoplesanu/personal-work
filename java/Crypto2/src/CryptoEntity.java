import javax.crypto.SecretKey;
import java.security.KeyPair;
import java.security.NoSuchAlgorithmException;

public interface CryptoEntity {
    KeyPair generateKeyPair() throws NoSuchAlgorithmException;
    SecretKey generateAESKey() throws NoSuchAlgorithmException;
    String encryptUsingAESKey(String message);
    String decryptUsingAESKey(String ciphertext);
    void encryptUsingRSAPublic();
    void decryptUsingRSAPrivate();
    String sha256(String message);
}
