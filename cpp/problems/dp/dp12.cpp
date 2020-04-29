// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #406

#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;


int main(int argc, char *argv[]) {
    clock_t start = clock();
    int n;
    string names[100], names2[100];
    int a[100];
    int dp[100];
    int drum[100];
    ifstream in("dp12.in");
    ofstream out("dp12.out");

    in >> n;
    for (int i = 0; i < n; i++) in >> names[i];
    for (int i = 0; i < n; i++) in >> names2[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (names[i] == names2[j]) a[j] = i;
        }
    }

    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

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
    /*int poz = n - 1, val = dp[n - 1];
    cout << max << endl;
    while (poz > 0) {
        while(dp[poz] == val) poz--;

    }*/

    for (int i = 0; i < n; i++) cout << dp[i] << " ";
    cout << endl;
    for (int i = 0; i < n; i++) cout << drum[i] << " ";
    cout << endl;

    in.close();
    out.close();
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}