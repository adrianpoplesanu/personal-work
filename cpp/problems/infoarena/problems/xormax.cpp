// https://infoarena.ro/problema/xormax
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream in("xormax.in");
    int n;
    int a[100000];
    in >> n;
    for (int i = 0; i < n; i++) in >> a[i];
    in.close();

    int dp[100000];
    int count[100000];
    dp[0] = a[0];
    count[0] = 0;
    int max = dp[0];
    int p = 0;

    for (int i = 1; i < n; i++) {
        if ((a[i] ^ dp[i - 1]) >= a[i]) {
        //if ((a[i] ^ dp[i - 1]) >= dp[i - 1]) {
            dp[i] = a[i] ^ dp[i - 1];
            count[i] = count[i - 1] + 1;
        } else {
            dp[i] = a[i];
            count[i] = 0;
        }
        if (dp[i] > max) {
            max = dp[i]; p = i;
        }
    }

    //for (int i = 0; i < n; i++) cout << dp[i] << " ";
    //cout << "\n";

    ofstream out("xormax.out");
    out << max << " " << p - count[p] + 1 << " " << p + 1;
    out.close();

    return 0;
}
