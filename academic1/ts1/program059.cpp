/*
   exercise: 059
   page: 200
   description: all subsets of an array
   command: echo 4 5 6 7 8 | ./program059
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], n, i, j;

    std::cin >> n;
    for (i = 0; i < n; i++) {
        a[i] = 0;
        std::cin >> b[i];
    }

    int total = 1;
    for(i = 0; i < n; i++) total *= 2;

    std::cout << "[ RESULT ]\n";

    for (i = 0; i < total; i++) {
        a[n - 1]++;
        for (j = n - 1; j > 0; j--) {
            if (a[j] > 1) {
                a[j] -= 2;
                a[j - 1]++;
            }
        }

        for(j = 0; j < n; j++) {
            if (a[j] == 1) std::cout << b[j] << " ";
        }
        std::cout << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

