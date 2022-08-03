#include <iostream>

void find_max_crossing_subarray(int a[100], int low, int mid, int high, int& left_pos, int& right_pos, int& total_sum) {
    int left_sum = -INT_MAX;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += a[i];
        if (sum > left_sum) {
            left_sum = sum;
            left_pos = i;
        }
    }
    int right_sum = -INT_MAX;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += a[i];
        if (sum > right_sum) {
            right_sum = sum;
            right_pos = i;
        }
    }
    total_sum = left_sum + right_sum;
}

void find_maximum_subarray(int a[100], int low, int high, int& left_pos, int& right_pos, int& total_sum) {
    if (low == high) {
        left_pos = low;
        right_pos = high;
        total_sum = a[low];
    } else {
        int mid = (low + high) / 2;
        int left_sum, left_low, left_high;
        int cross_sum, cross_low, cross_high;
        int right_sum, right_low, right_high;
        find_maximum_subarray(a, low, mid, left_low, left_high, left_sum);
        find_maximum_subarray(a, mid + 1, high, right_low, right_high, right_sum);
        find_max_crossing_subarray(a, low, mid, high, cross_low, cross_high, cross_sum);
        if (left_sum >= right_sum && left_sum >= cross_sum) {
            left_pos = left_low;
            right_pos = left_high;
            total_sum = left_sum;
        } else if (right_sum >= left_sum && right_sum >= cross_sum) {
            left_pos = right_low;
            right_pos = right_high;
            total_sum = right_sum;
        } else {
            left_pos = cross_low;
            right_pos = cross_high;
            total_sum = cross_sum;
        }
    }
}

int main(int argc, char* arv[]) {
    int a[100] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    int n = 16;

    int rez_low, rez_high, rez_sum;
    find_maximum_subarray(a, 0, n - 1, rez_low, rez_high, rez_sum);

    std::cout << rez_sum << "\n" << rez_low << "\n" << rez_high << "\n";
    for (int i = rez_low; i <= rez_high; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
