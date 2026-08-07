/*
   exercise: 018
   page: 117
   description: generating a pseudo-random number
   command: echo 123 234 | ./program018
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int random_probability(int a, int b) {
    int A[50];
    int n = ceil(log2(b - a + 1));

    while (true) {
        for (int i = 0; i < n; i++) {
            A[i] = rand() % 2;
        }
        int num = 0, pow = 1;
        for (int i = 0; i < n; i++) {
            num += pow * A[i];
            pow *= 2;
        }
        if (num < b - a + 1) {
            std::cout << a + num << "\n";
            return a + num;
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a, b;
    std::cin >> a >> b;

    srand(time(nullptr));
    random_probability(a, b);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

