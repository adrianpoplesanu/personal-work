// chapter 1
#include <iostream>

void merge(int a[100], int p, int q, int r) {
    int L[100], R[100];
    for (int i = p; i <= q; i++) {
        L[i] = a[i];
    }
    for (int i = q + 1; i <= r; i++) {
        R[i] = a[i];
    }
    int i = p;
    int  j = q + 1;
    for (int k = p; k <= r; k++) {
        if (i <= q && j <= r) {
            if (L[i] < R[j]) {
                a[k] = L[i++];
            } else {
                a[k] = R[j++];
            }
        } else if (i <= q) {
            a[k] = L[i++];
        } else if (j <= r) {
            a[k] = R[j++];
        }
    }
}

void merge_sort(int a[100], int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

int main(int argc, char *argv[]) {
    int a[100] = {6, 1, 8, 2, 9, 3, 5, 4, 7};
    merge_sort(a, 0, 8);
    for (int i = 0; i < 9; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}
