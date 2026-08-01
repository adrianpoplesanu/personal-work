/*
   exercise: 001
   page: 07
   description: best pointer example
   command: ./program001
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a = 7, *adra = &a, **adradra = &adra, ***adradradra = &adradra;
    std::cout << a << " " << *adra << " " << **adradra << " " << ***adradradra << "\n";
    std::cout << &a << " " << a << "\n";
    std::cout << adra << " " << &adra << " " << *adra << "\n";
    std::cout << *adradra << " " << adradra << " " << &adradra << **adradra << "\n";
    std::cout << **adradradra << " " << *adradradra << " " << adradradra << " " << &adradradra << " " << ***adradradra << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

