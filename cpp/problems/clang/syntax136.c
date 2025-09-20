// COMPILE:     gcc syntax136.c
// USAGE:       ./a.out
// BOOKMARK:    pg 116
// DESCRIPTION: rect declaration

#include <stdio.h>
#include <math.h>

struct point {
    int x;
    int y;
};

struct rect {
    struct point p1;
    struct point p2;
};

double area(struct rect r);

int main(int argc, char *argv[]) {
    struct point p1 = {1, 2};
    struct point p2 = {6, 7};
    struct point p3 = {-4, -3};
    struct rect r1 = {p1, p2};
    struct rect r2 = {p1, p3};
    double dist1 = area(r1);
    double dist2 = area(r2);
    printf("area1: %f\n", dist1);
    printf("area2: %f\n", dist2);
    return 0;
}

double area(struct rect r) {
    double result = (double)(r.p1.x - r.p2.x) * (double)(r.p1.y - r.p2.y);
    return result > 0 ? result : -1 * result;
}

