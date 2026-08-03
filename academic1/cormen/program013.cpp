/*
   exercise: 012
   page: 68
   description: the maximum subarray problem, cormen version
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
    int low;
    int high;
    int sum;

    result(int l, int h, int s): low(l), high(h), sum(s) {}
};

typedef result Result;

Result find_max_crossing_subarray(int a[], int low, int mid, int high) {
    int max_left, max_right, sum, i;
    int left_sum = INT_MIN;
    sum = 0;
    for (i = mid; i >= low; i--) {
        sum = sum + a[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for(i = mid + 1; i <= high; i++) {
        sum = sum + a[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    return Result(max_left, max_right, left_sum + right_sum);
}

Result find_maximum_subarray(int a[], int low, int high) {
    if (low == high) {
        return Result (low, high, a[low]);
    } else {
        int mid = (low + high) / 2;
        Result left_result = find_maximum_subarray(a, low, mid);
        Result right_result = find_maximum_subarray(a, mid + 1, high);
        Result cross_result = find_max_crossing_subarray(a, low, mid, high);
        if (left_result.sum > right_result.sum && left_result.sum > cross_result.sum) {
            return Result (left_result.low, left_result.high, left_result.sum);
        } else if (right_result.sum > left_result.sum && right_result.sum > cross_result.sum) {
            return Result (right_result.low, right_result.high, right_result.sum);
        } else {
            return Result (cross_result.low, cross_result.high, cross_result.sum);
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
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

