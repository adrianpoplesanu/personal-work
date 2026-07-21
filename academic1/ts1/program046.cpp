/*
   exercise: 046
   page: 179
   description: how many time a prime number divides the product of n numbers
   command: echo 2 4 2 4 6 8 | ./program046
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, p, total = 0;
    std::cin >> p >> n;
    while(n--) {
        int current;
        std::cin >> current;
        while(current % p == 0) {
            total++;
            current /= p;
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

