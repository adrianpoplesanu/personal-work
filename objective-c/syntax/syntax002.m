#import <Foundation/Foundation.h>

int main (int argc, const char * argv[]) {
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
   
   printf("buna dimineata!\n");
   [pool drain];
   return 0;
}
