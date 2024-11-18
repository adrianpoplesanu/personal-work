#include <stdio.h>

// COMPILE:	gcc syntax057.c
// USAGE:	./a.out
// BOOKMARK:	pg 57
// DESCRIPTION:	shell sort

void shell_sort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int a[] = {6, 3, 8, 2, 9, 1, 5, 4, 7};
    int n = 9;
    shell_sort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
