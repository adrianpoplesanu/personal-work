#include <iostream>
using namespace std;

void multiply(int a[2][2], int b[2][2], int rez[2][2]) {
    int c[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int cell_value = 0;
            for (int k = 0; k < 2; k++) cell_value += a[i][k] * b[k][j];
            c[i][j] = cell_value;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) rez[i][j] = c[i][j];
    }
}

void print_matrix(int a[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    int a[2][2] = {
        {1, 1},
        {1, 1}
    };
    int b[2][2] = {
        {2, 2},
        {2, 2}
    };
    int c[2][2] = {
        {3, 3},
        {3, 3}
    };

    int rez[2][2];
    multiply(a, b, rez);
    multiply(rez, c, rez);
    print_matrix(rez);
    return 0;
}
