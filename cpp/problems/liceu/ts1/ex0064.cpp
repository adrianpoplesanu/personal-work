// TS1 e14 p111 pdf - fibonacci
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a, fib = 1, n_1 = 0, n_2 = 0;
    cout << "a = "; cin >> a;
    while(--a) {
        int aux = n_1 + fib;
        n_2 = n_1;
        n_1 = fib;
        fib = aux;
    }
    cout << "fib = " << fib << endl; 
    return 0;
}
/*
1 0 0 1
2 0 1 1
3 1 1 2
4 1 2 3
5 2 3 5
6 3 5 8
7 5 8 13
*/
