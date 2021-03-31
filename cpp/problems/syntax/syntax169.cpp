#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int *p = new int(5);
    cout << *p << "\n";
    cout << p << "\n";
    cout << &p << " \n";

    int *d = new int(6);
    cout << *d << "\n";
    cout << d << "\n";
    cout << &d << "\n";

    int *m = new int(7);
    cout << *m << "\n";
    cout << m << "\n";
    cout << &m << "\n";

    int *l = new int(100);
    cout << *l << "\n";
    cout << l << "\n";
    cout << &l << "\n";
    return 0;
}