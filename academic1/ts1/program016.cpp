/*
   exercise: 016
   page: 130
   description: decompose in prime factors
   command: echo 13 | ./program016
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, current = 2;
    std::cin >> n;

    std::cout << "[ RESULT ] ";

    if (n == 0 || n == 1) {
        std::cout << "[ RESULT ] " << n;
    }

    while (n > 1) {
        int count = 0;
        while (n % current == 0) {
            n /= current;
            count++;
        }
        if (count > 0) {
            std::cout << current << "^" << count << " ";
        }
        current++;
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

