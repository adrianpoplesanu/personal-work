#import <Foundation/Foundation.h>

// class declaration
@interface SimpleClass : NSObject
- (void) PrintCommand;
@end

// class implementation
@implementation SimpleClass
- (void) PrintCommand {
    NSLog(@"printing command...");
}
@end

int main (int argc, const char * argv[]) { 
    NSLog (@"running...");
    // declaring and allocating an instance of the class
    SimpleClass *simpleClass = [[SimpleClass alloc] init];
    // calling method of class instance
    [simpleClass PrintCommand];
    return 0;
}
