/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    bool unique = true;
    for (int i = 0; i < n && unique; i++) {
        for (int j = i + 1; j < n; j++) {
            if (static_cast<double>(a[i]) / b[i] ==
                static_cast<double>(a[j]) / b[j]) {
                unique = false;
                break;
            }
        }
    }

    if (unique) {
        std::cout << "It is unique\n";
    } else {
        std::cout << "It is not unique\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
