// fibonacci - programare dinamica
#include <iostream>
using namespace std;

int dp[100];

int main(int argc, char *argv[]) {
    int n, i = 2;
    cout <<"n = "; cin >> n;
    dp[0] = 0;
    dp[1] = 1;
    while(i <= n) {
        dp[i] = dp[i - 1] + dp[i - 2];
        i++;
    }
    cout << dp[n] << endl;
    return 0;
}
