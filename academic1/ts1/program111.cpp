/*
   exercise: 111
   description: find a non-empty subarray whose sum is divisible by n
   command: echo 5 3 1 4 2 6 | ./program111
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

bool findDivisibleSubarray(const int a[], int n, int& left, int& right) {
    int firstPosition[50];
    for (int i = 0; i < n; i++) {
        firstPosition[i] = -2;
    }

    int remainder = 0;
    firstPosition[0] = -1;

    for (int i = 0; i < n; i++) {
        remainder = (remainder + a[i]) % n;
        if (remainder < 0) remainder += n;

        if (firstPosition[remainder] != -2) {
            left = firstPosition[remainder] + 1;
            right = i;
            return true;
        }
        firstPosition[remainder] = i;
    }
    return false;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, left, right;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    if (findDivisibleSubarray(a, n, left, right)) {
        std::cout << "Subarray: ";
        for (int i = left; i <= right; i++) {
            std::cout << a[i] << ' ';
        }
        std::cout << '\n';
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
