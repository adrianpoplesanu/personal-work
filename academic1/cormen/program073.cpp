/*
   exercise: 073
   page: 427
   description: floating point knapsack problem - greedy algorithm
   command: echo 3 10.0 60.0 20.0 100.0 30.0 120.0 50.0 | ./program073
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read(double v[50], double w[50], double ratio[50], int &n, int &W) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i] >> v[i];
        ratio[i] = v[i] / w[i];
    }
    std::cin >> W;
}

void sort_by_ration(double v[50], double w[50], double ratio[50], int n) {
    // bubble sort
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (ratio[i] < ratio[j]) {
                std::swap(ratio[i], ratio[j]);
                std::swap(v[i], v[j]);
                std::swap(w[i], w[j]);
            }
        }
    }
}

double greedy_knapsack(double v[50], double w[50], double ratio[50], int n, int W) {
    double max_value = 0;
    for (int i = 1; i <= n; i++) {
        if (W >= w[i]) {
            max_value += v[i];
            W -= w[i];
        } else {
            max_value += ratio[i] * W;
            break;
        }
    }
    return max_value;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    double v[50], w[50], ratio[50];
    int n, W;
    read(v, w, ratio, n, W);

    sort_by_ration(v, w, ratio, n);

    double max_value = greedy_knapsack(v, w, ratio, n, W);
    std::cout << max_value << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

