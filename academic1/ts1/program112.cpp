/*
   exercise: 112
   description: choose signs so that 1 +/- 2 +/- ... +/- n = 0
   command: echo 7 | ./program112
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

bool chooseSigns(int n, char signs[]) {
    long long total = static_cast<long long>(n) * (n + 1) / 2;
    if (total % 2 != 0) {
        return false;
    }

    // The positive terms must add up to half of the total.
    long long remaining = total / 2 - 1; // 1 is always positive.
    signs[1] = '+';

    for (int i = 2; i <= n; i++) {
        signs[i] = '-';
    }
    for (int i = n; i >= 2; i--) {
        if (i <= remaining) {
            signs[i] = '+';
            remaining -= i;
        }
    }

    return remaining == 0;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    char signs[51];
    std::cin >> n;

    if (chooseSigns(n, signs)) {
        std::cout << "1 ";
        for (int i = 2; i <= n; i++) {
            std::cout << signs[i] << ' ' << i << ' ';
        }
        std::cout << "= 0\n";
    } else {
        std::cout << "No sign choice exists.\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
