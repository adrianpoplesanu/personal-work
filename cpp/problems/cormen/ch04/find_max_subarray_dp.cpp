#include <iostream>

int main(int argc, char* argv[]) {
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    int n = 16;
    int dp[n];
    int start[n];
    int max;
    int poz;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp[i] = a[i];
            max = a[i];
            start[i] = i;
            poz = i;
        } else {
            if (dp[i - 1] + a[i] > a[i]) {
                dp[i] = dp[i - 1] + a[i];
                start[i] = start[i - 1];
                if (max < dp[i]) {
                    max = dp[i];
                    poz = i;
                }
            } else {
                dp[i] = a[i];
                start[i] = i;
                if (max < dp[i]) {
                    max = dp[i];
                    poz = i;
                }
            }
        }
    }

    std::cout << max << "\n" << start[poz] << "\n" << poz << "\n";
    for (int i = start[poz]; i <= poz; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
