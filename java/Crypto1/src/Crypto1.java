import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.security.*;
import java.util.Base64;

public class Crypto1 {
    private PublicKey publicKey;
    private PrivateKey privateKey;

    public PublicKey getPublicKey() {
        return publicKey;
    }

    public void setPublicKey(PublicKey publicKey) {
        this.publicKey = publicKey;
    }

    public PrivateKey getPrivateKey() {
        return privateKey;
    }

    public void setPrivateKey(PrivateKey privateKey) {
        this.privateKey = privateKey;
    }

    void generatePair() throws NoSuchAlgorithmException {
        KeyPairGenerator generator = KeyPairGenerator.getInstance("RSA");
        generator.initialize(2048);

        KeyPair pair = generator.generateKeyPair();

        privateKey = pair.getPrivate();
        publicKey = pair.getPublic();

    }

    private String generatePrivatePem(PrivateKey privateKey) {
        String pem =
                "-----BEGIN PRIVATE KEY-----\n" +
                        Base64.getMimeEncoder(64, "\n".getBytes())
                                .encodeToString(privateKey.getEncoded()) +
                        "\n-----END PRIVATE KEY-----";
        return pem;
    }

    private String generatePublicPem(PublicKey publicKey) {
        String pem =
                "-----BEGIN PUBLIC KEY-----\n" +
                        Base64.getMimeEncoder(64, "\n".getBytes())
                                .encodeToString(publicKey.getEncoded()) +
                        "\n-----END PUBLIC KEY-----";
        return pem;
    }

    void printPublicBytes() {
        byte[] publicBytes = publicKey.getEncoded();
        String publicBase64 = Base64.getEncoder().encodeToString(publicBytes);

        System.out.println(publicBase64);
    }

    void printPrivateBytes() {
        byte[] privateBytes = privateKey.getEncoded();
        String privateBase64 = Base64.getEncoder().encodeToString(privateBytes);

        System.out.println(privateBase64);
    }

    public static EncryptedMessage encrypt(String plaintext,
                                           PublicKey rsaPublicKey) throws Exception {

        // Generate AES-256 key
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
        keyGenerator.init(256);

        SecretKey aesKey = keyGenerator.generateKey();

        // Generate IV (12 bytes recommended for GCM)
        byte[] iv = new byte[12];
        SecureRandom random = new SecureRandom();
        random.nextBytes(iv);

        // Encrypt message with AES
        Cipher aesCipher = Cipher.getInstance("AES/GCM/NoPadding");
        aesCipher.init(
                Cipher.ENCRYPT_MODE,
                aesKey,
                new GCMParameterSpec(128, iv));

        byte[] ciphertext =
                aesCipher.doFinal(plaintext.getBytes(StandardCharsets.UTF_8));

        // Encrypt AES key with RSA
        Cipher rsaCipher =
                Cipher.getInstance("RSA/ECB/OAEPWithSHA-256AndMGF1Padding");

        rsaCipher.init(Cipher.ENCRYPT_MODE, rsaPublicKey);

        byte[] encryptedKey =
                rsaCipher.doFinal(aesKey.getEncoded());

        return new EncryptedMessage(
                Base64.getEncoder().encodeToString(encryptedKey),
                Base64.getEncoder().encodeToString(iv),
                Base64.getEncoder().encodeToString(ciphertext));
    }

    public static String decrypt(EncryptedMessage message,
                                 PrivateKey rsaPrivateKey) throws Exception {

        // Decrypt AES key
        Cipher rsaCipher =
                Cipher.getInstance("RSA/ECB/OAEPWithSHA-256AndMGF1Padding");

        rsaCipher.init(Cipher.DECRYPT_MODE, rsaPrivateKey);

        byte[] aesKeyBytes =
                rsaCipher.doFinal(
                        Base64.getDecoder().decode(message.getEncryptedAesKey()));

        SecretKeySpec aesKey =
                new SecretKeySpec(aesKeyBytes, "AES");

        // Decrypt message
        Cipher aesCipher = Cipher.getInstance("AES/GCM/NoPadding");

        aesCipher.init(
                Cipher.DECRYPT_MODE,
                aesKey,
                new GCMParameterSpec(
                        128,
                        Base64.getDecoder().decode(message.getIv())));

        byte[] plaintext =
                aesCipher.doFinal(
                        Base64.getDecoder().decode(message.getCiphertext()));

        return new String(plaintext, StandardCharsets.UTF_8);
    }

    public static void main(String[] args) throws Exception {
        Crypto1 crypto1 = new Crypto1();
        crypto1.generatePair();

        crypto1.printPublicBytes();
        crypto1.printPrivateBytes();

        System.out.println(crypto1.generatePublicPem(crypto1.publicKey));
        System.out.println(crypto1.generatePrivatePem(crypto1.privateKey));

        String text = """
This can be a very long text...
Lorem ipsum...
""";

        EncryptedMessage encrypted = Crypto1.encrypt(text, crypto1.publicKey);
        String decrypted = Crypto1.decrypt(encrypted, crypto1.privateKey);

        System.out.println(decrypted);
    }
}