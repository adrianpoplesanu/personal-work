#include <Foundation/Foundation.h>

int indx_a = 0;

@interface Test : NSObject {
    @private
    int a;
}
- (int) GetA;
@end

@implementation Test
- (id) init {
    self = [super init];
    a = indx_a++;
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
    functie([[Test alloc] init]);
    functie([[Test alloc] init]);
    return 0;
}
