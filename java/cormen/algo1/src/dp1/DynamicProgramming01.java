package dp1;

public class DynamicProgramming01 {
    /*
    http://info.mcip.ro/?cap=Programare%20dinamica
    #822
     */
    public static void numar_moduri(int n, int[][] a, int[][] dp) {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (i == n - 1 || j == 0) dp[i][j] = 1;
                else dp[i][j] = dp[i + 1][j] + dp[i + 1][j - 1] + dp[i][j - 1];
            }
        }
    }

    public static int maxim(int a, int b, int c) {
        if (a > b && a > c) return a;
        if (b > a && b > c) return b;
        return c;
    }

    public static void suma_maxima(int n, int[][] a, int[][] dp) {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (i == n - 1 && j == 0) {
                    dp[i][j] = a[i][j];
                } else if (i == n - 1) {
                    dp[i][j] = dp[i][j - 1] + a[i][j];
                } else if (j == 0) {
                    dp[i][j] = dp[i + 1][j] + a[i][j];
                } else {
                    dp[i][j] = maxim(dp[i + 1][j], dp[i + 1][j - 1], dp[i][j - 1]) + a[i][j];
                }
            }
        }
    }

    public static void main(String[] args) {
        int n = 3;
        int a[][] = {
                {1, 2, 3},
                {-1, 3, 4},
                {2, -1, -1}
        };
        int dp[][] = new int[n][n];
        numar_moduri(n, a, dp);
        MatrixUtils.printMatrix(n, dp);
        System.out.println();
        suma_maxima(n, a, dp);
        MatrixUtils.printMatrix(n, dp);
    }
}
