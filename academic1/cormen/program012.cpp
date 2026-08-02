/*
   exercise: 012
   page: 68
   description: the maximum subarray problem
   command: echo 16 13 -3 -25 20 -3 -16 -23 18 20 -7 12 -5 -22 15 -4 7 | ./program013
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
    int low, high, sum;
    result(int l, int h, int s): low(s), high(h), sum(s) {}
};

typedef result Result;

Result find_maximum_subarray(int a[], int n) {
    int dp[n], trav[n]; i, max = INT_MIN, pos = 0;
    for (i = 0; i < n; i++) {
        if (i == 0) {
            dp[i] = a[i];
            trav[i] = i;
        } else if (a[i] > dp[i - 1] + a[i])) {
            trav[i] = i;
            dp[i] = a[i];
        } else {
            trav[i] = trav[i - 1];
            dp[i] = dp[i - 1] + a[i];
        }
        if (max < dp[i]) {
            max = dp[i];
            pos = i;
        }
    }
    return Result(trav[pos], pos, max);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i;
    read_array(a, n);
    Result r = find_maximum_subarray(a, 0, n - 1);
    std::cout << r.low << " " << r.high << " " << r.sum << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

