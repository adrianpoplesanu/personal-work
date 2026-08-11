/*
   exercise: 93
   page: 238
   description: cyclic permutation of array
   command: echo 4 1 2 3 4 | ./program093
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    // Each cyclic permutation is obtained by choosing a different start index.
    for (int startIndex = 0; startIndex < n; startIndex++) {
        for (int offset = 0; offset < n; offset++) {
            std::cout << a[(startIndex + offset) % n];
            if (offset + 1 < n) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
