#include <Foundation/Foundation.h>

@interface Test : NSObject {
    @private
    int value;
}
@property (assign) int value2;
- (void) action : (int (^) (int, int)) _action;
- (void) PrintValue;
@end

@implementation Test
- (void) action : (int (^) (int, int)) _action {
    value = _action(3, 4);
    self.value2 = 5;
}
- (void) PrintValue {
    NSLog(@"%d", value);
    NSLog(@"%d", self.value2);
}
@end

int main(int argc, char *argv[]) {
    Test *test = [[Test alloc] init];
    int (^action) (int, int) = ^(int base, int pew) {
        return base + pew;
    };
    [test action : action];
    [test PrintValue];
    return 0;
}
