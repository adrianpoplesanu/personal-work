/*
   exercise: 102
   description: find the greatest common divisor of all array elements
   command: echo 4 12 18 24 30 | ./program102
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int greatestCommonDivisor(int x, int y) {
    if (x < 0) x = -x;
    if (y < 0) y = -y;

    while (y != 0) {
        int remainder = x % y;
        x = y;
        y = remainder;
    }
    return x;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int gcd = a[0];
    for (int i = 1; i < n; i++) {
        gcd = greatestCommonDivisor(gcd, a[i]);
    }

    std::cout << "Greatest common divisor: " << gcd << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
