#include <Foundation/Foundation.h>

@interface Test : NSObject {
    @private
    int a;
}
- (int) GetA;
@end

@implementation Test
- (id) init {
    self = [super init];
    a = 5;
    return self;
}
- (int) GetA {
    return a;
}
@end

void functie(Test *test) {
    int a = [test GetA];
    NSLog(@"in functie valoare atributului clasei este: %d", a);
}

int main(int argc, char *argv[]) {
    Test *test = [[Test alloc] init];
    functie(test);
    return 0;
}
