/*
   exercise: 062
   page: 206
   description: insertion sort
   command: echo 8 1 9 2 8 3 4 7 5 1 | ./program062
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], n, i, j, k;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    b[0] = a[0];
    for (i = 1; i < n; i++) {
        j = i - 1;
        while (j >= 0 && a[i] < b[j]) {
            j--;
        }
        for (k = i - 1; k > j; k--) {
            b[k + 1] = b[k];
        }
        b[j + 1] = a[i];
    }

    std::cout << "[ RESULT ] ";
    for (i = 0; i < n; i++) {
        std::cout << b[i] << " ";
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

