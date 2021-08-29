#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[] = {3, 4, 5, 6, 2, 7, 3, 6, 9, 1, 2, 5};
    int n = 12;
    int dp[n];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < n; i++) {
        if (a[i - 1] < a[i]) {
            dp[i] = dp[i - 1] + 1;
        } else {
            dp[i] = 0;
        }
    }
    int max = 0, poz = 0;
    for (int i = 0; i < n; i++) if (max < dp[i]) {
        max = dp[i];
        poz = i;
    }
    for (int i = poz - dp[poz]; i <= poz; i++) cout << a[i] << " ";

    cout << "\n";
    return 0;
}
