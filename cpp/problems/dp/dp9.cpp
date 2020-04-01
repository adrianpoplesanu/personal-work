// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #421
// nu inteleg problema asta

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n, m, a[100][100];
    int dp[100][100];
    ifstream in("dp9.in");
    ofstream out("dp9.out");
    in >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) in >> a[i][j];
    }
    in >> m;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}