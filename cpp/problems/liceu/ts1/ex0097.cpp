// TS1 e2 p122 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, a[30], min;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    min = a[0];
    for (int i = 1; i < n; i++) if (min > a[i]) min = a[i];
    cout << "min = " << min << endl;
    return 0;
}
