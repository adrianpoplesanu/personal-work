/*
   exercise: 014
   page: 128
   description: first n prime numbers
   command: echo 13 | ./program014
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, last = 2;
    std::cin >> n;

    std::cout << "[ RESULT ] ";

    while (n > 0) {
        for (int i = last; ; i++) {
            bool is_prime = true;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    is_prime = false;
                }
            }
            if (is_prime) {
                std:: cout << i << " ";
                last = i + 1;
                break;
            }
        }
        n--;
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

