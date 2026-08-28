/*
   exercise: 201
   page: 150
   description: dynamic programming - memoization
   command: echo 4 2 3 5 6 3 4 5 6 1 4 | ./program201
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
    std::cout << "[ RESULT ][ MEMOIZATION ] ";
    for (int i = n - 1; i >= 0; i--) {
        std::cout << a[i][pos] << " ";
        pos = drum[i][pos];
    }
    std::cout << "\n";
}

int memoization_recursive(const int a[50][50], int dp[50][50], int drum[50][50], bool calculated[50][50], int i, int j) {
    if (calculated[i][j]) {
        return dp[i][j];
    }

    if (i == 0) {
        dp[i][j] = a[i][j];
        drum[i][j] = -1;
    } else if (j == 0) {
        dp[i][j] = a[i][j] + memoization_recursive(a, dp, drum, calculated, i - 1, j);
        drum[i][j] = j;
    } else if (j == i) {
        dp[i][j] = a[i][j] + memoization_recursive(a, dp, drum, calculated, i - 1, j - 1);
        drum[i][j] = j - 1;
    } else {
        int left = memoization_recursive(a, dp, drum, calculated, i - 1, j);
        int right = memoization_recursive(a, dp, drum, calculated, i - 1, j - 1);
        if (left > right) {
            dp[i][j] = a[i][j] + left;
            drum[i][j] = j;
        } else {
            dp[i][j] = a[i][j] + right;
            drum[i][j] = j - 1;
        }
    }

    calculated[i][j] = true;
    return dp[i][j];
}

void memoization(const int a[50][50], int n) {
    int dp[50][50], drum[50][50];
    bool calculated[50][50] = {};
    for (int j = 0; j < n; j++) {
        memoization_recursive(a, dp, drum, calculated, n - 1, j);
    }
    print_triangle(dp, n);
    print_drum(a, n, dp, drum);
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

    std::cout << "MEMOIZATION\n";

    memoization(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
