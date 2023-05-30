#include <iostream>

int pivot(int a[100], int p, int q) {
    int val = a[q];
    int k = p;
    for (int i = p; i <= q; i++) {
        if (a[i] < val) {
            int aux = a[k];
            a[k] = a[i];
            a[i] = aux;
            k++;
        }
    }
    int aux = a[k];
    a[k] = a[q];
    a[q] = a[k];
    return k;
}

void quicksort(int a[100], int p, int q) {
    if (p < q) {
        int mid = pivot(a, p, q);
        quicksort(a, p, mid - 1);
        quicksort(a, mid + 1, q);
    }
}

int main(int argc, char *argv[]) {
    int a[100] = {4, 1, 9, 6, 3, 8, 5, 0, 2, 7};
    quicksort(a, 0, 9);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}