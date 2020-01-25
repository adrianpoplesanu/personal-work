#import <Foundation/Foundation.h>
#import "powerplant.h"
#import "reactor.h"
#import "reactor.m"

@implementation PowerPlant
- (id) init {
    self = [super init];
    total_reactors = 1;
    for (int i = 0; i < total_reactors; i++) {
        reactor[i] = [[Reactor alloc] init];
    }
    return self;
}
- (void) LogName {
    NSLog(@"Name: %@", _name);
}
- (int) GetNumberOfReactors {
    return total_reactors;
}
@end
