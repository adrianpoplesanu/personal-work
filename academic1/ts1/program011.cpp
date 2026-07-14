/*
   exercise: 011
   page: 126
   description: ecuatia gradul I
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float a, b;
    std::cout << "[ input ] a = ";
    std::cin >> a;
    std::cout << "[ input ] b = ";
    std::cin >> b;

    if (a != 0) {
        std::cout << "[ result ] max = " << -b/a << '\n';
    } else {
        if (b == 0) {
            std::cout << "[ undetermined ]";
        } else {
            std::cout << "[ no solutions ]";
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

