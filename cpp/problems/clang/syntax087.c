// COMPILE:	gcc syntax087.c
// USAGE:	./a.out
// BOOKMARK:	pg 79 ex 4-13
// DESCRIPTION:	recursive reverse

#include <stdio.h>

void reverse(char s[], int pos) {
   static int i = -1;
   if (s[pos] != '\0') {
       i++;
       reverse(s, pos + 1);
   }
   //printf("%d - %d\n", pos, i - pos);
   //printf("%c - %c\n", s[pos], s[i - pos]);
   if (pos < i - pos) {
       char tmp = s[i - pos];
       s[i - pos] = s[pos];
       s[pos] = tmp;
       if (pos == 0) i = -1; // resetarea valorii statice pentru urmatorul run
   }
}

int main(int argc, char *argv[]) {
    char s1[] = "buna dimineata!";
    reverse(s1, 0);
    printf("[ LOG ] %s\n", s1);

    char s2[] = "abcdefghijklmnopqrstuvxyz";
    reverse(s2, 0);
    printf("[ LOG ] %s\n", s2);
    return 0;
}
