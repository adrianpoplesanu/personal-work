/*
   exercise: 034
   page: 133
   description: first smaller and first bigger primes
   command: echo 123 | ./program034
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int x;
    std::cin >> x;

    std::cout << "[ RESULT ] ";
    bool found = false;
    for(int i = x; i > 1 && !found; i--) {
        bool is_prime = true;
        for(int j = 2; j < i; j++) {
            if (i % j == 0) is_prime = false;
        }
        if (is_prime) {
            std::cout << i << " ";
            found = true;
        }
    }
    found = false;
    for(int i = x + 1; !found; i++) {
        bool is_prime = true;
        for(int j = 2; j < i; j++) {
            if (i % j == 0) is_prime = false;
        }
        if (is_prime) {
            std::cout << i << " ";
            found = true;
        }
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

