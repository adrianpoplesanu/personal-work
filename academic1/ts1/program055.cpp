/*
   exercise: 055
   page: 196
   description: contains in an array
   command: echo 8 1 9 2 8 3 4 7 5 1 | ./program055
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, c, i;
    std::cin >> n >> c;
    for (i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    bool found = 0;
    for (i = 0; i < n && !found; i++) {
        if (a[i] == c) {
            found = 1;
        }
    }
    if (found) {
        std::cout << "[ RESULT ] found\n";
    } else {
        std::cout << "[ RESULT ] NOT found\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

