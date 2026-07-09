/*
   exercise: 000
   pageg: 00
   description: testing template
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 1

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here
    int s = 0;
    for (int i = 0; i < 1000000; i++) {
        s += i;
    }
    std::cout << s << '\n';
    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

