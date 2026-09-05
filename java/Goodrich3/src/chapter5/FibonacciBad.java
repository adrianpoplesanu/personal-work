package chapter5;

public class FibonacciBad {
    public static long fibonacciBad(int n) {
        if (n <= 1) return n;
        else return fibonacciBad(n - 2) + fibonacciBad(n - 1);
    }

    public static void main(String[] args) {
        System.out.println(fibonacciBad(40));
    }
}
