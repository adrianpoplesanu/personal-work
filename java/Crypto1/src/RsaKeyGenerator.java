import java.security.*;
import java.util.Base64;

public class RsaKeyGenerator {
    private PublicKey publicKey;
    private PrivateKey privateKey;

    public RsaKeyGenerator() {
    }

    public RsaKeyGenerator(PublicKey publicKey, PrivateKey privateKey) {
        this.publicKey = publicKey;
        this.privateKey = privateKey;
    }

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

    public void generatePair() throws NoSuchAlgorithmException {
        KeyPairGenerator generator = KeyPairGenerator.getInstance("RSA");
        generator.initialize(2048);

        KeyPair pair = generator.generateKeyPair();

        privateKey = pair.getPrivate();
        publicKey = pair.getPublic();

    }

    public String generatePrivatePem() {
        String pem =
                "-----BEGIN PRIVATE KEY-----\n" +
                        Base64.getMimeEncoder(64, "\n".getBytes())
                                .encodeToString(privateKey.getEncoded()) +
                        "\n-----END PRIVATE KEY-----";
        return pem;
    }

    public String generatePublicPem() {
        String pem =
                "-----BEGIN PUBLIC KEY-----\n" +
                        Base64.getMimeEncoder(64, "\n".getBytes())
                                .encodeToString(publicKey.getEncoded()) +
                        "\n-----END PUBLIC KEY-----";
        return pem;
    }

    public void printPublicBytes() {
        byte[] publicBytes = publicKey.getEncoded();
        String publicBase64 = Base64.getEncoder().encodeToString(publicBytes);

        System.out.println(publicBase64);
    }

    public void printPrivateBytes() {
        byte[] privateBytes = privateKey.getEncoded();
        String privateBase64 = Base64.getEncoder().encodeToString(privateBytes);

        System.out.println(privateBase64);
    }
}
