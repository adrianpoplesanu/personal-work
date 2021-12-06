import streams.StreamTest01;

import java.util.ArrayList;
import java.util.Arrays;

public class MainApplication {
    public static void main(String[] args) {
        ArrayList<String> numbers = new ArrayList<String>(Arrays.asList("1", "2", "3", "4", "5"));
        System.out.println(StreamTest01.retrieveAllNumbers(numbers));

        System.out.println(StreamTest01.retrieveEvenNumbers(numbers));
    }
}
