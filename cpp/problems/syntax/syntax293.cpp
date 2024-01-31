#include <iostream>

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int main(int argc, char *argv[]) {
    int n = 3;
    int a[3][3] = {
        {1, 2, 3},
        {-1, 3, 4},
        {2, -1, -1}
    };
    
    int dp[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = 0;
        }
    }

    //dp[n - 1][0] = a[n - 1][0];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 && j == 0) {
                dp[i][j] += a[i][j];
            } else if (i == n - 1) {
                //std::cout << i << ":" << j << "\n";
                dp[i][j] += dp[i][j - 1] + a[i][j];
            } else if (j == 0) {
	        dp[i][j] += dp[i + 1][j] + a[i][j];
            } else {
                //std::cout << i << ":" << j << "\n";
                dp[i][j] += max(dp[i + 1][j], dp[i + 1][j - 1], dp[i][j - 1]) + a[i][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}


/*
1 5 13
1 3 5
1 1 1
*/
