// ts2 p47 e16
#include <iostream>
using namespace std;

void sort_min(int a[100], int n) {
    for (int i = 0; i < n; i++) {
        int min = a[i], poz = i;
        for (int j = i; j < n; j++) {
            if (min > a[j]) {
                min = a[j];
                poz = j;
            }
        }
        int aux = a[i];
        a[i] = a[poz];
        a[poz] = aux;
    }
}

void sort_bubble(int a[100], int n) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                sorted = false;
                int aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
            }
        }
    }
}

void sort_normal(int a[100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (a[i] > a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
        }
    }
}

void merge(int a[100], int l, int mid, int r);
void merge_sort(int a[100], int l, int r) {
    if (l + 1 < r) { // ATENTION! if l + 1 == r then we only have one element, which is already sorted
        int mid = (l + r) / 2;
        merge_sort(a, l, mid);
        merge_sort(a, mid, r);
        merge(a, l, mid, r);
    }
}

void merge(int a[100], int l, int mid, int r) {
    int i1 = l, i2 = mid, c[100], poz = l;
    while(i1 < mid && i2 < r) {
        if (a[i1] < a[i2]) {
            c[poz++] = a[i1++];
        } else {
            c[poz++] = a[i2++];
        }
    }
    while(i1 < mid) c[poz++] = a[i1++];
    while(i2 < r) c[poz++] = a[i2++];
    for (int i = l; i < r; i++) a[i] = c[i];
}

void quick_sort() {

}

void display(int a[100], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

int main(int argc, char *argv[]) {
    int n = 6;
    int a[100] = {6, 2, 9, 3, 7, 4};
    int b[100] = {5, 6, 2, 8, 1, 3};
    int c[100] = {9, 6, 2, 3, 1, 5};
    int d[100] = {4, 9, 7, 1, 5, 3};
    sort_min(a, n);
    display(a, n);
    sort_bubble(b, n);
    display(b, n);
    sort_normal(c, n);
    display(c, n);
    merge_sort(d, 0, n);
    display(d, n);
    return 0;
}
