/*
   exercise: 039
   page: 177
   description: pseudo random ints - metoda congruentei cu valori precalculate
   command: echo 456 100 | ./program039
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int seed, n;
    std::cin >> seed >> n;
    while(n--) {
        seed = seed * 1103515245 + 12345;
        seed = (seed / 65536) % 32768;
        std::cout << "[ RESULT ] " << seed << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

