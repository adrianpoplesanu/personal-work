/*
   exercise: 018
   page: 132
   description: expressions
   command: echo 1 2 3 | ./program018
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float x, y, z;
    std::cin >> x >> y >> z;
    std::cout << "[ RESULT ] " << x << " " << y << " " << z << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

