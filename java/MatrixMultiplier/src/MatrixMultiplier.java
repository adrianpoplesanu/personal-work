public class MatrixMultiplier {

    public static int[][] multiply(int[][] a, int[][] b) {
        int[][] c = new int[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int sum = 0;
                for (int k = 0; k < 2; k++) sum += a[i][k] * b[k][j];
                c[i][j] = sum;
            }
        }
        return c;
    }

    public static void print(int[][] a) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) System.out.print(a[i][j] + " ");
            System.out.println();
        }
        System.out.println("------");
    }

    public static void main(String[] args) {
        int[][] a = {
                {1, 0},
                {0, 1}
        };
        int[][] b = {
                {1, 2},
                {3, 4}
        };
        int[][] c = {
                {3, 4},
                {-5, -6}
        };
        int[][] d = multiply(a, b);
        print(d);

        int[][] e = multiply(b, a);
        print(e);

        int[][] f = multiply(b, c);
        print(f);

        int[][] g = multiply(c, b);
        print(g);
    }
}
