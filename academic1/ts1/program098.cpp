/*
   exercise: 098
   description: merge two sorted arrays of ratios
   command: echo 3 1 1 3 4 2 4 3 1 2 2 3 4 4 | ./program098
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void mergeRatios(const int a[], const int b[], int n,
                 const int c[], const int d[], int m,
                 int resultNumerator[], int resultDenominator[]) {
    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {
        if (static_cast<double>(a[i]) / b[i] <=
            static_cast<double>(c[j]) / d[j]) {
            resultNumerator[k] = a[i];
            resultDenominator[k] = b[i];
            i++;
        } else {
            resultNumerator[k] = c[j];
            resultDenominator[k] = d[j];
            j++;
        }
        k++;
    }

    while (i < n) {
        resultNumerator[k] = a[i];
        resultDenominator[k] = b[i];
        i++;
        k++;
    }

    while (j < m) {
        resultNumerator[k] = c[j];
        resultDenominator[k] = d[j];
        j++;
        k++;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], c[50], d[50], resultNumerator[100], resultDenominator[100];
    int n, m;

    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) std::cin >> b[i];

    std::cin >> m;
    for (int i = 0; i < m; i++) std::cin >> c[i];
    for (int i = 0; i < m; i++) std::cin >> d[i];

    mergeRatios(a, b, n, c, d, m, resultNumerator, resultDenominator);

    std::cout << "Merged ratios: ";
    for (int i = 0; i < n + m; i++) {
        std::cout << resultNumerator[i] << '/' << resultDenominator[i] << ' ';
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
