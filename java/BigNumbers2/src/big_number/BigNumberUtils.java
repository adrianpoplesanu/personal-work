package big_number;

public class BigNumberUtils {
    public static BigNumber add(BigNumber number1, BigNumber number2) {
        BigNumber result = new BigNumber();
        int remainder = 0;
        for (int i = 0; i < BigNumber.CAPACITY; i++) {
            int nextDigit = remainder + number1.getDigit(i) + number2.getDigit(i);
            remainder = 0;
            while (nextDigit >= BigNumber.NUMBER_BASE) {
                nextDigit -= BigNumber.NUMBER_BASE;
                remainder += 1;
            }
            result.setDigit(i, nextDigit);
            if (nextDigit > 0) result.setSize(i + 1);
        }
        return result;
    }

    public static BigNumber minus(BigNumber number1, BigNumber number2) {
        return null;
    }

    public static BigNumber multiply(BigNumber number1, BigNumber number2) {
        return null;
    }

    public static BigNumber divide(BigNumber number1, BigNumber number2) {
        return null;
    }
}
