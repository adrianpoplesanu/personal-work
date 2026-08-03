/*
   exercise: 014
   page: 74
   description: the maximum subarray problem, brute force
   command: echo 16 13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7 | ./program014
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[], int &n) {
    int i;
    std::cin >> n;
    for(i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

struct result {
    int low;
    int high;
    int sum;

    result(int l, int h, int s): low(l), high(h), sum(s) {}
};

typedef result Result;

Result find_maximum_subarray(int a[], int n) {
    int i, j, low, high;
    int max = a[0];
    int sum = 0;
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = i; j < n; j++) {
            sum = sum + a[j];
            if (sum > max) {
                max = sum;
                low = i;
                high = j;
            }
        }
    }
    return Result (low, high, max);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    find_maximum_subarray(a, n);
    Result result = find_maximum_subarray(a, n);
    std::cout << "[ RESULT ] " << result.low << " " << result.high << " " << result.sum << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

