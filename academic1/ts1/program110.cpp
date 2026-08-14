/*
   exercise: 110
   description: evaluate a polynomial from its coefficients
   command: echo 4 2 -3 0 5 2 | ./program110
   F(x) = 2x^3 - 3x^2 + 0x + 5, evaluated for x = 2
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

float evaluatePolynomial(const float a[], int n, float value) {
    float result = a[0];

    for (int i = 1; i < n; i++) {
        result = result * value + a[i];
    }
    return result;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float a[50], value;
    int n;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cin >> value;

    std::cout << "F(" << value << ") = "
              << evaluatePolynomial(a, n, value) << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
