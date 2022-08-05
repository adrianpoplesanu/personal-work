#include <iostream>

int main(int argc, char* argv[]) {
    int a[10][10] = {{1, 2, 3}, 
                     {4, 5, 6}, 
                     {7, 8, 9}};
    int b[10][10] = {{2, 0, 0}, 
                     {0, 2, 0}, 
                     {0, 0, 2}};
    int c[10][10];
    int n = 3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) std::cout << c[i][j] << " ";
        std::cout << "\n";
    }

    return 0;
}