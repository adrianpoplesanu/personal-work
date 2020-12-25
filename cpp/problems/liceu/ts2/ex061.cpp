// ts2 p36 e1
#include <iostream>
using namespace std;

void s2();

void s1() {
    s2();
    cout << "in s1\n";
}

void s2() {
    cout << "in s2\n";
}

int main (int argc, char *argv[]) {
    s1();
    return 0;
}
