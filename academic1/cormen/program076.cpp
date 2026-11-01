/*
   exercise: 076
   page: 446
   description: coin changing - greedy algorithm
   command: echo 4 1 5 10 25 42 | ./program076
*/

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

void sort_descending(int d[50], int k) {
    for (int i = 1; i <= k; i++) {
        for (int j = i + 1; j <= k; j++) {
            if (d[i] < d[j]) {
                std::swap(d[i], d[j]);
            }
        }
    }
}

// CLRS 16-1(a): give the largest denomination that does not exceed the amount still owed.
void greedy_change(int d[50], int k, int n, int count[50], int &total) {
    total = 0;
    for (int i = 1; i <= k; i++) {
        count[i] = n / d[i];
        n = n % d[i];
        total += count[i];
    }
}

void print_change(int d[50], int count[50], int k, int total) {
    std::cout << total << "\n";
    if (total == 0) {
        return;
    }
    bool first = true;
    for (int i = 1; i <= k; i++) {
        for (int c = 0; c < count[i]; c++) {
            if (!first) {
                std::cout << " ";
            }
            first = false;
            std::cout << d[i];
        }
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int d[50], count[50], k, n, total;
    read(d, k, n);
    sort_descending(d, k);
    greedy_change(d, k, n, count, total);
    print_change(d, count, k, total);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
