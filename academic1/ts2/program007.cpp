/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void test_pointer(int *a, int &n) {
    n = 3;
    a[0] = 1;
    a[1] = 5;
    a[2] = 9;
}

void test_pointer2(int (*a)[50], int &n, int &m) {
    n = 3;
    m = 4;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = n * rand() % 10 + m * rand() % 10;
        }
    }
}

void test_pointer3(int a[][50], int &n, int &m) {
    std::cout << "this is also fine\n";
}

void test_pointer4(int (&a)[50][50], int& n, int& m) {
    std::cout << "this also works\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    test_pointer(a, n);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    int b[50][50], m, o;
    test_pointer2(b, m, o);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < o; j++) {
            std::cout << b[i][j] << " ";
        }
        std::cout << "\n";
    }

    test_pointer3(b, m, o);

    test_pointer4(b, m, o);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

