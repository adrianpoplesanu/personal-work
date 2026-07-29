/*
   exercise: 050
   page: 193
   description: read/write array
   command: echo 7 9 2 7 4 6 1 4 | ./program050
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int v[100], n, i;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    std::cout << "[ RESULT ] ";
    for (i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

