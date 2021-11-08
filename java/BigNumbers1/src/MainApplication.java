import bignumber.BigNumber;
import bignumber.BigNumberUtils;

public class MainApplication {
    public static void main(String[] args) {
        BigNumber number1 = new BigNumber();
        number1.load("9999");
        number1.inspect();

        BigNumber number2= new BigNumber();
        number2.load("9999");
        number2.inspect();

        BigNumber number3 = BigNumberUtils.add(number1, number2);
        number3.inspect();
    }
}
