// ts2 p33 e2
#include <iostream>
using namespace std;

void intersc(int *x, int *y) {
    int aux;
    aux = *x; *x = *y; *y = aux;
}

int main(int argc, char *argv[]) {
    int a = 2, b = 3;
    intersc(&a, &b);
    cout << a << " " << b << '\n';
    return 0;
}
