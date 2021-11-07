package bignumber;

public class BigNumber {
    private int[] digits;

    public BigNumber() {
        digits = new int[128];
        for (int i = 0; i < 128; i++) digits[i] = 0;
    }

    public void load(String numberRepr) {
        int digit_len = 4;
        int max_size = numberRepr.length();
        int i = 127;
        while (max_size > 0) {
            if (max_size < digit_len) {
                String digit = numberRepr.substring(0, max_size);
                digits[i--] = Integer.valueOf(digit);
                max_size -= digit_len;
            } else {
                String digit = numberRepr.substring(max_size - digit_len, max_size);
                digits[i--] = Integer.valueOf(digit);
                max_size -= digit_len;
            }
        }
    }

    public void load(BigNumber number) {
        for (int i = 0; i < 128; i++) digits[i] = number.getDigit(i);
    }

    public int getDigit(int pos) {
        return digits[pos];
    }

    public void setDigit(int pos, int val) {
        digits[pos] = val;
    }

    public void inspect() {
        int start_digit = 0;
        while (start_digit < 128 && digits[start_digit] == 0) start_digit++;
        if (start_digit == 128) System.out.println("0");
        for (int i = start_digit; i < 128; i++) {
            System.out.print(digits[i]);
        }
        System.out.println("");
    }
}
