// https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-03
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[6] = {-10, 2, 3, -1, 2, -3};
    int n = 6;
    int dp[n], start[n];

    dp[0] = a[0];
    start[0] = 0;
    for(int i = 1; i < n; i++) {
        if (dp[i - 1] > 0) {
            start[i] = start[i - 1];
            dp[i] = a[i] + dp[i - 1];
        }
        else {
            dp[i] = a[i];
            start[i] = i;
        }
    }

    for (int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << start[i] << " ";
    cout << "\n";
    return 0;
}
