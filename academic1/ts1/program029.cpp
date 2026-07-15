/*
   exercise: 029
   page: 133
   description: produsul numerelor non-zero
   command: echo 5 1 2 3 4 5 | ./program029
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, produs = 1;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        if (num != 0) produs *= num;
    }
    std::cout << "[ RESULT ] " << produs << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

