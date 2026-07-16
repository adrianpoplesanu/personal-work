/*
   exercise: 031
   page: 133
   description: digit per digit read number
   command: echo 3 6 7 3 | ./program031
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, num = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int digit;
        std::cin >> digit;
        num *= 10;
        num += digit;
    }
    std::cout << "[ RESULT ] " << num << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

