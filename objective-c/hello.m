#import <Foundation/Foundation.h>

int main (int argc, const char * argv[]) {
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
   
   NSLog (@"Hello world!!!");
   printf("buna dimineata!\n");
   [pool drain];
   return 0;
}
