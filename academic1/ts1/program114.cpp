/*
   exercise: 114
   description: decompose n into summands with maximum product
   command: echo 10 | ./program114
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int decomposeForMaximumProduct(int n, int factors[]) {
    int count = 0;

    // The decomposition must contain at least two positive summands.
    if (n == 2) {
        factors[count++] = 1;
        factors[count++] = 1;
        return count;
    }
    if (n == 3) {
        factors[count++] = 1;
        factors[count++] = 2;
        return count;
    }
    if (n == 4) {
        factors[count++] = 2;
        factors[count++] = 2;
        return count;
    }

    while (n > 4) {
        factors[count++] = 3;
        n -= 3;
    }
    factors[count++] = n;
    return count;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, factors[50];
    std::cin >> n;

    int factorCount = decomposeForMaximumProduct(n, factors);
    long long maximumProduct = 1;

    std::cout << n << " = ";
    for (int i = 0; i < factorCount; i++) {
        std::cout << factors[i];
        maximumProduct *= factors[i];
        if (i + 1 < factorCount) {
            std::cout << " + ";
        }
    }
    std::cout << '\n';
    std::cout << "Maximum product: " << maximumProduct << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
