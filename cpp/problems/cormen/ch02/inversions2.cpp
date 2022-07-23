// inversions by parsing with a merge-sort like algo
#include <iostream>

int merge(int a[100], int low, int mid, int high) {
    int inv = 0;
    int L[100], R[100];
    for (int i = low; i <= mid; i++) L[i] = a[i];
    for (int i = mid + 1; i <= high; i++) R[i] = a[i];
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (L[i] < R[j]) {
	    a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
            inv = inv + (mid - i + 1);
        }
    }
    while (i <= mid) { a[k++] = L[i++]; }
    while (j <= high) { a[k++] = R[j++]; }
    return inv;
}

int m_sort(int a[100], int low, int high) {
    int inv = 0;
    if (low < high) {
        int mid = (low + high) / 2;
        inv += m_sort(a, low, mid);
        inv += m_sort(a, mid + 1, high);
        inv += merge(a, low, mid, high);
    }
    return inv;
}

int main(int argc, char *argv[]) {
    int a[] = { 2, 3, 7, 8, 6, 1, 0 };
    int n = 7;
    int inversions = m_sort(a, 0, 6);
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    std::cout << inversions << "\n";
    return 0;
}
