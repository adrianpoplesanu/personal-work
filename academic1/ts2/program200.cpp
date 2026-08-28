/*
   exercise: 200
   page: 150
   description: dynamic programming - number 200 is placeholder
   command: echo 4 2 3 5 6 3 4 5 6 1 4 | ./program200
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void print_triangle(const int a[50][50], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_drum(const int a[50][50], int n, const int dp[50][50], const int drum[50][50]) {
    int max, pos;
    max = dp[n - 1][0];
    pos = 0;
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] > max) {
            max = dp[n - 1][i];
            pos = i;
        }
    }
    std::cout << "[ RESULT ][ TABULATION top-down ] ";
    for (int i = n - 1; i >= 0; i--) {
        std::cout << a[i][pos] << " ";
        pos = drum[i][pos];
    }
    std::cout << "\n";
}

void print_drum2(const int a[50][50], int n, const int dp[50][50], const int drum[50][50]) {
    int pos = 0;
    std::cout << "[ RESULT ][ TABULATION bottom-up ] ";
    for (int i = 0; i < n; i++) {
        std::cout << a[i][pos] << " ";
        pos = drum[i][pos];
    }
    std::cout << "\n";
}

void tabulation(const int a[50][50], int n) {
    int dp[50][50], drum[50][50];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == 0) {
                dp[i][j] = a[i][j];
                drum[i][j] = -1;
            } else if (j == 0) {
                dp[i][j] = a[i][j] + dp[i - 1][j];
                drum[i][j] = j;
            } else if (j == i) {
                dp[i][j] = a[i][j] + dp[i - 1][j - 1];
                drum[i][j] = j - 1;
            } else {
                if (a[i][j] + dp[i - 1][j] > a[i][j] + dp[i - 1][j - 1]) {
                    dp[i][j] = a[i][j] + dp[i - 1][j];
                    drum[i][j] = j;
                } else {
                    dp[i][j] = a[i][j] + dp[i - 1][j - 1];
                    drum[i][j] = j - 1;
                }
            }
        }
    }
    print_triangle(dp, n);
    print_drum(a, n, dp, drum);
}

void tabulation2(const int a[50][50], int n) {
    int dp[50][50], drum[50][50];
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (i == n - 1) {
                dp[i][j] = a[i][j];
                drum[i][j] = -1;
            } else {
                if (dp[i + 1][j] > dp[i + 1][j + 1]) {
                    dp[i][j] = a[i][j] + dp[i + 1][j];
                    drum[i][j] = j;
                } else {
                    dp[i][j] = a[i][j] + dp[i + 1][j + 1];
                    drum[i][j] = j + 1;
                }
            }
        }
    }
    print_triangle(dp, n);
    print_drum2(a, n, dp, drum);
 }

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "ORIGINAL TRIANGLE\n";

    print_triangle(a, n);

    std::cout << "TABULATION top-down\n";

    tabulation(a, n);

    std::cout << "TABULATION bottom-up\n";

    tabulation2(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

