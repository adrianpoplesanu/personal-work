/*
   exercise: 066
   page: 212
   description: spiral walk through a matrix
   command: echo 5 5 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 | ./program066
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m, i, j;
    std::cin >> n >> m;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    for (i = 0; i < n / 2 + 1; i++) {
        for (j = i; j < n - i; j++) std::cout << a[i][j] << " ";
        for (j = i + 1; j < n - i; j++) std::cout << a[j][n - i - 1] << " ";
        for (j = n - i - 2; j >= i; j--) std::cout << a[n - i - 1][j] << " ";
        for (j = n - i - 2; j >= i + 1; j--) std::cout << a[j][i] << " ";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

