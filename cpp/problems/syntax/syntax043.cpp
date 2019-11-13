#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int b = 5, *a;
    a = &b;
    cout << a << endl;
    cout << *a << endl;
    cout << &a << endl;

    int *c = &b;
    cout << c << endl;
    cout << *c << endl;
    cout << &c << endl;
    return 0;
}
