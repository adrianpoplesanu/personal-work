// TS1 e6 p128 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[30], n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) a[i] = 0;
    int s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    while(s < n) {
        a[0]++;
        for(int i = 0; i < n; i++) if (a[i] > 1) {
            a[i] -= 2;
            a[i + 1]++;
        }
        for (int i = 0; i < n; i++) if (a[i]) cout << i + 1 << " ";
        cout << endl;
        s = 0;
        for (int i = 0; i < n; i++) s += a[i];
    }
    return 0;
}
