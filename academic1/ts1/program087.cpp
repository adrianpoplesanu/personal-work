/*
   exercise: 087
   page: 237
   description: unique letter
   command: echo parcare | ./program087
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void check_uniqueness(char a[50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                std::cout << "[ RESULT ] letters not unique\n";
                return;
            }
        }
    }
    std::cout << "[ RESULT ] letters unique\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    char a[50], n;
    std::cin >> a;
    n = strlen(a);
    check_uniqueness(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

