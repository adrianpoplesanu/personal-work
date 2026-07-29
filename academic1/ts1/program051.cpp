/*
   exercise: 051
   page: 193
   description: more read/write arrays
   command: echo 7 9.1 2.2 7.3 4.4 6.5 1.6 4.7 | ./program051
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, i;
    float a[50], b[50];
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (i = 0; i < n; i++) {
        b[i] = a[i];
    }
    std::cout << "[ RESULT ] ";
    for (i = 0; i < n; i++) {
        std::cout << a[i] << " ";
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

