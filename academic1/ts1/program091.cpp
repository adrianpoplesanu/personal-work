/*
   exercise: 091
   page: 238
   description: subset sum problem with binary array, backtracking and dynamic programming tabulation
   command: echo 5 3 7 4 2 9 13 | ./program091
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void logic_array(int a[50], int n, int S) {
    int b[50];
    int steps = 1;
    for (int i = 0; i < n; i++) {
        b[i] = 0;
        steps *= 2;
    }

    int step = 1;
    while (step < steps) {
        b[0]++;
        for (int i = 0; i < n; i++) {
            if (b[i] > 1) {
                b[i + 1]++;
                b[i] -= 2;
            }
        }

        int currentSum = 0;
        for (int i = 0; i < n; i++) {
            if (b[i]) currentSum += a[i];
        }
        if (currentSum == S) {
            for (int i = 0; i < n; i++) {
                if (b[i]) std::cout << a[i] << " ";
            }
            std::cout << "\n";
        }
        step++;
    }
}

void backtracking(int a[50], int n, int S, int currentSum, int k, int trav[50]) {
    if (k == n) {
        if (S == currentSum) {
            for (int i = 0; i < n; i++) {
                if (trav[i]) {
                    std::cout << a[i] << " ";
                }
            }
            std::cout << "\n";
        }
        return;
    }
    if (S == currentSum) {
        for (int i = 0; i < n; i++) {
            if (trav[i]) {
                std::cout << a[i] << " ";
            }
        }
        std::cout << "\n";
    } else {
        trav[k] = 1;
        backtracking(a, n, S, currentSum + a[k], k + 1, trav);

        trav[k] = 0;
        backtracking(a, n, S, currentSum, k + 1, trav);
    }
}

void traceback(bool dp[51][1001], int a[], int i, int s,
               int solution[50], int k)
{
    if (s == 0) {
        std::cout << "{ ";

        for (int j = 0; j < k; j++)
            std::cout << solution[j] << " ";

        std::cout << "}\n";
        return;
    }

    if (i == 0)
        return;

    // Case 1: don't use a[i - 1]
    if (dp[i - 1][s]) {
        traceback(dp, a, i - 1, s, solution, k);
    }

    // Case 2: use a[i - 1]
    if (s >= a[i - 1] && dp[i - 1][s - a[i - 1]]) {
        solution[k] = a[i - 1];

        traceback(dp, a, i - 1,
                  s - a[i - 1],
                  solution, k + 1);
    }
}

void dynamic_programming(int a[50], int n, int S) {
    //bool dp[n + 1][S + 1];
    bool dp[51][1001];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else if (j == 0) {
                dp[i][j] = true;
            } else {
                dp[i][j] = false;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            if (dp[i - 1][j]) {
                dp[i][j] = true;
                if (j + a[i - 1] <= S) {
                    dp[i][j + a[i - 1]] = true;
                }
            }
        }
    }
    /*for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }*/
    int solution[50];
    traceback(dp, a, n, S, solution, 0);
}

void dynamic_programming2(int a[50], int n, int S) {
    bool dp[n + 1][S + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            dp[i][j] = false;
        }
    }

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
        for (int j = 0; j <= S; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = true;
            } else if (i == 0) {
                dp[i][j] = false;
            } else {
                if (dp[i - 1][j]) {
                    dp[i][j] = true;
                    if (j + a[i - 1] <= S) {
                        dp[i][j + a[i - 1]] = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << "\n";
    }
}



int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, S, trav[50];
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        trav[i] = 0;
        std::cin >> a[i];
    }
    std::cin >> S;

    std::cout << "binary logic\n";
    logic_array(a, n, S);
    std::cout << "backtracking\n";
    backtracking(a, n, S, 0, 0, trav);
    std::cout << "dynamic programming\n";
    dynamic_programming(a, n, S);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

