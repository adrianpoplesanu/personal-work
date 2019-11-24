#include <iostream>
using namespace std;

void init_mat(int **&a, int n) {
    a = new int*[n];
    for (int i = 0; i < n; i++) a[i] = new int[n];
}

void fill(int **a, int n, int val) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) a[i][j] = val;
}

void print_mat(int **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    int **a;
    init_mat(a, 10);
    fill(a, 10, 5);
    print_mat(a, 10);
    return 0;
}
