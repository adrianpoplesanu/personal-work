#include <iostream>
#include <fstream>
using namespace std;

void init_matrix(int **(&a)) {
    a = new int*[10];
    for (int i = 0; i < 10; i++) {
        a[i] = new int[10];
    }
}

void fill(int **(&a), int value) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            a[i][j] = value;
        }
    }
}

void print_matrix(int **a) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    int **a;
    init_matrix(a);
    fill(a, 10);
    print_matrix(a);   
    return 0;
}
