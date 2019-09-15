// TS1 e9 pg 132
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    int n;
    cout << "n = "; cin >> n;
    float E1 = 0, p1 = 1, E2 = 0, p2 = 1, E3;
    for (int i = 1; i <= n; i++) {
        p1 *= i;
        E1 += 1 / p1;
        E2 += p2;
        p2 *= (2 * i + 1);
    }
    cout << E1 << endl;
    cout << E2 << endl;
    return 0;
}
