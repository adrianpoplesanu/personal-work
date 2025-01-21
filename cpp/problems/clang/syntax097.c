// COMPILE:	    gcc syntax097.c
// USAGE:	    ./a.out
// BOOKMARK:	pg 91
// DESCRIPTION:	pointer arithmetic, alloc and afree, these crude implemenations only work for stack-based allocation, dealocate ONLY last allocated element

#include <stdio.h>

#define ALLOCSIZE   10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage */
static char *allocp = allocbuf; /* next free position */

char* alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;  /* old p */
    }
    return 0;
}

void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) allocp = p;
}

int main(int argc, char *argv[]) {
    printf("[ LOG ] alloc and afree\n");

    char *pointer1 = alloc(5);
    char *pointer2 = alloc(10);
    char *pointer3 = alloc(20);

    printf("[ LOG ] %p\n", pointer1);
    printf("[ LOG ] %p\n", pointer2);
    printf("[ LOG ] %p\n", pointer3);

    printf("[ LOG ] %ld\n", pointer3 - pointer2);
    printf("[ LOG ] %ld\n", pointer2 - pointer1);

    afree(pointer3);
    afree(pointer2);
    afree(pointer1);
    return 0;
}
