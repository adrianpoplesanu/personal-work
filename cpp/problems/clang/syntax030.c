#include <stdio.h>

// COMPILATION:	gcc syntax030.c
// USAGE:	./a.out
// BOOKMARK:	pg 38
// DESCRIPTION:	testing string concatenation on multiple lines	

int main() {
    char *test = "aaa" "bbb";
    printf("%s\n", test);

    char *test2 = "aaa"
    "bbb"
    "ccc";

    printf("%s\n", test2);
    return 0;
}
