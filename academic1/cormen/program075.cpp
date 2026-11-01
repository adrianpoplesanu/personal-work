/*
   exercise: 075
   page: 446
   description: coin changing - dynamic programming, always have a penny in the denominations
   command: echo 3 1 3 4 6 | ./program075
*/

#include <climits>
#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read(int d[50], int &k, int &n) {
    std::cin >> k;
    for (int i = 1; i <= k; i++) {
        std::cin >> d[i];
    }
    std::cin >> n;
}

// CLRS 16-1(d) MAKE-CHANGE: c[p] is the fewest coins that sum to p.
// s[p] is one coin used in a solution for p. A penny is assumed, so every p is reachable.
void make_change(int d[50], int k, int n, int c[], int s[]) {
    c[0] = 0;
    for (int p = 1; p <= n; p++) {
        c[p] = INT_MAX;
        for (int i = 1; i <= k; i++) {
            if (d[i] <= p && c[p - d[i]] + 1 < c[p]) {
                c[p] = c[p - d[i]] + 1;
                s[p] = d[i];
            }
        }
    }
}

void print_change(int c[], int s[], int n) {
    std::cout << c[n] << "\n";
    if (n == 0) {
        return;
    }
    while (n > 0) {
        std::cout << s[n];
        n = n - s[n];
        if (n > 0) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int d[50], k, n;
    read(d, k, n);

    int c[n + 1], s[n + 1];
    make_change(d, k, n, c, s);
    print_change(c, s, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
