/*
   exercise: 069
   page: 415
   description: activity selection dynamic programming
   command: echo 11 1 4 3 5 0 6 5 7 3 9 5 9 6 10 8 11 8 12 2 14 12 16 | ./program069
*/

#include <iostream>
#include <limits>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_activities(int s[50], int f[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i] >> f[i];
    }
}

// section 16.1 clrs
// activities a1..an are sorted by monotonically increasing finish time.
// a0 and a_{n+1} are fictitious, with f0 = 0 and s_{n+1} = infinity.
// c[i][j] is the maximum number of mutually compatible activities in Sij.
// act[i][j] is an activity ak in an optimal solution for Sij, or 0 if Sij is empty.
void activity_selection(int s[50], int f[50], int n, int c[50][50], int act[50][50]) {
    f[0] = 0;
    s[n + 1] = std::numeric_limits<int>::max();

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            c[i][j] = 0;
            act[i][j] = 0;
        }
    }

    for (int l = 2; l <= n + 1; l++) {
        for (int i = 0; i <= n + 1 - l; i++) {
            int j = i + l;
            for (int k = i + 1; k < j; k++) {
                if (f[i] <= s[k] && f[k] <= s[j] && c[i][k] + c[k][j] + 1 > c[i][j]) {
                    c[i][j] = c[i][k] + c[k][j] + 1;
                    act[i][j] = k;
                }
            }
        }
    }
}

void print_activities(int act[50][50], int i, int j) {
    int k = act[i][j];
    if (k != 0) {
        print_activities(act, i, k);
        std::cout << k << "\n";
        print_activities(act, k, j);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int s[50], f[50], n;
    read_activities(s, f, n);

    int c[50][50], act[50][50];
    activity_selection(s, f, n, c, act);

    std::cout << c[0][n + 1] << "\n";
    print_activities(act, 0, n + 1);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

