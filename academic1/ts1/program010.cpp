/*
   exercise: 007
   page: 125
   description: biggest read number
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, sum = 0, prod = 1;
    std::cout << "[ input ] n = ";
    std::cin >> n;

    for(int i = 1; i <= n; i++) {
        prod *= i;
        sum += prod;
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

