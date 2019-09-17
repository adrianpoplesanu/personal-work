// TS1 e11 p132
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    float x, p = 1;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "x = "; cin >> x;
        if (x != 0) p *= x;
    }
    cout << "p = " << p << endl;
    return 0;
}
