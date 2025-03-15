// COMPILE:     gcc syntax113.c
// USAGE:       ./a.out
// BOOKMARK:    pg 102 ex 5-9
// DESCRIPTION: day_of_year and month_day using pointers

#include <stdio.h>

static unsigned short daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int *year, int *month, int *day) {
    int i, leap;
    leap = *year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0;
    for (i = 1; i < *month; i++) {
        *day += daytab[leap][i];
    }
    return *day;
}

void month_day(int *year, int *yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = *year % 4 == 0 && *year % 100 != 0 || *year % 400 == 0;
    for (i = 1; *yearday > daytab[leap][i]; i++) {
        *yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = *yearday;
}

int main(int argc, char *argv[]) {
    int year = 2025;
    int month = 4;
    int day = 16;
    printf("[ LOG ] %d\n", day_of_year(&year, &month, &day));
    int num_days = 200;
    month_day(&year, &num_days, &month, &day);
    printf("[ LOG ] month = %d, day = %d\n", month, day);
    return 0;
}
