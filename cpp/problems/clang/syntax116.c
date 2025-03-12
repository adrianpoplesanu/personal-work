// COMPILE:     gcc syntax113.c
// USAGE:       ./a.out test1 test2 test3
// BOOKMARK:    pg 103
// DESCRIPTION: cmd line attributes

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    for(i = 1; i < argc; i++) {
        printf("%s%s", argv[i], (i < argc - 1) ? "," : "");
    }
    printf("\n");
    return 0;
}
