#include <iostream>

int main(int argc, char *argv[]) {
    int n = 3;
    int a[3][3] = {
        {1, 2, 3},
        {1, 13, 7},
        {8, 2, 3}
    };
    
    int dp[3][3];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 || j == 0) {
                //std::cout << i << ":" << j << "\n";
                dp[i][j] = 1;
            } else {
                //std::cout << i << ":" << j << "\n";
                dp[i][j] = dp[i + 1][j] + dp[i + 1][j - 1] + dp[i][j - 1];
            }
        }
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
