// http://info.mcip.ro/?cap=Programare%20dinamica ; ex #738

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[100], dp[100], s = 0;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    dp[0] = 1;
    s = 1;
    for (int i = 1; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] += dp[j];
            }
        }
        s += dp[i];
    }
    cout << s << endl;
    return 0;
}