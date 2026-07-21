/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 1234 3456 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, m, total = 0;
    std::cin >> n >> m;
    for (int i = 10; i <= 10000; i *= 10) {
        int current = (n % i) / (i / 10);
        for (int j = 10; j <= 10000; j*= 10) {
            int current2 = (m % j) / (j / 10);
            if (current == current2) total++;
        }
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

