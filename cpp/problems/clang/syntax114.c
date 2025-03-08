// COMPILE:     gcc syntax114.c
// USAGE:       ./a.out
// BOOKMARK:    pg 101
// DESCRIPTION: month name

#include <stdio.h>

char* month_name(int n) {
    static char *name[] = {
        "Illegal", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(int argc, char *argv[]) {
    printf("[ LOG ] %s\n", month_name(4));
    return 0;
}
