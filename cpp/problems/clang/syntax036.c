#include <stdio.h>

// COMPILE:	gcc syntax036.c
// USAGE:	./a.out
// BOOKMARK:	pg 44
// DESCRIPTION:	pseudo-random generated integers

int rand();
void srand(unsigned int seed);

unsigned long int next = 1;

int main(int argc, char *argv[]) {
    int i = 0;
    while (i++ < 100) {
        printf("[ LOG ] %lu\n", next);
        next = rand();
    }
    return 0;
}

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}
