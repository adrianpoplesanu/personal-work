#include <Foundation/Foundation.h>

@interface Joke : NSObject {
    @private
    NSString *text;
}
@end

@implementation Joke

@end

int main(int argc, char *argv[]) {
    NSMutableArray *jokes = [NSMutableArray array];
    for (int i = 0; i < 5; i++) {
        [jokes addObject : [[Joke alloc] init]];
    }
    NSArray *arrayOfJokes = [NSArray arrayWithArray : jokes];
    return 0;
}
