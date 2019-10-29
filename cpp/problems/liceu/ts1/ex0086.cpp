// TS1 e33 p113 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int k;
    cout << "k = "; cin >> k;
    for (int i = 2; i <= k; i++) {
        if (k % i == 0) {
            int a = i, b = k / i;
            if ((a + b) % 2 == 1 || (b -a) % 2 == 1) continue;
            int x = (a+b) / 2;
            int y = (b-a) / 2;
            cout << "(" << x << ", " << y << ") ";
            cout << "(" << -x << ", " << -y << ") "; 
            cout << "(" << x << ", " << -y << ") ";
            cout << "(" << -x << ", " << y << ") ";
        }
    }
    cout << endl;
    return 0;
}
