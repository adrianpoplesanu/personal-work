/*
   exercise: 033
   page: 133
   description: 0..a, 1..b so on and so forth
   command: echo 1267 ./program033
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;
    std::cout << "[ RESULT ] ";
    while (n > 0) {
        int current = n % 10;
        n /= 10;
        std::cout << (char) ('a' + current);
    }
    std::cout << " - e invers ca pozitionare, cu recursivitate s-ar fi rezolvat\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

