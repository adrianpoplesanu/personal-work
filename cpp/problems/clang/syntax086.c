#include <stdio.h>

void test(int *a) {
    *a = 7;
}

int main(int argc, char *argv[]) {
    int a = 5;
    printf("[ LOG ] %d\n", a);
    test(&a);
    printf("[ LOG ] %d\n", a);
    return 0;
}
