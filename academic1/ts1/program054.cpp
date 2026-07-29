/*
   exercise: 054
   page: 195
   description: determine if array elements are distinct
   command: echo 8 9 2 8 3 4 7 5 5 | ./program054
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, j;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    bool found = false;
    for (i = 0; i < n && !found; i++) {
        for (j = i + 1; j < n && !found; j++) {
            if (a[i] == a[j]) found = true;
        }
    }
    if (found) {
        std::cout << "[ RESULT ] duplicates found\n";
    } else {
        std::cout << "[ RESULT ] duplicates not found\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

