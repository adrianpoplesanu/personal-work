// https://infoarena.ro/problema/desc
#include <iostream>
#include <vector>
#include <map>

using namespace std;
	
int N, k;
int dp[3050][3050];
vector <int> divizori;

int main (int argc, char *argv[]) {
    cin >> N >> k;
    for (int i = 1; i * i <= N; i++) {
        if (N % i == 0) {
            divizori.push_back(i);
            if (N / i != i) divizori.push_back (N / i); // add sqaure root only once
        }
    }
    sort(begin(divizori), end(divizori));
    map<int, int> ind;
    int v = 0;
    for (int x : divizori) ind[x] = v++;
    int cnt = divizori.size();
    dp[cnt - 1][0] = 1;
    for (int i = cnt - 1; i > 0; i--) {
        for (int j = 0; j < cnt; j++) {
            int prod = divizori[j];
            int add = divizori[i];
            dp[i][j] += dp[i + 1][j];
            if (prod % add == 0 && ind.find(prod / add) != ind.end()) {
                dp[i][j] += dp[i][ind[prod / add]];
            }
        }
    }
    cout << dp[1][cnt - 1] << '\n';
    return 0;
}
