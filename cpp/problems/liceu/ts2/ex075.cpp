// ts2 p44 e1
#include <iostream>
using namespace std;

void functia(int n) {
    cout << "functia int\n";
}

void functia(int n, int m) {
    cout << "functia int int\n";
}

void functia(int *n) {
    cout << "functia int*\n";
}

int main(int argc, char *argv[]) {
    functia(2);
    functia(3, 4);
    int n;
    functia(&n);
    return 0;
}
