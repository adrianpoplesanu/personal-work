#include <iostream>
#include <fstream>
using namespace std;

void init_vector(int *(&a), int n) {
    a = new int[n];
}

void fill(int *(&a), int n, int value) {
    for (int i = 0; i < n; i++) a[i] = value;
}

void print_vector(int *a, int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    int *a;
    int n = 6;
    init_vector(a, n);
    fill(a, n, 7);
    print_vector(a, n);
    return 0;
}
