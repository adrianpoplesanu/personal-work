// COMPILE:     gcc syntax131.c
// USAGE:       ./a.out -nrf
// BOOKMARK:    pg n/a
// DESCRIPTION: print letters with ascii code

#include <stdio.h>

int main(int argc, char *argv[]) {
    for (char val = 'A'; val <= 'z'; val++) {
        printf("%c %d\n", val, val);
    }
    return 0;
}
