#include <iostream>

void merge(int a[100], int p, int q, int r) {
    int L[100], R[100];
    for (int i = p; i <= q; i++) {
        L[i] = a[i];
    }
    for (int i = q + 1; i <= r; i++) {
        R[i] = a[i]; 
    }
    int i = p, k = q + 1, pos = p;
    while (i <= q && k <= r) {
        if (L[i] > R[k]) {
            a[pos++] = L[i++];
        } else {
            a[pos++] = R[k++];
        }
    }
    while(i <= q) a[pos++] = L[i++];
    while(k <= r) a[pos++] = R[k++];
}

void merge_sort(int a[100], int p, int q) {
    if (p < q) {
        int mid = (p + q) / 2;
        merge_sort(a, p, mid);
        merge_sort(a, mid + 1, q);
        merge(a, p, mid, q);
    }
}

int main(int argc, char *argv[]) {
    int a[100] = {4, 1, 9, 6, 3, 8, 5, 0, 2, 7};
    merge_sort(a, 0, 9);
    for (int i = 0; i < 10; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}