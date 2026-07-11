/*
   exercise: 004
   page: 121
   description: multi-step addition for multiplication
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n1, n2;
    std::cin >> n1;
    std::cin >> n2;

    int sum = 0;
    while(n2-- > 0) {
        sum += n1;
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

