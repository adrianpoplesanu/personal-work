/*
   exercise: 049
   page: 180
   description: odd numbers only as input
   command: echo 5 | ./program049
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "[ RESULT ] no even numbers\n";
        return 0;
    }

    std::cout << "[ RESULT ]\n";
    int step = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            std::cout << i << " ";
            step++;
            if (step == n) {
                std::cout << "\n";
                step = 0;
            }
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

