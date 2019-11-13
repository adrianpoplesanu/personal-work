#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 5;
    int &b = a;
    int *c = &a;
    a++;
    cout << a << endl;
    cout << b << endl;
    cout << *c << endl;
    cout << &a << endl;
    cout << &b << endl;
    cout << c << endl;
    return 0;
}
