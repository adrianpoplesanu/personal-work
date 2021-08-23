// un algoritm merge sort, facut asa of the top of my head, sunt curios daca implementarea asta scrisa in 5 minute e chiar O(n * log(n))?
#include <iostream>

void merge(int a[100], int low, int mid, int high) {
    int i = low, j = mid, k = low;
    int b[100];
    while(i < mid && j <= high) {
        if (a[i] < a[j]) b[k++] = a[i++];
        else b[k++] = a[j++];
    }
    while(i < mid) b[k++] = a[i++];
    while(j <= high) b[k++] = a[j++];
    for (i = low; i <= high; i++) a[i] = b[i];
}

void sort(int a[100], int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    sort(a, low, mid);
    sort(a, mid + 1, high);
    merge(a, low, mid + 1, high);
}

int main(int argc, char* argv[]) {
    int a[100] = {5, 8, 2, 1, 7, 4, 6, 9, 8};
    int n = 9;
    sort(a, 0, n - 1);

    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n"; 
    return 0;
}
