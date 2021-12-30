package streams;

import java.util.List;
import java.util.function.Consumer;
import java.util.stream.Collectors;

public class StreamTest02 {
    public static List<String> lowerCase(List<String> names) {
        return names.stream().map(s -> s.toLowerCase()).collect(Collectors.toList());
    }

    private static String transform(String name, String suffix) {
        return name + suffix;
    }

    private void testStaticConsumer(String text) {
        System.out.println(text);
    }

    public static void add101(List<String> names) {
        Consumer<String> printConsumer = new Consumer<String>() {
            @Override
            public void accept(String s) {
                System.out.println(s);
            }
        };
        names.stream().map(s -> transform(s, "101")).forEach(printConsumer);
    }

    public void add102(List<String> names) {
        names.stream().map(s -> transform(s, "102")).forEach(this::testStaticConsumer);
    }
}
