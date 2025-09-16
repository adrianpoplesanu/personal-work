// COMPILE:     gcc syntax135.c
// USAGE:       ./a.out
// BOOKMARK:    pg 114
// DESCRIPTION: distance calculation

#include <stdio.h>
#include <math.h>

struct point {
    int x;
    int y;
};

int main(int argc, char *argv[]) {
    struct point p = {1, 2};
    double dist;
    dist = sqrt((double)p.x * p.x + (double)p.y * p.y);
    printf("point: %d, %d\n", p.x, p.y);
    printf("distance: %f\n", dist);
    return 0;
}

