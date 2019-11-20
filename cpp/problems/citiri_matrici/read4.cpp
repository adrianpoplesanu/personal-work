#include <iostream>
#include <fstream>
using namespace std;

void init_scalar(int &a) {
    // no need, a already has assigned a memory address
}

void fill(int &a, int value) {
    a = value;
}

void print_scalar(int a) {
    cout << a << endl;
}

int main(int argc, char *argv[]) {
    int a;
    init_scalar(a);
    fill(a, 9);
    print_scalar(a);
    return 0;
}
