/*
   exercise: 034
   page: 201
   description: bucket sort
   command: echo 10 0.78 0.17 0.39 0.26 0.72 0.94 0.21 0.12 0.23 0.68 | ./program034
*/

#include <iostream>
#include <chrono>
#include <vector>

#define PRINT_EXECUTION_DURATION 0

void read_array(float a[], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

void print_array(float a[], int n) {
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void insertion_sort(std::vector<float> &bucket) {
    for (int j = 1; j < static_cast<int>(bucket.size()); j++) {
        float key = bucket[j];
        int i = j - 1;

        while (i >= 0 && bucket[i] > key) {
            bucket[i + 1] = bucket[i];
            i--;
        }
        bucket[i + 1] = key;
    }
}

void bucket_sort(float a[], int n) {
    std::vector<std::vector<float>> buckets(n);

    for (int i = 1; i <= n; i++) {
        int bucket_index = static_cast<int>(n * a[i]);
        // Values are expected in [0, 1]; place 1.0 in the final bucket.
        if (bucket_index == n) {
            bucket_index = n - 1;
        }
        buckets[bucket_index].push_back(a[i]);
    }

    for (int i = 0; i < n; i++) {
        insertion_sort(buckets[i]);
    }

    int position = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < static_cast<int>(buckets[i].size()); j++) {
            a[position] = buckets[i][j];
            position++;
        }
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float a[50];
    int n;
    read_array(a, n);
    print_array(a, n);

    bucket_sort(a, n);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
