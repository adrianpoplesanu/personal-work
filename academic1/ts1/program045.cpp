/*
   exercise: 045
   page: 178
   description: a ^ n with less than n multiplication
   command: echo 2 25 | ./program045
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int power(int val, int pow, int& total_multiplications) {
    if (pow == 0) return 1;
    if (pow % 2 == 0) {
        total_multiplications++;
        return power(val * val, pow / 2, total_multiplications);
    }
    total_multiplications++;
    return val * power(val, pow - 1, total_multiplications);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a, n, total = 0;
    std::cin >> a >> n;
    std::cout << "[ RESULT ] " << power(a, n, total) << " " << total << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

