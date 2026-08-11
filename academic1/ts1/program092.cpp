/*
   exercise: 091
   page: 238
   description: subset sum problem with memoization
   command: echo 5 3 7 4 2 9 13 | ./program092
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

bool solve(bool dp[51][1001], bool visited[51][1001],
           int a[50], int i, int s)
{
    if (visited[i][s])
        return dp[i][s];

    visited[i][s] = true;

    if (s == 0)
    {
        dp[i][s] = true;
        return true;
    }

    if (i == 0)
    {
        dp[i][s] = false;
        return false;
    }

    bool without = solve(dp, visited, a, i - 1, s);

    bool with = false;

    if (s >= a[i - 1])
        with = solve(dp, visited, a, i - 1, s - a[i - 1]);

    dp[i][s] = without || with;

    return dp[i][s];
}

void print_solutions(bool dp[51][1001], int a[50], int i, int s,
                     int solution[51], int k)
{
    if (s == 0)
    {
        std::cout << "{ ";

        for (int j = k - 1; j >= 0; j--)
            std::cout << solution[j] << " ";

        std::cout << "}\n";
        return;
    }

    if (i == 0)
        return;

    // Don't take a[i - 1]
    if (dp[i - 1][s])
    {
        print_solutions(dp, a,
                        i - 1, s,
                        solution, k);
    }

    // Take a[i - 1]
    if (s >= a[i - 1] &&
        dp[i - 1][s - a[i - 1]])
    {
        solution[k] = a[i - 1];

        print_solutions(dp, a,
                        i - 1,
                        s - a[i - 1],
                        solution,
                        k + 1);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, S;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cin >> S;

    bool dp[51][1001], visited[51][1001];
    int solution[51];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= S; j++) {
            visited[i][j] = false;
        }
    }

    bool result = solve(dp, visited, a, n, S);
    if (result) {
        print_solutions(dp, a, n, S, solution, 0);
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

