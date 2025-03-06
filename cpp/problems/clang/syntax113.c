// COMPILE:     gcc syntax113.c
// USAGE:       ./a.out
// BOOKMARK:    pg 99
// DESCRIPTION: month day

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

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}

int main(int argc, char *argv[]) {
    printf("[ LOG ] %d\n", day_of_year(2025, 4, 16));
    int day, month;
    month_day(2025, 200, &month, &day);
    printf("[ LOG ] month = %d, day = %d\n", month, day);
    return 0;
}
