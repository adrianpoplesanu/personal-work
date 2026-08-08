/*
   exercise: 021
   page: 143
   description: random search
   command: echo 9 8 3 7 2 6 1 9 5 4 5 | ./program021
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct result {
    bool found;
    int index;

    result(bool f, int i): found(f), index(i) {}
};

typedef result Result;

void read_array(int a[50], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

Result random_search(int a[50], int n, int val) {
    Result result(false, -1);
    int p[50] = {0}, total = 0;
    while (total != n) {
        int i = rand() % n;
        if (a[i] == val) {
            result.found = true;
            result.index = i;
            return result;
        }
        if (p[i] == 0) {
            p[i] = 1;
            total++;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, val;

    read_array(a, n);
    std::cin >> val;

    srand(time(nullptr));
    Result result = random_search(a, n, val);
    if (result.found) {
        std::cout << "[ RESULT ] " << result.index << "\n";
    } else {
        std::cout << "[ RESULT ] not found\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

