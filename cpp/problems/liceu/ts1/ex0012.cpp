// TS1 e12 p132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    float x, sm = 0;
    cout << "n = "; cin >> n;
    for(int i = 0; i < n; i++) {
        cout << "x = "; cin >> x;
        if (x > 0) sm += x;
    }
    cout << "sm = " << sm << endl;
    return 0;
}
