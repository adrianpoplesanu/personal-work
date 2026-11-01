import javax.crypto.SecretKey;
import java.security.KeyPair;
import java.security.NoSuchAlgorithmException;
import java.security.PublicKey;

public interface CryptoEntity {
    KeyPair generateKeyPair() throws NoSuchAlgorithmException;
    SecretKey generateAESKey() throws NoSuchAlgorithmException;
    String encryptUsingAESKey(String message);
    String decryptUsingAESKey(String ciphertext);
    void encryptUsingRSAPublic();
    void decryptUsingRSAPrivate();
    String sha256(String message) throws NoSuchAlgorithmException;

    //...

    EncryptedMessage encryptMessageWithPublicKey(String message, PublicKey publicKey);
    EncryptedMessage encryptMessageWithPublicKeyAndSign(String message, PublicKey publicKey);
    String decryptMessage(String ciphertext);
    String decryptMessageAndCheckSignature(String message, PublicKey publicKey);
}
