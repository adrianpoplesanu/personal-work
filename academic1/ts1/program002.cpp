/*
   exercise: 002
   page: 120
   description: digit sum
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 1

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int number = 248;
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    std::cout << "[ result ] " << sum << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

