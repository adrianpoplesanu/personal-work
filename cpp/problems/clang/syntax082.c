// COMPILE:	gcc syntax082.c
// USAGE:	./a.out
// BOOKMARK:	pg 79
// DESCRIPTION: quick sort

#include <stdio.h>

void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right) return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left]) swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(int v[], int i, int j) {
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main(int argc, char *argv[]) {
    int a[] = {6, 2, 8, 3, 9, 1, 5, 7, 4};
    qsort(a, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
