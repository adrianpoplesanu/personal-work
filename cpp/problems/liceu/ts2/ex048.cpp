// ts2 p28 e1
#include <iostream>
using namespace std;

int a;

int t () {
    a = 3;
    cout << a << "\n";
}

int b;

int main(int argc, char *argv[]) {
    b = 4;
    cout << a  << "\n";
    t();
    return 0;
}
