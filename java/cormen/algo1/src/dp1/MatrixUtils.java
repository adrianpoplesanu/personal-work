package dp1;

public class MatrixUtils {
    public static void printMatrix(int n, int[][] a) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) System.out.print(a[i][j] + " ");
            System.out.println("");
        }
    }
}
