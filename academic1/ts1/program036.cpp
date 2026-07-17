/*
   exercise: 036
   page: 177
   description: pseudo random
   command: echo 100 0.12345678 | ./program036
*/

#include <iostream>
#include <chrono>
#include <iomanip>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    double num;
    std::cin >> n;
    std::cin >> num;
    while (n--) {
        float seed = (float) ((int)(num * 100000000 / 100) % 10000) / 10000;
        num = seed * seed;
        std::cout << "[ RESULT ] " << std::fixed << std::setprecision(8) << num << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

