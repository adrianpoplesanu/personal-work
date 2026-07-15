/*
   exercise: 022
   page: 132
   description: num is a sum of others
   command: echo 1 2 3 | ./program022
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a, b, c;
    std::cin >> a >> b >> c;
    if (a == b + c) {
        std::cout << "[ RESULT ] " << a << " = " << b << " + " << c << " \n";
    } else if (b == a + c) {
        std::cout << "[ RESULT ] " << b << " = " << a << " + " << c << " \n";
    } else if (c == a + b) {
        std::cout << "[ RESULT ] " << c << " = " << a << " + " << b << " \n";
    } else {
        std::cout << "[ RESULT ] no sum \n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

