package reference_testing;

public class ReferenceTest {
    private static void modify(int value) {
        // does not work
        value = 6;
    }

    private static void modify(Integer value) {
        // does not work
        value = 6;
    }

    private static void modify(Data data) {
        // does work
        data.info = 6;
    }

    public static void main(String[] args) {
        int a = 2;
        modify(a);
        System.out.println(a);
        Data b = new Data();
        b.info = 2;
        modify(b);
        System.out.println(b.info);
        Integer c = 2;
        modify(c);
        System.out.println(c);
    }
}
