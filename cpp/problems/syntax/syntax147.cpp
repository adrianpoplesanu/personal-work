// https://cdecl.org/ -> this is cool
#include <iostream>
using namespace std;

char test() {
    char a[5];
    return 'a';
}

char (*test2())[5] {
    char a[5] = {'c', 'a', 'b', 'c', 'a'};
    cout << a << "\n";
    return &a;
};

char (*test3())[5] {
    return NULL;
}

int main(int argc, char *argv[]) {
    char (*x[3])();
    char (*(*y[3])())[5];

    x[0] = &test;
    cout << x[0]() << "\n";

    y[0] = &test2;
    cout << y[0]() << "\n";
    cout << *y[0]() << "\n";

    y[1] = &test3;
    cout << y[1]() << "\n";
    return 0;
}
