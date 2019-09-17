// TS1 e10 p132
#include <iostream>
using namespace std;

bool prim(int n) {
     int i = 1;
     if (n < 2) return false;
     while (++i < n) {
         if (n % i == 0) return false;
     }
     return true;
}

int main(int argc, char *argv[]) {
    int n, m;
    cout << "n = "; cin >> n;
    cout << "m = "; cin >> m;
    for (int i = n; i <= m; i++) {
        if (prim(i)) cout << i << " ";
    }
    cout << endl;
    return 0;
}
