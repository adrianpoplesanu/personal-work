/*
   exercise: 001
   page: 18
   description: insertion sort
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program002
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, j, key;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (j = 1; j < n; j++) {
        key = a[j];
        i = j - 1;
        while(i >= 0 && a[i] < key) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }

    std::cout << "[ RESULT ] ";
    for(i = 0; i < n; i++) {
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

