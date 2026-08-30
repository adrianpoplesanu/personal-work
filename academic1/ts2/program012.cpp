/*
   exercise: 012
   page: 26
   description: checking side effects of params in function call
   command: ./program012
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int side_effect1(int a) {
    std::cout << "side_effect1: " << a << "\n";
    return a;
}

int side_effect2(int a) {
    std::cout << "side_effect2: " << a << "\n";
    return a;
}

int test(int a, int b) {
    return a + b;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    test(side_effect1(5), side_effect2(6));

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

