#import <Foundation/Foundation.h>

// function declaration
int func();

int main() {
   // function call
   int i = func();
   printf("%i\n", i);
}

// function definition
int func() {
   return 11;
}
