/*
   exercise: 011
   page: 026
   description: simple function call
   command: ./program011
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int prod(int a, int b) {
    return a * b;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a = 2, b = 3;
    std::cout << 1 + prod(a, b) << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

