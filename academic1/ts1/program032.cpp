/*
   exercise: 032
   page: 133
   description: count number digits
   command: echo 1078 | ./program032
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, total = 0;
    std::cin >> n;
    if (n == 0) total = 1;
    while (n > 0) {
        total++;
        n /= 10;
    }
    std::cout << "[ RESULT ] " << total << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

