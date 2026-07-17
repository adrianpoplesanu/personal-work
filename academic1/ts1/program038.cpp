/*
   exercise: 038
   page: 177
   description: pseudo random ints - metoda congruentei
   command: echo 17 31 100 456 100 | ./program038
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a, c, m, seed, n;
    std::cin >> a >> c >> m >> seed >> n;
    while(n--) {
        seed = (a * seed + c) % m;
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

