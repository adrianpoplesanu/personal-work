package big_number;

public class BigNumberUtils {
    public static BigNumber add(BigNumber number1, BigNumber number2) {
        BigNumber result = new BigNumber();
        int remainder = 0;
        for (int i = 0; i < 100; i++) {
            int nextDigit = remainder + number1.getDigit(i) + number2.getDigit(i);
            remainder = 0;
            while (nextDigit >= 10000) {
                nextDigit -= 10000;
                remainder += 1;
            }
            result.setDigit(i, nextDigit);
            if (nextDigit > 0) result.setSize(i + 1);
        }
        return result;
    }
}
