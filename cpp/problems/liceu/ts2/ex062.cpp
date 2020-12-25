// ts2 p36 e2
#include <iostream>
using namespace std;

void s1();
void s2();

int main(int argc, char *argv[]) {
    s1();
    return 0;
}

void s1() {
    s2();
    cout << "in s1\n";
}

void s2() {
    cout << "in s2\n";
}
