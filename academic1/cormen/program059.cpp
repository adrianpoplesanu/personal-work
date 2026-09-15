/*
   exercise: 059
   page: 366
   description: bottom-up cut rod - tabulation
   command: echo 10 1 5 8 9 10 17 17 20 24 30 | ./program059
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

int bottom_up_cut_rod(int a[50], int n) {
    int r[50];
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            q = std::max(q, a[i] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    std::cout << "[ RESULT ] " << bottom_up_cut_rod(a, 4) << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

