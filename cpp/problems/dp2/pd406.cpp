// http://info.mcip.ro/?cap=Programare%20dinamica #406
#include <iostream>
#include <string>
using namespace std;

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

void drum_back(string s[], int drum[], int poz) {
    if (poz != -1) {
        drum_back(s, drum, drum[poz]);
        cout << s[poz] << " ";
    }
}

int main(int argc, char *argv[]) {
    int n = 5;
    string s1[] = {"lenin", "brejnev", "marx", "stalin", "von der leyen"};
    string s2[] = {"marx", "stalin", "brejnev", "lenin", "von der leyen"};
    int dp[n], a[n], drum[n];
    memset(dp, 0, sizeof(dp));
    memset(drum, -1, sizeof(drum));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s1[i] == s2[j]) a[j] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (a[i] < a[j]) {
                //dp[j] = max(dp[i] + 1, dp[j]);
                if (dp[i] + 1 > dp[j]) {
                    dp[j] = dp[i] + 1;
                    drum[j] = i;
                }
            }
        }
    }

    int max = dp[0];
    int poz = 0;
    for (int i = 0; i < n; i++) {
        if (max < dp[i]) {
            max = dp[i];
            poz = i;
        }
    }

    //for (int i = 0; i < n; i++) cout << dp[i] << " ";
    //cout << "\n";
    //for (int i = 0; i < n; i++) cout << drum[i] << " ";
    //cout << "\n";

    cout << max + 1 << "\n";
    drum_back(s2, drum, poz);
    cout << "\n";

    return 0;
}