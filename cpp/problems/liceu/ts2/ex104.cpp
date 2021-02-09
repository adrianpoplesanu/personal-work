// ts2 p49 e26
#include <iostream>
using namespace std;

int f(int x) {
    return x + 1;
}

void t(int a) {
    cout << ++a << "\n";
}

int main(int argc, char *argv[]) {
    t(f(f(f(1))));
    return 0;
}
