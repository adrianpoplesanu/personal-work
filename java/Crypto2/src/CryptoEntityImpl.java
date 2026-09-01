import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import java.security.*;

public class CryptoEntityImpl implements CryptoEntity {
    private PublicKey rsaPublicKey;
    private PrivateKey rsaPrivateKey;

    private SecretKey aesKey;

    @Override
    public KeyPair generateKeyPair() throws NoSuchAlgorithmException {
        KeyPairGenerator generator = KeyPairGenerator.getInstance("RSA");
        generator.initialize(2048);

        KeyPair pair = generator.generateKeyPair();

        rsaPublicKey = pair.getPublic();
        rsaPrivateKey = pair.getPrivate();

        return pair;
    }

    @Override
    public SecretKey generateAESKey() throws NoSuchAlgorithmException {
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
        keyGenerator.init(256);

        aesKey = keyGenerator.generateKey();

        return aesKey;
    }

    @Override
    public String encryptUsingAESKey(String message) {
        return "";
    }

    @Override
    public String decryptUsingAESKey(String ciphertext) {
        return "";
    }

    @Override
    public void encryptUsingRSAPublic() {

    }

    @Override
    public void decryptUsingRSAPrivate() {

    }

    @Override
    public String sha256(String message) {
        return "";
    }

    public PublicKey getRsaPublicKey() {
        return rsaPublicKey;
    }

    public void setRsaPublicKey(PublicKey rsaPublicKey) {
        this.rsaPublicKey = rsaPublicKey;
    }

    public PrivateKey getRsaPrivateKey() {
        return rsaPrivateKey;
    }

    public void setRsaPrivateKey(PrivateKey rsaPrivateKey) {
        this.rsaPrivateKey = rsaPrivateKey;
    }

    public SecretKey getAesKey() {
        return aesKey;
    }

    public void setAesKey(SecretKey aesKey) {
        this.aesKey = aesKey;
    }
}
