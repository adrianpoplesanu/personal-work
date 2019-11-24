#include <iostream>
using namespace std;

void init_vector(int **a, int n) {
    for (int i = 0; i < n; i++) a[i] = new int(); // fara linia asta am segmentation fault!!! wow!!! de ce oare???
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
}

void fill(int **a, int n, int val) {
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) a[i][j] = val;
}

void print_vector(int **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    int **a = new int*();
    init_vector(a, 7);
    fill(a, 7, 2);
    print_vector(a, 7);
    return 0;
}
