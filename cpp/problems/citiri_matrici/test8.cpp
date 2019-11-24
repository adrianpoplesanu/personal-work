#include <iostream>
using namespace std;

void fill(int **a, int n, int val);
void print_mat(int **a, int n);

void init_mat(int **&a, int n) {
    a = new int*[n];
    for (int i = 0; i < n; i++) a[i] = new int[n];
    //a[2][2] = 23;
    //cout << a[2][2] << endl;
    fill(a, n, 3);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    //print_mat(a, n);
}

void fill(int **a, int n, int val) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = val;
        }
    }
}

void print_mat(int **a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    int **a = new int*();
    init_mat(a, 4);

    cout << a[2][2] << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << a[i][j] << " ";
        cout << endl; 
    }

    //cout << a[2][2] << endl;
    //fill(a, 4, 3);
    //cout << a[2][2] << endl;
    //print_mat(a, 4);
    return 0;
}
