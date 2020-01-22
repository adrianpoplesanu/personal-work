#include <Foundation/Foundation.h>

@interface Joke : NSObject {
    @private
    NSString *text;
}
@end

@implementation Joke

@end

int main(int argc, char *argv[]) {
    NSArray *jokes = [NSArray array];
    for (int i = 0; i < 5; i++) {
        jokes = [jokes arrayByAddingObject : [[Joke alloc] init]];
    }
    return 0;
}
