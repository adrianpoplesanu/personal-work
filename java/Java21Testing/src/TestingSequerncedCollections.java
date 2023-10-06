import java.util.List;

public class TestingSequerncedCollections {
    public static void main(String[] args) {
        System.out.println("running java21...");

        List names = List.of("aaa", "bbb", "ccc", "ddd", "eee", "fff");
        List rNames = names.reversed();
        System.out.println(names);
        System.out.println(rNames);

        //names.removeFirst(); // List.of is immutable

        System.out.println(names == rNames.reversed());
    }
}
