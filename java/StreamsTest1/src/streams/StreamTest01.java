package streams;

import java.util.List;
import java.util.stream.Collectors;

public class StreamTest01 {
    public static List<Integer> retrieveAllNumbers(List<String> numbers) {
        List<Integer> result = numbers.stream().map(s -> Integer.valueOf(s)).collect(Collectors.toList());
        return result;
    }

    public static List<Integer> retrieveEvenNumbers(List<String> numbers) {
        List<Integer> result = numbers.stream().map(s -> Integer.valueOf(s)).filter(n -> n % 2 == 0).collect(Collectors.toList());
        return result;
    }
}
