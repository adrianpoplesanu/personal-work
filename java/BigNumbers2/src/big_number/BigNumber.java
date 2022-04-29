package big_number;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

public class BigNumber {
    private int[] digits = new int[100];
    private int[] floatDigits = new int[100];
    private static final int NUMBER_BASE = 10000;
    private int size;

    public void load(String source) {
        int len = source.length();
        int start = len - 4, end = len;
        int i = 0;
        while (end > 0) {
            if (start < 0) start = 0;
            String digit = source.substring(start, end);
            digits[i] = Integer.valueOf(digit);
            start -= 4;
            end -= 4;
            i++;
        }
        size = i;
    }

    public void print() {
        /*for (int i = 0; i < size; i++) {
            System.out.println("digit" + i + ": " + digits[i]);
        }

        AtomicInteger i = new AtomicInteger();
        Arrays.stream(digits).forEach(x -> {
            System.out.println("digit" + i.getAndIncrement() + ": " + x);
        });*/

        IntStream.range(0, size).forEach(i -> {
            System.out.println("digit" + i + ": " + digits[i]);
        });
    }

    public static void main(String[] args) {
        System.out.println("testing BigNumber object implementation, delete when done...");
        BigNumber bigNumber = new BigNumber();
        bigNumber.load("11122223333");
        bigNumber.print();
    }
}
