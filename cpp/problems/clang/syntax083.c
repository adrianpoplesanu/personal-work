// COMPILE:	gcc syntax083.c
// USAGE:	./a.out
// BOOKMARK:	pg 79 ex 4-12
// DESCRIPTION: recursive itoa

#include<stdio.h>

int get_number_size(int n) {
    int total = 1;
    if (n < 0) {
        total++;
        n = -n;
    }
    while ((n / 10) > 0) {
        n = n / 10;
        total++;
    }
    return total;
}

void my_itoa(char s[], int n, int i, int max_size) {
    if (n < 0) {
        s[i] = '-';
        n = -n;
        my_itoa(s, n, i + 1, max_size);
    } else {
        char digit =  n % 10 + '0';
        if (n / 10) {
            my_itoa(s, n / 10, i + 1, max_size);
        } else { 
            s[i + 1] = '\0';
        }
        s[max_size - i] = digit;
    }
}

int main(int argc, char *argv[]) {
    char s[100];
    int n = -123456;
    my_itoa(s, n, 0, get_number_size(n));
    printf("%s\n", s);
    return 0;
}
