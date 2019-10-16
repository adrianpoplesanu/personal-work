// TS1 e27 p112 pdf
#include <iostream>
using namespace std;

bool prim(int n) {
    for (int i = 2; i < n; i++)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char *argv[]) {
    int n, i = 2;
    cout << "n = "; cin >> n;
    while (n) {
        if (prim(i) && prim(i+2)) {
            cout << "(" << i << "," << i + 2 << ")" << " ";
            n--;
        }
        i++;
    }
    cout << endl;
    return 0;
}
