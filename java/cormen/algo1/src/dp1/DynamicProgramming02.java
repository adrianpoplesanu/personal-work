package dp1;

public class DynamicProgramming02 {
    public static void solve() {
        int n = 4, m = 4;
        int a[][] = {
                {1, 4, 2, 3},
                {2, 9, 8, 7},
                {3, 6, 3, 8},
                {1, 2, 3, 3}
        };

        for (int i = 0; i < m; i++) {
            int dp[] = new int[n];
            for (int j = 0; j < n; j++) {
                if (j == 0) dp[j] = 1;
                else {
                    dp[j] = 1;
                    for (int k = 0; k < j; k++) {
                        if (a[k][i] < a[j][i] && dp[k] + 1 > dp[j]) dp[j] = dp[k] + 1;
                    }
                }
            }
            int max = dp[0];
            for (int j = 0; j < n; j++) if (dp[j] > max) max = dp[j];
            System.out.print(max + " ");
        }
    }
}
