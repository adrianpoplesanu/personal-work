/*
   exercise: 003
   page: 121
   description: inverse number
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int number = 248;
    int inv = 0;
    while (number > 0) {
        std::cout << "[ log ] digit = " << number % 10 << '\n';
        inv = inv * 10 + number % 10;
        std::cout << "[ log ] inv = " << inv << '\n';
        number /= 10;
    }
    std::cout << "[ result ] " << inv << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

