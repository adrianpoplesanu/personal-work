// DESCRIPTION:	using getline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
  char *string = NULL;
  size_t size = 0;
  ssize_t chars_read;

  // read a long string with getline

  puts("enter a string:");

  chars_read = getline(&string, &size, stdin);
  printf("getline returned %ld\n", chars_read);
  printf("read %s\n", string);
}
