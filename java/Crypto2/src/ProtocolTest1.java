import java.security.NoSuchAlgorithmException;

public class ProtocolTest1 {
    public void run() throws NoSuchAlgorithmException {
        CryptoEntityImpl alice = new CryptoEntityImpl();
        CryptoEntityImpl bob = new CryptoEntityImpl();

        alice.generateKeyPair();
        bob.generateKeyPair();

        String message = "bebe alex si bebe dex sunt micutzi";
        alice.generateAESKey();
        EncryptedMessage encryptedMessage = alice.encryptMessageWithPublicKeyAndSign(message, bob.getRsaPublicKey());

        System.out.println(encryptedMessage);

        String received = bob.decryptMessageAndCheckSignature(encryptedMessage.getCiphertext(), alice.getRsaPublicKey());
        System.out.println(received);
    }
}
