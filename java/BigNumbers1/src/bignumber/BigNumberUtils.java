package bignumber;

public class BigNumberUtils {
    public static BigNumber add(BigNumber number1, BigNumber number2) {
        BigNumber result = new BigNumber();
        int remainder = 0;
        for (int i = 127; i >= 0; i--) {
            int val = number1.getDigit(i) + number2.getDigit(i) + remainder;
            remainder = 0;
            if (val > 10000) {
                val -= 10000;
                remainder = 1;
            }
            result.setDigit(i, val);
        }
        return result;
    }

    public static boolean greaterThan(BigNumber number1, BigNumber number2) {
        for (int i = 127; i >= 0; i--) {
            if (number1.getDigit(i) > number2.getDigit(i)) return true;
            else if (number2.getDigit(i) > number1.getDigit(i)) return false;
        }
        return false;
    }

    public static boolean equal(BigNumber number1, BigNumber number2) {
        for (int i = 127; i >= 0; i--) {
            if (number1.getDigit(i) != number2.getDigit(i)) return false;
        }
        return true;
    }
}
