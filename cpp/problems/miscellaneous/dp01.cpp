#include <iostream>

int main(int argc, char *argv[]) {
    int dp[100];
    int a[] = {1, 9, 2, 9, 3, 4, 5, 9, 9, 1, 2, 9};
    int n = 12;

    dp[0] = 1;
    for (int i = 1; i < n; i++) {
        if (a[i - 1] < a[i]) dp[i] = dp[i - 1] + 1;
        else dp[i] = 1;
    }

    for (int i = 0; i < n; i++) std::cout << dp[i] << " ";
    std::cout << "\n";

    return 0;
}
