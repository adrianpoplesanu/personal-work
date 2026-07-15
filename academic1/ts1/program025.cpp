/*
   exercise: 025
   page: 132
   description: interest calculator
   command: echo 100 2 3 | ./program025
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float s, p;
    int k;

    std::cin >> s >> p >> k;
    while (k--) {
        s += s * p / 100;
    }

    std::cout << "[ RESULT ] " << s << " \n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

