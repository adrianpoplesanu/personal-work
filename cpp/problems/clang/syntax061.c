#include <stdio.h>

// COMPILE:	gcc syntax061.ad
// USAGE:	./a.out
// BOOKMARK:	pg 59 ex 3-5
// DESCRIPTION: int to base

void reverse(char s[], int n) {
    int i, j, c;
    for (i = 0, j = n - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itob(int n, char s[], int b) {
    int i, sign;
    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        int digit = n % 16;
        if (digit < 10) {
            s[i++] = n % 16 + '0';
        } else {
            switch(digit) {
                case 10:
                    s[i++] = 'a';
                break;
                case 11:
                    s[i++] = 'b';
                break;
                case 12:
                    s[i++] = 'c';
                break;
                case 13:
                    s[i++] = 'd';
                break;
                case 14:
                    s[i++] = 'e';
                break;
                case 15:
                    s[i++] = 'f';
                break;
            }
        }
    } while((n /= 16) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s, i);
}

int main(int argc, char *argv[]) {
    int n = 1529;
    char s[10];
    itob(n, s, 16);
    printf("[ out ] %s\n", s);
    return 0;
}
