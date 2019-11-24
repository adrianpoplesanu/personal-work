#include <iostream>
using namespace std;

void init_vector(int *a, int n) {
    a = new int[n];
}

void fill(int *a, int n, int val) {
    for (int i = 0; i < n; i++) a[i] = val;
}

void print_vector(int *a, int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    int *a = new int();
    init_vector(a, 12);
    fill(a, 12, 2);
    print_vector(a, 12);
    return 0;
}
