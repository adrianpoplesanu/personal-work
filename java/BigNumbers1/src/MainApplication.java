import bignumber.BigNumber;

public class MainApplication {
    public static void main(String[] args) {
        BigNumber number = new BigNumber();
        number.load("111122223333");
        number.inspect();
    }
}
