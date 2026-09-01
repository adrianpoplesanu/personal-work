import java.security.NoSuchAlgorithmException;

public class Main {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        String text1 = "buna dimineata";

        Sha256Generator sha256Generator = new Sha256Generator();
        String hash1 = sha256Generator.hash(text1);

        System.out.println(hash1);
    }
}