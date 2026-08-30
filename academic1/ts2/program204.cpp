/*
   exercise: 202
   page: 151
   description: longest increasing subsequence
   command: echo 10 2 3 5 6 3 4 5 6 1 4 | ./program204
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int dp[50], drum[50];
    for (int i = n - 1; i >= 0; i--) {        
        dp[i] = 1;
        drum[i] = -1;
        for (int j = i + 1; j < n; j++) {
            if (a[i] < a[j] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                drum[i] = j;
            }
        }
    }

    int max = dp[0];
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > max) {
            max = dp[i];
            pos = i;
        }
    }
    std::cout << "Longest increasing subsequence: " << max << "\n";
    while (pos != -1) {
        std::cout << a[pos] << " ";
        pos = drum[pos];
    }
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

