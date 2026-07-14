/*
   exercise: 012
   page: 126
   description: compare three numbers
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a, b, c;
    std::cout << "[ input ] a = ";
    std::cin >> a;
    std::cout << "[ input ] b = ";
    std::cin >> b;
    std::cout << "[ input ] c = ";
    std::cin >> c;

    if (a < b) {
        if (c < a) {
            std::cout << "[ RESULT ] " << c << " " << a << " " << b;
        } else {
            if (c < b) {
                std::cout << "[ RESULT ] " << a << " " << c << " " << b;
            } else {
                std::cout << "[ RESULT ] " << a << " " << b << " " << c;
            }
        }
    } else {
        if (c < b) {
            std::cout << "[ RESULT ] " << c << " " << b << " " << a;
        } else {
            if (c < a) {
                std::cout << "[ RESULT ] " << b << " " << c << " " << a;
            } else {
                std::cout << "[ RESULT ] " << b << " " << a << " " << c;
            }
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

