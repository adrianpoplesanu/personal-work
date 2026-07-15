/*
   exercise: 027
   page: 132
   description: expressions
   command: echo 7 | ./program027
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;

    int produs1 = 1;
    int produs2 = 1;
    float suma1 = 0;
    float suma2 = 1;

    for (int i = 1; i <= n; i++) {
        produs1 *= i;
        suma1 += 1.0 / produs1;
    }

    for (int i = 1; i <= n; i++) {
        produs2 *= (2 * i + 1);
        suma2 += produs2;
    }

    std::cout << "[ RESULT ] " << suma1 << " \n";
    std::cout << "[ RESULT ] " << suma2 << " \n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

