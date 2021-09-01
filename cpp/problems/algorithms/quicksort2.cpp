#include <iostream>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j <= high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void sort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        sort(a, low, pi - 1);
        sort(a, pi + 1, high);
    }
}

void print(int a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    int a[] = {8, 4, 2, 6, 5, 1, 3, 7, 9};
    int n = 9;
    sort(a, 0, n - 1);
    print(a, n);
    return 0;
}
