#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int *a[3]; // trei pointeri catre int*
    int (*b)[3]; // un pointer catre un element int[3]

    int t[] = {0, 10, 20, 30, 40, 50};
    a[1] = t;

    cout << a[1][2] << "\n";

    int p[3] = {15, 25, 35};
    b = &p;

    cout << b[0][2] << "\n";
    cout << b[1][2] << "\n";
    cout << *b[2] << "\n";
    cout << b[11][2] << "\n";

    cout << (*b)[2] << "\n";

    return 0;
}
