/*
   exercise: 037
   page: 177
   description: pseudo random ints
   command: echo 12345678 100 | ./program037
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
        seed /= 100;
        seed = seed % 10000;
        seed = seed * seed;
        seed = seed % 100000000;
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

