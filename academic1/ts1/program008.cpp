/*
   exercise: 005
   page: 123
   description: remainder calculation without divide
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n1, n2, cat = 0, rest;
    std::cout << "[ input ] n1 = ";
    std::cin >> n1;
    std::cout << "[ input ] n2 = ";
    std::cin >> n2;

    while(n1 >= n2) {
        n1 -= n2;
        cat += 1;
    }
    rest = n1;

    std::cout << "[ result ] cat = " << cat << ", rest = " << rest << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

