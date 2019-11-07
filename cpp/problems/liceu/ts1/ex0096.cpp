// TS1 e1 p122 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[30], max;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    max = a[0];
    for (int i = 1; i < n; i++) if (max < a[i]) max = a[i];
    cout << "max = " << max << endl;
    return 0;
}
