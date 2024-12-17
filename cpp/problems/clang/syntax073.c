// COMPILE:	gcc syntax073.c
// USAGE:	./a.out
// BOOKMARK:	pg 65
// DESCRIPTION:	my atof

#include <stdio.h>
#include <ctype.h>

double atof(char s[]) {
    double val, power;
    int i, sign;

    for(i = 0; isspace(s[i]); i++)
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

int main(int argc, char *argv[]) {
    printf("%f\n", atof("12.34"));
    printf("%f\n", atof("912.56"));
    return 0;
}
