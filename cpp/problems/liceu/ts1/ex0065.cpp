// TS1 e15 p111 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n_2 = 0, n_1 = 0, fib = 1, n;
    cout << "n = "; cin >> n;
    while(fib < n) {
        cout << fib << " ";
        n_2 = n_1;
        n_1 = fib;
        fib = n_2 + n_1;
    }
    cout << endl;
    return 0;
}

// -2 -1  f
//  0  0  1
//  0  1  1
//  1  1  2
//  1  2  3
//  2  3  5
