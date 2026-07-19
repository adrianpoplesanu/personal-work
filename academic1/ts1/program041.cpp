/*
   exercise: 041
   page: 178
   description: all numbers up to n whose digit ^ 2 sum is equal to k
   command: echo 123 | ./program041
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int current = i;
        int sum = 0;
        while(current) {
            sum += (current % 10) * (current % 10);
            current /= 10;
        }
        if (i == sum) {
            std::cout << "[ RESULT ] " << i << "\n";
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

