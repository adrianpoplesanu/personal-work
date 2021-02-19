#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = 4;
    int a[10][10] = {
        {0, 0, 0, 0},
        {0, 1, 2, 1},
        {0, 3, 6, 1},
        {0, 1, 3, 6}
    };
    int dp[10][10];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = a[i][j] + a[i- 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << '\n';
    }
    cout << a[3][3] - a[1][3] - a[2][1] + a[1][1] << '\n';
    return 0;
}
