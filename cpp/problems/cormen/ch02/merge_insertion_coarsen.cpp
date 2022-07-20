#include <iostream>

void insertion(int a[100], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int current = a[i];
        int j = i - 1;
        while (j >= low && a[j] > current) {
            int aux = a[j + 1];
            a[j + 1] = a[j];
            a[j] = aux;
            j--;
        }
        //j++;
        //a[j] = current;
    }
}

void merge(int a[100], int low, int mid, int high) {
    int b[100];
    for (int i = low; i <= high; i++) b[i] = a[i];
    int i = low, j = low, k = mid + 1;
    while (j <= mid && k <= high) {
        if (b[j] < b[k]) {
            a[i++] = b[j++];
        } else {
            a[i++] = b[k++];
        }
    }
    while (j <= mid) {
        a[i++] = b[j++];
    }
    while (k <= high) {
        a[i++] = b[k++];
    }
}

void merge_sort(int a[100], int low, int high) {
    if (high - low <= 2) {
	insertion(a, low, high);
    } else
    if (low < high) {
        int mid = (high + low) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main(int argc, char* argv[]) {
    int a[100] = {6, 2, 7, 3, 8, 1, 9, 5, 4};
    merge_sort(a, 0, 8);
    for (int i = 0; i < 9; i++) std::cout << a[i] << " ";
    std::cout << "\n";
    return 0;
}
