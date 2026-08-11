/*
   exercise: 094
   page: 238
   description: simple expression evaluator
   command: echo 4 1 2 3 4 5 6 7 8 9 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], n;
    double s = 0;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    for (int i = 0; i < n; i++) {
        s += static_cast<double>(a[i]) / b[i];
    }

    std::cout << s << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
