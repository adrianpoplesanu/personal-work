#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10] = {100, 12, 13, -1, 15, -30}, n = 6;
    int dp[n], prev[n];
    dp[0] = 1;
    prev[0] = -1;
    for(int i = 1; i < n; ++i) {
        dp[i] = 1;
        prev[i] = -1;
        for(int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) cout << dp[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << prev[i] << " ";
    cout << "\n";
    return 0;
}
