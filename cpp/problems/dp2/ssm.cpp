// secventa din sir care are suma elementelor maxima
// secventa = elemente consecutive
// e aceeasi problema ca ssm din cursul de pa sau ca #403 de pe http://info.mcip.ro/?cap=Programare%20dinamica
// in cursul de pa se face o verificare in functie de suma precedenta, daca e pozitiva
// eu am alta implementare, imi place mai mult asa, mi se pare ca are mai multa logica
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[100] = {-2, 1, -3, 3, -1, 4, -6, 2, 3}, n = 9;
    int dp[n];
    dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        dp[i] = a[i];
        if (dp[i] < dp[i - 1] + a[i]) dp[i] = dp[i - 1] + a[i];
    }

    for (int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << "\n";
    return 0;
}
