/*
   exercise: 060
   page: 369
   description: bottom-up cut rod - tabulation + solution print
   command: echo 10 1 5 8 9 10 17 17 20 24 30 | ./program060
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

int extended_bottom_up_cut_rod(int a[50], int n, int r[50], int s[50]) {
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (q < a[i] + r[j - i]) {
                q = a[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return r[n];
}

void print_cut_rod_solution(int a[50], int n) {
    int r[50], s[50];
    extended_bottom_up_cut_rod(a, n, r, s);
    while(n > 0) {
        std::cout << s[n] << " ";
        n -= s[n];
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    print_cut_rod_solution(a, 4);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

