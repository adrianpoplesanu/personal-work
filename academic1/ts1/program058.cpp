/*
   exercise: 058
   page: 199
   description: cartesian product
   command: echo 3 1 2 3 3 4 5 6 | ./program058
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], c[50], n, m, i, j, k = 0;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cin >> m;
    for(i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << "[ RESULT ] ";
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cout << "(" << a[i] << ", " << b[j] << ") ";
        }
    }
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

