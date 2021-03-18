// http://info.mcip.ro/?cap=Programare%20dinamica #405
#include <iostream>
using namespace std;

void afisare(int a[], int drum[], int poz) {
    if (poz != -1) {
        afisare(a, drum, drum[poz]);
        cout << a[poz] << " ";
    }
}

int main(int argc, char *argv[]) {
    int n = 9;
    int a[] = {4, 2, 3, 0, 5, 2, 6, 9, 8};
    int dp[n], drum[n];
    memset(dp, 0, sizeof(dp));
    memset(drum, -1, sizeof(drum));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {
                if (dp[i] + 1 > dp[j]) {
                    dp[j] = dp[i] + 1;
                    drum[j] = i;
                }
            }
        }
    }

    //for (int i = 0; i < n; i++) cout << dp[i] << " ";
    //cout << "\n";
    //for (int i = 0; i < n; i++) cout << drum[i] << " ";
    //cout << "\n";
    int max = dp[0], poz = 0;
    for (int i = 1; i < n; i++) {
        if (max < dp[i]) {
            max = dp[i];
            poz = i;
        }
    }
    cout << max + 1 << "\n";
    afisare(a, drum, poz);
    cout << "\n";
    return 0;
}