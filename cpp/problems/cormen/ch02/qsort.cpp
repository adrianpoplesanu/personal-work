#include <iostream>

int partition(int a[], int low, int high) {
    int pivot = a[high];
    int k = low;
    for (int i = low; i <= high; i++) {
        if (a[i] < pivot) {
            int aux = a[i];
            a[i] = a[k];
            a[k] = aux;
            k++;
        }
    }
    int aux = a[high];
    a[high] = a[k];
    a[k] = aux;
    return k;
}

void qsort(int a[], int low, int high) {
    if (low < high) {
        int mid = partition(a, low, high);
        qsort(a, low, mid - 1);
        qsort(a, mid + 1, high);
    }
}

int main(int argc, char* argv[]) {
    int a[] = {7, 3, 6, 4, 8, 2, 9, 1, 15};
    qsort(a, 0, 8);
    for (int i = 0; i < 9; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}