// ts2 p44 e1 ver b
// https://www.tutorialspoint.com/variable-number-of-arguments-in-cplusplus
#include <iostream>
#include <cstdarg>
using namespace std;

int suma(int n, ...) {
    int suma = 0;

    va_list valist;
    va_start(valist, n);
    for(int i = 0; i < n; i++) {
        suma += va_arg(valist, int);
    }
    va_end(valist);

    return suma;
}

int main(int argc, char *argv[]) {
    cout << suma(3, 1, 7, 9) << "\n";
    cout << suma(5, 1, 2, 0, 9, 7) << "\n";
    return 0;
}
