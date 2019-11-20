#include <iostream>
#include <fstream>
using namespace std;

void init_vector(int *&a) {
    a = new int[10];
    a[0] = 23;
    cout << a[0] << endl;
}

void fill(int *&a, int value) {
    for (int i = 0; i < 10; i++) a[i] = value;
}

void print_vector(int *a) {
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    int *a;
    init_vector(a);
    fill(a, 7);
    print_vector(a);
    return 0;
}
