// http://info.mcip.ro/?cap=Programare%20dinamica #738
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 5;
    int a[100] = {1, 2, 3, 4, 2};
    int dp[100];

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) dp[i] += dp[j];
        }
    }

    int total = 0;
    for (int i = 0; i < n; i++) total += dp[i];
    cout << total << "\n";
    return 0;
}
