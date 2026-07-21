/*
   exercise: 047
   page: 179
   description: number n decomposed as a sum of k unique numbers
   command: echo 123 7 | ./program047
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, k;
    std::cin >> n >> k;
    if (n - (k * (k - 1)) > k - 1) {
        std::cout << "[ RESULT ] ";
        for(int i = 0; i < k - 1; i++) {
            std::cout << i + 1 << " ";
        }
        std::cout << n - (k * (k - 1)) << "\n";
    } else {
        std::cout <<"[ RESULT ] impossible\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

