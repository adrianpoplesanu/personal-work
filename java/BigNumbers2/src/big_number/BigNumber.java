package big_number;

public class BigNumber {
    private int[] digits = new int[100];
    private int[] floatDigits = new int[100];
    private static final int NUMBER_BASE = 10000;

    public void load(String source) {
        int len = source.length();
        int start = len - 4, end = len;
        while (end > 0) {
            String digit = source.substring(start, end);
            System.out.println(digit);
            start -= 4;
            end -= 4;
        }
    }

    public static void main(String[] args) {
        System.out.println("testing BigNumber object implementation, delete when done...");
        BigNumber bigNumber = new BigNumber();
        bigNumber.load("111122223333");
    }
}
