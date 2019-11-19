// exemplu clasic de programare dinamica
// care sunt toate posibilitatile de a scrie numarul n ca suma de alte m numere
// ex n = 6, m = 3, {1, 3, 5}
// 1 + 1 + 1 + 1 + 1 + 1
// 1 + 1 + 1 + 3
// 1 + 1 + 3 + 1
// 1 + 3 + 1 + 1
// 3 + 1 + 1 + 1
// 3 + 3 
// 1 + 5
// 5 + 1
// si in plus avem lookup in dp[i] ca sa nu calculam valorile de mai multe ori
// si sume(7) = sume(6) + sume(4) + sume(2) adica sume(7) = sume(7-1) + sume(7-3) + sume(7-5)

#include <iostream>
using namespace std;

int dp[200];

int suma(int n, int m, int a[10]) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (dp[n] != 0) return dp[n];
    else {
        for(int i = 0; i < m; i++)
            dp[n] += suma(n - a[i], m, a);
    }
    return dp[n];
}

int main(int argc, char *argv[]) {
    int n, m, a[10];
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = 0; i <= n; i++) dp[i] = 0;
    for (int i = 0; i < m; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    int total = suma(n, m, a);
    cout << "total = " << total << endl;
    return 0;
}
