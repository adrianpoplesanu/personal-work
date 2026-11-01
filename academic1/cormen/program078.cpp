/*
   exercise: 078
   page: 00
   description: incrementing a binary counter
   command: ./program078
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void increment(int a[], int n) {
    int i = 0;
    while (i < n && a[i] == 1) {
        a[i] = 0;
        i++;
    }
    if (i < n) {
        a[i] = 1;
    }
}

void initBinary(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

void printBinary(int a[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        std::cout << a[i];
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n = 50;

    initBinary(a, n);
    printBinary(a, n);

    for (int i = 0; i < 100; i++) {
        increment(a, n);
        printBinary(a, n);
    }
    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

