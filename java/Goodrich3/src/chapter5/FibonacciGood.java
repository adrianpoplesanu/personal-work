package chapter5;

public class FibonacciGood {
    public static long[] fibonacciGood(int n) {
        if (n <= 1) {
            long[] answer = {n, 0};
            return answer;
        } else {
            long[] tmp = fibonacciGood(n - 1);
            long[] answer = {tmp[0] + tmp[1], tmp[0]};
            return answer;
        }
    }

    public static void main(String[] args) {
        System.out.println(fibonacciGood(40)[0]);
    }
}
