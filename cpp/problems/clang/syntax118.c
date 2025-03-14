// COMPILE:     gcc syntax118.c
// USAGE:       ./a.out test1 test2 test3
// BOOKMARK:    pg 103
// DESCRIPTION: cmd line attributes

#include <stdio.h>

int main(int argc, char *argv[]) {
    while(--argc > 0) {
        printf((argc > 1) ? "%s," : "%s", *++argv);
    }
    printf("\n");
    return 0;
}
