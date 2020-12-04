// ts2 p17 e1
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
    int a = 5, *b=&a;

    cout << a << "\n";    // 5
    cout << &a << "\n";   // adresa de memorie a variabilei a
    cout << b << "\n";    // adresa de memorie a variabilei a
    cout << &b << "\n";   // adresa de memorie a pointerului b
    cout << *b << "\n";   // 5
    cout << *&a << "\n";  // 5

    return 0;
}
