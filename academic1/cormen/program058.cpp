/*
   exercise: 58
   page: 366
   description: memoized cut rod - memoization
   command: echo 10 1 5 8 9 10 17 17 20 24 30 | ./program058
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

int memoized_cut_rod_aux(int a[50], int n, int r[50]) {
    if (r[n] >= 0) {
        return r[n];
    }
    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = -1;
        for (int i = 1; i <= n; i++) {
            q = std::max(q, a[i] + memoized_cut_rod_aux(a, n - i, r));
        }
    }
    r[n] = q;
    return q;
}

int memoized_cut_rod(int a[50], int n) {
    int r[50];
    for (int i = 0; i <= n; i++) {
        r[i] = -1;
    }
    return memoized_cut_rod_aux(a, n, r);
}


int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    std::cout << memoized_cut_rod(a, 4) << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

