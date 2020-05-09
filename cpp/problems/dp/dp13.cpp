// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #405

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

void afisare_drum(int a[100], int dp[100], int drum[100], int poz) {
    if (poz != -1) {
        afisare_drum(a, dp, drum, drum[poz]);
        cout << a[poz] << " ";
    }
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n;
    int a[100];
    int dp[100];
    int drum[100];
    ifstream in("dp13.in");
    ofstream out("dp13.out");

    in >> n;
    for (int i = 0; i < n; i++) in >> a[i];

    dp[0] = 1;
    drum[0] = -1;

    for (int i = 1; i < n; i++) {
        dp[i] = 1;
        drum[i] = -1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    drum[i] = j;
                }
            }
        }
    }

    int max = dp[0], poz = 0;
    for (int i = 1; i < n; i++) {
        if (max < dp[i]) {
            max = dp[i];
            poz = i;
        }
    }

    afisare_drum(a, dp, drum, poz);
    cout << endl;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}