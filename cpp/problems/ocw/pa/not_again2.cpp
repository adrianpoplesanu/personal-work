#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10] = {2, 3, 10, 11}, n = 4, s = 23;
    int dp[s + 1];
    for (int i = 0; i <= s; i++) dp[i] = INT_MAX;
    for (int i = 0; i < n; i++) if (a[i] <= s) dp[a[i]] = 1;
    //cout << dp[2] << "\n";
    for (int i = 0; i <= s; i++) {
        for (int j = 0; j < n; j++) {
            if (a[j] <= i) {
               if (dp[i - a[j]] != INT_MAX && dp[i] > dp[i - a[j]] + 1) dp[i] = dp[i - a[j]] + 1;
            }
        }
    }
    //cout << INT_MAX << "\n";
    //for (int i = 0; i <= s; i++) cout << dp[i] << "\n";
    cout << dp[s] << "\n";
    return 0;
}
