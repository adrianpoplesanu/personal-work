/*
   exercise: 061
   page: 204
   description: interchange sorting
   command: echo 8 1 9 2 8 3 4 7 5 1 | ./program061
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, tmp;
    std::cin >> n;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    bool sorted = 0;
    while(!sorted) {
        sorted = 1;
        for (i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                sorted = 0;
            }
        }
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

