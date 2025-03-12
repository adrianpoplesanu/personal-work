// COMPILE:     gcc syntax117.c
// USAGE:       ./a.out test1 test2 test3
// BOOKMARK:    pg 103
// DESCRIPTION: cmd line attributes

#include <stdio.h>

int main(int argc, char *argv[]) {
    while (--argc > 0) {
        printf("%s%s", *++argv, (argc > 1) ? "," : "");
    }
    printf("\n");
    return 0;
}
