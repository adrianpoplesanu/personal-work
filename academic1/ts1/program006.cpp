/*
   exercise: 007
   page: 123
   description: 0.1 + 0.2 + ... + 0.9
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float sum = 0;

    for(float i = 0.1; i < 1; i += 0.1) {
        sum += i;
    }

    std::cout << "[ result ] sum = " << sum << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

