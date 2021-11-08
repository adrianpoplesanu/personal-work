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
}
