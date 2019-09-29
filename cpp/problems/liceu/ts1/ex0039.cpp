// TS1 e6 p105 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n, max, i = 0;
    cout << "n = "; cin >> n;
    do {
        int k;
        cout << "k = "; cin >> k;
        if (i == 0) { max = k; continue; }
        if (k > max) max = k;
    } while(++i < n);
    cout << "max = " << max << endl;
    return 0;
}
