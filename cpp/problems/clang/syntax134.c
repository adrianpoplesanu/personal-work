// COMPILE:     gcc syntax134.c
// USAGE:       ./a.out
// BOOKMARK:    pg 114
// DESCRIPTION: struct point example

#include <stdio.h>

struct point {
    int x;
    int y;
};

int main(int argc, char *argv[]) {
    struct point p;
    printf("un-initialized: %d, %d\n", p.x, p.y);
    struct point p2 = {1, 2};
    printf("initialized: %d, %d\n", p2.x, p2.y);
    return 0;
}

