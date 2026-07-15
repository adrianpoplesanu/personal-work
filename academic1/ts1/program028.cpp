/*
   exercise: 028
   page: 133
   description: numere prime intre doua numere
   command: echo 123 235 | ./program028
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n1, n2;
    std::cin >> n1 >> n2;

    std::cout << "[ RESULT ] ";
    for(int i = n1; i <= n2; i++) {
        bool is_prime = 1;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) is_prime = 0;
        }
        if (is_prime) std::cout << i << " ";
    }
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

