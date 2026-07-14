/*
   exercise: 013
   page: 127
   description: prime test
   command: echo 13 | ./program013
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cout << "[ input ] n = ";
    std::cin >> n;

    bool is_prime = true;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) is_prime = false;
    }

    std::cout << "[ RESULT ] " << is_prime << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

