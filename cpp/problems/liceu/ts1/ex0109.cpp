// TS1 e3 p134 - insertie
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10], b[10], n, j = 1;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    b[0] = a[0];
    for (int i = 1; i < n; i++) {
        int k = 0;
        while(a[i] > b[k] && (k < j)) {
            k++;
        }
        for (int l = j; l > k; l--) b[l] = b[l - 1];
        b[k] = a[i];
        j++;
    }
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    cout << endl;
    return 0;
}
