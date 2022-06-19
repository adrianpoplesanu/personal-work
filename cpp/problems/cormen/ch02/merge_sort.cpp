#include <iostream>

void merge(int a[], int low, int mid, int high) {
    int L[mid - low + 1];
    int R[high - mid + 1];
    int n1 = 0;
    int n2 = 0;
    for (int i = low; i <= mid; i++) {
        L[n1++] = a[i];
    }
    for (int i = mid + 1; i <= high; i++) {
        R[n2++] = a[i];
    }
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void merge_sort(int a[], int low, int high) {
    if (low < high) {
        int mid = (high + low) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main(int argc, char* argv[]) {
    int a[] = {3, 6, 8, 2, 5, 9, 1, 4, 7};
    merge_sort(a, 0, 8);
    for (int i = 0; i < 9; i++) {
        std::cout << a[i] << " ";
    }
    return 0;
}
