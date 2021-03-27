#include <iostream>
using namespace std;

void foo(void) {
    int a = 5;
    cout << a * a << "\n";
}

int main(int argc, char *argv[]) {
    void (*p)(void);
    p = foo;
    p();
    return 0;
}