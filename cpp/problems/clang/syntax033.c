#include <stdio.h>

// COMPILE:	gcc syntax033.c
// USAGE:	./a.out
// BOOKMARK:	pg 40
// DESCRIPTION: leap year calculation

char isLeapYear(int year);

int main(int argc, char *argv[]) {
    isLeapYear(2024);
    return 0;
}

char isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
       printf("[ LOG ] %d is leap\n", year);
       return 1;
    } else {
       printf("[ LOG ] %d is NOT leap\n", year);
       return 0;
    }
}
