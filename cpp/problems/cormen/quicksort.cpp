#include <iostream>

void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

int partition(int a[100], int low, int high) {
    int pivot = a[high];
    int k = low - 1;
    for(int i = low; i <= high; i++) {
        if (a[i] < pivot) {
            k++;
            swap(a[k], a[i]);
        }
    }
    swap(a[k + 1], a[high]);
    return k + 1;
}

void quicksort(int a[100], int low, int high) {
    if (low < high) {
        int mid = partition(a, low, high);
        quicksort(a, low, mid - 1);
        quicksort(a, mid + 1, high);
    }
}

void print(int a[100], int n) {
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    int a[100] = {9, 5, 2, 8, 6, 1, 3, 7, 4};
    quicksort(a, 0, 8);
    print(a, 9);
    return 0;
}
