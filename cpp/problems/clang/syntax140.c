// COMPILE:     gcc syntax140.c
// USAGE:       ./a.out
// BOOKMARK:    pg 117
// DESCRIPTION: canonrect

#include <stdio.h>
#include <math.h>

#define		XMAX	640
#define		YMAX	480

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
    int x;
    int y;
};

struct rect {
    struct point p1;
    struct point p2;
};

double area(struct rect r);
struct point makepoint(int x, int y) {
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

struct point addpoint(struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

void test_addpoint() {
    struct point p1, p2;
    p1.x = 2;
    p1.y = 5;
    p2.x = 4;
    p2.y = 8;

    struct point p3 = addpoint(p1, p2);
    printf("%d %d\n", p3.x, p3.y);
}

int pt_in_rect(struct rect r, struct point p) {
    return p.x >= r.p1.x && p.x < r.p2.x && p.y >= r.p1.y && p.y < r.p2.y;
}

struct rect canonrect(struct rect r) {
    struct rect temp;
    temp.p1.x = min(r.p1.x, r.p2.x);
    temp.p1.y = min(r.p1.y, r.p2.y);
    temp.p2.x = max(r.p1.x, r.p2.x);
    temp.p2.y = max(r.p1.y, r.p2.y);

    return temp;
}

void test_canonrect() {
    struct point p1 = makepoint(2, 11), p2 = makepoint(7, 3);
    struct rect r;
    r.p1 = p1;
    r.p2 = p2;

    struct point p3 = makepoint(5, 4);
    printf("test_canonrect = %d\n", pt_in_rect(canonrect(r), p3));

    struct point p4 = makepoint(12, 12);
    printf("test_canonrect = %d\n", pt_in_rect(canonrect(r), p4));
}

int main(int argc, char *argv[]) {
    struct rect screen;
    struct point middle;

    screen.p1 = makepoint(0, 0);
    screen.p2 = makepoint(XMAX, YMAX);

    middle.x = (screen.p1.x + screen.p2.x) / 2;
    middle.y = (screen.p1.y + screen.p2.y) / 2;

    test_addpoint();
    test_canonrect();

    printf("middle x: %d y: %d\n", middle.x, middle.y);

    printf("middle in screen: %d\n", pt_in_rect(screen, middle));
    return 0;
}

double area(struct rect r) {
    double result = (double)(r.p1.x - r.p2.x) * (double)(r.p1.y - r.p2.y);
    return result > 0 ? result : -1 * result;
}

