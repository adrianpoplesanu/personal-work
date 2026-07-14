import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.nio.charset.StandardCharsets;
import java.security.*;
import java.util.Base64;

public class Crypto1 {

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
        RsaKeyGenerator rsaKeyGenerator = new RsaKeyGenerator();
        rsaKeyGenerator.generatePair();

        rsaKeyGenerator.printPublicBytes();
        rsaKeyGenerator.printPrivateBytes();

        System.out.println(rsaKeyGenerator.generatePublicPem());
        System.out.println(rsaKeyGenerator.generatePrivatePem());

        String text = """
This can be a very long text...
Lorem ipsum...
Adrianus per Scorillo
""";

        EncryptedMessage encrypted = Crypto1.encrypt(text, rsaKeyGenerator.getPublicKey());
        String decrypted = Crypto1.decrypt(encrypted, rsaKeyGenerator.getPrivateKey());

        System.out.println(decrypted);
    }
}