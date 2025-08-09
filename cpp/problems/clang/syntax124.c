// COMPILE:     gcc syntax124.c
// USAGE:       ./a.out -xn pattern location
// BOOKMARK:    n/a
// DESCRIPTION: a better grep - TODO: implement this
// param:	-n : show line numbers
// param:	-x : show extended lines

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return 0;
}
