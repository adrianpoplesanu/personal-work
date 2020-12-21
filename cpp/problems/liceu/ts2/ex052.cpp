// ts2 p29 e4
#include <iostream>
using namespace std;

int a;

void t() {
    int a = 4;
    {
        int a = 3;
        cout << a << '\n';
    }
    cout << a << '\n';
}

int main (int argc, char *argv[]) {
    a = 5;
    t();
    cout << a << '\n';
    return 0;
}
