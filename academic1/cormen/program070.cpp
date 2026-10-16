/*
   exercise: 069
   page: 415
   description: greedy activity selection
   command: echo 11 1 4 3 5 0 6 5 7 3 9 5 9 6 10 8 11 8 12 2 14 12 16 | ./program070
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_activities(int s[50], int f[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i] >> f[i];
    }
}

void recursive_activity_selector(int s[50], int f[50], int k, int n, int a[50]) {
    int m = k + 1;
    while (m <= n && s[m] < f[k]) {
        m++;
    }
    if (m <= n) {
        a[m] = 1;
        recursive_activity_selector(s, f, m, n, a);
    } else {
        return;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int s[50], f[50], n;
    read_activities(s, f, n);
    int a[50] = {0};
    f[0] = 0;
    recursive_activity_selector(s, f, 0, n, a);

    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            std::cout << "Activity " << i << " selected" << std::endl;
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

