// https://www.infoarena.ro/problema/custi
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[1001][1001], n;
    ifstream in("custi.in");
    in >> n;

    int dp[1001][1001], count[1001];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> a[i][j];
            if (i == 0) dp[i][j] = a[i][j];
            else if (j == 0) dp[i][j] = a[i][j];
            else {
                if (a[i][j] == 1) {
                    dp[i][j] = min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j])) + a[i][j];
                } else {
                    dp[i][j] = 0;
                }
            }
            ++count[dp[i][j]];
        }
    }
    in.close();
    for(int i = n - 1; i >= 1; --i) {
        count[i] += count[i + 1];
    }

    ofstream out("custi.out");
    for (int i = 1; i <= n; ++i) out << count[i] << '\n';
    out.close();

    return 0;
}
