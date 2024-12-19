// COMPILE:	gcc syntax076.c
// USAGE:	./a.out
// BOOKMARK:	pg 67 ex 4-2
// DESCRIPTION:	atof with scientific notation

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

    if (s[i] == 'e') {
        int exponent;
        i++;
        if (s[i] == '-') {
            i++;
            for (exponent = 0; isdigit(s[i]); i++) {
                exponent = 10 * exponent + (s[i] - '0');
            }
            exponent = -exponent;
        } else if (s[i] == '+') {
            i++;
            for (exponent = 0; isdigit(s[i]); i++) {
                exponent = 10 * exponent + (s[i] - '0');
            }
        } else {
            for (exponent = 0; isdigit(s[i]); i++) {
                exponent = 10 * exponent + (s[i] - '0');
            }
        }
        printf("[ LOG ] exponent = %d\n", exponent);
        if (exponent > 0) {
            while(exponent-- > 0) val *= 10.0;
        } else {
            while(exponent++ < 0) val /= 10.0;
        }
    }

    return sign * val / power;
}

int main(int argc, char *argv[]) {
    printf("[ OUT ] %f\n", atof("12.34e-6"));
    printf("[ OUT ] %f\n", atof("912.56e5"));
    return 0;
}
