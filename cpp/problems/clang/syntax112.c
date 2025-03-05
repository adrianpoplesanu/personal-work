// COMPILE:     gcc syntax112.c
// USAGE:       ./a.out
// BOOKMARK:    pg 99
// DESCRIPTION: n-th day of the year

#include <stdio.h>

static unsigned short daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

int main(int argc, char *argv[]) {
    printf("[ LOG ] %d\n", day_of_year(2025, 4, 16));
    return 0;
}
