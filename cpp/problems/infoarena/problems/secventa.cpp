#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, k;
    int a[500000];
    ifstream in("secventa.in");
    in >> n >> k;
    for (int i = 0; i < n; i++) in >> a[i];
    in.close();

    int dp[500000];
    for (int i = k - 1; i < n; ++i) {
        int min = a[i - k + 1];
        for (int j = i - k + 1; j <= i; j++) {
            if (a[j] < min) min = a[j];
        }
        dp[i] = min;
    }

    int max = dp[k - 1], pos = k;
    for (int i = k - 1; i < n; ++i) {
        if (dp[i] > max) {
            max = dp[i];
            pos = i + 1;
        }
    }

    ofstream out("secventa.out");
    out << pos - k + 1 << " " << pos << " " << max;
    out.close();

    return 0;
}
