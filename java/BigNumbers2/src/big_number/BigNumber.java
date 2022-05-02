package big_number;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

public class BigNumber {
    private int[] digits = new int[100];
    private int[] floatDigits = new int[100];
    public static final int NUMBER_BASE = 10000;
    public static final int CAPACITY = 100;
    public static final int DIGIT_SIZE = 4;
    private int size;

    public void load(String source) {
        int len = source.length();
        int start = len - DIGIT_SIZE, end = len;
        int i = 0;
        while (end > 0) {
            if (start < 0) start = 0;
            String digit = source.substring(start, end);
            digits[i] = Integer.valueOf(digit);
            start -= DIGIT_SIZE;
            end -= DIGIT_SIZE;
            i++;
        }
        size = i;
    }

    public void print() {
        String text = "";
        for (int i = size - 1; i >= 0; i--) {
            if (i == size - 1) {
                text += String.valueOf(digits[i]);
            } else {
                text += String.format("%04d", digits[i]);
            }
        }
        System.out.println(text);

        /*AtomicInteger i = new AtomicInteger();
        Arrays.stream(digits).forEach(x -> {
            System.out.println("digit" + i.getAndIncrement() + ": " + x);
        });*/

        /*IntStream.range(0, size).forEach(i -> {
            System.out.println("digit" + i + ": " + digits[i]);
        });*/
    }

    public int getDigit(int i) {
        return digits[i];
    }

    public void setDigit(int i, int value) {
        digits[i] = value;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public static void main(String[] args) {
        System.out.println("testing BigNumber object implementation, delete when done...");
        BigNumber bigNumber1 = new BigNumber();
        bigNumber1.load("11122223333");

        BigNumber bigNumber2 = new BigNumber();
        bigNumber2.load("11122226667");

        BigNumber bigNumber3 = BigNumberUtils.add(bigNumber1, bigNumber2);
        bigNumber3.print();
    }
}
