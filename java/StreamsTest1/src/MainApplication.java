import streams.StreamTest01;
import streams.StreamTest02;

import java.util.ArrayList;
import java.util.Arrays;

public class MainApplication {
    public static void main(String[] args) {
        ArrayList<String> numbers = new ArrayList<>(Arrays.asList("1", "2", "3", "4", "5"));
        System.out.println(StreamTest01.retrieveAllNumbers(numbers));

        System.out.println(StreamTest01.retrieveEvenNumbers(numbers));

        ArrayList<String> names = new ArrayList<>(Arrays.asList("Magnus", "Naka", "Ian"));
        System.out.println(StreamTest02.lowerCase(names));
        StreamTest02.add101(names);
        System.out.println(names);

        StreamTest02 streamTest02 = new StreamTest02();
        streamTest02.add102(names);
    }
}
