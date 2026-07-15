/*
   exercise: 020
   page: 132
   description: produsul cifrelor
   command: echo 123 | ./program20
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, produs = 1;
    std::cin >> n;
    while(n > 0) {
        produs *= n % 10;
        n /= 10;
    }
    std::cout << "[ RESULT ] " << produs << " \n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

