// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #403

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start = clock();
    ifstream in("dp14.in");
    ofstream out("dp14.out");
    int n, a[100], dp[100], max, im, inceput[100];
    in >> n;
    for (int i = 0; i < n; i++) in >> a[i];

    dp[0] = a[0];
    inceput[0] = 0;
    max = a[0];
    for (int i = 1; i < n; i++) {
        dp[i] = a[i];
        inceput[i] = i;
        if (dp[i - 1] + a[i] > dp[i]) {
            dp[i] = dp[i - 1] + a[i];
            inceput[i] = inceput[i - 1];
            if (max <= dp[i]) {
                max = dp[i];
                im = i;
            }
        }
    }

    cout << max << endl << im << endl << inceput[im] << endl;
    for (int i = inceput[im]; i <= im; i++) cout << a[i] << " ";
    cout << endl;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}