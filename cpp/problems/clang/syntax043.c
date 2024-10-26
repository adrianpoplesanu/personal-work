#include <stdio.h>

// COMPILE:	gcc syntax043.c
// USAGE:	./a.out
// BOOKMARK:	none
// DESCRIPTION:	max int using bitwise operators

void calculate_max() {
    int a = 1;
    int pow = 0;
    while (pow < 31) {
        a = a | (1 << pow);
        pow++;
    }
    printf("[ LOG ] max integer %d\n", a);
}

void calculate_min() { // this doesn't work
    int a = 1;
    int pow = 0;
    while (pow < 31) {
        a = a & (1 >> pow);
        pow++;
    }
    printf("[ LOG ] min integer %d\n", a);
}

int main(int argc, char *argv[]) {
    int a = 1 << 16;
    printf("[ LOG ] %d\n", a);

    int b = 1 << 31;
    printf("[ LOG ] %d\n", b);

    calculate_max();
    //calculate_min();
    return 0;
}
