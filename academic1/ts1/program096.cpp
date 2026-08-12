/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], c[50], d[50], n, m;

    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) std::cin >> b[i];

    std::cin >> m;
    for (int i = 0; i < m; i++) std::cin >> c[i];
    for (int i = 0; i < m; i++) std::cin >> d[i];

    std::cout << "Intersection: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (static_cast<double>(a[i]) / b[i] ==
                static_cast<double>(c[j]) / d[j]) {
                std::cout << a[i] << '/' << b[i] << ' ';
            }
        }
    }
    std::cout << '\n';

    std::cout << "Reunion: ";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << '/' << b[i] << ' ';
    }
    for (int j = 0; j < m; j++) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (static_cast<double>(a[i]) / b[i] ==
                static_cast<double>(c[j]) / d[j]) {
                found = true;
                break;
            }
        }
        if (!found) std::cout << c[j] << '/' << d[j] << ' ';
    }
    std::cout << '\n';

    std::cout << "Difference A - B: ";
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < m; j++) {
            if (static_cast<double>(a[i]) / b[i] ==
                static_cast<double>(c[j]) / d[j]) {
                found = true;
                break;
            }
        }
        if (!found) std::cout << a[i] << '/' << b[i] << ' ';
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
