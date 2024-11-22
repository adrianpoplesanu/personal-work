package dp1;

import static java.lang.Integer.max;

public class DynamicProgramming03 {
    /*
    http://info.mcip.ro/?cap=Programare%20dinamica
    ex 750
     */
    public static void solve() {
        int n = 3, m = 3;
        int a[][] = {
                {0, 4, 1},
                {0, 1, 1},
                {1, 0, 1}
        };
        int dp[][] = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = a[i][j];
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1] + a[i][j];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + a[i][j];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j -1]) + a[i][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(dp[i][j]);
                System.out.print(" ");
            }
            System.out.println("");
        }
    }
}
