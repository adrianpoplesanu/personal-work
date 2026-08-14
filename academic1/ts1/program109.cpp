/*
   exercise: 109
   description: calculate sums of products of all element combinations
   command: echo 4 1 2 3 4 | ./program109
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void calculateSums(const int a[], int n, long long sums[]) {
    for (int i = 0; i <= n; i++) {
        sums[i] = 0;
    }
    sums[0] = 1;

    for (int i = 0; i < n; i++) {
        // Go backwards so each element is used only once in a product.
        for (int k = i + 1; k >= 1; k--) {
            sums[k] += sums[k - 1] * a[i];
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    long long sums[51];

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    calculateSums(a, n, sums);

    for (int i = 1; i <= n; i++) {
        std::cout << "s" << i << " = " << sums[i] << '\n';
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
