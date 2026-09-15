/*
   exercise: 057
   page: 360
   description: rod cutting - exponential
   command: echo 10 1 5 8 9 10 17 17 20 24 30 | ./program057
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int cut_rod(int a[50], int n) {
   if (n == 0) {
       return 0;
   }
   int q = INT_MIN;
   for (int i = 1; i <= n; i++) {
       q = max(q, a[i] + cut_rod(a, n - i));
   }
   return q;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    std::cout << cut_rod(a, 4) << std::endl;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

