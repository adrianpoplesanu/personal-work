/*
   exercise: 033
   page: 198
   description: radix sort, using couting sort as stable sorting mechanism
   command: echo 7 329 457 657 839 436 720 355 | ./program033
*/

#include <iostream>
#include <chrono>
#include <vector>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void find_max_digits(int a[], int n, int &d) {
    d = 0;
    for (int i = 1; i <= n; i++) {
        int value = a[i];
        int digits = 0;
        do {
            digits++;
            value /= 10;
        } while (value > 0);

        if (digits > d) {
            d = digits;
        }
    }
}

void radix_sort(int a[], int n, int d) {
    std::vector<int> b(n + 1);
    int divisor = 1;
    for (int i = 1; i <= d; i++) {
        int c[10] = {0};

        for (int j = 1; j <= n; j++) {
            int digit = (a[j] / divisor) % 10;
            c[digit]++;
        }
        for (int digit = 1; digit < 10; digit++) {
            c[digit] += c[digit - 1];
        }
        // Traverse backward so values with equal digits keep their order.
        for (int j = n; j >= 1; j--) {
            int digit = (a[j] / divisor) % 10;
            b[c[digit]] = a[j];
            c[digit]--;
        }
        for (int j = 1; j <= n; j++) {
            a[j] = b[j];
        }
        if (i < d) {
            divisor *= 10;
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, d = 0;
    read_array(a, n);
    print_array(a, n);

    find_max_digits(a, n, d);

    radix_sort(a, n, d);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
