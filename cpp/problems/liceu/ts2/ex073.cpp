// ts2 p44 e1
#include <iostream>
using namespace std;

int suma(int n, ...) {
    int suma = 0;
    for (int i = 1; i <= n; i++) suma += *(&n + i);
    return suma;
}

int main(int argc, char *argv[]) {
    int a = 5;
    cout << suma(1, a) << "\n";
    cout << suma(3, 1, 7, 9) << "\n";
    cout << suma(5, 1, 2, 0, 9, 7) << "\n";
    return 0;
}
