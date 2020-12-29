// ts2 p40 e1
#include <iostream>
using namespace std;

int next(int n) {
    if (n == 9) return 1;
    return n + 1;
}

void next2(int &n) {
    if (n == 9) n = 1;
    else n++;
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "m = "; cin >> m;
    cout << "n = "; cin >> n;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << n << " ";
            //n = next(n);
            next2(n);
        }
        cout << "\n";
    }
    return 0;
}
