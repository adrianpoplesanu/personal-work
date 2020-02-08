#include <Foundation/Foundation.h>

@interface Test : NSObject {
    @private
    int value;
}
@property (assign) int value2;
- (void) process : (int (^) (int, int)) action;
- (void) PrintValue;
@end

@implementation Test
- (void) process : (int (^) (int, int)) action {
    value = action(3, 4);
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
    [test process : action];
    [test PrintValue];
    int (^action2) (int, int) = ^(int base, int pew) {
        return base * pew;
    };
    [test process : action2];
    [test PrintValue];
    return 0;
}
