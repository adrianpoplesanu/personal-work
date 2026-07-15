/*
   exercise: 023
   page: 132
   description: expressions
   command: echo 123 | ./program023
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float x, result = 0;
    std::cin >> x;

    if (x <= 10) {
        result = x * x + x - 2;
    } else if (x <= 20) {
        result = 1 / x;
    } else {
        result = (x - 1) / (x + 1);
    }

    std::cout << "[ RESULT ] " << result << " \n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

