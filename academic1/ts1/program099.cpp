/*
   exercise: 099
   description: place even numbers before odd numbers
   command: echo 7 3 8 1 4 7 2 6 | ./program099
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void placeEvensBeforeOdds(int a[], int n) {
    int result[50];
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            result[k++] = a[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) {
            result[k++] = a[i];
        }
    }
    for (int i = 0; i < n; i++) {
        a[i] = result[i];
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    placeEvensBeforeOdds(a, n);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
