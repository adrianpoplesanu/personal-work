// COMPILE:	    gcc syntax096.c
// USAGE:	    ./a.out
// BOOKMARK:	pg 90
// DESCRIPTION:	testing a few pointer expressions

#include <stdio.h>

void change_value(int *a, int value) {
    *a = value;
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) { 
        printf("[ OUT ] %d\n", a[i]);
    }
}

int main(int argc, char *argv[]) {
    printf("[ LOG ] pointer tests\n");
    int a[] = {1, 2, 3, 4};
    change_value(&a[2], 77);
    print_array(a, 4);

    change_value(a + 1, 44);
    print_array(a, 4);
    return 0;
}
