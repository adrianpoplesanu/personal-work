/*
   exercise: 021
   page: 132
   description: numar maxim cu cifre
   command: echo 123 | ./program021
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, result;
    std::cin >> n;
    int c1 = n % 10;
    n /= 10;
    int c2 = n % 10;
    n /= 10;
    int c3 = n;

    if (c1 < c2) {
        if (c3 < c1) result = c2 * 100 + c1 * 10 + c3;
        else if (c3 < c2) result = c2 * 100 + c3 * 10 + c1;
        else result = c3 * 100 + c2 * 10 + c1;
    } else {
        if (c3 < c2) result = c1 * 100 + c2 * 10 + c3;
        else if (c3 < c1) result = c1 * 100 + c3 * 10 + c2;
        else result = c3 * 100 + c1 * 10 + c2;
    }

    std::cout << "[ RESULT ] " << result << " \n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

