// TS1 e6 p105 pdf v1
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, max;
    cout << "n = "; cin >> n;
    cout << "k = "; cin >> max;
    for(int i = 1; i < n; i++) {
        int k;
        cout << "k = "; cin >> k;
        if (k > max) max = k;
    }
    cout << "max = " << max << endl;
    return 0;
}
