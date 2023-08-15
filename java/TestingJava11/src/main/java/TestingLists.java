import java.util.List;

public class TestingLists {
    public static void main(String[] args) {
        List<String> a = List.of("bebe", "dex", "e" , "drabutz");
        System.out.println(a);
        try {
            a.remove(2);
            System.out.println(a);
        } catch (UnsupportedOperationException exception) {
            System.out.println("asta e dovada ca List.of genereaza o lista imutabila in java 11");
        }
    }
}
