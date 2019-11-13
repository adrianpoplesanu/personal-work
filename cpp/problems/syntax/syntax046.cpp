#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a = 5;
    int *b = &a;
    cout << &a << endl << b << endl;
    cout << a << endl << *b << endl;
    cout << sizeof(&a) << endl;
    cout << sizeof(b) << endl;
    return 0;
}
