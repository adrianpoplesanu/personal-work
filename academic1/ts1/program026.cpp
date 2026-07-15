/*
   exercise: 026
   page: 132
   description: square sum
   command: echo 13 | ./program026
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    bool is_sum = 0;
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (n == i * i + j * j) {
                is_sum = 1;
                std::cout << "[ RESULT ] yes, " << n << " = " << i << "^2 + " << j << "^2 \n";
            }
        }
    }
    if (!is_sum) {
        std::cout << "[ RESULT ] no dice \n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

