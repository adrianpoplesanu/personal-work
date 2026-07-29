/*
   exercise: 060
   page: 203
   description: min sorting
   command: echo 8 1 9 2 8 3 4 7 5 1 | ./program060
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, j, min, pos, tmp;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (i = 0; i < n; i++) {
        min = a[i];
        pos = i;
        for (j = i; j < n; j++) {
            if (a[j] < min) {
                min = a[j];
                pos = j;
            }
        }

        tmp = a[i];
        a[i] = a[pos];
        a[pos] = tmp;
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

