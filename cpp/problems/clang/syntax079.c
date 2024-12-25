// COMPILE:	gcc syntax078.c
// USAGE:	./a.out
// BOOKMARK:	pg 71 ex 4-4
// DESCRIPTION:	4-4

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP	100
#define NUMBER	'0'
#define MAXVAL	100

#define BUFSIZE	100

int sp = 0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int);

int main(int argc, char *argv[]) {
    int type;
    double op2;
    char s[MAXOP];

    printf("CMD: q - quit | t - top | s - swap | d - duplicate | c - clear\n");

    while((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
		        push(atof(s));
            break;
            case '+':
                push(pop() + pop());
            break;
            case '*':
                push(pop() * pop());
            break;
            case '-':
                op2 = pop();
                push(pop() - op2);
            break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) push(pop() / op2);
                else printf("error: zero divisor\n");
            break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) push((int)pop() % (int)op2 * 1.0f);
                else printf("error: zero divisor\n");
            break;
            case 'q':
                return 0;
                break;
            case 't':
                if (sp > 0) {
                    printf("stack top: %f\n", val[sp - 1]);
                } else {
                    printf("stack top: empty\n");
                }
                break;
            case 's':
                if (sp > 1) {
                    float aux = val[sp - 1];
                    val[sp - 1] = val[sp - 2];
                    val[sp - 2] = aux;
                }
                break;
            case 'd':
                if (sp > 0) {
                    sp++;
                    val[sp - 1] = val[sp - 2];
                }
                break;
            case 'c':
                sp = 0;
                break;
            case '\n':
                printf("\t%.8g\n", pop());
            break;
            default:
                printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL) val[sp++] = f;
    else printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0) return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t') ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') return c;
    i = 0;
    if (c == '-') {
        s[++i] = c = getch();
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == EOF) {
            ungetch(c);
            return '-';
        }
    }
    if (isdigit(c))
        while(isdigit(s[++i] = c = getch())) ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch())) ;
    s[i] = '\0';
    if (c != EOF) ungetch(c);
    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}
