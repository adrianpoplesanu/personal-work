/*
   exercise: 090
   page: 238
   description: biggest sume with array elements
   command: echo 5 -1 -2 3 4 -8 | ./program090
   command: echo 5 -7 -2 -3 -1 -8 | ./program090
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

    int sum = a[0];
    for (int i = 1; i < n; i++) {
        if (sum + a[i] > sum) {
            sum += a[i];
        }
        if (a[i] > sum) {
            sum = a[i];
        }
    }
    std::cout << "[ RESULT ] " << sum << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

