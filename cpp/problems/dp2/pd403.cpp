// http://info.mcip.ro/?cap=Programare%20dinamica #403
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[] = {-2, 1, -3, 3, -1, 4, -6, 2, 3}, n = 9;
    int dp[n], d[n];
    memset(dp, 0, sizeof(dp));
    memset(d, 0, sizeof(d));
    dp[0] = a[0];
    d[0] = 1;
    for(int i = 1; i < n; i++) {
        if (dp[i - 1] + a[i] > a[i]) {
            dp[i] = dp[i - 1] + a[i];
            d[i] = d[i - 1] + 1;
        } else {
            dp[i] = a[i];
            d[i] = 1;
        }
    }

    int max = dp[0], len = 0, poz = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
            len = d[i] - 1;
            poz = i;
        }
    }
    cout << max << "\n";
    for (int i = poz - len; i <= poz; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}
