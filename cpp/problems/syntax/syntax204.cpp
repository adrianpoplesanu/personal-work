#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int c = 0;
    while(c != '.') {
        c = getchar();
        putchar(c);
    }
    return 0;
}
