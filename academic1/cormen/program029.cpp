/*
   exercise: 029
   page: 179
   description: randomize quicksort
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program029
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void swap(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int a[], int p, int r) {
    int x = a[r];
    int k = p - 1;
    for(int i = p; i < r; i++) {
        if (a[i] < x) {
            k++;
            swap(a, k, i);
        }
    }
    swap(a, k + 1, r);
    return k + 1;
}

int randomized_partition(int a[], int p, int r) {
    int i = p + rand() % (r - p + 1);
    swap(a, r, i);
    return partition(a, p, r);
}

void randomized_quicksort(int a[], int p, int r) {
    if (p < r) {
        int q = randomized_partition(a, p, r);
        randomized_quicksort(a, p, q - 1);
        randomized_quicksort(a, q + 1, r);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here
    srand(time(nullptr));

    int a[50], n;
    read_array(a, n);
    print_array(a, n);

    randomized_quicksort(a, 0, n - 1);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

