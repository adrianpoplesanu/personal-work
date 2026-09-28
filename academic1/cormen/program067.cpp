/*
   exercise: 067    
   page: 391
   description: longest common subsequence
   command: ./program067
*/

#include <iostream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void print_solution(std::string word1, std::string word2, int dp[50][50], int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }

    if (word1[i - 1] == word2[j - 1]) {
        print_solution(word1, word2, dp, i - 1, j - 1);
        std::cout << word1[i - 1];
    } else {
        if (dp[i - 1][j] >= dp[i][j - 1]) {
            print_solution(word1, word2, dp, i - 1, j);
        } else {
            print_solution(word1, word2, dp, i, j - 1);
        }    
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::string word1 = "ala bala portocala";
    std::string word2 = "xxxportocalayyy";

    int dp[50][50] = {0};

    for (int i = 1; i <= word1.length(); i++) {
        for (int j = 1; j <= word2.length(); j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    for (int i = 0; i <= word1.length(); i++) {
        for (int j = 0; j <= word2.length(); j++) {
            std::cout << std::setw(2) << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    print_solution(word1, word2, dp, word1.length(), word2.length());
    std::cout << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

