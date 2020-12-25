// ts2 p35 e1
#include <iostream>
using namespace std;

void s1() {
    cout << "in S1\n";
}

void s2() {
    s1();
    cout << "in S2\n";
}

int main(int argc, char *argv[]) {
    s1();
    s2();
    return 0;
}
