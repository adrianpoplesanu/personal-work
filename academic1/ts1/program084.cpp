/*
   exercise: 084
   page: 00
   description: testing template
   command: echo 3 3 7.1 4.2 6.3 2.4 8.5 1.6 9.7 3.8 5.9 | ./program084
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, m, i, j;
    double a[10][10];
    std::cin >> n >> m;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "[ RESULT ]\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

