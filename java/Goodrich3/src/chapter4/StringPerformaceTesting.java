package chapter4;

public class StringPerformaceTesting {
    public static String repeat1(char c, int n) {
        String answer = "";
        for(int i = 0; i < n; i++) {
            answer += c;
        }
        return answer;
    }

    public static String repeat2(char c, int n) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n; i++) {
            sb.append(c);
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        long start1 = System.currentTimeMillis();

        repeat1('a', 100000);

        long end1 = System.currentTimeMillis();
        System.out.println("repeat1, run time = " + (end1 - start1));

        long start2 = System.currentTimeMillis();

        repeat2('a', 100000);

        long end2 = System.currentTimeMillis();
        System.out.println("repeat2, run time = " + (end2 - start2));
    }
}
