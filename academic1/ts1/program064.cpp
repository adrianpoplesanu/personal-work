/*
   exercise: 064
   page: 210
   description: binary search
   command: echo 8 1 2 3 4 5 6 7 9 6 | ./program064
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, c, left, right, mid, found;
    std::cin >> n;
    for(i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::cin >> c;
    left = 0;
    right = n - 1;
    found = 0;
    while (left <= right && !found) {
        mid = (left + right) / 2;
        if (a[mid] == c) {
            std::cout << "[ RESULT ] found at position " << mid + 1 << "\n";
            found = 1;
        }
        if (a[mid] < c) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (!found) {
        std::cout << "[ RESULT ] not found\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

