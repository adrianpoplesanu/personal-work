// TS1 e14 p111 pdf v2
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n_2 = 0, n_1 = 0, fib = 1, n;
    cout << "n = "; cin >> n;
    while(--n) {
        n_2 = n_1;
        n_1 = fib;
        fib = n_1 + n_2;
    }
    cout << "fib = " << fib << endl;
    return 0;
}

//  -2 -1 fi
//   0  0  1
//   0  1  1
//   1  1  2
//   1  2  3
//   2  3  5
//   3  5  8
